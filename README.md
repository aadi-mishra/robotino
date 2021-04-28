# Robotino mBot

The repository contains the directories:
1. __robotino_arduino__ : Includes source code for running ros_nodes on Arduino Mega.
2. __robotino_ros__ : Includes high level applications.

## 1. Setting up
* Clone the repository to your computer.
* Clone the compatible [rosserial](https://github.com/aadi-mishra/rosserial.git) to your catkin_ws and compile.
    ### Arduino End
    * Copy the files under '__robotino_arduino__ to your arduino sketch libraries. And load the sketch to your arduino.

    ### ROS End
    * Move the __robotino_ros__ folder to your catkin_ws and compile.

* Open bashrc and add following lines then source. 
    * `export ROS_IP=134.28.45.113`
    * `export ROS_MASTER_URI=http://<Your IP adadress>:11311`

* Connect the arduino/robot with the companion computer. 


## 2. Running the program
* Once you have done the setup and everything works smooth. Call `rosocore` in a terminal.
* Now in a separate terminal run the following. Make sure you have permissions to access the port.
    * `rosrun rosserial_python serial_node.py /dev/ttyACM0 _baud:=115200` 
* Then run the following
    * `roslaunch robotino_ros robot.launch`
* Finally, run
    * `rosrun robotino_ros teleop_twist_keyboard.py` 
* Robot can now be controlled using teleop.







