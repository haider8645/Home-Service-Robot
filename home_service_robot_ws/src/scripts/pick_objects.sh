#!/bin/sh


# launch world.launch to deploy my robot in the environment
xterm -e  "roslaunch my_robot world.launch"  &
sleep 5

# launch amcl.launch for localization done in the Where Am I project
xterm -e  "roslaunch where_am_i amcl.launch" &
sleep 5

xterm  -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5

xterm  -e "roslaunch pick_objects pick_objects.launch" 
sleep 5

