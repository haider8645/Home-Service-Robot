#!/bin/sh

xterm  -e "roslaunch my_robot world.launch" &
sleep 5

xterm  -e "roslaunch my_robot gmapping_Haider.launch" &
sleep 5

xterm  -e "roslaunch my_robot view_navigation.launch" &
sleep 5

xterm  -e "roslaunch my_robot keyboard_teleop.launch" 
sleep 5

