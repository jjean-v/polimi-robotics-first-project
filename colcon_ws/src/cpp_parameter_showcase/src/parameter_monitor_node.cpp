#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/parameter_event_handler.hpp"
#include "rcl_interfaces/msg/parameter_event.hpp"

class ParameterMonitorNode : public rclcpp::Node
{
public:
  ParameterMonitorNode()
  : Node("parameter_monitor_node")
  {
    target_node_ = this->declare_parameter<std::string>(
      "target_node", "/validated_parameters_node");

    handler_ = std::make_shared<rclcpp::ParameterEventHandler>(this);

    speed_cb_handle_ = handler_->add_parameter_callback(
      "target_speed",
      [this](const rclcpp::Parameter & p) {
        RCLCPP_INFO(
          this->get_logger(),
          "Observed %s target_speed -> %s",
          target_node_.c_str(),
          p.value_to_string().c_str());
      },
      target_node_);

    mode_cb_handle_ = handler_->add_parameter_callback(
      "mode",
      std::bind(&ParameterMonitorNode::on_mode_changed, this, std::placeholders::_1),
      target_node_);

    event_cb_handle_ = handler_->add_parameter_event_callback(
      [this](const rcl_interfaces::msg::ParameterEvent & event) {
        if (event.node != target_node_) {
          return;
        }

        RCLCPP_INFO(
          this->get_logger(),
          "Parameter event from %s", event.node.c_str());

        for (const auto & p : event.new_parameters) {
          RCLCPP_INFO(
            this->get_logger(),
            "  new: %s = %s",
            p.name.c_str(),
            rclcpp::Parameter::from_parameter_msg(p).value_to_string().c_str());
        }

        for (const auto & p : event.changed_parameters) {
          RCLCPP_INFO(
            this->get_logger(),
            "  changed: %s = %s",
            p.name.c_str(),
            rclcpp::Parameter::from_parameter_msg(p).value_to_string().c_str());
        }

        for (const auto & p : event.deleted_parameters) {
          RCLCPP_INFO(this->get_logger(), "  deleted: %s", p.name.c_str());
        }
      });
  }

private:

  void on_mode_changed(const rclcpp::Parameter & p)
  {
    RCLCPP_INFO(
      this->get_logger(),
      "Observed %s mode -> %s",
      target_node_.c_str(),
      p.value_to_string().c_str());
  }

  std::string target_node_;
  std::shared_ptr<rclcpp::ParameterEventHandler> handler_;
  std::shared_ptr<rclcpp::ParameterCallbackHandle> speed_cb_handle_;
  std::shared_ptr<rclcpp::ParameterCallbackHandle> mode_cb_handle_;
  std::shared_ptr<rclcpp::ParameterEventCallbackHandle> event_cb_handle_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ParameterMonitorNode>());
  rclcpp::shutdown();
  return 0;
}
