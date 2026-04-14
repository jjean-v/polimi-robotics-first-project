#include <memory>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/static_transform_broadcaster.h"

class SensorStaticTfBroadcaster : public rclcpp::Node
{
public:
  SensorStaticTfBroadcaster()
  : Node("sensor_static_tf_broadcaster")
  {
    tf_static_broadcaster_ =
      std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);

    publish_static_transform();
  }

private:
  void publish_static_transform()
  {
    geometry_msgs::msg::TransformStamped t;

    t.header.stamp = this->get_clock()->now();
    t.header.frame_id = "turtle1";
    t.child_frame_id = "laser";

    t.transform.translation.x = 0.30;
    t.transform.translation.y = 0.00;
    t.transform.translation.z = 0.10;

    tf2::Quaternion q;
    q.setRPY(0.0, 0.0, 0.0);

    t.transform.rotation.x = q.x();
    t.transform.rotation.y = q.y();
    t.transform.rotation.z = q.z();
    t.transform.rotation.w = q.w();

    tf_static_broadcaster_->sendTransform(t);

    RCLCPP_INFO(
      this->get_logger(),
      "Published static transform turtle1 -> laser");
  }

  std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_static_broadcaster_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SensorStaticTfBroadcaster>());
  rclcpp::shutdown();
  return 0;
}
