#include <chrono>
#include <memory>
#include <thread>

#include "rclcpp/create_timer.hpp"
#include "rclcpp/executors/multi_threaded_executor.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class CallbackGroupTimersNode : public rclcpp::Node
{
public:
  CallbackGroupTimersNode()
  : Node("callback_group_timers_node")
  {
    group_a_ = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    group_b_ = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);

    timer_a_ = rclcpp::create_wall_timer(
      1s,
      [this]() { this->slow_callback("A"); },
      group_a_,
      this->get_node_base_interface().get(),
      this->get_node_timers_interface().get());

    timer_b_ = rclcpp::create_wall_timer(
      1s,
      [this]() { this->slow_callback("B"); },
      group_b_,
      this->get_node_base_interface().get(),
      this->get_node_timers_interface().get());
  }

private:
  void slow_callback(const char * name)
  {
    RCLCPP_INFO(this->get_logger(), "Timer %s START", name);
    std::this_thread::sleep_for(1500ms);
    RCLCPP_INFO(this->get_logger(), "Timer %s END", name);
  }

  rclcpp::CallbackGroup::SharedPtr group_a_;
  rclcpp::CallbackGroup::SharedPtr group_b_;
  rclcpp::TimerBase::SharedPtr timer_a_;
  rclcpp::TimerBase::SharedPtr timer_b_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<CallbackGroupTimersNode>();

  rclcpp::executors::MultiThreadedExecutor executor;
  executor.add_node(node);
  executor.spin();

  rclcpp::shutdown();
  return 0;
}

