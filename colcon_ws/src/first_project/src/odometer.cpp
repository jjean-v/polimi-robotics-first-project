#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include "bunker_msgs/msg/bunker_status.hpp"

using std::placeholders::_1;

class Odometer : public rclcpp::Node {
    public:

        Odometer(): Node("odometer") {
            subscription_ = this->create_subscription<bunker_msgs::msg::BunkerStatus>("/bunker_status", 10, std::bind(&Odometer::topic_callback, this, _1));

        }

    private:
        
        void topic_callback(const bunker_msgs::msg::BunkerStatus::SharedPtr msg) const {
            RCLCPP_INFO(this->get_logger(), "vehicle state:'%u'\n control_mode:'%u'\n battery_voltage:'%f'", msg->vehicle_state, msg->control_mode, msg->battery_voltage);
        }

        rclcpp::Subscription<bunker_msgs::msg::BunkerStatus>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Odometer>());
  rclcpp::shutdown();
  return 0;
}
