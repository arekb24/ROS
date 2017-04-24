#include "ros/ros.h"
#include "global_variables.h"
#include "std_msgs/Float64.h"

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "angle_publisher");
  ros::NodeHandle n;


  ros::Publisher pub_steering_angle = n.advertise<std_msgs::Float64>("steering_angle", 1000);

  ros::Rate loop_rate(1000);

  while (ros::ok())
  {
 
    std_msgs::Float64 msg_steering_angle;
    msg_steering_angle.data = angle;

    ROS_INFO("Published steering angle: [%f]", msg_steering_angle.data);

    pub_steering_angle.publish(msg_steering_angle);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}
