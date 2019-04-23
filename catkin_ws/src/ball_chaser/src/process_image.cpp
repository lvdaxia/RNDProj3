#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget srv;
    srv.request.angular_z = ang_z;
    srv.request.linear_x = lin_x;
    if(!client.call(srv)){
        ROS_ERROR("Failed client call in process_image");
    } 
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
    bool stop_driving = true;
    int white_pixel = 255;
    int pixel_count = img.height*img.width;
    for(int pixel = 0; pixel < pixel_count; pixel++){
        // ROS_INFO("%i", img.data[pixel]);
        // TODO: Need to evaluate based on the averages of the pixels, not just the value of a single pixel
        // TODO: Need to fix the turn right portion of the code as it is not functioning properly

        if(img.data[3 * pixel] == 255 && img.data[(3*pixel) + 1] == 255 && img.data[(3*pixel) + 2] == 255){
            int row = pixel/img.width;
            int col = pixel%img.width;
            ROS_INFO("Pixel found in pixel:[%i][%i]", row, col);
            ROS_INFO("Pixel:[%i]", pixel);
            if(col < img.width*0.3333f){
                ROS_INFO("Turning Right");
                drive_robot(-0.5f, 0);
                stop_driving = false;
            }
            else if((col > img.width* 0.33333f) && (col < img.width* 0.66666f)){
                ROS_INFO("Driving Straight");
                drive_robot(0, -5.0f);
                stop_driving = false;
            }
            else{
                ROS_INFO("Turning Left");
                drive_robot(0.5f, 0);
                stop_driving = false;
            }
            break;
        }
    }
    if(stop_driving == true){
        drive_robot(0.0, 0.0);
    }

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}