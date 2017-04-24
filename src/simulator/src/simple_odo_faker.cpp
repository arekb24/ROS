#include "ros/ros.h"
#include "global_variables.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Float64MultiArray.h"
#include <cmath>
#include <stdlib.h>

// Mode: odo_mounting=1  -> right wheel
//		  	odo_mounting=0  -> left wheel


double carPath[3];
float messageSteeringAngle = 0;
float streamTimeSteeringAngle = 1;

struct tickData {
	bool tick;
	double speed;
	int currentTickTime;
};

void carPoseCallback (const std_msgs::Float64MultiArray::ConstPtr& msg_carPose) {
	for (int i = 0; i < 3; i++) {
		carPath[i] = msg_carPose->data[i];
	}
//	ROS_INFO("Obtained point coordinates : [%f %f]", carPath[0], carPath[1]);
}

void steeringAngleCallback(const std_msgs::Float64::ConstPtr& msg_steering_angle) {
	messageSteeringAngle = msg_steering_angle->data;
//	ROS_INFO("Obtained steering angle : [%f]", messageSteeringAngle);
	streamTimeSteeringAngle = 0;
}

tickData makeTick (double previousDistance, double currentDistance, int previousTickTime) {
	tickData data;
	double tickSpacing=wheel_radius*2*PI/amount_of_ticks; //spacing between the ticks on the wheel circumference
	double distanceOnWheel;

	if (odo_mounting == 1)
	distanceOnWheel = ( currentDistance - previousDistance) * (( 1 - tan (messageSteeringAngle)) / car_length * dist_between_wheels / 2);
	else
	distanceOnWheel = ( currentDistance - previousDistance) * (( 1 + tan (messageSteeringAngle)) / car_length * dist_between_wheels / 2);
	
	if (distanceOnWheel > tickSpacing) {
		data.tick = true;
		data.currentTickTime = ros::Time::now().toSec();
		data.speed = distanceOnWheel * (data.currentTickTime - previousTickTime);
		}
	else
		data.tick = false;

	return data; 
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "odo_faker");

	ros::NodeHandle n;

	ros::Publisher pub_odoFakePublisher = n.advertise<std_msgs::Float64>("odo_fake_speed", 1000);
	ros::Subscriber sub = n.subscribe("real_car_pose", 1000, carPoseCallback);
	ros::Subscriber sub_steering_angle = n.subscribe("steering_angle", 1000, steeringAngleCallback);
	
	float loopRate = 10; // loop rate in [Hz]
	ros::Rate r(loopRate);
	
	double distanceIncrement = 0;
	double previousCarPath[3] = {0, 0, 0};
	double currentDistance = 0;
	double previousTickDistance = 0;
	int previousTickTime = ros::Time::now().toSec();
	double previousMsg = 0;
	std_msgs::Float64 msg_odoFakePublisher;	
	msg_odoFakePublisher.data = 0.0;
	int totalTicks = 0;

	while (ros::ok()) {
		
		currentDistance += sqrt (pow (carPath[0] - previousCarPath[0], 2)
							 + pow (carPath[1] - previousCarPath[1], 2));
		ROS_INFO("previousTickDistance %f, currentDistance %f, previousTickTime %f"
					"total ticks %d", previousTickDistance, currentDistance,
					 previousTickTime, totalTicks);
		ROS_INFO("result %f ", msg_odoFakePublisher.data);

		tickData odoData = makeTick (previousTickDistance, currentDistance, previousTickTime);
		if (odoData.tick == true) {
			msg_odoFakePublisher.data = odoData.speed;
			previousTickTime = odoData.currentTickTime;
			previousTickDistance = currentDistance;
			totalTicks ++;
		}
		else
			msg_odoFakePublisher.data = previousMsg;

		// ROS_INFO("Result is : [%f]", msg_odoFakePublisher.data);

		pub_odoFakePublisher.publish(msg_odoFakePublisher);

		for (int i = 0; i < 3; i++) {
		previousCarPath[i] = carPath[i];
		}
		previousMsg = msg_odoFakePublisher.data;

		streamTimeSteeringAngle += 1 / loopRate;

		if (streamTimeSteeringAngle >= 1)
		ROS_INFO("Warning: steering angle streaming stopped!");

		ros::spinOnce();
		r.sleep();
	}
  return 0;
}
