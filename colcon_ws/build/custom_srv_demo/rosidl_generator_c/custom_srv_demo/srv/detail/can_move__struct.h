// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_srv_demo:srv/CanMove.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_SRV_DEMO__SRV__DETAIL__CAN_MOVE__STRUCT_H_
#define CUSTOM_SRV_DEMO__SRV__DETAIL__CAN_MOVE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/CanMove in the package custom_srv_demo.
typedef struct custom_srv_demo__srv__CanMove_Request
{
  float battery_level;
  bool obstacle_detected;
} custom_srv_demo__srv__CanMove_Request;

// Struct for a sequence of custom_srv_demo__srv__CanMove_Request.
typedef struct custom_srv_demo__srv__CanMove_Request__Sequence
{
  custom_srv_demo__srv__CanMove_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_srv_demo__srv__CanMove_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/CanMove in the package custom_srv_demo.
typedef struct custom_srv_demo__srv__CanMove_Response
{
  bool can_move;
  rosidl_runtime_c__String message;
} custom_srv_demo__srv__CanMove_Response;

// Struct for a sequence of custom_srv_demo__srv__CanMove_Response.
typedef struct custom_srv_demo__srv__CanMove_Response__Sequence
{
  custom_srv_demo__srv__CanMove_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_srv_demo__srv__CanMove_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_SRV_DEMO__SRV__DETAIL__CAN_MOVE__STRUCT_H_
