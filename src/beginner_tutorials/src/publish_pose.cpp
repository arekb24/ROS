#include "ros/ros.h"
#include "std_msgs/String.h"
#include <stdlib.h>
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Float32.h"
#include "global_variables.h" //include the file with global variables
#include <math.h> /* sin, cos etc. */


double *car_kinematics(double pose[3], double ts, double speed, double angle)
{
	double rotation_matrix[3][3]={{cos(pose[2]), -sin (pose[2]), 0},
										  {sin (pose[2]), cos (pose[2]), 0},{0, 0, 1}};
	double result[3];
	double speed_vector[3]={speed, 0, speed / car_length * tan (angle)};
	for (int row = 0; row < 3; row++) {
		for (int inner = 0; inner < 3; inner++) {
			result[row]=rotation_matrix[row][inner] * speed_vector[inner];
		}
	}
	return result;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;

  // Define real pose publisher
  ros::Publisher pub_real_pose = n.advertise<std_msgs::Float32>("real_pose", 1000);

  // Define main program loop rate in [Hz]
  ros::Rate loop_rate(1000);

  double current_pose[3];
 
  //find a better way of implementing this:
	    current_pose[0] = pose_init[0];
	    current_pose[1] = pose_init[1];
	    current_pose[2] = pose_init[2];

  double *pose_pointer;

  while (ros::ok())
  {

    //Calculate the current pose
    pose_pointer = car_kinematics(current_pose,ts,speed,angle);
    
	for (int i=0; i<3; i++){
		current_pose[i] = *(pose_pointer+i);
	}
    //Publish the current pose
	
	 //find a  way of implementing this:
	   /* std_msgs::Float32MultiArray real_pose_msg[3];
	     real_pose_msg[0].data = current_pose[0];
	     real_pose_msg[1].data = current_pose[1];
	     real_pose_msg[2].data = current_pose[2];
            */
			std_msgs::Float32 real_pose_msg;
    		real_pose_msg.data = current_pose[0];
	      pub_real_pose.publish(real_pose_msg);
	    

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}


