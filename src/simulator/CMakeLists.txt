cmake_minimum_required(VERSION 2.8.3)


project(simulator)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

## Declare ROS messages and services

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})


## 
## add_executable(publish_pose src/publish_pose.cpp)
## target_link_libraries(publish_pose ${catkin_LIBRARIES})
## add_dependencies(publish_pose publish_pose_generate_messages_cpp)
## add_dependencies(publish_pose publish_pose_gencpp)

add_executable(car_param_publisher src/car_param_publisher.cpp)
target_link_libraries(car_param_publisher ${catkin_LIBRARIES})
add_dependencies(car_param_publisher simulator_generate_messages_cpp)

## add_executable(car_param_subscriber src/car_param_subscriber.cpp)
## target_link_libraries(car_param_subscriber ${catkin_LIBRARIES})
## add_dependencies(car_param_subscriber simulator_gencpp)

add_executable(publish_velocity src/publish_velocity.cpp)
target_link_libraries(publish_velocity ${catkin_LIBRARIES})
add_dependencies(publish_velocity simulator_generate_messages_cpp)

add_executable(publish_steering_angle src/publish_steering_angle.cpp)
target_link_libraries(publish_steering_angle ${catkin_LIBRARIES})
add_dependencies(publish_steering_angle simulator_generate_messages_cpp)

add_executable(car_kinematics src/car_kinematics.cpp)
target_link_libraries(car_kinematics ${catkin_LIBRARIES})
add_dependencies(car_kinematics simulator_generate_messages_cpp)

add_executable(car_model_noROS src/car_model_noROS.cpp)
target_link_libraries(car_model_noROS ${catkin_LIBRARIES})
add_dependencies(car_model_noROS simulator_generate_messages_cpp)

add_executable(odo_faker src/odo_faker.cpp)
target_link_libraries(odo_faker ${catkin_LIBRARIES})
add_dependencies(odo_faker simulator_generate_messages_cpp)

add_executable(simple_odo_faker src/simple_odo_faker.cpp)
target_link_libraries(simple_odo_faker ${catkin_LIBRARIES})
add_dependencies(simple_odo_faker simulator_generate_messages_cpp)

add_executable(display_path src/display_path.cpp)
target_link_libraries(display_path ${catkin_LIBRARIES})

add_executable(basic_shapes src/basic_shapes.cpp)
target_link_libraries(basic_shapes ${catkin_LIBRARIES})

