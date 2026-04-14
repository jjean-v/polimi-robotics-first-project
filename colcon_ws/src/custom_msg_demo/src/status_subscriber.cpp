#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "custom_msg_demo/msg/robot_status.hpp"

class StatusSubscriber : public rclcpp::Node
{
public:
  StatusSubscriber()
  : Node("status_subscriber")
  {
    subscription_ = this->create_subscription<custom_msg_demo::msg::RobotStatus>(
      "robot_status",
      10,
      std::bind(&StatusSubscriber::topic_callback, this, std::placeholders::_1));
  }

private:
  void topic_callback(const custom_msg_demo::msg::RobotStatus::SharedPtr msg) const
  {
    RCLCPP_INFO(
      this->get_logger(),
      "Received <- name: %s, battery: %.1f, obstacle: %s, mode: %u",
      msg->robot_name.c_str(),
      msg->battery_level,
      msg->obstacle_detected ? "true" : "false",
      msg->mode);
  }

  rclcpp::Subscription<custom_msg_demo::msg::RobotStatus>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<StatusSubscriber>());
  rclcpp::shutdown();
  return 0;
}
