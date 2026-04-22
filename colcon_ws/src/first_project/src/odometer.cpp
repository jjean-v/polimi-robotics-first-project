#include <chrono>
#include <cmath>
#include <functional>
#include <memory>
#include <string>

// standard include
#include "rclcpp/rclcpp.hpp"

// custom message sub
#include "bunker_msgs/msg/bunker_status.hpp"

// custom message pub
#include "nav_msgs/odometry.hpp"

// custom service
#include "first_project/srv/reset.hpp"

// tf includes
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include "tf2_ros/transform_broadcaster.h"

// for easier writing, so we can write 500ms 
// instead of std::chrono::milliseconds(500)
using namespace std::chrono_literals;

// Placeholders for std::bind, so we can write _1 and _2 
// instead of std::placeholders::_1
using std::placeholders::_1;
using std::placeholders::_2;

class Odometer : public rclcpp::Node
{
public:
  Odometer()
  : Node("odometer"), x_(0.0), y_(0.0), theta_(0.0)
  {
    bunker_sub_ = this->create_subscription<bunker_msgs::msg::BunkerStatus>(
      "/bunker_status",
      10,
      std::bind(&Odometer::update_odom, this, _1));

    odom_publisher_ = this->create_publisher<nav_msgs::Odometry>(
      "/project_odom", 10);

    tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

    // I don't know if we need the 2 placeholders but the template has it
    reset_service_ = this->create_service<first_project::srv::Reset>(
      "reset",
      std::bind(
        &Odometer::reset_callback,
        this,
        _1,
        _2));

    // RCLCPP_INFO(this->get_logger(), "Reset service ready.");
  

    last_time_ = this->get_clock()->now();
  }

private:
  void update_odom(const bunker_msgs::msg::BunkerStatus::SharedPtr msg)
  {
    const rclcpp::Time current_time = this->get_clock()->now();
    const double dt = std::max(0.0, (current_time - last_time_).seconds());

    const double linear_velocity = static_cast<double>(msg->linear_velocity);
    const double angular_velocity = static_cast<double>(msg->angular_velocity);

    // Euler
    // x_ += linear_velocity * std::cos(theta_) * dt;
    // y_ += linear_velocity * std::sin(theta_) * dt;
    // theta_ += angular_velocity * dt;

    // RK2
    // x_ += linear_velocity * std::cos(theta_ + angular_velocity * dt / 2) * dt;
    // y_ += linear_velocity * std::sin(theta_ + angular_velocity * dt / 2) * dt;
    // theta_ += angular_velocity * dt;

    // Exact
    const double sin_prev = std::sin(theta_);
    const double cos_prev = std::cos(theta_);
    theta_ += angular_velocity * dt;
    x_ += linear_velocity / angular_velocity * (std::sin(theta_) - sin_prev);
    y_ -= linear_velocity / angular_velocity * (std::cos(theta_) - cos_prev);


    publish_odom(current_time, linear_velocity, angular_velocity);
    publish_tf(current_time);
    last_time_ = current_time;
  }

  void publish_odom(
    const rclcpp::Time & stamp,
    double linear_velocity,
    double angular_velocity)
  {
    // Odometry messages store orientation as a quaternion, so the planar yaw
    // angle (theta_) must be converted before publishing.
    tf2::Quaternion q;
    q.setRPY(0.0, 0.0, theta_);

    // Even if our custom Odometry.msg does not store every field, this ROS
    // odometry message still needs its standard pose and twist members filled
    // so other nodes can interpret the robot state correctly.
    nav_msgs::Odometry odom;
    odom.header.stamp = stamp;
    odom.header.frame_id = "odom";
    odom.child_frame_id = "base_link2";
    
    odom.pose.pose.position.x = x_;
    odom.pose.pose.position.y = y_;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = tf2::toMsg(q);
    odom.twist.twist.linear.x = linear_velocity;
    odom.twist.twist.angular.z = angular_velocity;
    odom_publisher_->publish(odom);
  }

  void publish_tf(const rclcpp::Time & stamp)
  {
    // TF also requires orientation in quaternion form, even though the robot
    // state is tracked internally as a single yaw angle.
    tf2::Quaternion q;
    q.setRPY(0.0, 0.0, theta_);

    geometry_msgs::msg::TransformStamped transform;
    transform.header.stamp = stamp;
    transform.header.frame_id = "odom";
    transform.child_frame_id = "base_link2";
    transform.transform.translation.x = x_;
    transform.transform.translation.y = y_;
    transform.transform.translation.z = 0.0;
    transform.transform.rotation.x = q.x();
    transform.transform.rotation.y = q.y();
    transform.transform.rotation.z = q.z();
    transform.transform.rotation.w = q.w();
    tf_broadcaster_->sendTransform(transform);
  }

  void reset_callback(
    const std::shared_ptr<first_project::srv::Reset::Request> /*request*/,
    std::shared_ptr<first_project::srv::Reset::Response> /*response*/)
  {
    // reset the odometry to zero
    x_ = 0.0;
    y_ = 0.0;
    theta_ = 0.0;

    // we still reset the last_time_ to avoid a large dt when the next bunker status message arrives
    last_time_ = this->get_clock()->now();

    // RCLCPP_INFO(this->get_logger(), "Odometry reset to zero");
  }

  rclcpp::Subscription<bunker_msgs::msg::BunkerStatus>::SharedPtr bunker_sub_;
  rclcpp::Publisher<nav_msgs::Odometry>::SharedPtr odom_publisher_;
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  rclcpp::Service<first_project::srv::Reset>::SharedPtr reset_service_;

  rclcpp::Time last_time_;
  double x_;
  double y_;
  double theta_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Odometer>());
  rclcpp::shutdown();
  return 0;
}
