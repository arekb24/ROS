#include "ros/ros.h"
#include "global_variables.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Float64MultiArray.h"
#include <stdlib.h>

// so far haven't found a better way of passing subscriber values into main ROS loop than global variables
float messageSteeringVel = 0;
float messageSteeringAngle = 0;

float streamTimeSteeringVel = 1;
float streamTimeSteeringAngle = 1;

double *car_kinematics(double pose[3], double ts, double speed, double angle) {
	static double result[3];
	double increment[3];
	double rotationMatrix[3][3] = {{cos(pose[2]), -sin (pose[2]), 0},
										   {sin (pose[2]), cos (pose[2]), 0},{0, 0, 1}};
	double speedVector[3] = {speed, 0, speed / car_length * tan (angle)};
	for (int row = 0; row < 3; row++) {
		for (int inner = 0; inner < 3; inner++) {
			increment[row] += rotationMatrix[row][inner] * speedVector[inner];
		}
	}
	for (int i = 0; i < 3; i++) {
		result[i] = pose[i] + increment [i] * ts;
	}
	return result;
}

void velocityCallback (const std_msgs::Float64::ConstPtr& msg_steering_vel) {
	messageSteeringVel = msg_steering_vel->data;
	streamTimeSteeringVel = 0;
}

void steeringAngleCallback(const std_msgs::Float64::ConstPtr& msg_steering_angle) {
	messageSteeringAngle = msg_steering_angle->data;
	streamTimeSteeringAngle = 0;
}


int main(int argc, char **argv) {

	ros::init(argc, argv, "car_kinematics");

	ros::NodeHandle n;

	ros::Publisher pub_carPosePublisher = n.advertise<std_msgs::Float64MultiArray>("real_car_pose", 1000);
	ros::Subscriber sub_steering_vel = n.subscribe("steering_velocity", 1000, velocityCallback);
	ros::Subscriber sub_steering_angle = n.subscribe("steering_angle", 1000, steeringAngleCallback);
	
	float loopRate = 1000; // loop rate in [Hz]
	ros::Rate r(loopRate);

	double current_pose[3];
	current_pose[0] = pose_init[0];
	current_pose[1] = pose_init[1];
	current_pose[2] = pose_init[2];

	while (ros::ok()) {

		std_msgs::Float64MultiArray msg_carPosePublisher;

		double *pose_pointer;
		double current_speed = messageSteeringVel;
		double current_angle = messageSteeringAngle;
		pose_pointer = car_kinematics(current_pose,ts,speed,angle);
		for (int i=0; i<3; i++){
		current_pose[i] = *(pose_pointer+i);
		msg_carPosePublisher.data.push_back(current_pose[i]);
		}
		
		// Wrapping around <-PI, +PI>:
		if (current_pose[2] > PI)
		current_pose[2] = -2 * PI + current_pose[2];
		if (current_pose[2] < -PI)
		current_pose[2] = 2 * PI - current_pose[2];
		

		ROS_INFO("Result is : [%f %f %f]", current_pose[0], current_pose[1], current_pose[2]);

		pub_carPosePublisher.publish(msg_carPosePublisher);
		ROS_INFO("Result published :)  as %f %f %f", msg_carPosePublisher.data[0], msg_carPosePublisher.data[1], msg_carPosePublisher.data[2]);

		streamTimeSteeringAngle += 1 / loopRate;
		streamTimeSteeringVel += 1 / loopRate;

		if (streamTimeSteeringVel >= 1)
		ROS_INFO("Warning: car velocity streaming stopped!");

		if (streamTimeSteeringAngle >= 1)
		ROS_INFO("Warning: steering angle streaming stopped!");

		ros::spinOnce();
		r.sleep();
	}
  return 0;
}
