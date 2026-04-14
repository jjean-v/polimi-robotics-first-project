#include <chrono>
#include <functional>
#include <memory>

#include "message_filters/subscriber.h"
#include "message_filters/time_synchronizer.h"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/fluid_pressure.hpp"
#include "sensor_msgs/msg/temperature.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;

class ExactSyncNode : public rclcpp::Node
{
public:
  ExactSyncNode()
  : Node("exact_sync_node"), match_count_(0)
  {
    int queue_size = this->declare_parameter<int>("queue_size", 10);
    rclcpp::QoS qos(10);

    temp_sub_.subscribe(this, "temp", qos.get_rmw_qos_profile());
    pressure_sub_.subscribe(this, "pressure", qos.get_rmw_qos_profile());

    sync_ = std::make_shared<
      message_filters::TimeSynchronizer<
        sensor_msgs::msg::Temperature,
        sensor_msgs::msg::FluidPressure>>(temp_sub_, pressure_sub_, queue_size);

    sync_->registerCallback(std::bind(&ExactSyncNode::sync_callback, this, _1, _2));

    status_timer_ = this->create_wall_timer(
      3s, std::bind(&ExactSyncNode::status_callback, this));

    RCLCPP_INFO(this->get_logger(), "Exact synchronizer ready");
  }

private:
  void sync_callback(
    const sensor_msgs::msg::Temperature::ConstSharedPtr & temp,
    const sensor_msgs::msg::FluidPressure::ConstSharedPtr & pressure)
  {
    ++match_count_;

    RCLCPP_INFO(
      this->get_logger(),
      "EXACT   MATCH #%zu | temp=%u.%09u pressure=%u.%09u",
      match_count_,
      temp->header.stamp.sec,
      temp->header.stamp.nanosec,
      pressure->header.stamp.sec,
      pressure->header.stamp.nanosec);
  }

  void status_callback()
  {
    RCLCPP_INFO(
      this->get_logger(),
      "EXACT   status: matches so far = %zu",
      match_count_);
  }

  message_filters::Subscriber<sensor_msgs::msg::Temperature> temp_sub_;
  message_filters::Subscriber<sensor_msgs::msg::FluidPressure> pressure_sub_;

  std::shared_ptr<
    message_filters::TimeSynchronizer<
      sensor_msgs::msg::Temperature,
      sensor_msgs::msg::FluidPressure>> sync_;

  rclcpp::TimerBase::SharedPtr status_timer_;
  size_t match_count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ExactSyncNode>());
  rclcpp::shutdown();
  return 0;
}
