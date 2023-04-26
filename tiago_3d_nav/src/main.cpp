//
// Created by haozhe on 19.01.23.
//

#include <ros/ros.h>
#include "tiago_3d_nav/scan_pc.h"

using namespace tiago_3d_nav;

int main(int argc, char** argv){
    ros::init(argc, argv, "integral_optical_sensor");
    ros::NodeHandle nh("/");
    ScanPC scanPC(nh);

    scanPC.start();
}