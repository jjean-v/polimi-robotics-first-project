	#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class BasicTimerNode : public rclcpp::Node
{
public:
  BasicTimerNode()
  : Node("basic_timer_node"), count_(0)
  {
    timer_ = this->create_wall_timer(
      1s, std::bind(&BasicTimerNode::timer_callback, this));
  }

private:
  void timer_callback()
  {
    RCLCPP_INFO(this->get_logger(), "Basic timer tick %zu", count_++);
  }

  rclcpp::TimerBase::SharedPtr timer_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BasicTimerNode>());
  rclcpp::shutdown();
  return 0;
}
