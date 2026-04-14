#include <algorithm>
#include <cctype>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class CommandProcessorNode : public rclcpp::Node
{
public:
  CommandProcessorNode()
  : Node("command_processor_node")
  {
    // Publisher: sends the reaction/result of the node
    publisher_ = this->create_publisher<std_msgs::msg::String>("robot_status", 10);

    // Subscriber: listens for incoming commands
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "robot_command",
      10,
      std::bind(&CommandProcessorNode::command_callback, this, _1));

    RCLCPP_INFO(this->get_logger(), "CommandProcessorNode started.");
    RCLCPP_INFO(this->get_logger(), "Listening on /robot_command");
    RCLCPP_INFO(this->get_logger(), "Publishing on /robot_status");
  }

private:
  void command_callback(const std_msgs::msg::String::SharedPtr msg)
  {
    const std::string command = msg->data;
    std_msgs::msg::String response;

    if (command == "start") {
      response.data = "Robot status: RUNNING";
    } else if (command == "stop") {
      response.data = "Robot status: STOPPED";
    } else if (command == "dock") {
      response.data = "Robot status: DOCKING";
    } else {
      std::string upper = command;
      std::transform(
        upper.begin(), upper.end(), upper.begin(),
        [](unsigned char c) { return static_cast<char>(std::toupper(c)); });

      response.data = "Robot status: UNKNOWN COMMAND -> " + upper;
    }

    RCLCPP_INFO(
      this->get_logger(),
      "Received command: '%s' | Publishing: '%s'",
      command.c_str(),
      response.data.c_str());

    publisher_->publish(response);
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CommandProcessorNode>());
  rclcpp::shutdown();
  return 0;
}
