/** @ package exp_rob_lab
* 
*  \file go_to_waypoint.cpp
*  \brief implements the go_to_waypoint action
*
*  \author Jacopo Ciro Soncini
*  \version 1.0
*  \date 28/08/2022
*  \details
*   
*  Subscribes to: <BR>
*	None
*
*  Publishes to: <BR>
*	None
*
*  Services: <BR>
*    None
* 
*  Client Services: <BR>
*    None
*    
*  Action Services: <BR>
*    /reaching_goal
*
*  Description: <BR>
*  This program implements the real action to be completed when the planner dispatches the action go_to_waypoint.
*/

#include "exp_rob_lab/InterfaceAction.h"
#include <unistd.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <motion_plan/PlanningAction.h>
#include <math.h>

namespace KCL_rosplan{
    Go_To_PointInterface::Go_To_PointInterface(ros::NodeHandle &nh){
    }
/**
 * \brief: Go_to_pointInterface callback
 * \param msg : rosplan_dispatch_msgs::ActionDispatch, variables received from the plan dispatcher
 * 
 * \return True
 * 
 * This function implements the behaviour for the robot when the planner dispatches
 * the action go_to_waitpoint. Initializes and publishes to the /reaching_goal action service.
 */
    bool Go_To_PointInterface::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg){

        actionlib::SimpleActionClient<motion_plan::PlanningAction>  client("/reaching_goal", true);
        motion_plan::PlanningGoal target;
        client.waitForServer();
        std::cout << "Reaching "<<msg->parameters[1].value << "from" << msg->parameters[0].value <<std::endl;
        
        if(msg->parameters[1].value == "wp0")
            {
                target.target_pose.pose.position.x = 2.7;
                target.target_pose.pose.position.y = 0.0;
                target.target_pose.pose.orientation.w= -M_PI/2;
            }
        else if(msg->parameters[1].value == "wp1")
            {
                target.target_pose.pose.position.x = 0.0;
                target.target_pose.pose.position.y = 2.7;
                target.target_pose.pose.orientation.w= 0.0;
            }
        else if(msg->parameters[1].value == "wp2")
            {
                target.target_pose.pose.position.x = -2.7;
                target.target_pose.pose.position.y = 0.0;
                target.target_pose.pose.orientation.w= M_PI/2;
            }
        else if(msg->parameters[1].value == "wp3")
            {
                target.target_pose.pose.position.x = 0.0;
                target.target_pose.pose.position.y = -2.7;
                target.target_pose.pose.orientation.w= M_PI;
            }
        else
            {
                std::cout << "out of bound" << std::endl ;
            }
        client.sendGoal(target);
        client.waitForResult();
        ("Action(%s) performed!", msg->name.c_str());
        return true;
    }
}
/**
 * \brief: Main function
 * \param msg : None
 * 
 * \return 0
 * 
 * This function implements the main function.
 */

int main(int argc, char **argv){
    ros::init(argc, argv, "go_to_waypoint", ros::init_options::AnonymousName);
    ros::NodeHandle nh("~");
    KCL_rosplan::Go_To_PointInterface act(nh);
    act.runActionInterface();
    return 0;
}