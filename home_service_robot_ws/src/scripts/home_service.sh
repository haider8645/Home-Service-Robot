#!/bin/sh

#source /opt/ros/kinetic/setup.bash
#source $(pwd)/../..devel/setup.bash
#source /home/robond/ROS/Home-Service-Robot/home_service_robot_ws/devel/setup.bash 

xterm  -e "roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5

xterm  -e "roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5

xterm  -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5

xterm  -e "roslaunch add_markers add_markers.launch" &
sleep 5

xterm  -e "roslaunch pick_objects pick_objects.launch" 
sleep 5
