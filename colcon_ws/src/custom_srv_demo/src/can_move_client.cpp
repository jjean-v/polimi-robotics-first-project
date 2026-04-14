#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "custom_srv_demo/srv/can_move.hpp"

using namespace std::chrono_literals;

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  if (argc != 3) {
    RCLCPP_INFO(
      rclcpp::get_logger("rclcpp"),
      "usage: can_move_client BATTERY_LEVEL OBSTACLE(0|1|true|false)");
    return 1;
  }

  auto node = rclcpp::Node::make_shared("can_move_client");
  auto client = node->create_client<custom_srv_demo::srv::CanMove>("can_move");

  auto request = std::make_shared<custom_srv_demo::srv::CanMove::Request>();
  request->battery_level = std::stof(argv[1]);

  std::string obstacle_arg = argv[2];
  request->obstacle_detected =
    (obstacle_arg == "1" || obstacle_arg == "true" || obstacle_arg == "True");

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Service not available, waiting again...");
  }

  auto result = client->async_send_request(request);

  if (rclcpp::spin_until_future_complete(node, result) ==
      rclcpp::FutureReturnCode::SUCCESS)
  {
  auto response = result.get();
  RCLCPP_INFO(
    rclcpp::get_logger("rclcpp"),
    "Result: can_move=%s, message='%s'",
    response->can_move ? "true" : "false",
    response->message.c_str());

  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service can_move");
  }

  rclcpp::shutdown();
  return 0;
}
