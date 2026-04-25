#include <chrono>
#include <cmath>
#include <functional>
#include <memory>
#include <string>

// standard ros2 include
#include "rclcpp/rclcpp.hpp"

// tf includes
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/exceptions.h"
#include "tf2/LinearMath/Matrix3x3.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"

// message includes
#include "first_project/msg/tf_error_msg.hpp"

// for easier writing, so we can write 500ms 
// instead of std::chrono::milliseconds(500)
using namespace std::chrono_literals;

class TfError : public rclcpp::Node {
    public:
    
        TfError(): Node("tf_error") {

            tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
            tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
            publisher_ = this->create_publisher<first_project::msg::TfErrorMsg>("/tf_error_msg", 10);
            start_time_ = this->get_clock()->now();

            // Arbitrary timer period
            timer_ = this->create_wall_timer(
                250ms, std::bind(&TfError::on_timer, this)
            );

        }
    private:

        double distance_travelled_ = 0.0;
        double prev_x = -1.0;
        double prev_y = -1.0;
        rclcpp::Time start_time_;
        
        void on_timer() {
            geometry_msgs::msg::TransformStamped t;
            first_project::msg::TfErrorMsg tf_error_msg;
            double distance_error = 0.0;

            // Get the transform between base_link and base_link2
            try {
                t = tf_buffer_->lookupTransform("base_link", "base_link2", tf2::TimePointZero);
                double dx = t.transform.translation.x;
                double dy = t.transform.translation.y;
                distance_error = std::sqrt(dx * dx + dy * dy);
            } catch (const tf2::TransformException & ex) {
                RCLCPP_WARN(this->get_logger(), "Lookup base_link->base_link2 failed: %s", ex.what());
                distance_error = 0.0;
            }

            // Get the transform between odom and base_link
            try {
                t = tf_buffer_->lookupTransform("odom", "base_link", tf2::TimePointZero);
                double dx = t.transform.translation.x;
                double dy = t.transform.translation.y;

                // Just use to initialize the previous position at the first iteration
                if (prev_x != 0.0 || prev_y != 0.0) {
                    const double distance = std::sqrt(std::pow(dx - prev_x, 2) + std::pow(dy - prev_y, 2));
                    distance_travelled_ += distance;
                }

                prev_x = dx;
                prev_y = dy;
            } catch (const tf2::TransformException & ex) {
                RCLCPP_WARN(this->get_logger(), "Lookup odom->base_link failed: %s", ex.what());
            }

            tf_error_msg.header.stamp = this->get_clock()->now();
            tf_error_msg.header.frame_id = "odom";
            tf_error_msg.tf_error = distance_error;
            tf_error_msg.travelled_distance = distance_travelled_;
            rclcpp::Time current_time = this->get_clock()->now();
            tf_error_msg.time_from_start = (current_time - start_time_).seconds();

            RCLCPP_INFO(this->get_logger(), "\ntf_error: %.4f m\ndistance travelled: %.3f m\ntime from start: %d s", distance_error, distance_travelled_, tf_error_msg.time_from_start);
            publisher_->publish(tf_error_msg)   ;
        }

        rclcpp::TimerBase::SharedPtr timer_;
        std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
        std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
        rclcpp::Publisher<first_project::msg::TfErrorMsg>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TfError>());
  rclcpp::shutdown();
  return 0;
}