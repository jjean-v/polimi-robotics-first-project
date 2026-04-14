// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from custom_srv_demo:srv/CanMove.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_SRV_DEMO__SRV__DETAIL__CAN_MOVE__TRAITS_HPP_
#define CUSTOM_SRV_DEMO__SRV__DETAIL__CAN_MOVE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "custom_srv_demo/srv/detail/can_move__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace custom_srv_demo
{

namespace srv
{

inline void to_flow_style_yaml(
  const CanMove_Request & msg,
  std::ostream & out)
{
  out << "{";
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
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CanMove_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CanMove_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace custom_srv_demo

namespace rosidl_generator_traits
{

[[deprecated("use custom_srv_demo::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const custom_srv_demo::srv::CanMove_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  custom_srv_demo::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use custom_srv_demo::srv::to_yaml() instead")]]
inline std::string to_yaml(const custom_srv_demo::srv::CanMove_Request & msg)
{
  return custom_srv_demo::srv::to_yaml(msg);
}

template<>
inline const char * data_type<custom_srv_demo::srv::CanMove_Request>()
{
  return "custom_srv_demo::srv::CanMove_Request";
}

template<>
inline const char * name<custom_srv_demo::srv::CanMove_Request>()
{
  return "custom_srv_demo/srv/CanMove_Request";
}

template<>
struct has_fixed_size<custom_srv_demo::srv::CanMove_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<custom_srv_demo::srv::CanMove_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<custom_srv_demo::srv::CanMove_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace custom_srv_demo
{

namespace srv
{

inline void to_flow_style_yaml(
  const CanMove_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: can_move
  {
    out << "can_move: ";
    rosidl_generator_traits::value_to_yaml(msg.can_move, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CanMove_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: can_move
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "can_move: ";
    rosidl_generator_traits::value_to_yaml(msg.can_move, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CanMove_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace custom_srv_demo

namespace rosidl_generator_traits
{

[[deprecated("use custom_srv_demo::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const custom_srv_demo::srv::CanMove_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  custom_srv_demo::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use custom_srv_demo::srv::to_yaml() instead")]]
inline std::string to_yaml(const custom_srv_demo::srv::CanMove_Response & msg)
{
  return custom_srv_demo::srv::to_yaml(msg);
}

template<>
inline const char * data_type<custom_srv_demo::srv::CanMove_Response>()
{
  return "custom_srv_demo::srv::CanMove_Response";
}

template<>
inline const char * name<custom_srv_demo::srv::CanMove_Response>()
{
  return "custom_srv_demo/srv/CanMove_Response";
}

template<>
struct has_fixed_size<custom_srv_demo::srv::CanMove_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<custom_srv_demo::srv::CanMove_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<custom_srv_demo::srv::CanMove_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<custom_srv_demo::srv::CanMove>()
{
  return "custom_srv_demo::srv::CanMove";
}

template<>
inline const char * name<custom_srv_demo::srv::CanMove>()
{
  return "custom_srv_demo/srv/CanMove";
}

template<>
struct has_fixed_size<custom_srv_demo::srv::CanMove>
  : std::integral_constant<
    bool,
    has_fixed_size<custom_srv_demo::srv::CanMove_Request>::value &&
    has_fixed_size<custom_srv_demo::srv::CanMove_Response>::value
  >
{
};

template<>
struct has_bounded_size<custom_srv_demo::srv::CanMove>
  : std::integral_constant<
    bool,
    has_bounded_size<custom_srv_demo::srv::CanMove_Request>::value &&
    has_bounded_size<custom_srv_demo::srv::CanMove_Response>::value
  >
{
};

template<>
struct is_service<custom_srv_demo::srv::CanMove>
  : std::true_type
{
};

template<>
struct is_service_request<custom_srv_demo::srv::CanMove_Request>
  : std::true_type
{
};

template<>
struct is_service_response<custom_srv_demo::srv::CanMove_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // CUSTOM_SRV_DEMO__SRV__DETAIL__CAN_MOVE__TRAITS_HPP_
