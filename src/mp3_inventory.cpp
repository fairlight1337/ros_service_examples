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
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>

// ROS
#include <ros/ros.h>
#include <ros/package.h>

// Local
#include <ros_service_examples/MP3InventoryService.h>


bool mp3_inventory_interaction(ros_service_examples::MP3InventoryService::Request &req,
                               ros_service_examples::MP3InventoryService::Response &res) {
  std::string strDirectory = ros::package::getPath("ros_service_examples") + "/albums";
  ROS_INFO("request string: %s", req.request_string.c_str());
  
  if(std::strcmp(req.request_string.c_str(), "album_list") == 0) {
    std::string str_temp;
    std::stringstream sts;
    
    DIR* dp;
    struct dirent* dirp;
    if((dp = opendir(strDirectory.c_str())) != NULL) {
      while((dirp = readdir(dp)) != NULL) {
	std::string strTempFilename = std::string(dirp->d_name);
	
        if(std::strcmp(strTempFilename.c_str(), ".") != 0 &&
	   std::strcmp(strTempFilename.c_str(), "..") != 0) {
          res.list_strings.push_back(std::string(dirp->d_name));
        }
      }
    }
    
    sts.str("");
    sts << req.request_string.c_str();
    res.response_string = sts.str();
    
    ROS_INFO("Sending back %ld album(s).", res.list_strings.size());
  } else if(std::strcmp(req.request_string.c_str(), "title_list") == 0) {
    std::string strAlbumDirectory = strDirectory + "/" + req.album.c_str();
    
    std::string str_temp;
    std::stringstream sts;
    
    DIR* dp;
    struct dirent *dirp;
    if((dp = opendir(strAlbumDirectory.c_str())) != NULL) {
      while((dirp = readdir(dp)) != NULL) {
	std::string strTempFilename = std::string(dirp->d_name);
	
        if(std::strcmp(strTempFilename.c_str(), ".") != 0 &&
	   std::strcmp(strTempFilename.c_str(), "..") != 0) {
          res.list_strings.push_back(std::string(dirp->d_name));
        }
      }
    }
    
    ROS_INFO("Sending back %ld title(s) for album '%s'.", res.list_strings.size(), req.album.c_str());
  } else {
    ROS_INFO("Faulty request string: '%s'", req.request_string.c_str());
    res.response_string = "error_faulty_request_string";
  }
  
  return true;
}


int main(int argc, char** argv) {
  ros::init(argc, argv, "mp3_inventory_node");
  ros::NodeHandle nh;
  
  ros::ServiceServer service = nh.advertiseService("mp3_inventory_interaction", mp3_inventory_interaction);
  
  ROS_INFO("MP3 Inventory up and running.");
  ros::spin();
  
  return EXIT_SUCCESS;
}
