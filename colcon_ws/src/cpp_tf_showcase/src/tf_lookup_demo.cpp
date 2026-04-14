#include <chrono>
#include <functional>
#include <memory>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/exceptions.h"
#include "tf2/LinearMath/Matrix3x3.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"

using namespace std::chrono_literals;

class TfLookupDemo : public rclcpp::Node
{
public:
  TfLookupDemo()
  : Node("tf_lookup_demo")
  {
    tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
    tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

    timer_ = this->create_wall_timer(
      500ms, std::bind(&TfLookupDemo::on_timer, this));
  }

private:
  void on_timer()
  {
    geometry_msgs::msg::TransformStamped t;

    try {
      t = tf_buffer_->lookupTransform("world", "laser", tf2::TimePointZero);
    } catch (const tf2::TransformException & ex) {
      RCLCPP_WARN(this->get_logger(), "Lookup failed: %s", ex.what());
      return;
    }

    const auto & r = t.transform.rotation;
    tf2::Quaternion q(r.x, r.y, r.z, r.w);

    double roll, pitch, yaw;
    tf2::Matrix3x3(q).getRPY(roll, pitch, yaw);

    RCLCPP_INFO(
      this->get_logger(),
      "laser in world -> x: %.2f  y: %.2f  z: %.2f  yaw: %.2f rad",
      t.transform.translation.x,
      t.transform.translation.y,
      t.transform.translation.z,
      yaw);
  }

  rclcpp::TimerBase::SharedPtr timer_;
  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TfLookupDemo>());
  rclcpp::shutdown();
  return 0;
}
