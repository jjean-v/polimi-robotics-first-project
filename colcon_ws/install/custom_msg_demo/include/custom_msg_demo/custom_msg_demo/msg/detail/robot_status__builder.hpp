// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_msg_demo:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MSG_DEMO__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_
#define CUSTOM_MSG_DEMO__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "custom_msg_demo/msg/detail/robot_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace custom_msg_demo
{

namespace msg
{

namespace builder
{

class Init_RobotStatus_mode
{
public:
  explicit Init_RobotStatus_mode(::custom_msg_demo::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  ::custom_msg_demo::msg::RobotStatus mode(::custom_msg_demo::msg::RobotStatus::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_msg_demo::msg::RobotStatus msg_;
};

class Init_RobotStatus_obstacle_detected
{
public:
  explicit Init_RobotStatus_obstacle_detected(::custom_msg_demo::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_mode obstacle_detected(::custom_msg_demo::msg::RobotStatus::_obstacle_detected_type arg)
  {
    msg_.obstacle_detected = std::move(arg);
    return Init_RobotStatus_mode(msg_);
  }

private:
  ::custom_msg_demo::msg::RobotStatus msg_;
};

class Init_RobotStatus_battery_level
{
public:
  explicit Init_RobotStatus_battery_level(::custom_msg_demo::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_obstacle_detected battery_level(::custom_msg_demo::msg::RobotStatus::_battery_level_type arg)
  {
    msg_.battery_level = std::move(arg);
    return Init_RobotStatus_obstacle_detected(msg_);
  }

private:
  ::custom_msg_demo::msg::RobotStatus msg_;
};

class Init_RobotStatus_robot_name
{
public:
  Init_RobotStatus_robot_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotStatus_battery_level robot_name(::custom_msg_demo::msg::RobotStatus::_robot_name_type arg)
  {
    msg_.robot_name = std::move(arg);
    return Init_RobotStatus_battery_level(msg_);
  }

private:
  ::custom_msg_demo::msg::RobotStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_msg_demo::msg::RobotStatus>()
{
  return custom_msg_demo::msg::builder::Init_RobotStatus_robot_name();
}

}  // namespace custom_msg_demo

#endif  // CUSTOM_MSG_DEMO__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_
