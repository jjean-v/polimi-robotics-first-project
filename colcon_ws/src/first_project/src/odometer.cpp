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

// using namespace std::chrono_literals;


#define COMPUTED_GEAR_RATIO 0.04969097624
#define WHEEL_RADIUS 0.225
#define LENGTH_BETWEEN_WHEELS 0.700

// Placeholders for std::bind, so we can write _1 and _2 
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

            // We declare the parametersx, y and theta with default values of 0.0, so that we can set them to different values if needed
            // Useful for the not cented bag files 
            this->declare_parameter<double>("x", 0.0);
            this->declare_parameter<double>("y", 0.0);
            this->declare_parameter<double>("theta", 0.0);
            x_ = this->get_parameter("x").as_double();
            y_ = this->get_parameter("y").as_double();
            theta_ = this->get_parameter("theta").as_double();

        }

    private:
        
        double x_;
        double y_;
        double theta_;
        
        void topic_callback(const bunker_msgs::msg::BunkerStatus::SharedPtr msg) {

            
            const rclcpp::Time current_time(msg->header.stamp);

            if (last_time_.nanoseconds() == 0) {
                last_time_ = current_time;
            }

            const double dt = std::max(0.0, (current_time - last_time_).seconds());

            const double rpm_right = static_cast<double>(msg->actuator_states[0].rpm);
            const double rpm_left = static_cast<double>(msg->actuator_states[1].rpm);
            
            RCLCPP_INFO(this->get_logger(), "\nReceiving:\n RPM left: '%f'\n RPM right: '%f'\n Battery voltage: '%f'", rpm_left, rpm_right, msg->battery_voltage);

            tf2::Quaternion q;
            q.setRPY(0.0, 0.0, theta_);

            publish_odometry(current_time, dt, rpm_left, rpm_right, q);
            publish_transform(current_time, q);

            last_time_ = current_time;

        }

        void publish_odometry(
            const rclcpp::Time & stamp,
            const double dt,
            const double rpm_left,
            const double rpm_right,
            const tf2::Quaternion & q
            ) {
                nav_msgs::msg::Odometry odom_msg;
                odom_msg.header.stamp = stamp;
                odom_msg.header.frame_id = "odom";
                odom_msg.child_frame_id = "base_link2";


                const double linear_velocity = ((rpm_right + rpm_left) * WHEEL_RADIUS * COMPUTED_GEAR_RATIO * 2.0 * M_PI / 60.0)/2.0;
                const double angular_velocity = ((rpm_right - rpm_left) * WHEEL_RADIUS * COMPUTED_GEAR_RATIO * 2.0 * M_PI / 60.0)/ LENGTH_BETWEEN_WHEELS;
                

                //Euler
                x_ += linear_velocity * std::cos(theta_) * dt;
                y_ += linear_velocity * std::sin(theta_) * dt;
                theta_ += angular_velocity * dt;

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
                // For debugging purposes
                // RCLCPP_INFO(this->get_logger(), "\nPublishing:\n Odometer message:\n linear velocity:'%f'\n angular vel:'%f'\n", linear_velocity, angular_velocity);

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
      
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Odometer>());
    rclcpp::shutdown();
    return 0;
}
