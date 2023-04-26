//
// Created by haozhe on 19.01.23.
//

#include "tiago_3d_nav/scan_pc.h"
#include <ros/ros.h>

using namespace tiago_3d_nav;

ScanPC::ScanPC(ros::NodeHandle nh) : nh(nh), rate(100)
{
    scanSub = nh.subscribe<sensor_msgs::LaserScan> ("/scan_raw", 100, &ScanPC::scanCallback, this);
    cameraSub = nh.subscribe<sensor_msgs::PointCloud2> ("/xtion/depth_registered/points", 100, &ScanPC::cameraCallback, this);
    pointCloudPublisher = nh.advertise<sensor_msgs::PointCloud2> ("/scan2pc", 100, false);
    mergedPointCloudPublisher = nh.advertise<sensor_msgs::PointCloud2> ("/merged_pc", 100, false);
    tfListener.setExtrapolationLimit(ros::Duration(0.1));


}

ScanPC::~ScanPC()
{

}

void ScanPC::scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan){
    sensor_msgs::PointCloud2 cloud;
//    projector.transformLaserScanToPointCloud("odom", *scan, cloud, tfListener);
    projector.projectLaser(*scan, cloud);
//    cloud.fields.pop_back();
//    cloud.fields[3].name = "rgb";
//    cloud.fields[3].offset = 16;
//    cloud.height = 480;
//    cloud.width = 640;
    ROS_INFO_STREAM("===============");
    ROS_INFO_STREAM(cloud.fields[3]);
    ROS_INFO_STREAM(typeid(cloud.fields[3]).name());
    ROS_INFO_STREAM("----------------");
    pointCloudPublisher.publish(cloud);
    mergedPointCloudPublisher.publish(cloud);
}

void ScanPC::cameraCallback(const sensor_msgs::PointCloud2::ConstPtr& camera){
    mergedPointCloudPublisher.publish(camera);
}
void ScanPC::start()
{
    while (ros::ok()){
        ros::spin();
        rate.sleep();
    }
}