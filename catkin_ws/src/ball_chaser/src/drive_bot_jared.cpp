#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <std_msgs/Float64.h>

//TODO: Include the ball_chaser "DriveToTarget" header file
#include "ball_chaser/DriveToTarget.h"

//ROS::Publisher motor commands
ros::Publisher linear_x_pub, angular_z_pub;
ros::ServiceClient client;


// TODO: Create a handle_drive_request callback function that executes 
// whenever a drive_bot service is requested. This function should publish 
// the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should be 
// returned with the requested wheel velocities
bool handle_drive_request_callback(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res){
    // TODO: Figured out how to get the service call up and running, solved issue around sending data
    // TODO: Figure out what joints I should be sending this data to other than /cmd/vel
    ROS_INFO("DriveToTargetRequest Received - linear_x: %1.2f, angular_z: %1.2f", (float) req.linear_x, (float)req.angular_z);
    std_msgs::Float64 linear_x, angular_z;
    linear_x.data = req.linear_x;
    angular_z.data = req.angular_z;

    linear_x_pub.publish(linear_x);
    angular_z_pub.publish(angular_z);
    res.msg_feedback = "joint angles set to - linear_x: " + std::to_string(linear_x.data) + "angular_z: " + std::to_string(angular_z.data);
    ROS_INFO_STREAM(res.msg_feedback);
    return true;

}

int main(int argc, char** argv){
    ROS_WARN("Entered main in drive_bot");
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    //Create a ROS NodeHandle object
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of
    // type geometry_msgs::Twist on the robot actuation topic with a
    // publishing queue size of 10
    linear_x_pub = n.advertise<std_msgs::Float64>("/ball_chaser/command_robot", 10);
    angular_z_pub = n.advertise<std_msgs::Float64>("/ball_chaser/command_robot", 10);
    // TODO: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function
    // client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
    ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot", handle_drive_request_callback); 
    motor_command_publisher = n.advertise<std_msgs::Float64>("Something here", 10f);

    // ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot", handle_drive_request_callback);
    // TODO: Delete the loop, move the code to the inside of the callback function
    // and make the necessary changes to publish the requested velocities instead of constant values

    // ! It appears that I'm thoroughly lost on what I should be doing. I had assumed that I needed to move the wheels
    // ! of the robot individually, but it looks as if I should be using command velocity call and calculating the 
    // ! required wheel rotation speed to make the velocity functionally correct. I'll need to look into this more tomorrow.
    // ! I'll likely need to recopy the while loop section as well as the advertise section to have the robot function as desired
    
    while(ros::ok){
        // Create a motor_command object of type geometry_msgs::Twist
        geometry_msgs::Twist motor_command;
        
        // Set wheel velocities, forward [0.5, 0.5]
        motor_command.linear.x = 0.5;
        motor_command.angular.z = 0.0;
        // Publish angles to drive the robot
        motor_command_publisher.publish(motor_command);
    }
    // TODO: Handle ROS communication events
    ROS_INFO("Ready to send motor commands");
    ros::spin();
    
    return 0;
}
