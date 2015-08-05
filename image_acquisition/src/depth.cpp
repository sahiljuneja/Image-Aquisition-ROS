#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <string.h>
#include <ros/callback_queue.h>

using namespace std;

char filename[50];
int imgtype;

bool done=false;

static const int MY_ROS_QUEUE_SIZE = 100;
void depth_node_callback(const sensor_msgs::Image::ConstPtr& msg)
{
	
	cout << "Entering Callback" << endl;

	cv_bridge::CvImageConstPtr cv_ptr;
	cv_ptr = cv_bridge::toCvShare(msg);
	
	double max = 0,min=0;
	
	cv::minMaxLoc(cv_ptr->image, &min, &max, 0, 0);
	cv::Mat normalized,op;
	cv_ptr->image.convertTo(normalized, CV_32F, 255/(max-min), -min) ;


	cv::imwrite(filename,normalized);
	
	done=true;
}

int main(int argc, char **argv)
{
	string type;
	strcpy(filename,argv[1]);
	imgtype=atoi(argv[2]);
	
	ros::init(argc, argv, "depth_node");

	cout << "Save image" << endl;
	ros::NodeHandle nh;

	if(imgtype==1)
	type="camera/rgb/image_color";

	else if(imgtype==0)
	type="camera/depth_registered/image_raw";

	ros::Subscriber sub = nh.subscribe(type,MY_ROS_QUEUE_SIZE, depth_node_callback);


	while(!done && ros::ok()) 
	{
		ros::spinOnce();
		loop_rate.sleep();
    	}

	cout <<filename<<" Saved" << endl;
	return 0;
}
