# Robot Operating System (ROS)
Programming Robots with ROS

ROS, the Robot Operating System, is an open source framework for getting robots to do things.

ROS consists of number of parts
1. A set of **drivers** that let you read data from sensors and send commands to motors and other actuators, in an abstracted, well-defined format.
2. A large and growing collection of fundamental **robotics algorithms** that allow you to build maps of the world, navigate around it, represent and interpret sensor data, plan
motions, manipulate objects, and do a lot of other stuff.
3. All of the **computational infrastructure** that allows you to move data around. ROS is inherently *distributed* and allows you to split the workload across multiple computers seamlessly.
4. A large set of **tools** that make it easy to visualize the state of the robot and the algorithms

Knowing something about the underlying mathematics used by robotics, such as *coordinate transforms* and *kinematic chains*

The **Robot Operating System (ROS)** is a framework for writing robot software. It is a collection of *tools, libraries, and conventions* that aim to simplify the task of creating complex and robust robot behavior across a wide variety of robotic platforms.

ROS software modules can be written in any language for which a **client library** has been written. At the time of writing, client libraries exist for *C++, Python, LISP, Java,
JavaScript, MATLAB, Ruby, Haskell, R, Julia*, and others.

ROS client libraries communicate with one another by following a convention that describes how messages are *“flattened”* or *“serialized”* before being transmitted over the network.

### Installing ROS
```bash
$ sudo sh -c \
'echo "deb http://packages.ros.org/ros/ubuntu trusty main" > \
/etc/apt/sources.list.d/ros-latest.list'
$ wget http://packages.ros.org/ros.key -O - | sudo apt-key add -
$ sudo apt-get update
$ sudo apt-get install ros-indigo-desktop-full python-rosinstall
$ sudo rosdep init
$ rosdep update
$ echo "source /opt/ros/indigo/setup.bash" >> ~/.bashrc
$ source ~/.bashrc
```

A ROS graph *node* (POSIX processes) represents a software module that is sending or receiving messages, and a ROS graph *edge* (TCP connections) represents a stream of messages between two nodes.

`roscore` is a service that provides connection information to nodes so that they can transmit messages to one another.

The ROS architecture is a hybrid between a classical client/server system and a fully distributed one, due to the presence of a central roscore that provides a name service for the peer-to-peer
message streams.

When a ROS node starts up, it expects its process to have an environment variable named `ROS_MASTER_URI`.

`roscore` also provides a *parameter server*, which is used extensively by ROS nodes for configuration. There is a simple command-line tool to interact with the parameter server: `rosparam`.

`catkin` is the ROS build system: the set of tools that ROS uses to generate executable programs, libraries, scripts, and  interfaces that other code can use.

`catkin` comprises a set of CMake macros and custom Python scripts to provide extra functionality on top of the normal CMake workflow.

A workspace is simply a set of directories in which a related set of ROS code lives.

```bash
$ source /opt/ros/indigo/setup.bash
$ mkdir -p ~/catkin_ws/src
$ cd ~/catkin_ws/src
$ catkin_init_workspace
$ cd ~/catkin_ws
$ catkin_make
```

The `catkin_init_workspace` command creates a CMakeLists.txt file for you in the src directory.

`catkin_make` will make two new directories: *build* and *devel*.

If you open a new shell (or Linux terminal), you have to source the setup.bash file for the workspace you want to work with.

ROS software is organized into *packages*, each of which contains some combination of code, data, and documentation.

Packages sit inside workspaces, in the src directory. Each package directory must include a *CMakeLists.txt* file and a *package.xml* file that describes the contents of the package and how catkin should interact with it.

```bash
$ cd ~/catkin_ws/src
$ catkin_create_pkg my_awesome_code rospy
```

The `catkin_create_pkg` command makes a directory with the same name as the new package (my_awesome_code) with a CMakeLists.txt file, a package.xml file, and a src directory in it.

To automate chasing long paths in filesystems, ROS provides a
command-line utility called `rosrun` that will search a package for the requested program and pass it any parameters supplied on the command line.

```bash
$ rosrun PACKAGE EXECUTABLE [ARGS]
```

command-line tool `rostopic`, which is an extremely useful tool for introspecting running ROS systems.

`rqt_graph` is the Qt-based graph visualizer.

Typical ROS development follows the pattern of an *anonymous*
publish/subscribe system: nodes generally do not receive or use any details about the identity or function of the peer nodes, where their inbound messages are coming from, or where they are going.

ROS includes a tool for starting collections of nodes, called `roslaunch`.

ROS uses the forward slash (/) to delimit namespaces. In ROS, any string in a program that defines a name can be *remapped* at runtime.

ROS provides a standard syntax to remap names when starting nodes on the command line.
```bash
# Remap image topic to right/image topic
$ ./image_view image:=right/image
```

Pushing a node into a namespace can be accomplished with a special `__ns` namespace-remapping syntax (note the double underscore).
```bash
# Launch camera into the namespace right
$ ./camera __ns:=right
```

If the same node is launched twice, `roscore` directs the older node to exit to make way for the newer instance of the node.

To change the name of a node on the command line, the special `__name` remapping syntax can be used.
```bash
$ ./talker __name:=talker1
$ ./talker __name:=talker2
```

`roslaunch` is a command-line tool designed to automate the launching of collections of ROS nodes.
```bash
$ roslaunch PACKAGE LAUNCH_FILE
```

Launch files are XML files that describe a collection of nodes along with their topic remappings and parameters.

```xml
<launch>
    <node name="talker" pkg="rospy_tutorials"
        type="talker.py" output="screen" />
    <node name="listener" pkg="rospy_tutorials"
        type="listener.py" output="screen" />
</launch>
```

One of the most useful features of roslaunch is that it closes all
of its nodes when Ctrl-C is pressed in the console containing roslaunch.

we need to pick for each component a coordinate frame of reference, or *origin*.

In our 3D world, a **position** is a vector of three numbers
(x, y, z) that describe how far we have translated along each axis, with respect to some origin. Similarly, an **orientation** is a vector of three numbers (roll, pitch, yaw) that describe how far we have rotated about each axis, again with respect to some origin. Taken together, a (position, orientation) pair is called a **pose**. This kind of pose, which varies in six dimensions (three for translation plus three for rotation) is sometimes called a **6D pose**.

This system is implemented in the tf (short for transform) package, which is extremely widely used throughout ROS software.

A **topic** is a name for a stream of messages with a defined type.

Before nodes start to transmit data over topics, they must first announce, or *advertise*, both the topic name and the types of
messages that are going to be sent. Then they can start to send, or publish, the actual data on the topic.

In ROS, all messages on the same topic must be of the same data type.

we’re using a message from another package, we have to tell the ROS build system about this by adding a dependency to our package.xml file:
```xml
<depend package="std_msgs" />
```

## A Gentle Introduction to ROS

ROS is not a real operating system. It is a *meta operating system* that provides some operating system functionalities. These functionalities include *multithreading*, *low-level device control*, *package management*, and *hardware abstraction*. ROS 
also provides tools and libraries for obtaining, building, writing, and running code across multiple computers.

Major versions of ROS are called **distributions**, and are named using adjectives that start with successive letters of the alphabet.

Older, pre-groovy distributions used a build system called
`rosbuild`, but more recent versions have begun to replace rosbuild with a new build system called `catkin`.

```bash
# Install ROS packages
sudo apt-get install ros-indigo-desktop-full

# Install turtlesim
sudo apt-get install ros-indigo-turtlesim

# Setting up rosdep systemwide
sudo rosdep init

# Setup rosdep in user acccount
rosdep update
```

`rosdep` is a tool for checking and installing package dependencies in an OS-independent way.

`rosinstall` tool's job is to install ROS software from source.

ROS relies on a few environment variables to locate the
files it needs. To set these environment variables, you’ll need to execute the `setup.bash` script that ROS provides, using this command:
```bash
source /opt/ros/indigo/setup.bash

# Verify
export | grep ROS
```

`setup.bash` script defines bash functions to implement a few commands, including `roscd` and `rosls`. These functions are defined in the `rosbash` package.

```bash
roscore
rosrun turtlesim turtlesim_node
rosrun turtlesim turtle_teleop_key
```
ROS provides client libraries for these languages, meaning the programmer can get ROS functionalities in the languages mentioned.

ROS has implemented popular robotics algorithms such as [PID](http://wiki.ros.org/pid), [SLAM (Simultaneous Localization and Mapping)](http://wiki.ros.org/gmapping); and path planners such as A*, [Dijkstra](http://wiki.ros.org/global_planner), and [AMCL(Adaptive Monte Carlo Localization)](http://wiki.ros.org/amcl).

[Rviz](http://wiki.ros.org/rviz) tool is used for visualization with cameras, laser scanners, inertial measurement units, and so forth. For working with robot simulations, there are simulators such as **Gazebo**.

A project called ROS 2.0 is developing a much better version of the existing ROS in terms of security and real-time processing.

Basically, ROS is a framework to communicate between two programs or process.

**Node** is the ROS term for an executable that is connected to the ROS network. 

These messages are sent through a message bus or path called *ROS topics*.

The ROS file system includes packages, meta packages, package manifests, repositories, message types, and services types.

ROS packages are the individual units, or the atomic units, of ROS software. All source code, data files, build files, dependencies, and other files are organized in packages.

A ROS meta package groups a set of similar packages for a specific application.

A package manifest is an *XML* file placed inside a ROS package. It has all the primary information of a ROS package, including the name of the package, description, author, dependencies, and so forth. 

A ROS repository is a collection of ROS packages that share a common version control system.

The ROS Service has Request/Reply mechanism.

When we run `roscore` command in the terminal, it starts the **ROS master**, the **parameter server**, and a **logging node**.

```bash
sudo apt-get install ros-<distro>-ros-tutorials
```

For most packages using the new catkin build system; compiled executables are not stored in the package directory, but in a separate standardized directory hierarchy. For packages installed by `apt-get`, this hierarchy is rooted at `/opt/ros/indigo`.

In ROS, there is a build system for compiling ROS packages. The name of the build system is [catkin](http://wiki.ros.org/catkin). catkin is a custom build system made from the CMake build system and Python scripting. 

**out-of-source compilation** is one of the primary changes
introduced by `catkin` in the groovy distribution of ROS.

A running instance of a ROS program is called a **node**.

The `/rosout` node is a special node that is started automatically by `roscore`. Its purpose is somewhat similar to the standard output (i.e. std::cout).

**node names** are not necessarily the same as the names of the executables underlying those nodes.

There is a built-in message package in ROS called `std_msgs` that has a message definition of standard data types, such as `int`, `float`, `string`, and so forth.

The output of `rosnode info` is a list of topics for which that node is a publisher or subscriber, the services offered by node etc.

Messages in ROS are organized into named *topics*. The idea is that a node that wants to share information will **publish** messages on the appropriate topic or topics; a node that
wants to receive information will **subscribe** to the topic or topics that it’s interested in.

The **message type of a topic** tells you what information is included in each message on that topic, and how that information is organized.

A common is `std_msgs/Header`, which contains some basic sequence, timestamp, and coordinate frame information.

`sensor_msgs/NavSatFix` contains arrays with fixed length.

An alternative is to give single parameter specifying all of the fields as a single YAML (a recursive acronym for “YAML Ain’t Markup Language” Í 24 ) dictionary. 
```bash
rostopic pub /turtle1/cmd_vel geometry_msgs/Twist "linear:
    x: 2.0
    y: 0.0
    z: 0.0
angular:
    x: 0.0
    y: 0.0
    z: 0.0"
```

In ROS every message type belongs to a specific package. Message type names always contain a slash, and the part before the slash is the name of the containing package.

ROS does provide a mechanism, called **services**, for slightly more direct, one-to-one communication.

make the robot model in ROS, which is called URDF
(Unified Robot Description Format)

The URDF is basically an XML file that has XML tags to represent a
joint and a link (http://wiki.ros.org/urdf). Another representation
of URDF is called Xacro

### Writing ROS Programs
Packages created should live together in a directory called
a **workspace**.

ROS’s catkin build system attempts to build all of the packages in a workspace at once.

The three-layered directory structure; a workspace directory, containing a src directory, containing a package directory; is required by catkin build system.

ROS package names follow a naming convention that allows only lowercase letters, digits, and underscores.

```cpp
// This i s a ROS version of the standard " hello , world"
// program.
// This header defines the standard ROS classes.
#include <ros/rosh.h>

int main(int argc, char **argv) {}
// Initialize the ROS system.
ros::init(argc, argv, "hello_ros"); 

// Establish this program as a ROS node.
ros::NodeHandle nh;

// Send some output as a log message.
ROS_INFO_STREAM("Hello, ROS!");
```
It is not possible, using the standard `roscpp` interface, to run multiple distinct nodes within a single program.

#### Publisher Example
```cpp
#include <ros/ros.h>
#include <geometry_msgs/Twist.h> // For geometry_msg::Twist
#include <stdlib.h>              // For rand() and RAND_MAX

int main(int argc, char *argv[]) {
    // Initialize ROS system and become a node
    ros::init(argc, argv, "publish_velocity");
    ros::NodeHandle nh;

    // Create a publisher object
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>(
            "turtle1/cmd_vel", 1000);

    // Seed random number generator
    srand(time(0));

    // Loop at 2Hz until the node is shut down
    ros::Rate rate(2);
    while(ros::ok()) {
        // Create and fill message.
        geometry_msgs::Twist msg;
        msg.linear.x = double(rand())/double(RAND_MAX);
        msg.angular.z = 2 * double(rand())/double(RAND_MAX) - 1;

        // Publish the message
        pub.publish(msg);

        // Send a message to rosout with the details
        ROS_INFO_STREAM("Sending random velocity command: " 
                << "linear = " << msg.linear.x
                << " angular = " << msg.angular.z);

        // Wait until it's time for another iteration.
        rate.sleep();
    }
}
```

The work of actually publishing the messages is done by an
object of class ros::Publisher.

```cpp
    ros::Publisher pub = node_handle.advertise<msg_type>(
        topic_name, queue_zie);
```
If your program rapidly publishes more messages than the queue can hold, the oldest unsent messages will be discarded.

ROS client library is smart enough to know when the publisher and subscriber nodes are part of the same underlying *process*. In these cases, the message is delivered directly to the subscriber, without using any network transport. This feature is very important for making **nodelets** that is, multiple nodes that can be dynamically loaded into a single process efficient.

If you want to publish messages on multiple topics from the same node, you’ll need to create a separate ros::Publisher object for each topic. Creating the publisher is an expensive operation, so it’s a usually bad idea to create a new `ros::Publisher` object each time you want to publish a message.

fields with array types—shown with square brackets by `rosmsg show` are realized as STL vectors in C++ code.

```cpp
ROS_INFO_STREAM( " Sending random velocity command: "
<< "linear=" << msg.linear.x
<< "angular=" << msg.angular.z) ;
```
The `ros::Rate` object controls how rapidly the loop runs. The parameter in its constructor is in units of Hz, that is, in cycles per second.

The advantage of `ros::Rate` object over `sleep` or `usleep` approach is that `ros::Rate` can account for the time consumed by other parts of the loop. If real work of the loop takes longer than the requested rate, the delay induced by sleep() can be reduced to zero.

```cmake
find_package(catkin REQUIRED COMPONENTS roscpp geometry_msgs)
```
ROS will only execute our callback function when we give it explicit permission to do so. Two different ways to accomplish this: `ros::spinOnce()` and `ros::spin()`.

### Subscriber Example

```cpp
#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <iomanip>

void poseMessageReceived(const turtlesim::Pose& msg) {
    ROS_INFO_STREAM(std::setprecision(2) << std::fixed 
            << "position = (" << msg.x << ", " << msg.y << ")"
            << " direction = " << msg.theta);
}

int main(int argc, char *argv[]) {
    ros::init(argc, argv, "subscribe_to_pose");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("turtle1/pose", 
        1000, 
        &poseMessageReceived);
    ros::spin();
}
```

## Log Messages

ROS provides a rich logging system that includes different **log messages**. In ROS, log messages are classified into five groups called **severity levels**
1. DEBUG: ROS_DEBUG_STREAM
1. INFO:  ROS_INFO_STREAM
1. WARN:  ROS_WARN_STREAM
1. ERROR: ROS_ERROR_STREAM
1. FATAL: ROS_FATAL_STREAM

Page-63



### Common ROS Commands
```bash
# Start ros master
roscore

# list all installed ROS packages
rospack list

# find directory of a single package
rospack find <PACKAGE-NAME>

# view files in a package directory
rosls <PACKAGE-NAME>

# change the current directory to a particular package
roscd <package-name>

# create a node by running ROS program
rosrun <package-name> <executable-name>

# set the name of a node
rosrun <package-name> <executable-name> __name:=<node-name>

# list of running nodes
rosnode list

# get infomration about a node
rosnode info <node-name>

# Kill a node
rosnode kill <node-name>

# Remove dead nodes from the list
rosnode cleanup

# Visualize publisher/subscriber relationships
rqt_graph

# get list of active topics
rostopic list

# see actual msgs that are being published on a topic
rostopic echo <topic-name>
rostopic echo /chatter => print/echo topic data
rostopic echo /turtle1/cmd_vel

# measure published speed (msg/sec)
rostopic hz <topic-name>

# measure published bandwidth (bytes/sec)
rostopic bw <topic-name>

# show details about message type
rosmsg show <msg-type-name>
rosmsg show turtlesim/Color
rosmsg show geometry_msgs/Twist
rosmsg show turtlesim/Pose

# publish msgs from command line
# <msg-content> parameter should provide values for all fields in order
rostopic pub -r <rate> <topic-name> <msg-type> <msg-content>
rostopic pub -r 5 /hello std_msgs/String "Hello" # rate mode
rostopic pub -r 1 /turtle1/cmd_vel geometry_msgs/Twists '[2, 0, 2]' '[0,0,0]'
rostopic pub -1 ... # one time mode
rostopic pub -l ... # latched mode

# perform broad variety of sanity checks
roswtf

# creat new ROS package, run in workspace/src directory
catkin_create_pkg <package-name>

rostopic type /turtle1/cmd_vel

rosparam list
roslaunch
catkin_make
catkin_make install
catkin_create_pkg ros_package_name package_dependencies
```

*Deep Neural Networks (dnn)* module. This module supports a number of deep learning frameworks, including `Caffe`, `TensorFlow`, and `Torch/PyTorch`.

**YOLO “You Only Look Once”** is an algorithm that uses *convolutional neural networks (CNN)* for object detection.
