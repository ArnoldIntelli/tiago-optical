//
// Created by haozhe on 19.01.23.
//

#ifndef TIAGO_OPTICAL_SCAN_PC_H
#define TIAGO_OPTICAL_SCAN_PC_H

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <laser_geometry/laser_geometry.h>
#include <pcl_ros/transforms.h>
#include <pcl_ros/point_cloud.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

namespace tiago_3d_nav {
    class ScanPC {
    public:
        ScanPC(ros::NodeHandle nh);
        ~ScanPC();
        void start();
    protected:
        laser_geometry::LaserProjection projector;
        tf::TransformListener tfListener;

        ros::Publisher pointCloudPublisher;
        ros::Publisher  mergedPointCloudPublisher;
        ros::Subscriber scanSub;
        ros::Subscriber cameraSub;

        typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::PointCloud2, sensor_msgs::PointCloud2> MySyncPolicy;

//        message_filters::Subscriber<sensor_msgs::PointCloud2> pointcloudSubscriber1;
//        message_filters::Subscriber<sensor_msgs::PointCloud2> pointcloudSubscriber2;
//        message_filters::Synchronizer<MySyncPolicy> sync;

        void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan);
        void cameraCallback(const sensor_msgs::PointCloud2::ConstPtr& camera);
//        void mergeCallback(const sensor_msgs::PointCloud2::ConstPtr &msg1, const sensor_msgs::PointCloud2::ConstPtr &msg2);
    private:
        ros::NodeHandle nh;
        ros::Rate rate;
    };
}

#endif //TIAGO_OPTICAL_SCAN_PC_H
