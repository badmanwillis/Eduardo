#include "mbed.h"
#include "rtos.h"
#include "Servo.h"
#include "ros.h"
#include <std_msgs/Float32.h>
#include <ros.h>
#include <std_msgs/Empty.h>
#include <sensor_msgs/JointState.h>

Serial pc(USBTX, USBRX);
ros::NodeHandle nh;

DigitalOut green(LED1); //Green LED Used to indicate when nucleo has finished executing a movement.
DigitalOut blue(LED2); //Blue LED Used to indicate that the robot is moving.
DigitalOut red(LED3); // Red LED

//Stepper Motors
DigitalOut rev_step(D4); // toggle high to step one increment. //D5 on my nucleo board has a jumper pin stuck in it.
DigitalOut rev_direction(D7); //1 for forwards, 0 for backwards
DigitalOut pris_step(D6);
DigitalOut pris_direction(D8); //1 for forwards, 0 for backwards

//Servo Motors
Servo elbow(D11);
Servo wrist(D10);
Servo hand(D9);

// Flex sensor
AnalogIn   flex_A0(A0);
AnalogIn   flex_A1(A1);
float flex_delta;
float flex_total;
float flex_1;
float flex_2;
float flex_3;
float flex_4;
float flex_5;
float flex_6;
float flex_7;
float flex_8;
float flex_9;
float flex_10;


// goal positions for Servo motors, to be set by the joint_states publisher.
float elbow_goal;
float wrist_goal;
float hand_goal;


// goal positions for Stepper motors, to be set by the joint_states publisher.
int revolute_goal;
int prismatic_goal;

// Current stepper positions
int revolute_pos;
int prismatic_pos;

Thread thread;

void messageCb(const std_msgs::Empty& toggle_msg);
void messageCb1(const std_msgs::Empty& toggle_msg);

ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb);
ros::Subscriber<std_msgs::Empty> sub1("toggle_execute", &messageCb1);
std_msgs::Float32 flex_msg;
ros::Publisher flex("flex", &flex_msg);

 
void ros_thread() {
    while (true) {
        //red = !red;
        //Thread::wait(1000);
        nh.spinOnce();
        Thread::wait(1);
    }
}

// callback messages: Toggle LED
void messageCb(const std_msgs::Empty& toggle_msg){
    green= !green;   // blink the led
}
// callback messages: EXECUTE
int execute = 0;
void messageCb1(const std_msgs::Empty& toggle_msg){
    execute = 1;
    
    green = !green;   // blink the led
}





int main() {
    
    // ROS setup
    nh.initNode();
    pc.baud (115200);
    nh.subscribe(sub);
    nh.subscribe(sub1);
    nh.advertise(flex);
    thread.start(ros_thread);
    
    // initialise stepper positions to 0
    prismatic_pos =0;
    revolute_pos =0;
    //initialise servo positions to 0
    elbow   =0.5;
    wrist   =0.5;
    hand    =0.7;
    
    int step_rate = 1; // the wait time, in us. Essentially speed control for all motors.
    
    // TESTING goal positions
    prismatic_goal  =4000;
    revolute_goal   =0;
    elbow_goal      =0.5;
    wrist_goal      =0.5;
    hand_goal       =0.7;
    
    // Servo goal tolerances
    float elbow_plus = elbow_goal + 0.01f;
    float elbow_minus = elbow_goal - 0.01f;
    
    float wrist_plus = wrist_goal + 0.01f;
    float wrist_minus = wrist_goal - 0.01f;
    
    float hand_plus = hand_goal + 0.01f;
    float hand_minus = hand_goal - 0.01f;
    
    // Flex sensor upper and lower thresholds (too much force, too little force)
    float flex_high =  0.002;
    float flex_low = 0.001;
    
    
    
    while(1){
        

        while (execute == 1) {
            
            // FLEX SAMPLING
            flex_1 = flex_A0 - flex_A1;
            Thread::wait(1);
            flex_2 = flex_A0 - flex_A1;
            Thread::wait(1);
            flex_3 = flex_A0 - flex_A1;
            Thread::wait(1);
            flex_4 = flex_A0 - flex_A1;
            Thread::wait(1);
            flex_5 = flex_A0 - flex_A1;
            Thread::wait(1);
            flex_6 = flex_A0 - flex_A1;
            Thread::wait(1);
            flex_7 = flex_A0 - flex_A1;
            Thread::wait(1);
            flex_8 = flex_A0 - flex_A1;
            Thread::wait(1);
            flex_9 = flex_A0 - flex_A1;
            Thread::wait(1);
            flex_10 = flex_A0 - flex_A1;
        
            
            flex_total = flex_1 + flex_2 + flex_3 + flex_4 + flex_5 + flex_6 + flex_7 + flex_8 + flex_9 + flex_10;
            flex_delta = flex_total / 10;
            
            flex_delta = fabs(flex_delta);
            
            if(flex_delta < flex_low){
                // TO LOW
                red=1;
                blue=0;
                elbow = elbow - 0.003f;
                wait_ms(step_rate);
                red=0;
            } else if(flex_delta > flex_high){
                // TOO HIGH
                red=0;
                blue=1;
                elbow = elbow + 0.003f;
                wait_ms(step_rate);
                blue = 0;
            }
            

            // Check all motors have reached goal positions. IDGAF about how long the condition statement is.
            if(prismatic_pos == prismatic_goal){
                // goal reached
                green = 0;
                execute = 0;
                
                //reset positions, may not be needed with moveit intergration.
                prismatic_pos = 0;
                revolute_pos = 0;
            }  
            
            /*
            // ELBOW
            if(elbow < elbow_goal){
                blue=1;
                elbow = elbow + 0.01f;
                wait_us(step_rate);
                blue=0;
            } else if(elbow > elbow_goal){
                blue=1;
                elbow = elbow - 0.01f;
                wait_us(step_rate);
                blue=0;
            }
            */
           
            
            // PRISMATIC
            if(prismatic_pos < prismatic_goal){
                // step fwd 1
                pris_direction = 1;
                
                // STEP
                blue=1;
                pris_step = 1;
                wait_us(step_rate);
                blue=0;
                pris_step = 0;
                wait_us(step_rate);
                // Increment current position
                prismatic_pos +=1;
                 
            } else if(prismatic_pos > prismatic_goal){
                // step back 1
                pris_direction = 0;
                
                // STEP
                blue=1;
                pris_step = 1;
                wait_us(step_rate);
                blue=0;
                pris_step = 0;
                wait_us(step_rate);
                // Decrement current position
                prismatic_pos -=1;
                
            } else if(revolute_pos == revolute_goal){
                // to keep the speeds roughly the same
                wait_us(step_rate);
                wait_us(step_rate);
            }
            
        }
    }
    
}

