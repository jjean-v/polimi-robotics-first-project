#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "custom_msg_demo/msg/robot_status.hpp"

using namespace std::chrono_literals;

class StatusPublisher : public rclcpp::Node
{
public:
  StatusPublisher()
  : Node("status_publisher"), counter_(0)
  {
    publisher_ = this->create_publisher<custom_msg_demo::msg::RobotStatus>(
      "robot_status", 10);

    timer_ = this->create_wall_timer(
      1s, std::bind(&StatusPublisher::on_timer, this));
  }

private:
  void on_timer()
  {
    custom_msg_demo::msg::RobotStatus msg;

    msg.robot_name = "robot_1";
    msg.battery_level = 100.0f - 5.0f * (counter_ % 10);
    msg.obstacle_detected = (counter_ % 3 == 0);

    if (counter_ % 5 == 0) {
      msg.mode = custom_msg_demo::msg::RobotStatus::MODE_ERROR;
    } else if (counter_ % 2 == 0) {
      msg.mode = custom_msg_demo::msg::RobotStatus::MODE_MOVING;
    } else {
      msg.mode = custom_msg_demo::msg::RobotStatus::MODE_IDLE;
    }

    RCLCPP_INFO(
      this->get_logger(),
      "Publishing -> name: %s, battery: %.1f, obstacle: %s, mode: %u",
      msg.robot_name.c_str(),
      msg.battery_level,
      msg.obstacle_detected ? "true" : "false",
      msg.mode);

    publisher_->publish(msg);
    counter_++;
  }

  rclcpp::Publisher<custom_msg_demo::msg::RobotStatus>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  size_t counter_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<StatusPublisher>());
  rclcpp::shutdown();
  return 0;
}
