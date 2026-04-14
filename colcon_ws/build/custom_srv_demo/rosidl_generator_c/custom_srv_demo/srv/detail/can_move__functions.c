// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from custom_srv_demo:srv/CanMove.idl
// generated code does not contain a copyright notice
#include "custom_srv_demo/srv/detail/can_move__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
custom_srv_demo__srv__CanMove_Request__init(custom_srv_demo__srv__CanMove_Request * msg)
{
  if (!msg) {
    return false;
  }
  // battery_level
  // obstacle_detected
  return true;
}

void
custom_srv_demo__srv__CanMove_Request__fini(custom_srv_demo__srv__CanMove_Request * msg)
{
  if (!msg) {
    return;
  }
  // battery_level
  // obstacle_detected
}

bool
custom_srv_demo__srv__CanMove_Request__are_equal(const custom_srv_demo__srv__CanMove_Request * lhs, const custom_srv_demo__srv__CanMove_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // battery_level
  if (lhs->battery_level != rhs->battery_level) {
    return false;
  }
  // obstacle_detected
  if (lhs->obstacle_detected != rhs->obstacle_detected) {
    return false;
  }
  return true;
}

bool
custom_srv_demo__srv__CanMove_Request__copy(
  const custom_srv_demo__srv__CanMove_Request * input,
  custom_srv_demo__srv__CanMove_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // battery_level
  output->battery_level = input->battery_level;
  // obstacle_detected
  output->obstacle_detected = input->obstacle_detected;
  return true;
}

custom_srv_demo__srv__CanMove_Request *
custom_srv_demo__srv__CanMove_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_srv_demo__srv__CanMove_Request * msg = (custom_srv_demo__srv__CanMove_Request *)allocator.allocate(sizeof(custom_srv_demo__srv__CanMove_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(custom_srv_demo__srv__CanMove_Request));
  bool success = custom_srv_demo__srv__CanMove_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
custom_srv_demo__srv__CanMove_Request__destroy(custom_srv_demo__srv__CanMove_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    custom_srv_demo__srv__CanMove_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
custom_srv_demo__srv__CanMove_Request__Sequence__init(custom_srv_demo__srv__CanMove_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_srv_demo__srv__CanMove_Request * data = NULL;

  if (size) {
    data = (custom_srv_demo__srv__CanMove_Request *)allocator.zero_allocate(size, sizeof(custom_srv_demo__srv__CanMove_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = custom_srv_demo__srv__CanMove_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        custom_srv_demo__srv__CanMove_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
custom_srv_demo__srv__CanMove_Request__Sequence__fini(custom_srv_demo__srv__CanMove_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      custom_srv_demo__srv__CanMove_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

custom_srv_demo__srv__CanMove_Request__Sequence *
custom_srv_demo__srv__CanMove_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_srv_demo__srv__CanMove_Request__Sequence * array = (custom_srv_demo__srv__CanMove_Request__Sequence *)allocator.allocate(sizeof(custom_srv_demo__srv__CanMove_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = custom_srv_demo__srv__CanMove_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
custom_srv_demo__srv__CanMove_Request__Sequence__destroy(custom_srv_demo__srv__CanMove_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    custom_srv_demo__srv__CanMove_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
custom_srv_demo__srv__CanMove_Request__Sequence__are_equal(const custom_srv_demo__srv__CanMove_Request__Sequence * lhs, const custom_srv_demo__srv__CanMove_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!custom_srv_demo__srv__CanMove_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
custom_srv_demo__srv__CanMove_Request__Sequence__copy(
  const custom_srv_demo__srv__CanMove_Request__Sequence * input,
  custom_srv_demo__srv__CanMove_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(custom_srv_demo__srv__CanMove_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    custom_srv_demo__srv__CanMove_Request * data =
      (custom_srv_demo__srv__CanMove_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!custom_srv_demo__srv__CanMove_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          custom_srv_demo__srv__CanMove_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!custom_srv_demo__srv__CanMove_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
custom_srv_demo__srv__CanMove_Response__init(custom_srv_demo__srv__CanMove_Response * msg)
{
  if (!msg) {
    return false;
  }
  // can_move
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    custom_srv_demo__srv__CanMove_Response__fini(msg);
    return false;
  }
  return true;
}

void
custom_srv_demo__srv__CanMove_Response__fini(custom_srv_demo__srv__CanMove_Response * msg)
{
  if (!msg) {
    return;
  }
  // can_move
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
custom_srv_demo__srv__CanMove_Response__are_equal(const custom_srv_demo__srv__CanMove_Response * lhs, const custom_srv_demo__srv__CanMove_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // can_move
  if (lhs->can_move != rhs->can_move) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
custom_srv_demo__srv__CanMove_Response__copy(
  const custom_srv_demo__srv__CanMove_Response * input,
  custom_srv_demo__srv__CanMove_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // can_move
  output->can_move = input->can_move;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

custom_srv_demo__srv__CanMove_Response *
custom_srv_demo__srv__CanMove_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_srv_demo__srv__CanMove_Response * msg = (custom_srv_demo__srv__CanMove_Response *)allocator.allocate(sizeof(custom_srv_demo__srv__CanMove_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(custom_srv_demo__srv__CanMove_Response));
  bool success = custom_srv_demo__srv__CanMove_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
custom_srv_demo__srv__CanMove_Response__destroy(custom_srv_demo__srv__CanMove_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    custom_srv_demo__srv__CanMove_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
custom_srv_demo__srv__CanMove_Response__Sequence__init(custom_srv_demo__srv__CanMove_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_srv_demo__srv__CanMove_Response * data = NULL;

  if (size) {
    data = (custom_srv_demo__srv__CanMove_Response *)allocator.zero_allocate(size, sizeof(custom_srv_demo__srv__CanMove_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = custom_srv_demo__srv__CanMove_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        custom_srv_demo__srv__CanMove_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
custom_srv_demo__srv__CanMove_Response__Sequence__fini(custom_srv_demo__srv__CanMove_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      custom_srv_demo__srv__CanMove_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

custom_srv_demo__srv__CanMove_Response__Sequence *
custom_srv_demo__srv__CanMove_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_srv_demo__srv__CanMove_Response__Sequence * array = (custom_srv_demo__srv__CanMove_Response__Sequence *)allocator.allocate(sizeof(custom_srv_demo__srv__CanMove_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = custom_srv_demo__srv__CanMove_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
custom_srv_demo__srv__CanMove_Response__Sequence__destroy(custom_srv_demo__srv__CanMove_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    custom_srv_demo__srv__CanMove_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
custom_srv_demo__srv__CanMove_Response__Sequence__are_equal(const custom_srv_demo__srv__CanMove_Response__Sequence * lhs, const custom_srv_demo__srv__CanMove_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!custom_srv_demo__srv__CanMove_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
custom_srv_demo__srv__CanMove_Response__Sequence__copy(
  const custom_srv_demo__srv__CanMove_Response__Sequence * input,
  custom_srv_demo__srv__CanMove_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(custom_srv_demo__srv__CanMove_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    custom_srv_demo__srv__CanMove_Response * data =
      (custom_srv_demo__srv__CanMove_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!custom_srv_demo__srv__CanMove_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          custom_srv_demo__srv__CanMove_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!custom_srv_demo__srv__CanMove_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
