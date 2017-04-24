cmake_minimum_required(VERSION 2.8.3)
project(beginner_tutorials)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

## Declare ROS messages and services
add_message_files(DIRECTORY msg FILES Num.msg)
add_service_files(DIRECTORY srv FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})
add_dependencies(talker beginner_tutorials_generate_messages_cpp)

add_executable(talker_summer src/talker_summer.cpp)
target_link_libraries(talker_summer ${catkin_LIBRARIES})
add_dependencies(talker_summer beginner_tutorials_generate_messages_cpp)

add_executable(simple_talker_1 src/simple_talker_1.cpp)
target_link_libraries(simple_talker_1 ${catkin_LIBRARIES})
add_dependencies(simple_talker_1 beginner_tutorials_generate_messages_cpp)

add_executable(simple_talker_2 src/simple_talker_2.cpp)
target_link_libraries(simple_talker_2 ${catkin_LIBRARIES})
add_dependencies(simple_talker_2 beginner_tutorials_generate_messages_cpp)

add_executable(listener_and_talker src/listener_and_talker.cpp)
target_link_libraries(listener_and_talker ${catkin_LIBRARIES})
add_dependencies(listener_and_talker beginner_tutorials_generate_messages_cpp)

add_executable(publish_array src/publish_array.cpp)
target_link_libraries(publish_array ${catkin_LIBRARIES})
add_dependencies(publish_array beginner_tutorials_generate_messages_cpp)

add_executable(Publish src/Publish.cpp)
target_link_libraries(Publish ${catkin_LIBRARIES})
add_dependencies(Publish beginner_tutorials_generate_messages_cpp)

add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})
add_dependencies(listener beginner_tutorials_generate_messages_cpp)

add_executable(listener_spinonce src/listener_spinonce.cpp)
target_link_libraries(listener_spinonce ${catkin_LIBRARIES})
add_dependencies(listener_spinonce beginner_tutorials_generate_messages_cpp)

add_executable(listener_2talkers src/listener_2talkers.cpp)
target_link_libraries(listener_2talkers ${catkin_LIBRARIES})
add_dependencies(listener_2talkers beginner_tutorials_generate_messages_cpp)

add_executable(listener_summer src/listener_summer.cpp)
target_link_libraries(listener_summer ${catkin_LIBRARIES})
add_dependencies(listener_summer beginner_tutorials_generate_messages_cpp)

add_executable(subscribe_array src/subscribe_array.cpp)
target_link_libraries(subscribe_array ${catkin_LIBRARIES})
add_dependencies(subscribe_array beginner_tutorials_generate_messages_cpp)

add_executable(Subscribe src/Subscribe.cpp)
target_link_libraries(Subscribe ${catkin_LIBRARIES})
add_dependencies(Subscribe beginner_tutorials_generate_messages_cpp)

add_executable(add_two_ints_server src/add_two_ints_server.cpp)
target_link_libraries(add_two_ints_server ${catkin_LIBRARIES})
add_dependencies(add_two_ints_server beginner_tutorials_gencpp)

add_executable(add_two_ints_client src/add_two_ints_client.cpp)
target_link_libraries(add_two_ints_client ${catkin_LIBRARIES})
add_dependencies(add_two_ints_client beginner_tutorials_gencpp)




add_executable(publish_pose src/publish_pose.cpp)
target_link_libraries(publish_pose ${catkin_LIBRARIES})
add_dependencies(publish_pose beginner_tutorials_generate_messages_cpp)
add_dependencies(publish_pose beginner_tutorials_pose_gencpp)

