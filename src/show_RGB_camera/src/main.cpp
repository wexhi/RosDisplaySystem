#include "ros/ros.h"
#include <iostream>
#include <sensor_msgs/Imu.h>
#include <opencv2/opencv.hpp>
#include "sensor_msgs/Image.h"
#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.h"

void cameraCallback(const sensor_msgs::ImageConstPtr& ptr)
{
    cv_bridge::CvImagePtr cvPtr;
    try {
        cvPtr = cv_bridge::toCvCopy(ptr, sensor_msgs::image_encodings::BGR8);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
    cv::imshow("color_camera", cvPtr->image);
    cv::waitKey(1);
    return;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "show_color_camera");
    ros::NodeHandle nodeHandle;
    image_transport::ImageTransport imageTransport(nodeHandle);
    image_transport::Subscriber subscriber = imageTransport.subscribe("/camera/color/image_raw", 1000, cameraCallback);
    ros::spin();

    return 0;
}
