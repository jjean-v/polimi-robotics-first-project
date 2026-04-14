#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class LocalOnlyParametersNode : public rclcpp::Node
{
public:
  explicit LocalOnlyParametersNode(const rclcpp::NodeOptions & options)
  : Node("local_only_parameters_node", options)
  {
    this->declare_parameter<int64_t>("secret_number", 42);

    timer_ = this->create_wall_timer(
      2s,
      [this]() {
        RCLCPP_INFO(
          this->get_logger(),
          "secret_number=%ld (works locally, but remote param services are disabled)",
          this->get_parameter("secret_number").as_int());
      });
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  rclcpp::NodeOptions options;
  options.start_parameter_services(false);
  options.start_parameter_event_publisher(false);

  rclcpp::spin(std::make_shared<LocalOnlyParametersNode>(options));
  rclcpp::shutdown();
  return 0;
}
