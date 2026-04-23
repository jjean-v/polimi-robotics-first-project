#include <chrono>
#include <cmath>
#include <functional>
#include <memory>
#include <string>

// standard ros2 include
#include "rclcpp/rclcpp.hpp"

// tf includes
#include "tf2/LinearMath/Quaternion.h"

// custom message includes
#include "nav_msgs/msg/odometry.hpp"
#include "bunker_msgs/msg/bunker_status.hpp"

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

        }

    private:
        
        void topic_callback(const bunker_msgs::msg::BunkerStatus::SharedPtr msg) const {
            nav_msgs::msg::Odometry odom_msg;
            // odom_msg.header.stamp = this->get_clock()->now();
            odom_msg.header.frame_id = "odom";
            odom_msg.child_frame_id = "base_link2";

            // For demonstration, we use set position and orientation values
            odom_msg.pose.pose.position.x = 1.0;
            odom_msg.pose.pose.position.y = 1.0;
            odom_msg.pose.pose.position.z = 1.0;

            tf2::Quaternion q;
            q.setRPY(0.0, 0.0, 0.0);

            odom_msg.pose.pose.orientation.x = q.x();
            odom_msg.pose.pose.orientation.y = q.y();
            odom_msg.pose.pose.orientation.z = q.z();
            odom_msg.pose.pose.orientation.w = q.w();

            RCLCPP_INFO(this->get_logger(), "\nReceiving:\n Linear velocity: '%f'\n Angular velocity: '%f'\n Battery voltage: '%f'", msg->linear_velocity, msg->angular_velocity, msg->battery_voltage);
            RCLCPP_INFO(this->get_logger(), "\nPublishing:\n Odometer message:\n position x:'%f'\n position y:'%f'\n position z:'%f'", odom_msg.pose.pose.position.x, odom_msg.pose.pose.position.y, odom_msg.pose.pose.position.z);

            publisher_->publish(odom_msg);

        }

        rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr publisher_;
        rclcpp::Subscription<bunker_msgs::msg::BunkerStatus>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Odometer>());
  rclcpp::shutdown();
  return 0;
}
