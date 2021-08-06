#include <ros/ros.h>
#include <visualization_msgs/Marker.h>


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers_test");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

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
  marker.ns = "add_markers_test";
  marker.id = 0;
  marker.type = shape;
  marker.lifetime = ros::Duration();
  ros::Duration(5.0).sleep();
  marker.action = visualization_msgs::Marker::ADD;
  marker.pose.position.x = 3;
  marker.pose.position.y = -2;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0;
  marker.pose.orientation.y = 0;
  marker.pose.orientation.z = 0;
  marker.pose.orientation.w = 1;
  marker_pub.publish(marker);
  ROS_INFO("Marker is at the pick up location!");

  ros::Duration(5.0).sleep();
  marker.action = visualization_msgs::Marker::DELETE;
  marker_pub.publish(marker);
  ROS_INFO("Marker is picked up!");

  ros::Duration(5.0).sleep();
  marker.pose.position.x = 0;
  marker.pose.position.y = 0;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0;
  marker.pose.orientation.y = 0;
  marker.pose.orientation.z = 0;
  marker.pose.orientation.w = 1;
  marker.action = visualization_msgs::Marker::ADD;
  marker_pub.publish(marker);
  ROS_INFO("Marker is now at the target position!");
  ros::Duration(5.0).sleep();
}
