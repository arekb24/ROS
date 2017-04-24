#include "ros/ros.h"
#include "global_variables.h"
#include "std_msgs/Float64.h"

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "velocity_publisher");
  ros::NodeHandle n;


  ros::Publisher pub_steering_vel = n.advertise<std_msgs::Float64>("steering_velocity", 1000);

  ros::Rate loop_rate(1000);

  while (ros::ok())
  {
 
    std_msgs::Float64 msg_steering_vel;
    msg_steering_vel.data = speed;

    ROS_INFO("Published velocity: [%f]", msg_steering_vel.data);

    pub_steering_vel.publish(msg_steering_vel);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}

