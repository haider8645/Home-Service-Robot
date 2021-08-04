#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <move_base_msgs/MoveBaseAction.h>
#include "std_msgs/String.h"

move_base_msgs::MoveBaseGoal goal;

std_msgs::String goal_state;

void goalStateCallback(const std_msgs::String msg)
{
  goal_state = msg;
}

void goalReceivedCallback(const move_base_msgs::MoveBaseGoal new_goal)
{
  ROS_INFO("Goal position received");
  goal = new_goal;
}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber sub1 = n.subscribe("goal", 10, goalReceivedCallback);
  ros::Subscriber sub2 = n.subscribe("goal_reached", 10, goalStateCallback);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.2;
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();
    marker.ns = "add_markers";
    marker.id = 0;
    marker.type = shape;
    marker.lifetime = ros::Duration();

    if (goal_state.data.compare("goal sent 0") == 0){
        marker.action = visualization_msgs::Marker::ADD;
    	marker.pose.position.x = goal.target_pose.pose.position.x;
    	marker.pose.position.y = goal.target_pose.pose.position.y;
    	marker.pose.position.z = goal.target_pose.pose.position.z;
    	marker.pose.orientation.x = goal.target_pose.pose.orientation.x;
    	marker.pose.orientation.y = goal.target_pose.pose.orientation.y;
    	marker.pose.orientation.z = goal.target_pose.pose.orientation.z;
    	marker.pose.orientation.w = goal.target_pose.pose.orientation.w;
        marker_pub.publish(marker);
        ROS_INFO("Going to pick up the marker!");
    }

    else if (goal_state.data.compare("second goal reached") == 0){	
        marker.action = visualization_msgs::Marker::ADD;
    	marker.pose.position.x = goal.target_pose.pose.position.x;
    	marker.pose.position.y = goal.target_pose.pose.position.y;
    	marker.pose.position.z = goal.target_pose.pose.position.z;
    	marker.pose.orientation.x = goal.target_pose.pose.orientation.x;
    	marker.pose.orientation.y = goal.target_pose.pose.orientation.y;
    	marker.pose.orientation.z = goal.target_pose.pose.orientation.z;
    	marker.pose.orientation.w = goal.target_pose.pose.orientation.w;
        marker_pub.publish(marker);
        ROS_INFO("Dropped off the marker at the target location!");
     }
    else if (goal_state.data.compare("first goal reached") == 0){
        marker.action = visualization_msgs::Marker::DELETE;
        marker_pub.publish(marker);
    	ROS_INFO("Picked up the marker!");
    }
    r.sleep();
    ros::spinOnce();
  }
}
