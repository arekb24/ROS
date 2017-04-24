#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

#include "ros/ros.h"

#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/Float64MultiArray.h"

float Arr[2];
void arrayCallback(const std_msgs::Float64MultiArray::ConstPtr& array);

int main(int argc, char **argv)
{


	ros::init(argc, argv, "arraySubscriber");

	ros::NodeHandle n;	

	ros::Subscriber car_parameters_sub = n.subscribe("car_parameters", 1000, arrayCallback);

	ros::spinOnce();

	for(int j = 1; j < 90; j++)
	{
		printf("%f, ", Arr[j]);
	}

	printf("\n");
	return 0;
   }

void arrayCallback(const std_msgs::Float64MultiArray::ConstPtr& array)
{

	int i = 0;
	// print all the remaining numbers
	for(std::vector<float>::const_iterator it = array->data.begin(); it != array->data.end(); ++it)
	{
		Arr[i] = *it;
		i++;
	}
 
	return;
}
