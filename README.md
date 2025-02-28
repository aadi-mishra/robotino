# Robotino mBot

The repository contains the directories:
1. __robotino_arduino__ : Includes source code for running ros_nodes on Arduino Mega.
2. __robotino_ros__ : Includes high level applications.

## 1. Setting up
* Clone the repository to your computer.
* Clone the compatible [rosserial](https://github.com/aadi-mishra/rosserial.git) to your catkin_ws and compile.
    ### Arduino End
    * Copy the files under '__robotino_arduino__ to your arduino sketch libraries.
    * Open `robotino_arduino_IO` on your adrduino IDE and burn the sketch to your board (Currently supported Arduino MEGA only).

    ### ROS End
    * Move the __robotino_ros__ folder to your catkin_ws and compile.

* Open bashrc and add following lines then source. 
    * `export ROS_IP=http://<Your IP adadress>`
    * `export ROS_MASTER_URI=http://<Your MASTER(Robotino) IP adadress>:11311`

* Connect the arduino/robot with the companion computer. 


## 2. Running programs on Robotino
* SSH into Robotino from your companion computer as `ssh nvidia@134.28.45.77`
* Once you have done the setup and everything works smooth. Call `roscore` in a terminal.
* Now in a separate terminal run the following. Make sure you have permissions to access the port.
    * `rosrun rosserial_python serial_node.py /dev/ttyACM0 _baud:=115200` 
* Then run the following
    * `roslaunch robotino_ros robotino.launch`
* Finally, run
    * `rosrun robotino_ros teleop_twist_keyboard.py` 
* Robot can now be controlled using teleop.







