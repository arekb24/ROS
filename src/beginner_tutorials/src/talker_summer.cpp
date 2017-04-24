#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker_summer");
  ros::NodeHandle n;


  ros::Publisher chatter_pub1 = n.advertise<std_msgs::Int16>("chatter_summer", 1000);

  ros::Rate loop_rate(10);


  int count = 0;
  while (ros::ok())
  {
 
    std_msgs::Int16 msg_summer;
    msg_summer.data = count;

    ROS_INFO("I output: [%i]", msg_summer.data);

    chatter_pub1.publish(msg_summer);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
