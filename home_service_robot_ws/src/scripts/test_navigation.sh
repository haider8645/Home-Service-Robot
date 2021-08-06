#!/bin/sh

xterm  -e "roslaunch my_robot world.launch" &
sleep 5

xterm  -e "roslaunch where_am_i amcl.launch" &
sleep 5

xterm  -e "roslaunch my_robot view_navigation.launch"
sleep 5

