/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2015, Jan Winkler, Institute for Artificial Intelligence,
 *  Universität Bremen.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Institute for Artificial Intelligence,
 *     Universität Bremen, nor the names of its contributors may be
 *     used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/** \author Jan Winkler */


// System
#include <iostream>

// ROS
#include <ros/ros.h>

// Local
#include <ros_service_examples/MP3InventoryService.h>


int main(int argc, char** argv) {
  ros::init(argc, argv, "mp3_inventory_client");
  
  ros::NodeHandle nh;
  ros::ServiceClient client = nh.serviceClient<ros_service_examples::MP3InventoryService>("mp3_inventory_interaction");
  
  ros_service_examples::MP3InventoryService srv;
  
  std::stringstream sts;
  sts << "album_list";
  srv.request.request_string = sts.str();
  
  if(client.call(srv)) {
    ROS_INFO("OK, sent. Here is the answer:");
    ROS_INFO(" - Response string: '%s'", srv.response.response_string.c_str());
    
    if(strcmp(srv.response.response_string.c_str(), "album_list") == 0) {
      ROS_INFO(" - Albums:");
      
      for(std::string strString : srv.response.list_strings) {
        ROS_INFO("   * %s", strString.c_str());
	
        // Call server for information about this album (i.e. titles).
        std::stringstream sts;
        sts << "title_list";
        ros_service_examples::MP3InventoryService srv_titles;
        srv_titles.request.request_string = sts.str();
        sts.str("");
        sts << strString.c_str();
        srv_titles.request.album = sts.str();
	
        if(client.call(srv_titles)) {
          ROS_INFO("     Titles:");
	  
	  for(std::string strTitle : srv_titles.response.list_strings) {
            ROS_INFO("       o %s", strTitle.c_str());
	  }
        } else {
          ROS_INFO("Failed to retrieve album titles for album '%s'", strString.c_str());
        }
      }
    } else {
      ROS_INFO("Response string not recognized.");
    }
  } else {
    ROS_INFO("Unable to call().");
  }
  
  return EXIT_SUCCESS;
}
