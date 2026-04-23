#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "first_project/srv/reset.hpp"

using namespace std::chrono_literals;

int main(int argc, char * argv[]){

    rclcpp::init(argc, argv);

    // Create the client to call the reset service
    auto reset_node = rclcpp::Node::make_shared("reset_client");
    auto reset_client = reset_node->create_client<first_project::srv::Reset>("reset");
    auto request = std::make_shared<first_project::srv::Reset::Request>();

    // Wait for the service to be available
    while (!reset_client->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service.");
            return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Service not available, waiting again...");
    }

    // Get the result of the service call
    auto result = reset_client->async_send_request(request);

    if (rclcpp::spin_until_future_complete(reset_node, result) ==
        rclcpp::FutureReturnCode::SUCCESS)
    {
    auto response = result.get();
    RCLCPP_INFO(
        rclcpp::get_logger("rclcpp"),
        "Reset service called successfully");
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call reset service");
    }
    rclcpp::shutdown();
    return 0;
}