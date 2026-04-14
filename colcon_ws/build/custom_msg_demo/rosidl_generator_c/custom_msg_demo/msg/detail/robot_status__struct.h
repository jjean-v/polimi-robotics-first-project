// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_msg_demo:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MSG_DEMO__MSG__DETAIL__ROBOT_STATUS__STRUCT_H_
#define CUSTOM_MSG_DEMO__MSG__DETAIL__ROBOT_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'MODE_IDLE'.
enum
{
  custom_msg_demo__msg__RobotStatus__MODE_IDLE = 0
};

/// Constant 'MODE_MOVING'.
enum
{
  custom_msg_demo__msg__RobotStatus__MODE_MOVING = 1
};

/// Constant 'MODE_ERROR'.
enum
{
  custom_msg_demo__msg__RobotStatus__MODE_ERROR = 2
};

// Include directives for member types
// Member 'robot_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/RobotStatus in the package custom_msg_demo.
typedef struct custom_msg_demo__msg__RobotStatus
{
  rosidl_runtime_c__String robot_name;
  float battery_level;
  bool obstacle_detected;
  uint8_t mode;
} custom_msg_demo__msg__RobotStatus;

// Struct for a sequence of custom_msg_demo__msg__RobotStatus.
typedef struct custom_msg_demo__msg__RobotStatus__Sequence
{
  custom_msg_demo__msg__RobotStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_msg_demo__msg__RobotStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_MSG_DEMO__MSG__DETAIL__ROBOT_STATUS__STRUCT_H_
