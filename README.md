# Eduardo
Eduardo the hair combing robot. A University of Plymouth MEng Robotics ROCO504 project.

Olly Smith and Sam White 2018. Module lead by Martin F Stoelen.

## About Eduardo

People with temporary or permanent disabilities often struggle to perform daily tasks, and as a result, this loss of agency can cause undue emotional distress. For this project, we present “Eduardo”; a prototype robot arm designed with the intention of returning autonomy to the user. In particular, we utilise a passive compliant element in the end effector of the arm, to greatly simplify the control of the arm, and ensure the safety of the user during physical interaction. As a demonstration of the prototype, we have programmed the arm to comb hair, although we envision a wider range of potential applications.

From our research, this may well be the first prototype of assistive robot that features a passive compliant end effector. It was built in under three months, by two people, on a budget of £70. As a result, shortcuts were taken for the sake of creating a functioning prototype, and much of the work here does not adhere to best practices.

## ROS packages

You'll need to setup a catkin workspace, and put the packages into the src folder.

### sam

This package features the Fusion360 stl files for the the arm links, as well as the urdf (Universal Robot Description Format) file. It can be used to visualize the arm in Rviz, and control the joints via GUI sliders.

#### usage
Navigate to your workspace

> cd ros_ws

Source your workspace

> source devel/setup.bash

run the demo

> roslaunch sam arm_display.launch 

### sam_moveit_config

words here about the package

#### usage

