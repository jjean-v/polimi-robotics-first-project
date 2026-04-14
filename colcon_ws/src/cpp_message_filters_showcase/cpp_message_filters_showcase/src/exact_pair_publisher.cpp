#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/fluid_pressure.hpp"
#include "sensor_msgs/msg/temperature.hpp"

using namespace std::chrono_literals;

class ExactPairPublisher : public rclcpp::Node
{
public:
  ExactPairPublisher()
  : Node("exact_pair_publisher"), count_(0)
  {
    rclcpp::QoS qos(10);

    temp_pub_ = this->create_publisher<sensor_msgs::msg::Temperature>("temp", qos);
    pressure_pub_ = this->create_publisher<sensor_msgs::msg::FluidPressure>("pressure", qos);

    timer_ = this->create_wall_timer(
      1s, std::bind(&ExactPairPublisher::publish_pair, this));

    RCLCPP_INFO(this->get_logger(), "Publishing exact timestamp pairs");
  }

private:
  void publish_pair()
  {
    auto now = this->get_clock()->now();

    sensor_msgs::msg::Temperature temp;
    temp.header.stamp = now;
    temp.header.frame_id = "demo_frame";
    temp.temperature = 25.0 + 0.2 * static_cast<double>(count_);
    temp.variance = 0.01;

    sensor_msgs::msg::FluidPressure pressure;
    pressure.header.stamp = now;
    pressure.header.frame_id = "demo_frame";
    pressure.fluid_pressure = 1013.25 + static_cast<double>(count_);
    pressure.variance = 0.5;

    temp_pub_->publish(temp);
    pressure_pub_->publish(pressure);

    RCLCPP_INFO(
      this->get_logger(),
      "PAIR    stamp=%u.%09u temp=%.2f pressure=%.2f",
      temp.header.stamp.sec,
      temp.header.stamp.nanosec,
      temp.temperature,
      pressure.fluid_pressure);

    ++count_;
  }

  rclcpp::Publisher<sensor_msgs::msg::Temperature>::SharedPtr temp_pub_;
  rclcpp::Publisher<sensor_msgs::msg::FluidPressure>::SharedPtr pressure_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ExactPairPublisher>());
  rclcpp::shutdown();
  return 0;
}
