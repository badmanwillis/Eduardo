# Eduardo
Eduardo the hair combing robot. An assistive robot arm prototype featuring a passive compliant end effector. A University of Plymouth MEng Robotics ROCO504 project.

Olly Smith and Sam White 2018. Module lead by Martin F Stoelen.

## About Eduardo

People with temporary or permanent disabilities often struggle to perform daily tasks, and as a result, this loss of agency can cause undue emotional distress. For this project, we present “Eduardo”; a prototype robot arm designed with the intention of returning autonomy to the user. In particular, we utilise a passive compliant element in the end effector, to greatly simplify the control of the arm, and ensure the safety of the user during physical interaction. As a demonstration of the prototype, we have programmed the arm to comb hair, although we envision a wider range of potential applications.

From our research, this may well be the first prototype of assistive robot that features a passive compliant end effector. It was built in under three months, by two people, on a budget of £70. As a result, shortcuts were taken for the sake of creating a functioning prototype, and much of the work here does not adhere to best practices.

Sam White was responsible for the design and manufacture of the arm. This was his first project attempted using Fusion360. Parts were rapidly protoyped and developed iterativley, through 3D printing. Additional work included parts procurement, sensor testing, and building a wheatstone bridge for the flex sensor.

Olly Smith was responsible for the ROS software and c++ microcontroller code for the arm. This was his first project attempted using ROS. Addtional work included advising Sam on designing parts for 3D printing - having built an ANET A8, creating a custom control board for the stepper drivers and servo power rails.

Finally, the robot arm itself lends itself to further use as a development platform at the university for research projects. The large workspace (including the vertical prismatic element of the pedestal), well executed construction of the arm using low cost components, and open source software, makes the arm a viable candidate for students to use in their own research projects, continuing the research we present, and for their own ideas.


## ROS packages

The software was developed on a Ubuntu 16.04 LTS machine,using ROS-Kinetic. You'll need to setup a catkin workspace, and put the packages into the src folder.

#### Setup a workspace
[Creating a Catkin Workspace](http://wiki.ros.org/catkin/Tutorials/create_a_workspace)

Open a terminal (should default to the home directory):
 
create the folders
> mkdir -p ~/eduardo_ws/src

navigate to the root folder
> cd ~/eduardo_ws/

make the workspace using the catkin_make command
> catkin_make

#### Add the packages
[Creating a ROS Package](http://wiki.ros.org/catkin/Tutorials/CreatingPackage)

Move the two folders "sam" and "sam_moveit_config" into the src folder.

Make sure you are still in the root folder "eduardo_ws" using the "cd" and "cd .." commands

re-build the workspace

> catkin_make

"source the workspace". This means adding the workspace to the ROS enviroment by sourcing the generated setup file.

> source devel/setup.bash 

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

The [moveit!](https://moveit.ros.org/) configuration package for the samcad.urdf. Unfortunatley it doesn't support path planning right now, as the deafult kinematics solvers only support 6DOF arms. I've tried adding a dummy link, which should fix the issue with a bit more work.

#### usage
Navigate to your workspace

> cd ros_ws

Source your workspace

> source devel/setup.bash

run the demo

> roslaunch sam_moveit_config demo.launch

Wait for Rviz to load, tick the "Allow Approx IK Solutions" option in the Planning tab. Drag the arm Query Start State and Query Goal State (found under Planning Request), and use the commands within the Planning tab to have moveit perform path planning and simulate the arms movement.

## Motor control code

A [ST-Nucleo-F429ZI Microcontroller](https://os.mbed.com/platforms/ST-Nucleo-F429ZI/) was used to control the stepper and servo motors, as well as read the the flex sensor value.

### Legit code

### Hacky code

#### Simple combing demonstration

For the project showcase day a greatly simplified version of the code was run, to ensure a successful demonstration.
**_WARNING_ The arm will move to a starting position as soon as the microcontroller and PSU are on.**

In a terminal.
> roscore

Open a new terminal tab (Ctrl + shift + T). Then run the ros serial command to connect the Ubuntu machine to the Microcontroller. If you forgot to plug the microcontroller into the computer first, that's okay, I've done it as well.
> rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0 _baud:=115200

Have the arm execute a hard coded path
> rostopic pub toggle_execute std_msgs/Empty --once

#### Other useful commands
These have proven useful in development.

List the current ROS topics
> rostopic list

Print the updating values of the joints of the arm.
> rostopic echo joint_states

Generate a ROS computation graph to visualize the topics and nodes.
> rqt_graph

## Further improvements
There is no shortage of improvements to be made to this project, and we hope to see the continued development of this arm in the future.

### Safety
- Add microswitches to the prismatic gantry and shoulder revolute joints as endstops. Like a 3D printer.
- Add padding to the arm itself, potentially with sensors or microswithces to detect a collision.
- Add a big red emergency stop button.

### Design and construction

### Control Software

### Fun ideas
