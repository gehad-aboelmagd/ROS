cmake_minimum_required(VERSION 3.8)
project(circular_turtle)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(rosidl_default_generators REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)
find_package(std_srvs REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# patrol_controller node
add_executable(patrol src/patrol_controller.cpp)
ament_target_dependencies(patrol rclcpp geometry_msgs std_srvs)

install(TARGETS patrol
  DESTINATION lib/${PROJECT_NAME}
)

# status_publisher node

add_executable(status_publisher src/status_publisher.cpp)
ament_target_dependencies(status_publisher rclcpp turtlesim geometry_msgs)

install(TARGETS status_publisher
  DESTINATION lib/${PROJECT_NAME}
)

ament_export_dependencies(rosidl_default_runtime)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/RobotStatus.msg"
  DEPENDENCIES geometry_msgs
)

rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME}
  "rosidl_typesupport_cpp")

target_link_libraries(status_publisher
  "${cpp_typesupport_target}")


# launch file
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)


ament_package()
