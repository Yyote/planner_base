cmake_minimum_required(VERSION 3.5)
project(planner_base)


# Default to C99
if(NOT CMAKE_C_STANDARD)
set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# # find dependencies
# find_package(ament_cmake REQUIRED)
# # find_package(std_msgs REQUIRED)
# find_package(rclcpp REQUIRED)
# find_package(rubin_msgs REQUIRED)
# # uncomment the following section in order to fill in
# # further dependencies manually.
# # find_package(<dependency> REQUIRED)

# if(BUILD_TESTING)
# find_package(ament_lint_auto REQUIRED)
# # the following line skips the linter which checks for copyrights
# # uncomment the line when a copyright and license is not present in all source files
# #set(ament_cmake_copyright_FOUND TRUE)
# # the following line skips cpplint (only works in a git repo)
# # uncomment the line when this package is not in a git repo
# #set(ament_cmake_cpplint_FOUND TRUE)
# ament_lint_auto_find_test_dependencies()
# endif()

add_library(planner_base_lib SHARED src/planner_base.cpp include/planner_base.hpp)
target_link_libraries(planner_base_lib protobuf)

target_include_directories(planner_base_lib
PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>)

# add_executable(sim_su_bridge_node src/sim_su_bridge.cpp)
# target_link_libraries(sim_su_bridge_node planner_base_lib zmq pthread)
# ament_target_dependencies(sim_su_bridge_node rclcpp rubin_msgs)

# add_executable(test_reg_publisher src/test_reg_publisher.cpp)
# target_link_libraries(test_reg_publisher zmq)
# ament_target_dependencies(test_reg_publisher rclcpp rubin_msgs)

# target_link_libraries(test_reg_subscriber zmq planner_base_lib)
# ament_target_dependencies(test_reg_subscriber rclcpp rubin_msgs)

# install(TARGETS
#     sim_su_bridge_node
#     test_reg_publisher
#     test_reg_subscriber
#     DESTINATION lib/${PROJECT_NAME})
#     # RUNTIME bin/${PROJECT_NAME})

# install(TARGETS
#     planner_base_lib
#     DESTINATION install/${PROJECT_NAME})

add_executable(test_main src/test_main.cpp)
target_link_libraries(test_main planner_base_lib)
target_include_directories(test_main PUBLIC include)


# ament_package()