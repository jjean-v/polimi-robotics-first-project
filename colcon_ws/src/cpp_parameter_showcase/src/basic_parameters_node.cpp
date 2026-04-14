#include <chrono>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "rcl_interfaces/msg/floating_point_range.hpp"
#include "rcl_interfaces/msg/parameter_descriptor.hpp"

using namespace std::chrono_literals;

class BasicParametersNode : public rclcpp::Node
{
public:
  BasicParametersNode()
  : Node("basic_parameters_node")
  {
    rcl_interfaces::msg::ParameterDescriptor robot_name_desc;
    robot_name_desc.description = "Name of the robot";

    rcl_interfaces::msg::ParameterDescriptor enabled_desc;
    enabled_desc.description = "Whether the robot logic is enabled";

    rcl_interfaces::msg::ParameterDescriptor speed_desc;
    speed_desc.description = "Maximum robot speed in m/s";
    speed_desc.additional_constraints = "Expected range is [0.0, 2.0] with 0.1 steps";
    rcl_interfaces::msg::FloatingPointRange speed_range;
    speed_range.from_value = 0.0;
    speed_range.to_value = 2.0;
    speed_range.step = 0.1;
    speed_desc.floating_point_range.push_back(speed_range);

    rcl_interfaces::msg::ParameterDescriptor waypoint_desc;
    waypoint_desc.description = "List of waypoint IDs";

    rcl_interfaces::msg::ParameterDescriptor robot_id_desc;
    robot_id_desc.description = "Robot identifier";
    robot_id_desc.read_only = true;

    this->declare_parameter<std::string>("robot_name", "honey_badger", robot_name_desc);
    this->declare_parameter<bool>("enabled", true, enabled_desc);
    this->declare_parameter<double>("max_speed", 0.8, speed_desc);
    this->declare_parameter<std::vector<int64_t>>("waypoint_ids", {1, 2, 3}, waypoint_desc);
    this->declare_parameter<std::string>("robot_id", "HB-01", robot_id_desc);

    timer_ = this->create_wall_timer(
      2s, std::bind(&BasicParametersNode::on_timer, this));
  }

private:
  static std::string vector_to_string(const std::vector<int64_t> & data)
  {
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < data.size(); ++i) {
      oss << data[i];
      if (i + 1 < data.size()) {
        oss << ", ";
      }
    }
    oss << "]";
    return oss.str();
  }

  void on_timer()
  {
    const auto robot_name = this->get_parameter("robot_name").as_string();
    const auto enabled = this->get_parameter("enabled").as_bool();
    const auto max_speed = this->get_parameter("max_speed").as_double();
    const auto waypoint_ids = this->get_parameter("waypoint_ids").as_integer_array();
    const auto robot_id = this->get_parameter("robot_id").as_string();

    RCLCPP_INFO(
      this->get_logger(),
      "robot_name=%s | enabled=%s | max_speed=%.2f | waypoint_ids=%s | robot_id=%s",
      robot_name.c_str(),
      enabled ? "true" : "false",
      max_speed,
      vector_to_string(waypoint_ids).c_str(),
      robot_id.c_str());
  }

  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BasicParametersNode>());
  rclcpp::shutdown();
  return 0;
}
