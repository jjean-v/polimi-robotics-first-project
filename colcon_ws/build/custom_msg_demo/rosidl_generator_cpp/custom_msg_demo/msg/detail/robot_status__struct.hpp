// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from custom_msg_demo:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MSG_DEMO__MSG__DETAIL__ROBOT_STATUS__STRUCT_HPP_
#define CUSTOM_MSG_DEMO__MSG__DETAIL__ROBOT_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__custom_msg_demo__msg__RobotStatus __attribute__((deprecated))
#else
# define DEPRECATED__custom_msg_demo__msg__RobotStatus __declspec(deprecated)
#endif

namespace custom_msg_demo
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RobotStatus_
{
  using Type = RobotStatus_<ContainerAllocator>;

  explicit RobotStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->robot_name = "";
      this->battery_level = 0.0f;
      this->obstacle_detected = false;
      this->mode = 0;
    }
  }

  explicit RobotStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : robot_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->robot_name = "";
      this->battery_level = 0.0f;
      this->obstacle_detected = false;
      this->mode = 0;
    }
  }

  // field types and members
  using _robot_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _robot_name_type robot_name;
  using _battery_level_type =
    float;
  _battery_level_type battery_level;
  using _obstacle_detected_type =
    bool;
  _obstacle_detected_type obstacle_detected;
  using _mode_type =
    uint8_t;
  _mode_type mode;

  // setters for named parameter idiom
  Type & set__robot_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->robot_name = _arg;
    return *this;
  }
  Type & set__battery_level(
    const float & _arg)
  {
    this->battery_level = _arg;
    return *this;
  }
  Type & set__obstacle_detected(
    const bool & _arg)
  {
    this->obstacle_detected = _arg;
    return *this;
  }
  Type & set__mode(
    const uint8_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t MODE_IDLE =
    0u;
  static constexpr uint8_t MODE_MOVING =
    1u;
  static constexpr uint8_t MODE_ERROR =
    2u;

  // pointer types
  using RawPtr =
    custom_msg_demo::msg::RobotStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_msg_demo::msg::RobotStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_msg_demo::msg::RobotStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_msg_demo::msg::RobotStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_msg_demo::msg::RobotStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_msg_demo::msg::RobotStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_msg_demo::msg::RobotStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_msg_demo::msg::RobotStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_msg_demo::msg::RobotStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_msg_demo::msg::RobotStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_msg_demo__msg__RobotStatus
    std::shared_ptr<custom_msg_demo::msg::RobotStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_msg_demo__msg__RobotStatus
    std::shared_ptr<custom_msg_demo::msg::RobotStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotStatus_ & other) const
  {
    if (this->robot_name != other.robot_name) {
      return false;
    }
    if (this->battery_level != other.battery_level) {
      return false;
    }
    if (this->obstacle_detected != other.obstacle_detected) {
      return false;
    }
    if (this->mode != other.mode) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotStatus_

// alias to use template instance with default allocator
using RobotStatus =
  custom_msg_demo::msg::RobotStatus_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t RobotStatus_<ContainerAllocator>::MODE_IDLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t RobotStatus_<ContainerAllocator>::MODE_MOVING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t RobotStatus_<ContainerAllocator>::MODE_ERROR;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace custom_msg_demo

#endif  // CUSTOM_MSG_DEMO__MSG__DETAIL__ROBOT_STATUS__STRUCT_HPP_
