#include <chrono>
#include <cmath>
#include <functional>
#include <memory>

#include "message_filters/subscriber.hpp"
#include "message_filters/sync_policies/approximate_time.hpp"
#include "message_filters/synchronizer.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/fluid_pressure.hpp"
#include "sensor_msgs/msg/temperature.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;

class ApproximateSyncNode : public rclcpp::Node
{
public:
  using ApproxPolicy = message_filters::sync_policies::ApproximateTime<
    sensor_msgs::msg::Temperature,
    sensor_msgs::msg::FluidPressure>;

  ApproximateSyncNode()
  : Node("approximate_sync_node"), match_count_(0)
  {
    int queue_size = this->declare_parameter<int>("queue_size", 10);
    double age_penalty = this->declare_parameter<double>("age_penalty", 0.50);

    rclcpp::QoS qos(10);

    temp_sub_.subscribe(this, "temp", qos.get_rmw_qos_profile());
    pressure_sub_.subscribe(this, "pressure", qos.get_rmw_qos_profile());

    sync_ = std::make_shared<message_filters::Synchronizer<ApproxPolicy>>(
      ApproxPolicy(queue_size), temp_sub_, pressure_sub_);

    sync_->setAgePenalty(age_penalty);
    sync_->registerCallback(std::bind(&ApproximateSyncNode::sync_callback, this, _1, _2));

    status_timer_ = this->create_wall_timer(
      3s, std::bind(&ApproximateSyncNode::status_callback, this));

    RCLCPP_INFO(
      this->get_logger(),
      "Approximate synchronizer ready (queue_size=%d, age_penalty=%.2f)",
      queue_size, age_penalty);
  }

private:
  void sync_callback(
    const sensor_msgs::msg::Temperature::ConstSharedPtr & temp,
    const sensor_msgs::msg::FluidPressure::ConstSharedPtr & pressure)
  {
    ++match_count_;

    rclcpp::Duration dt = rclcpp::Time(temp->header.stamp) - rclcpp::Time(pressure->header.stamp);
    double dt_ms = std::abs(dt.seconds() * 1000.0);

    RCLCPP_INFO(
      this->get_logger(),
      "APPROX  MATCH #%zu | dt=%.1f ms | temp=%u.%09u pressure=%u.%09u",
      match_count_,
      dt_ms,
      temp->header.stamp.sec,
      temp->header.stamp.nanosec,
      pressure->header.stamp.sec,
      pressure->header.stamp.nanosec);
  }

  void status_callback()
  {
    RCLCPP_INFO(
      this->get_logger(),
      "APPROX  status: matches so far = %zu",
      match_count_);
  }

  message_filters::Subscriber<sensor_msgs::msg::Temperature> temp_sub_;
  message_filters::Subscriber<sensor_msgs::msg::FluidPressure> pressure_sub_;

  std::shared_ptr<message_filters::Synchronizer<ApproxPolicy>> sync_;

  rclcpp::TimerBase::SharedPtr status_timer_;
  size_t match_count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ApproximateSyncNode>());
  rclcpp::shutdown();
  return 0;
}
