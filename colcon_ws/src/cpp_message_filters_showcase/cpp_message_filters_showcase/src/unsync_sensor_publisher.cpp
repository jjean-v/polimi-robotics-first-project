#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/fluid_pressure.hpp"
#include "sensor_msgs/msg/temperature.hpp"

using namespace std::chrono_literals;

class UnsyncSensorPublisher : public rclcpp::Node
{
public:
  UnsyncSensorPublisher()
  : Node("unsync_sensor_publisher"), temp_count_(0), pressure_count_(0)
  {
    rclcpp::QoS qos(10);

    temp_pub_ = this->create_publisher<sensor_msgs::msg::Temperature>("temp", qos);
    pressure_pub_ = this->create_publisher<sensor_msgs::msg::FluidPressure>("pressure", qos);

    temp_timer_ = this->create_wall_timer(
      500ms, std::bind(&UnsyncSensorPublisher::publish_temperature, this));

    pressure_timer_ = this->create_wall_timer(
      550ms, std::bind(&UnsyncSensorPublisher::publish_pressure, this));

    RCLCPP_INFO(this->get_logger(), "Publishing unsynchronized temp and pressure topics");
  }

private:
  void publish_temperature()
  {
    sensor_msgs::msg::Temperature msg;
    auto now = this->get_clock()->now();

    msg.header.stamp = now;
    msg.header.frame_id = "demo_frame";
    msg.temperature = 20.0 + 0.1 * static_cast<double>(temp_count_);
    msg.variance = 0.01;

    temp_pub_->publish(msg);

    RCLCPP_INFO(
      this->get_logger(),
      "TEMP    stamp=%u.%09u value=%.2f",
      msg.header.stamp.sec,
      msg.header.stamp.nanosec,
      msg.temperature);

    ++temp_count_;
  }

  void publish_pressure()
  {
    sensor_msgs::msg::FluidPressure msg;
    auto now = this->get_clock()->now();

    msg.header.stamp = now;
    msg.header.frame_id = "demo_frame";
    msg.fluid_pressure = 1000.0 + static_cast<double>(pressure_count_);
    msg.variance = 0.5;

    pressure_pub_->publish(msg);

    RCLCPP_INFO(
      this->get_logger(),
      "PRESS   stamp=%u.%09u value=%.2f",
      msg.header.stamp.sec,
      msg.header.stamp.nanosec,
      msg.fluid_pressure);

    ++pressure_count_;
  }

  rclcpp::Publisher<sensor_msgs::msg::Temperature>::SharedPtr temp_pub_;
  rclcpp::Publisher<sensor_msgs::msg::FluidPressure>::SharedPtr pressure_pub_;

  rclcpp::TimerBase::SharedPtr temp_timer_;
  rclcpp::TimerBase::SharedPtr pressure_timer_;

  size_t temp_count_;
  size_t pressure_count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<UnsyncSensorPublisher>());
  rclcpp::shutdown();
  return 0;
}
