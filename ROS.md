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

filter out tree/building/bus