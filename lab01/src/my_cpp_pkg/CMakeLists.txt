cmake_minimum_required(VERSION 3.8)
project(my_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

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




add_executable(ayha7a src/ayha7a.cpp)
add_executable(hello_world src/hello_world.cpp)
add_executable(publisher1 src/publisher1.cpp)
add_executable(publisher2 src/publisher2.cpp)
add_executable(subscriber src/subscriber.cpp)
# target_include_directories(ayha7a PUBLIC 
# $<BUILDINT>)
ament_target_dependencies(ayha7a rclcpp)
ament_target_dependencies(hello_world rclcpp)
ament_target_dependencies(publisher1 rclcpp std_msgs)
ament_target_dependencies(publisher2 rclcpp std_msgs)
ament_target_dependencies(subscriber rclcpp std_msgs)

install(TARGETS ayha7a
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS hello_world
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS publisher1
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS publisher2
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS subscriber
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
