#include<stdlib.h>
#include <ros/ros.h>
#include<time.h>
#include <geometry_msgs/Twist.h>

using namespace std;

void letswait(int);

int main(int argc, char **argv)
{
	// Initialize ROS and Create
	ros::init(argc, argv,"husky_move");
	ros::NodeHandle nh;
	
	//rCeates the publisher, and tells it to publish
     	//to the husky/cmd_vel topic, with a queue size of 100
     	ros::Publisher pub=nh.advertise<geometry_msgs::Twist>("husky/cmd_vel", 100);
	ros::Rate rate(10);
	
	
	// Move base forward for 2 seconds
	for (int i =0; i<21; i++)
	{
		geometry_msgs::Twist msg;
		msg.linear.x= 0.1;
		pub.publish(msg);
		rate.sleep();

		
	}
	
	geometry_msgs::Twist msg;
	pub.publish(msg);
}


void letswait(int secs){
	clock_t end;
	end=clock()+secs*CLOCKS_PER_SEC;
	while(clock()<end);
}

