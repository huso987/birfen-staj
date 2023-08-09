cmake_minimum_required(VERSION 3.8)
project(my_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(turtlesim REQUIRED)


add_executable(shape src/shapedrawernode.cpp)
ament_target_dependencies(shape rclcpp)

add_executable(pathcontrol src/pathfollowernode.cpp)
ament_target_dependencies(pathcontrol rclcpp)

add_executable(turtlecontrol src/turtlecontrolnode.cpp)
ament_target_dependencies(turtlecontrol rclcpp)

add_executable(turtlebot src/turtlebotcontrolnode.cpp)
ament_target_dependencies(turtlebot rclcpp)

add_executable(turtlebot1 src/turtlebot1metre.cpp)
ament_target_dependencies(turtlebot1 rclcpp)

add_executable(threepoints src/threepoints.cpp)
ament_target_dependencies(threepoints rclcpp)

add_executable(engel src/engel.cpp)
ament_target_dependencies(engel rclcpp)

install(TARGETS 
    shape
    pathcontrol
    turtlecontrol
    turtlebot
    turtlebot1
    threepoints
    engel
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()
