#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include "std_msgs/Float64MultiArray.h"

// so far haven't found a better way of passing subscriber values into main ROS loop than global variables
double carPath[3];

void carPoseCallback(const std_msgs::Float64MultiArray::ConstPtr& msg_carPose) {
	for (int i = 0; i < 3; i++) {
		carPath[i] = msg_carPose->data[i];
	}
	ROS_INFO("Obtained point coordinates : [%f %f]", carPath[0], carPath[1]);
}

int main( int argc, char** argv )
{
	ros::init(argc, argv, "points_and_lines");
	ros::NodeHandle n;
	ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
	ros::Subscriber sub = n.subscribe("real_car_pose", 1000, carPoseCallback);
	ros::Rate r(30);

	while (ros::ok()) {
		visualization_msgs::Marker points;
		points.header.frame_id = "/car_global_frame";
		points.header.stamp = ros::Time::now();
		points.ns = "car_pose_points";
		points.action = visualization_msgs::Marker::ADD;
		points.pose.orientation.w = 1.0;
		points.id = 0;

		points.type = visualization_msgs::Marker::POINTS;

		// POINTS markers use x and y scale for width/height respectively
		points.scale.x = 0.2;
		points.scale.y = 0.2;

		// Points are green
		points.color.g = 1.0f;
		points.color.a = 1.0;

		// Create the vertices for the points
		geometry_msgs::Point p;

		p.x = carPath[0];
		p.y = carPath[1];
		p.z = 0;
		ROS_INFO("Publishing point coordinates : [%f %f]", p.x, p.y);
		points.points.push_back(p);

		marker_pub.publish(points);
		ros::spinOnce();
		r.sleep();
	}
}
