#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "std_msgs/String.h"

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;
  ros::Publisher pub_goal_reached = n.advertise<std_msgs::String>("goal_reached", 10);
  ros::Publisher pub_goal         = n.advertise<move_base_msgs::MoveBaseGoal>("goal", 10);

  std_msgs::String _data;

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  std::vector<move_base_msgs::MoveBaseGoal> goals; 
	
  move_base_msgs::MoveBaseGoal first_goal;
  move_base_msgs::MoveBaseGoal second_goal;

  // Set up the frame parameters
  first_goal.target_pose.header.frame_id = "map";
  first_goal.target_pose.header.stamp = ros::Time::now();

  second_goal.target_pose.header.frame_id = "map";
  second_goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  first_goal.target_pose.pose.position.x = 1.0;
  first_goal.target_pose.pose.orientation.w = 1.0;

  second_goal.target_pose.pose.position.x = 2.0;
  second_goal.target_pose.pose.position.y = 1.0;
  second_goal.target_pose.pose.orientation.w = 1.0;

  goals.push_back(first_goal);
  goals.push_back(second_goal);

  for (int i{0}; i < goals.size(); ++i ){

  // Send the goal position and orientation for the robot to reach

  ROS_INFO("Sending goal: %d ",i);
  ac.sendGoal(goals.at(i));

  if (i == 0){
        _data.data= "goal sent 0";
  	pub_goal_reached.publish(_data); 
  }
  if (i == 1){
        _data.data= "goal sent 1";
  	pub_goal_reached.publish(_data); 
  }
  pub_goal.publish(goals.at(i));

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the base has reached the goal: %d", i);

    if (i == 0){
        _data.data= "first goal reached";
    	pub_goal_reached.publish(_data);
    }
    else if (i == 1){
        _data.data= "second goal reached"; 
    	pub_goal_reached.publish(_data);
    }
  }	
  else {
    ROS_INFO("The base failed to reach the goal: %d", i);
    _data.data= "goal not reached";
    pub_goal_reached.publish(_data); 
  }

  ros::Duration(5.0).sleep();

  }

  return 0;
}
