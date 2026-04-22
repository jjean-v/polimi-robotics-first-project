cmake_minimum_required(VERSION 3.8)
project(first_project)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)

find_package(bunker_msgs REQUIRED)

rosidl_generate_interfaces(bunker_msgs/msg/BunkerStatus)

add_executable(odometer src/odometer.cpp)
ament_target_dependencies(odometer 
rclcpp 
bunker_msgs)

rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

target_link_libraries(odometer "${cpp_typesupport_target}")

install(TARGETS
  odometer
  DESTINATION lib/${PROJECT_NAME}
  )
ament_package()
