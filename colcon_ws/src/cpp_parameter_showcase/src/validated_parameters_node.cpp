#include <chrono>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "rcl_interfaces/msg/parameter_descriptor.hpp"
#include "rcl_interfaces/msg/set_parameters_result.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class ValidatedParametersNode : public rclcpp::Node
{
public:
  ValidatedParametersNode()
  : Node("validated_parameters_node")
  {
    rcl_interfaces::msg::ParameterDescriptor battery_desc;
    battery_desc.description = "Battery threshold in percent";

    rcl_interfaces::msg::ParameterDescriptor speed_desc;
    speed_desc.description = "Target speed in m/s";

    rcl_interfaces::msg::ParameterDescriptor mode_desc;
    mode_desc.description = "Operating mode: idle, manual, auto";

    rcl_interfaces::msg::ParameterDescriptor dynamic_desc;
    dynamic_desc.description = "Parameter intentionally allowed to change type";
    dynamic_desc.dynamic_typing = true;

    this->declare_parameter<int64_t>("battery_threshold", 25, battery_desc);
    this->declare_parameter<double>("target_speed", 0.5, speed_desc);
    this->declare_parameter<std::string>("mode", "idle", mode_desc);
    this->declare_parameter("dynamic_value", rclcpp::ParameterValue("unset"), dynamic_desc);

    callback_handle_ = this->add_on_set_parameters_callback(
      std::bind(&ValidatedParametersNode::validate_parameters, this, _1));

    timer_ = this->create_wall_timer(
      2s, std::bind(&ValidatedParametersNode::on_timer, this));
  }

private:
  rcl_interfaces::msg::SetParametersResult validate_parameters(
    const std::vector<rclcpp::Parameter> & parameters)
  {
    rcl_interfaces::msg::SetParametersResult result;
    result.successful = true;
    result.reason = "success";

    static const std::set<std::string> valid_modes{"idle", "manual", "auto"};

    for (const auto & param : parameters) {
      if (param.get_name() == "battery_threshold") {
        if (param.get_type() != rclcpp::ParameterType::PARAMETER_INTEGER) {
          result.successful = false;
          result.reason = "battery_threshold must be an integer";
          return result;
        }
        const auto value = param.as_int();
        if (value < 0 || value > 100) {
          result.successful = false;
          result.reason = "battery_threshold must be in [0, 100]";
          return result;
        }
      }

      if (param.get_name() == "target_speed") {
        if (param.get_type() != rclcpp::ParameterType::PARAMETER_DOUBLE) {
          result.successful = false;
          result.reason = "target_speed must be a double";
          return result;
        }
        const auto value = param.as_double();
        if (value < 0.0 || value > 2.0) {
          result.successful = false;
          result.reason = "target_speed must be in [0.0, 2.0]";
          return result;
        }
      }

      if (param.get_name() == "mode") {
        if (param.get_type() != rclcpp::ParameterType::PARAMETER_STRING) {
          result.successful = false;
          result.reason = "mode must be a string";
          return result;
        }
        const auto value = param.as_string();
        if (valid_modes.count(value) == 0) {
          result.successful = false;
          result.reason = "mode must be one of: idle, manual, auto";
          return result;
        }
      }
    }

    return result;
  }

  void on_timer()
  {
    rclcpp::Parameter dynamic_value;
    this->get_parameter("dynamic_value", dynamic_value);

    RCLCPP_INFO(
      this->get_logger(),
      "battery_threshold=%ld | target_speed=%.2f | mode=%s | dynamic_value=%s",
      this->get_parameter("battery_threshold").as_int(),
      this->get_parameter("target_speed").as_double(),
      this->get_parameter("mode").as_string().c_str(),
      dynamic_value.value_to_string().c_str());
  }

  rclcpp::node_interfaces::OnSetParametersCallbackHandle::SharedPtr callback_handle_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ValidatedParametersNode>());
  rclcpp::shutdown();
  return 0;
}
