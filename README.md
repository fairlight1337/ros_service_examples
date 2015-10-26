ros_service_examples
====================

ROS service and client examples in CPP, LISP and Python


Practical use
=============

In order to understand the ROS environment, salvaging it's
parts and looking at it from more than one side can help a
lot. This repository includes a simple "MP3 database server"
which serves album names and included title names to other
ROS nodes on the network.


The service server node
=======================

The service node is written in C++. It sends the filenames
from within the "albums" folder when requested. When a
client node requests a specific album, the server sends a
list of all filenames included in this album's folder.
A custom message type "MP3InventoryService" is used for
this example.


The client nodes
================

Client node source code is given in three programming languages:

       * C++
       * Python
       * LISP

All three client nodes are looking for the service
"mp3_inventory_interaction" on the ROS core and send their
requests to the server node once found.


Execution
=========

To start the example environment, do the following (assuming, you
have a working ROS core running):

     > roscd ros_service_examples
     > rosrun ros_service_examples mp3_inventory

The first line is important because the inventory server looks for
the directory "albums" in its current working directory.

The C++ and Python client nodes can also be started using rosrun.
There is no need to "roscd" to any specific directory first.

   Python:

   > rosrun ros_service_examples mp3_controller_python.py

   C++:

   > rosrun ros_service_examples mp3_controller

To launch the LISP client, be sure to completely set up your Emacs,
LISP and roslisp environment first. After that, you can run the LISP
client node through SLIME:

    > (ros-load:load-system "ros_service_examples" :mp3-controller)


Purpose of this example
=======================

This example shows the use of custom messages, the exposition of
a service from within a C++ node and the use of this service from
various clients.
The choice of different programming languages was intended explicitly
to

     a) show the differences between their usage and
     b) give a rough guide on how to execute these calls.

Furthermore, the directory structure as shown in this example fits
the use of the ASDF build system for LISP.
