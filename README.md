# Home Service Robot based on ROS

## Problem Statement

> The goal of this project was to combine mapping, localization, navigation, and planning of a mobile robot into one project. The mobile robot is a differential wheeled robot. In order to function as a home service robot, the robot has to be able to map its environment using the available sensors, afterwards it should find its own position in the home. After it is able to localize itself, it has to plan a feasible path to a pick up point. From the pick up point, the robot has to pick up an object and deliver the object to a drop off point.

## Home Environment
>![home](https://user-images.githubusercontent.com/23505408/128580977-c23170ec-c2b1-4e5e-989b-40dfc0083957.png)


## Robot Model

> The robot was modeled by setting up a URDF file. A picture of the model is shown below:
> ![Robot](https://user-images.githubusercontent.com/23505408/128578658-9536e3c5-3a44-4600-9951-eaee33704692.png)

## Sensors
The robot is equipped with Lidar and a RGBD Kinect camera.
> The Lidar sensor is mounted at the top of the robot\
> The camera sensor is mounted in the front facing side of the robot

## Software Dependencies
The project was performed using ROS Kinetic and the following packages are required as dependencies

[Gmapping](http://wiki.ros.org/gmapping)
> Gmapping was used to create a 2D map of the home environment. The package uses the information from the Lidar sensor to create an occupancy grid map. The robot was navigated manually in the home environment using a teleop ROS package.

[turtlebot_teleop](http://wiki.ros.org/turtlebot_teleop)
> This package enables to control a mobile robot using a joystick or the keyboard. For this project only the keyboard was used to manually navigate the robot.

[move_base](http://wiki.ros.org/move_base)
> ROS move_base offers a navigation stack for a mobile base. It comes with build in local and global planners. You can choose to use one of the available planners or integrate any external planner that is compatible with the move_base interface.
>
> **Localization**: For localization the Adaptive Monte Carlo Localization (AMCL) was used. This algorithm is also known as a particle filter. It requies a map of the environment and creates random states or particles in the entire map. As the robot senses the environment, the particles are gradually filtered out based on the actual sensor readings. The final result of localization is to have only those particles left in the environment that estimate closely the actual pose of the mobile robot in the known map.
>
> **Global Planner**: Move_base offers two options A* and Dijkstra's as a global planner. For this project the Dijkstra's planner was used to plan global paths. 
>
> **Local Planner**: The DWA local planner was used to find tactical solutions for local trajectory following.

## Scripts
The project offers a number of scripts to test out different components

### SLAM: test_slam.sh
> You can use the test_slam.sh script in order to manually navigate the environment using the teleop package. The resulting map can be saved as a 2D map using the map_server package.\
> 
> ![Mapping - SLAM](https://user-images.githubusercontent.com/23505408/128580236-ff936162-3f69-4282-93fa-345396795a95.png)
> ![map](https://user-images.githubusercontent.com/23505408/128580979-5cdaddea-d6bd-461c-878a-54912084f00d.png)

### Navigation: test_navigation.sh
> To test out the navigation using AMCL, Map, and Move base use the script test_navigation.sh. In the picture below, you can see that the robot was commanded to go to a target position using the 2D Nav Goal in RViz. The red arrows are the particles from AMCL estimating the robot pose in the map. The close proxity of the particles to the actual robot pose show that the AMCL is able to accurately localize the robot in the map.\
>![navigation](https://user-images.githubusercontent.com/23505408/128580336-d49b7f54-57c6-42a3-b2ff-462f02adeeff.png)

### Visualization Markers: add_marker.sh
> RViz offers us the capability to add virtual objects or markers to our environment. The green marker box can be seen added to simulated environment in the picture below. Additionally notice the particle filters in this picture as well. The picture was taken before AMCL had a chance to filter our unnecessary particles. The accuracy of the particles gets better as the robot moves and gathers sensor data from the environment.\
>![marker](https://user-images.githubusercontent.com/23505408/128580633-aebec907-0e0e-4846-b98c-ed0f9f5842ba.png)

### Pick Up Object: pick_objects.sh
> This script executes the navigation and planning components of the robot to take it to multiple goal positions. The path to the goal positions is planned using the global planner and the local planner is used to follow the generated path

### Home Service Robot: home_service.sh
> The final script combines all of the concepts mentioned above. The robot is commanded to pick up an object from a pick up point and afterwards it has to deliver the object to a drop off point. This two step process requires mapping, planning, localization, and control of the mobile robot. 

#### Going to pick up location
>![1](https://user-images.githubusercontent.com/23505408/128580862-c354afba-2290-48aa-a0bd-6d6b7b607052.png)

#### Picked up the object
>![2](https://user-images.githubusercontent.com/23505408/128580863-908a6165-5f7f-4cae-ad38-67c44af58aac.png)\
>![3](https://user-images.githubusercontent.com/23505408/128580864-1c5276e3-2ccc-4413-bce8-2943298d68cf.png)

#### Dropped off the object
![4](https://user-images.githubusercontent.com/23505408/128580866-543ebed3-399a-4d70-85d1-ea936f3e9364.png)
