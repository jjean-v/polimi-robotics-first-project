// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from custom_srv_demo:srv/CanMove.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_SRV_DEMO__SRV__DETAIL__CAN_MOVE__STRUCT_HPP_
#define CUSTOM_SRV_DEMO__SRV__DETAIL__CAN_MOVE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__custom_srv_demo__srv__CanMove_Request __attribute__((deprecated))
#else
# define DEPRECATED__custom_srv_demo__srv__CanMove_Request __declspec(deprecated)
#endif

namespace custom_srv_demo
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct CanMove_Request_
{
  using Type = CanMove_Request_<ContainerAllocator>;

  explicit CanMove_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->battery_level = 0.0f;
      this->obstacle_detected = false;
    }
  }

  explicit CanMove_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->battery_level = 0.0f;
      this->obstacle_detected = false;
    }
  }

  // field types and members
  using _battery_level_type =
    float;
  _battery_level_type battery_level;
  using _obstacle_detected_type =
    bool;
  _obstacle_detected_type obstacle_detected;

  // setters for named parameter idiom
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

  // constant declarations

  // pointer types
  using RawPtr =
    custom_srv_demo::srv::CanMove_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_srv_demo::srv::CanMove_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_srv_demo::srv::CanMove_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_srv_demo::srv::CanMove_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_srv_demo::srv::CanMove_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_srv_demo::srv::CanMove_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_srv_demo::srv::CanMove_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_srv_demo::srv::CanMove_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_srv_demo::srv::CanMove_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_srv_demo::srv::CanMove_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_srv_demo__srv__CanMove_Request
    std::shared_ptr<custom_srv_demo::srv::CanMove_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_srv_demo__srv__CanMove_Request
    std::shared_ptr<custom_srv_demo::srv::CanMove_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CanMove_Request_ & other) const
  {
    if (this->battery_level != other.battery_level) {
      return false;
    }
    if (this->obstacle_detected != other.obstacle_detected) {
      return false;
    }
    return true;
  }
  bool operator!=(const CanMove_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CanMove_Request_

// alias to use template instance with default allocator
using CanMove_Request =
  custom_srv_demo::srv::CanMove_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace custom_srv_demo


#ifndef _WIN32
# define DEPRECATED__custom_srv_demo__srv__CanMove_Response __attribute__((deprecated))
#else
# define DEPRECATED__custom_srv_demo__srv__CanMove_Response __declspec(deprecated)
#endif

namespace custom_srv_demo
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct CanMove_Response_
{
  using Type = CanMove_Response_<ContainerAllocator>;

  explicit CanMove_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->can_move = false;
      this->message = "";
    }
  }

  explicit CanMove_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->can_move = false;
      this->message = "";
    }
  }

  // field types and members
  using _can_move_type =
    bool;
  _can_move_type can_move;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__can_move(
    const bool & _arg)
  {
    this->can_move = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    custom_srv_demo::srv::CanMove_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_srv_demo::srv::CanMove_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_srv_demo::srv::CanMove_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_srv_demo::srv::CanMove_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_srv_demo::srv::CanMove_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_srv_demo::srv::CanMove_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_srv_demo::srv::CanMove_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_srv_demo::srv::CanMove_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_srv_demo::srv::CanMove_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_srv_demo::srv::CanMove_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_srv_demo__srv__CanMove_Response
    std::shared_ptr<custom_srv_demo::srv::CanMove_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_srv_demo__srv__CanMove_Response
    std::shared_ptr<custom_srv_demo::srv::CanMove_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CanMove_Response_ & other) const
  {
    if (this->can_move != other.can_move) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const CanMove_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CanMove_Response_

// alias to use template instance with default allocator
using CanMove_Response =
  custom_srv_demo::srv::CanMove_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace custom_srv_demo

namespace custom_srv_demo
{

namespace srv
{

struct CanMove
{
  using Request = custom_srv_demo::srv::CanMove_Request;
  using Response = custom_srv_demo::srv::CanMove_Response;
};

}  // namespace srv

}  // namespace custom_srv_demo

#endif  // CUSTOM_SRV_DEMO__SRV__DETAIL__CAN_MOVE__STRUCT_HPP_
