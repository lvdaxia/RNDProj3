// ! Copy the code from Udacity template, then determine what is needed to make it work properly with minimal work. Past work is left in
// ! the drive_bot_jared.cpp file.
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"
//TODO: Include the ball_chaser "DriveToTarget" header file

// ROS::Publisher motor commands;
// ros::Publisher motor_command_publisher;
ros::Publisher chase_pub;
ros::Subscriber chase_sub;
ros::Publisher left_wheel_pub, right_wheel_pub;

// TODO: Create a handle_drive_request callback function that executes whenever a drive_bot service is requested
bool handle_drive_request_callback(ball_chaser::DriveToTarget::Request &req, ball_chaser::DriveToTarget::Response &res){
        // Create a motor_command object of type geometry_msgs::Twist
        
        // ROS_INFO("handle_drive_request_callback executed");
        geometry_msgs::Twist motor_command;
        // Set wheel velocities, forward [0.5, 0.0]
        motor_command.linear.x = req.linear_x;
        motor_command.angular.z = req.angular_z;

        chase_pub.publish(motor_command);

        // Publish angles to drive the robot
        // motor_command_publisher.publish(motor_command);
        res.msg_feedback = "Sent - linear x: " + std::to_string(req.linear_x) + "- angular_z: " + std::to_string(req.angular_z); 
        // ROS_INFO_STREAM(res.msg_feedback);
        return true;
}
// This function should publish the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities

int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    // motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot", handle_drive_request_callback);
    chase_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 100);
    // chase_sub = n.subscribe("/ball_chaser/command_robot", 10, handle_drive_request_callback);

    // TODO: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function

    // TODO: Delete the loop, move the code to the inside of the callback function and make the necessary changes to publish the requested velocities instead of constant values
    // while (ros::ok()) {
    //     // Create a motor_command object of type geometry_msgs::Twist
    //     // geometry_msgs::Twist motor_command;
    //     // // Set wheel velocities, forward [0.5, 0.0]
    //     // motor_command.linear.x = 0.5;
    //     // motor_command.angular.z = 0.0;
    //     // // Publish angles to drive the robot
    //     // motor_command_publisher.publish(motor_command);
    // }

    // TODO: Handle ROS communication events
    ros::spin();
    ROS_INFO("drive_bot ready to receive messages");

    return 0;
}