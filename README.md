![image](https://github.com/huso987/birfen-staj/assets/66470348/7455271a-1755-4f8d-ba2a-352bf4bb0330)

## Install Dependent ROS 2 Packages

Open the terminal with Ctrl+Alt+T from Remote PC.
### Install Gazebo
$ sudo apt install ros-humble-gazebo-*
### Install Cartographer
$ sudo apt install ros-humble-cartographer       
$ sudo apt install ros-humble-cartographer-ros
### Install Navigation2
$ sudo apt install ros-humble-navigation2   
$ sudo apt install ros-humble-nav2-bringup


## Install TurtleBot3 Packages
Install TurtleBot3 via Debian Packages.

$ source ~/.bashrc  
$ sudo apt install ros-humble-dynamixel-sdk  
$ sudo apt install ros-humble-turtlebot3-msgs  
$ sudo apt install ros-humble-turtlebot3

## Environment Configuration
Set the ROS environment for PC.  
$ echo 'export ROS_DOMAIN_ID=30 #TURTLEBOT3' >> ~/.bashrc  
$ source ~/.bashrc

# Run turtlesim


To run the Turtlesim simulation in ROS 2, you can follow these steps:

#### Install ROS 2:
Make sure you have ROS 2 installed on your system. If not, you can follow the steps mentioned in the previous response to install ROS 2.

#### Create a ROS 2 Workspace:
Create a workspace directory and navigate to it. You will build and run your ROS 2 packages within this workspace.

mkdir -p ~/ros2_ws/src   
cd ~/ros2_ws/src

#### Install Turtlesim:
Turtlesim is not available by default in ROS 2. You'll need to clone the Turtlesim repository from GitHub and build it in your workspace.

git clone https://github.com/ros2/turtlesim.git

#### Build the Workspace:
Go back to the root of your workspace and build it using colcon.

cd ~/ros2_ws  
colcon build   
source install/setup.bash

#### Run Turtlesim Node:
Open a new terminal window and source the workspace again to load the environment variables. Then, you can run the Turtlesim node.

source ~/ros2_ws/install/setup.bash  
ros2 run turtlesim turtlesim_node

#### Run Teleop Node (Optional):
To control the turtle using keyboard inputs, you can run the teleop node.

source ~/ros2_ws/install/setup.bash  
ros2 run turtlesim turtle_teleop_key

# Run TURTLEBOT3

#### Install ROS 2:
If you haven't already, install ROS 2 on your system. You can follow the official ROS 2 installation instructions for your platform.

#### Create a Workspace:
Create a workspace for your ROS 2 packages. This is where you'll build and run TurtleBot3 packages.

mkdir -p ~/ros2_ws/src  
cd ~/ros2_ws/src

#### Install TurtleBot3 Packages:
Clone the TurtleBot3 repository for ROS 2 into your workspace.

git clone https://github.com/ROBOTIS-GIT/turtlebot3.git

#### Build the Workspace:
Go back to the root of your workspace and build it using colcon.

cd ~/ros2_ws   
colcon build  
source install/setup.bash

### Run the Simulation:

Launch the simulation for TurtleBot3. Replace <model> with the model you want to simulate, such as burger, waffle,waffle_pi etc.

source ~/ros2_ws/install/setup.bash   
export TURTLEBOT3_MODEL =<model>  
ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py

ros run turtlebot3_teleop teleop_keyboard

# run my_py_pkg
To run a python code in my_py_pkg package, they are called by their defined name in the section entry_points={ 'console_scripts': [ ]} in setup.py

#### example:        
    entry_points={
        'console_scripts': [
           "shapedrawer = my_py_pkg.shapedrawernode:main",
           "pathfollower = my_py_pkg.pathfollowernode:main",
           "turtlecontrol = my_py_pkg.turtlecontroler:main",
           "turtlebot3 = my_py_pkg.turtlebot3control:main"
           
        ],
    },

source .bashrc  
ros2 run my_py_pkg shapedrawer


# run my_cpp_pkg
To run a cpp code from the my_cpp_pkg package, also install(TARGETS) CMakeLists.txt
    DESTINATION lib/${PROJECT_NAME}
) are run by their name in the partition

#### example: 
install(TARGETS  
    shape  
    pathcontrol  
    turtlecontrol  
    turtlebot  
    turtlebot1  
    threepoints   
    engel   
    DESTINATION lib/${PROJECT_NAME}  
)


source .bashrc  
ros2 run my_cpp_pkg shape


# Mapping

colcon build --symlink-install  
export TURTLEBOT3_MODEL=<model>  
source ./install/setup.bash  
ros2 launch turtlebot3_gazebo turtlebot3_house.launch.py
#### new terminal:
ros2 launch slam_toolbox online_async_launch.py

#### new terminal

rviz2 


When rviz opens, click the Add button and add Laser scan, Map, TFs
Set the topic to /scan in laser scan and set the topic of Mapin to /map

#### new terminal
export TURTLEBOT3_MODEL=<model>   
ros run turtlebot3_teleop teleop_keyboard


move and create the map


#### new terminal
save the resulting map

ros2 run nav2_map_server map_saver_cli -f ~/house_map
