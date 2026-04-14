#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class MultiTimerNode : public rclcpp::Node
{
public:
  MultiTimerNode()
  : Node("multi_timer_node"), fast_count_(0), slow_count_(0)
  {
    fast_timer_ = this->create_wall_timer(
      500ms,
      [this]() {
        RCLCPP_INFO(this->get_logger(), "Fast timer tick %zu", fast_count_++);
      });

    slow_timer_ = this->create_wall_timer(
      2s, std::bind(&MultiTimerNode::slow_timer_callback, this));
  }

private:
  void slow_timer_callback()
  {
    RCLCPP_INFO(this->get_logger(), "Slow timer tick %zu", slow_count_++);
  }

  rclcpp::TimerBase::SharedPtr fast_timer_;
  rclcpp::TimerBase::SharedPtr slow_timer_;
  size_t fast_count_;
  size_t slow_count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MultiTimerNode>());
  rclcpp::shutdown();
  return 0;
}
