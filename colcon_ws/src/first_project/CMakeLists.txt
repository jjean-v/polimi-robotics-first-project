cmake_minimum_required(VERSION 3.8)
project(first_project)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)

find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)

find_package(bunker_msgs REQUIRED)

set(srv_file
  "srv/Reset.srv"
)

set(tf_error_msg_file
  "tf_error_msg/TfErrorMsg.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${srv_files}
  ${tf_error_msg_files}
  
  # not sure if this is the correct way to specify 
  # the dependency for the custom message
  # because it is not in the same package
  DEPENDENCIES bunker_msgs
)

ament_export_dependencies(rosidl_default_runtime)

add_executable(odometer src/odometer.cpp)
ament_target_dependencies(odometer
  rclcpp
  tf2
  tf2_ros
  geometry_msgs
  bunker_msgs
)

add_executable(tf_error src/tf_error.cpp)
ament_target_dependencies(tf_error
  rclcpp
  tf2
  tf2_ros
  geometry_msgs
  bunker_msgs
)

# custom_msg_demo uses the "rosidl_typesupport_cpp" 
# but custom_srv_demo uses it without the quotes
rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

target_link_libraries(odometer "${cpp_typesupport_target}")
target_link_libraries(tf_error "${cpp_typesupport_target}")

install(TARGETS
  odometer
  tf_error
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
