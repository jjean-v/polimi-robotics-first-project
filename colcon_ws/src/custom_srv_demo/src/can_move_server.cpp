#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "custom_srv_demo/srv/can_move.hpp"

using std::placeholders::_1;
using std::placeholders::_2;

class CanMoveServer : public rclcpp::Node
{
public:
  CanMoveServer()
  : Node("can_move_server")
  {
    service_ = this->create_service<custom_srv_demo::srv::CanMove>(
      "can_move",
      std::bind(&CanMoveServer::handle_request, this, _1, _2));

    RCLCPP_INFO(this->get_logger(), "CanMove service ready.");
  }

private:
  void handle_request(
    const std::shared_ptr<custom_srv_demo::srv::CanMove::Request> request,
    std::shared_ptr<custom_srv_demo::srv::CanMove::Response> response)
  {
    RCLCPP_INFO(
      this->get_logger(),
      "Request received: battery=%.1f obstacle=%s",
      request->battery_level,
      request->obstacle_detected ? "true" : "false");

    if (request->battery_level < 30.0f) {
      response->can_move = false;
      response->message = "Battery too low";
    } else if (request->obstacle_detected) {
      response->can_move = false;
      response->message = "Obstacle detected";
    } else {
      response->can_move = true;
      response->message = "Path is clear";
    }

    RCLCPP_INFO(
      this->get_logger(),
      "Response sent: can_move=%s message='%s'",
      response->can_move ? "true" : "false",
      response->message.c_str());
  }

  rclcpp::Service<custom_srv_demo::srv::CanMove>::SharedPtr service_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CanMoveServer>());
  rclcpp::shutdown();
  return 0;
}
