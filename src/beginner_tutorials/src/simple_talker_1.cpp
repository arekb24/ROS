#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "simple_talker_1");
  ros::NodeHandle n;


  ros::Publisher chatter_pub1 = n.advertise<std_msgs::Int16>("chatter_talker1", 1000);

  ros::Rate loop_rate(10);


  int count = 0;
  while (ros::ok())
  {
 
    std_msgs::Int16 msg_talker1;
    msg_talker1.data = count;

    ROS_INFO("Talker 1 outputs: [%i]", msg_talker1.data);

    chatter_pub1.publish(msg_talker1);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}

