#include <chrono>
#include <cmath>
#include <functional>
#include <memory>
#include <string>

// standard include
#include "rclcpp/rclcpp.hpp"

// custom message sub
#include "bunker_msgs/msg/bunker_status.hpp"

// for easier writing, so we can write 500ms 
// instead of std::chrono::milliseconds(500)
using namespace std::chrono_literals;

// Placeholders for std::bind, so we can write _1 and _2 
// instead of std::placeholders::_1
using std::placeholders::_1;
using std::placeholders::_2;

class Odometer : public rclcpp::Node
{
public:
	Odometer() : Node("odometer")
	{
		bunker_sub_ = this->create_subscription<bunker_msgs::msg::BunkerStatus>(
			"/bunker_status", 
			10, 
			std::bind(&Odometer::bunker_status_callback, this, _1));
	}
private:
	void bunker_status_callback(const bunker_msgs::msg::BunkerStatus::SharedPtr msg)
	{
		RCLCPP_INFO(this->get_logger(), "Received bunker status: %s", msg->status.c_str());
	}

	rclcpp::Subscription<bunker_msgs::msg::BunkerStatus>::SharedPtr bunker_sub_;
}

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<Odometer>());
	rclcpp::shutdown();
	return 0;
}