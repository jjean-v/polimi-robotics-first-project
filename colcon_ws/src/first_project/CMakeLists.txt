cmake_minimum_required(VERSION 3.8)
project(first_project)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)

find_package(bunker_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2_ros REQUIRED)

# find dependencies
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

set(srv_files
  "srv/Reset.srv"
)

set(msg_files
  "msg/TfErrorMsg.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${srv_files}
  ${msg_files}
  DEPENDENCIES std_msgs
)

rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} "rosidl_typesupport_cpp"
)

add_executable(odometer src/odometer.cpp)
ament_target_dependencies(odometer 
  rclcpp  
  bunker_msgs 
  nav_msgs 
  tf2
  geometry_msgs
  tf2_ros
)
target_link_libraries(odometer "${cpp_typesupport_target}")

add_executable(tf_error src/tf_error.cpp)
ament_target_dependencies(tf_error
  rclcpp
  tf2_ros
  tf2
  geometry_msgs
  std_msgs
)
target_link_libraries(tf_error "${cpp_typesupport_target}")


install(TARGETS
  odometer
  tf_error
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
