#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class ControlTimerNode : public rclcpp::Node
{
public:
  ControlTimerNode()
  : Node("control_timer_node"), work_count_(0), toggle_count_(0)
  {
    work_timer_ = this->create_wall_timer(
      1s, std::bind(&ControlTimerNode::work_callback, this));

    one_shot_timer_ = this->create_wall_timer(
      3s, std::bind(&ControlTimerNode::one_shot_callback, this));

    control_timer_ = this->create_wall_timer(
      5s, std::bind(&ControlTimerNode::control_callback, this));
  }

private:
  void work_callback()
  {
    RCLCPP_INFO(this->get_logger(), "Work timer tick %zu", work_count_++);
  }

  void one_shot_callback()
  {
    RCLCPP_INFO(this->get_logger(), "One-shot timer fired once, now canceling itself");
    one_shot_timer_->cancel();
  }

  void control_callback()
  {
    toggle_count_++;

    if (work_timer_->is_canceled()) {
      work_timer_->reset();
      RCLCPP_INFO(this->get_logger(), "Work timer resumed with reset()");
    } else {
      work_timer_->cancel();
      RCLCPP_INFO(this->get_logger(), "Work timer paused with cancel()");
    }

    if (toggle_count_ >= 4) {
      control_timer_->cancel();
      RCLCPP_INFO(this->get_logger(), "Control timer finished its demo and canceled itself");
    }
  }

  rclcpp::TimerBase::SharedPtr work_timer_;
  rclcpp::TimerBase::SharedPtr one_shot_timer_;
  rclcpp::TimerBase::SharedPtr control_timer_;
  size_t work_count_;
  size_t toggle_count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ControlTimerNode>());
  rclcpp::shutdown();
  return 0;
}
