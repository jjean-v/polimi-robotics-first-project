#include <algorithm>
#include <chrono>
#include <memory>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class FlexibleParametersNode : public rclcpp::Node
{
public:
  explicit FlexibleParametersNode(const rclcpp::NodeOptions & options)
  : Node("flexible_parameters_node", options)
  {
    if (!this->has_parameter("frame_id")) {
      this->declare_parameter<std::string>("frame_id", "base_link");
    }

    timer_ = this->create_wall_timer(
      2s, std::bind(&FlexibleParametersNode::on_timer, this));
  }

private:
  void on_timer()
  {
    auto result = this->list_parameters({}, 10);
    std::sort(result.names.begin(), result.names.end());

    RCLCPP_INFO(this->get_logger(), "Current parameters:");
    for (const auto & name : result.names) {
      rclcpp::Parameter param;
      if (this->get_parameter(name, param)) {
        RCLCPP_INFO(
          this->get_logger(),
          "  %s = %s",
          name.c_str(),
          param.value_to_string().c_str());
      }
    }
  }

  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  rclcpp::NodeOptions options;
  options.allow_undeclared_parameters(true);
  options.automatically_declare_parameters_from_overrides(true);

  rclcpp::spin(std::make_shared<FlexibleParametersNode>(options));
  rclcpp::shutdown();
  return 0;
}
