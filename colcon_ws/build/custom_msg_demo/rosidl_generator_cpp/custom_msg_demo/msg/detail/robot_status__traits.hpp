// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from custom_msg_demo:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MSG_DEMO__MSG__DETAIL__ROBOT_STATUS__TRAITS_HPP_
#define CUSTOM_MSG_DEMO__MSG__DETAIL__ROBOT_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "custom_msg_demo/msg/detail/robot_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace custom_msg_demo
{

namespace msg
{

inline void to_flow_style_yaml(
  const RobotStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: robot_name
  {
    out << "robot_name: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_name, out);
    out << ", ";
  }

  // member: battery_level
  {
    out << "battery_level: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_level, out);
    out << ", ";
  }

  // member: obstacle_detected
  {
    out << "obstacle_detected: ";
    rosidl_generator_traits::value_to_yaml(msg.obstacle_detected, out);
    out << ", ";
  }

  // member: mode
  {
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RobotStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: robot_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "robot_name: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_name, out);
    out << "\n";
  }

  // member: battery_level
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_level: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_level, out);
    out << "\n";
  }

  // member: obstacle_detected
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "obstacle_detected: ";
    rosidl_generator_traits::value_to_yaml(msg.obstacle_detected, out);
    out << "\n";
  }

  // member: mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RobotStatus & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace custom_msg_demo

namespace rosidl_generator_traits
{

[[deprecated("use custom_msg_demo::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const custom_msg_demo::msg::RobotStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  custom_msg_demo::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use custom_msg_demo::msg::to_yaml() instead")]]
inline std::string to_yaml(const custom_msg_demo::msg::RobotStatus & msg)
{
  return custom_msg_demo::msg::to_yaml(msg);
}

template<>
inline const char * data_type<custom_msg_demo::msg::RobotStatus>()
{
  return "custom_msg_demo::msg::RobotStatus";
}

template<>
inline const char * name<custom_msg_demo::msg::RobotStatus>()
{
  return "custom_msg_demo/msg/RobotStatus";
}

template<>
struct has_fixed_size<custom_msg_demo::msg::RobotStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<custom_msg_demo::msg::RobotStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<custom_msg_demo::msg::RobotStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CUSTOM_MSG_DEMO__MSG__DETAIL__ROBOT_STATUS__TRAITS_HPP_
