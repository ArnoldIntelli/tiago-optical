for testing on real robot:
1. source ros_master_122.sh
2. source /opt/pal/ferrum/setup.bash
3. source IROSA/tiago-optical/catkin_ws/devel/setup.bash

http://tiago-122c:8080/

for mapping:
1. rosrun map_server map_saver map:=/projected_map -f real_map
2. replace the nan in yaml with 0.0

for navigation:
1. rosrun rviz rviz -d `rospack find tiago_dual_2dnav`/config/rviz/advanced_navigation.rviz
2. 