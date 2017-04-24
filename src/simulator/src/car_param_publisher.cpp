#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "ros/ros.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float64MultiArray.h"
#include "global_variables.h"
#include "std_msgs/Int16.h"

int Arr[2];

int main(int argc, char **argv)
{
  ros::init(argc, argv, "car_parameters");
  ros::NodeHandle n;
  ros::Publisher car_parameters_pub = n.advertise<std_msgs::Float64MultiArray>("car_parameters", 1000);
 ros::Publisher chatter_pub1 = n.advertise<std_msgs::Int16>("chatter_talker1", 1000);
  ros::Rate loop_rate(1000);

  double time_start = ros::Time::now().toSec(); //get the current time in [s]

  while (ros::ok())
  {

	 std_msgs::Int16 msg_talker1;
    msg_talker1.data = 1;
    ROS_INFO("Talker 1 outputs: [%i]", msg_talker1.data);
    chatter_pub1.publish(msg_talker1);

 
    std_msgs::Float64MultiArray msg_car_parameters;

    msg_car_parameters.data.clear();
    ROS_INFO("Talker 1 outputs: [%i]", msg_talker1.data);
    msg_car_parameters.data.push_back(speed);
    msg_car_parameters.data.push_back(angle);

	 car_parameters_pub.publish(msg_car_parameters);

/*


int i = 0;
	// print all the remaining numbers
	for(std::vector<int>::const_iterator it = msg_car_parameters->data.begin(); it != msg_car_parameters->data.end(); ++it)
	{
		Arr[i] = *it;
		i++;
}
for(int j = 1; j < 3; j++)
	{
		printf("%d, ", Arr[j]);
	}

printf("\n");
*/

/*
	 msg_car_parameters.data[1] = speed;
	 msg_car_parameters.data[2] = angle;
/*
    //ROS_INFO("published");

    car_parameters_pub.publish(msg_car_parameters);
	 printf("%f %f \n", msg_car_parameters.data[1], msg_car_parameters.data[2]);

*/
    ros::spinOnce();

    loop_rate.sleep();
  }



  return 0;
}



/*
#include "std_msgs/Int16.h"
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
*/
