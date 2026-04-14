// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_srv_demo:srv/CanMove.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_SRV_DEMO__SRV__DETAIL__CAN_MOVE__BUILDER_HPP_
#define CUSTOM_SRV_DEMO__SRV__DETAIL__CAN_MOVE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "custom_srv_demo/srv/detail/can_move__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace custom_srv_demo
{

namespace srv
{

namespace builder
{

class Init_CanMove_Request_obstacle_detected
{
public:
  explicit Init_CanMove_Request_obstacle_detected(::custom_srv_demo::srv::CanMove_Request & msg)
  : msg_(msg)
  {}
  ::custom_srv_demo::srv::CanMove_Request obstacle_detected(::custom_srv_demo::srv::CanMove_Request::_obstacle_detected_type arg)
  {
    msg_.obstacle_detected = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_srv_demo::srv::CanMove_Request msg_;
};

class Init_CanMove_Request_battery_level
{
public:
  Init_CanMove_Request_battery_level()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CanMove_Request_obstacle_detected battery_level(::custom_srv_demo::srv::CanMove_Request::_battery_level_type arg)
  {
    msg_.battery_level = std::move(arg);
    return Init_CanMove_Request_obstacle_detected(msg_);
  }

private:
  ::custom_srv_demo::srv::CanMove_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_srv_demo::srv::CanMove_Request>()
{
  return custom_srv_demo::srv::builder::Init_CanMove_Request_battery_level();
}

}  // namespace custom_srv_demo


namespace custom_srv_demo
{

namespace srv
{

namespace builder
{

class Init_CanMove_Response_message
{
public:
  explicit Init_CanMove_Response_message(::custom_srv_demo::srv::CanMove_Response & msg)
  : msg_(msg)
  {}
  ::custom_srv_demo::srv::CanMove_Response message(::custom_srv_demo::srv::CanMove_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_srv_demo::srv::CanMove_Response msg_;
};

class Init_CanMove_Response_can_move
{
public:
  Init_CanMove_Response_can_move()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CanMove_Response_message can_move(::custom_srv_demo::srv::CanMove_Response::_can_move_type arg)
  {
    msg_.can_move = std::move(arg);
    return Init_CanMove_Response_message(msg_);
  }

private:
  ::custom_srv_demo::srv::CanMove_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_srv_demo::srv::CanMove_Response>()
{
  return custom_srv_demo::srv::builder::Init_CanMove_Response_can_move();
}

}  // namespace custom_srv_demo

#endif  // CUSTOM_SRV_DEMO__SRV__DETAIL__CAN_MOVE__BUILDER_HPP_
