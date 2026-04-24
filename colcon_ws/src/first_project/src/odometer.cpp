#include <chrono>
#include <cmath>
#include <functional>
#include <memory>
#include <string>

// standard ros2 include
#include "rclcpp/rclcpp.hpp"

// tf includes
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_ros/transform_broadcaster.h"

// message includes
#include "nav_msgs/msg/odometry.hpp"
#include "bunker_msgs/msg/bunker_status.hpp"

// service includes
#include "first_project/srv/reset.hpp"

// for easier writing, so we can write 500ms 
// instead of std::chrono::milliseconds(500)
using namespace std::chrono_literals;

// Placeholders for std::bind, so we can write _1 and _2 
// instead of std::placeholders::_1
using std::placeholders::_1;
using std::placeholders::_2;

class Odometer : public rclcpp::Node {
    public:

        Odometer(): Node("odometer") {

            publisher_ = this->create_publisher<nav_msgs::msg::Odometry>("/project_odom", 10);
            subscription_ = this->create_subscription<bunker_msgs::msg::BunkerStatus>("/bunker_status", 10, std::bind(&Odometer::topic_callback, this, _1));

            reset_service_ = this->create_service<first_project::srv::Reset>(
                "reset",
                std::bind(&Odometer::handle_reset_request, this, _1, _2)
            );

            tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

            last_time_ = rclcpp::Time(0, 0, RCL_ROS_TIME);
        }

    private:
        
        void topic_callback(const bunker_msgs::msg::BunkerStatus::SharedPtr msg) {

            
            const rclcpp::Time current_time(msg->header.stamp);

            if (last_time_.nanoseconds() == 0) {
                last_time_ = current_time;
            }

            const double dt = std::max(0.0, (current_time - last_time_).seconds());

            const double linear_velocity = static_cast<double>(msg->linear_velocity);
            const double angular_velocity = static_cast<double>(msg->angular_velocity);
            
            RCLCPP_INFO(this->get_logger(), "\nReceiving:\n Linear velocity: '%f'\n Angular velocity: '%f'\n Battery voltage: '%f'", linear_velocity, angular_velocity, msg->battery_voltage);
            
            // Euler
            x_ += linear_velocity * std::cos(theta_) * dt;
            y_ += linear_velocity * std::sin(theta_) * dt;
            theta_ += angular_velocity * dt;

            // RK2
            // x_ += linear_velocity * std::cos(theta_ + angular_velocity * dt / 2) * dt;
            // y_ += linear_velocity * std::sin(theta_ + angular_velocity * dt / 2) * dt;
            // theta_ += angular_velocity * dt;

            // Exact
            // theta_ += angular_velocity * dt;
            // x_ += linear_velocity / angular_velocity * (std::sin(theta_) - sin_prev);
            // y_ -= linear_velocity / angular_velocity * (std::cos(theta_) - cos_prev);
            // const double sin_prev = std::sin(theta_);
            // const double cos_prev = std::cos(theta_);

            tf2::Quaternion q;
            q.setRPY(0.0, 0.0, theta_);

            publish_odometry(current_time, linear_velocity, angular_velocity, q);
            publish_transform(current_time, q);

            last_time_ = current_time;

        }

        void publish_odometry(
            const rclcpp::Time & stamp,
            const double linear_velocity,
            const double angular_velocity,
            const tf2::Quaternion & q
            ) {
                nav_msgs::msg::Odometry odom_msg;
                odom_msg.header.stamp = stamp;
                odom_msg.header.frame_id = "odom";
                odom_msg.child_frame_id = "base_link2";

                odom_msg.pose.pose.position.x = x_;
                odom_msg.pose.pose.position.y = y_;
                odom_msg.pose.pose.position.z = 0.0;
            
                odom_msg.pose.pose.orientation.x = q.x();
                odom_msg.pose.pose.orientation.y = q.y();
                odom_msg.pose.pose.orientation.z = q.z();
                odom_msg.pose.pose.orientation.w = q.w();

                odom_msg.twist.twist.linear.x = linear_velocity;
                odom_msg.twist.twist.angular.z = angular_velocity;

                RCLCPP_INFO(this->get_logger(), "\nPublishing:\n Odometer message:\n position x:'%f'\n position y:'%f'\n angle theta:'%f'", x_, y_, theta_);

                publisher_->publish(odom_msg);
        }

        void publish_transform(
            const rclcpp::Time & stamp,
            const tf2::Quaternion & q
            ) {
                geometry_msgs::msg::TransformStamped t;

                t.header.stamp = stamp;
                t.header.frame_id = "odom";
                t.child_frame_id = "base_link2";

                t.transform.translation.x = x_;
                t.transform.translation.y = y_;
                t.transform.translation.z = 0.0;

                t.transform.rotation.x = q.x();
                t.transform.rotation.y = q.y();
                t.transform.rotation.z = q.z();
                t.transform.rotation.w = q.w();

                tf_broadcaster_->sendTransform(t);
        }

        void handle_reset_request(
            const std::shared_ptr<first_project::srv::Reset::Request> /*request*/,
            std::shared_ptr<first_project::srv::Reset::Response> /*response*/) {
                RCLCPP_INFO(this->get_logger(), "Reset request received. Resetting odometry.");
                x_ = 0.0;
                y_ = 0.0;
                theta_ = 0.0;
        }

        rclcpp::Subscription<bunker_msgs::msg::BunkerStatus>::SharedPtr subscription_;
        rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr publisher_;
        std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
        rclcpp::Service<first_project::srv::Reset>::SharedPtr reset_service_;
        rclcpp::Time last_time_;
        double x_ = 0.0;
        double y_ = 0.0;
        double theta_ = 0.0;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Odometer>());
  rclcpp::shutdown();
  return 0;
}
