#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt
import rospy
from nav_msgs.msg import OccupancyGrid


def callback(data):
    rospy.loginfo("new data ==============================")
    rospy.loginfo(data)
    rospy.loginfo("data size")
    rospy.loginfo(len(data.data))

    map = np.array(data.data)
    map = map.reshape((160, 160))
    rospy.loginfo(map)

    # dx, dy = 0.025, 0.025
    #
    # x = np.arange(-160.0, 160.0, dx)
    # y = np.arange(-160.0, 160.0, dy)
    # X, Y = np.meshgrid(x, y)

    fig = plt.figure(frameon=False)
    plt.imshow(map)
    cax = plt.axes([0.85, 0.1, 0.075, 0.8])
    plt.colorbar(cax=cax)
    plt.show()


def listener():
    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber("/move_base/local_costmap/costmap", OccupancyGrid, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()


if __name__ == '__main__':
    listener()