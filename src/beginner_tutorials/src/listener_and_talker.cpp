#include "ros/ros.h"
#include "std_msgs/String.h"
#include <stdlib.h>
#include "std_msgs/Int16.h"

 bool Callback1_done=false;
 bool Callback2_done=false;
 bool Callback3_done=false;
 int message_1=0;
 int message_2=0;
 int message_3=0;

int processing (int input1, int input2, int input3)
{
  int result = input1 + input2*input3;
  return result;
}

void chatterCallback1(const std_msgs::Int16::ConstPtr& msg_talker1)
{
 Callback1_done=true;
 message_1=msg_talker1->data;

  if (Callback1_done && Callback2_done) {
  int result=processing (message_1,message_2,message_3);
  ROS_INFO("Result is : [%i]", result);
  Callback1_done=false;
  Callback2_done=false;
  Callback3_done=false;
  }

}

void chatterCallback2(const std_msgs::Int16::ConstPtr& msg_talker2)
{
 Callback2_done=true;
 message_2=msg_talker2->data;

  if (Callback1_done && Callback2_done) {
  int result=processing (message_1,message_2,message_3);
  ROS_INFO("Result is : [%i]", result);
  Callback1_done=false;
  Callback2_done=false;
  Callback3_done=false;
  }

}

void chatterCallback3(const std_msgs::Int16::ConstPtr& msg_talker3)
{
 Callback3_done=true;
 message_3=msg_talker3->data;

  if (Callback1_done && Callback2_done) {
  int result=processing (message_1,message_2,message_3);
  ROS_INFO("Result is : [%i]", result);
  Callback1_done=false;
  Callback2_done=false;
  Callback3_done=false;
  }

}

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "listener");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */

  ros::Publisher pub_self = n.advertise<std_msgs::Int16>("chatter_talker3", 1000);


  ros::Subscriber sub_talker1 = n.subscribe("chatter_talker1", 1000, chatterCallback1);
  ros::Subscriber sub_talker2 = n.subscribe("chatter_talker2", 1000, chatterCallback2);
  ros::Subscriber sub_self = n.subscribe("chatter_talker3", 1000, chatterCallback3);
  
  ros::Rate loop_rate(10);
  int count=0;
  while (ros::ok())
  {
    ROS_INFO("Loop number: [%i]", count);

    std_msgs::Int16 msg_talker3;
    msg_talker3.data = count;

    pub_self.publish(msg_talker3);


    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
