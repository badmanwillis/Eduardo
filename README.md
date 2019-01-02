# Eduardo
Eduardo the hair combing robot. A University of Plymouth MEng Robotics ROCO504 project.

Olly Smith and Sam White 2018. Module lead by Martin F Stoelen.

## About Eduardo

People with temporary or permanent disabilities often struggle to perform daily tasks, and as a result, this loss of agency can cause undue emotional distress. For this project, we present “Eduardo”; a prototype robot arm designed with the intention of returning autonomy to the user. In particular, we utilise a passive compliant element in the end effector of the arm, to greatly simplify the control of the arm, and ensure the safety of the user during physical interaction. As a demonstration of the prototype, we have programmed the arm to comb hair, although we envision a wider range of potential applications.

From our research, this may well be the first prototype of assistive robot that features a passive compliant end effector. It was built in under three months, by two people, on a budget of £70. As a result, shortcuts were taken for the sake of creating a functioning prototype, and much of the work here does not adhere to best practices.

## ROS packages

The software was developed on a Ubuntu 16.04 LTS machine,using ROS-Kinetic. You'll need to setup a catkin workspace, and put the packages into the src folder.

#### setup
[Creating a Catkin Workspace](http://wiki.ros.org/catkin/Tutorials/create_a_workspace)

In the terminal:
 
create the folders
> mkdir -p ~/eduardo_ws/src

navigate to the root folder
> cd ~/eduardo_ws/

make the workspace using the catkin_make command
> catkin_make

### sam

This package features the Fusion360 stl files for the the arm links, as well as the samcad.urdf (Universal Robot Description Format) file. It can be used to visualize the arm in Rviz, and control the joints via GUI sliders.

#### usage
Navigate to your workspace

> cd ros_ws

Source your workspace

> source devel/setup.bash

run the demo

> roslaunch sam arm_display.launch 

Wait for Rviz to load, then use the joint_state_publisher window sliders to play about with the arm.

### sam_moveit_config

The moveit! configuration package for the samcad.urdf. Unfortunatley it doesn't support path planning right now, as the deafult kinematics solvers only support 6DOF arms. I've tried adding a dummy link, which should fix the issue with a bit more work.

#### usage
Navigate to your workspace

> cd ros_ws

Source your workspace

> source devel/setup.bash

run the demo

> roslaunch sam_moveit_config demo.launch

Wait for Rviz to load, tick the "Allow Approx IK Solutions" option in the Planning tab. Drag the arm Query Start State and Query Goal State (found under Planning Request), and use the commands within the Planning tab to have moveit perform path planning and simulate the arms movement.

## Motor control code

Nuceleo 

#### simple combing demonstration

For the demonstration day accasaaxsv

