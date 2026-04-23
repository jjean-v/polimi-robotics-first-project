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

            timer_ = this->create_wall_timer(
                500ms, std::bind(&TfError::on_timer, this)
            );
        }
    private:
        void on_timer() {
            geometry_msgs::msg::TransformStamped t;

            try {
                t = tf_buffer_->lookupTransform("base_link", "base_link2", tf2::TimePointZero);
            } catch (const tf2::TransformException & ex) {
                RCLCPP_WARN(this->get_logger(), "Lookup failed: %s", ex.what());
                return;
            }

            const double dx = t.transform.translation.x;
            const double dy = t.transform.translation.y;
            const double dz = t.transform.translation.z;
            const double distance = std::sqrt(dx * dx + dy * dy + dz * dz);
            RCLCPP_INFO(this->get_logger(), "Distance between base_link and base_link2: %.3f m", distance);


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