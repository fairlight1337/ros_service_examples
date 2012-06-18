#include <iostream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include "ros/ros.h"
#include "rosdemo_mp3/MP3InventoryService.h"

using namespace std;


bool mp3_inventory_interaction(rosdemo_mp3::MP3InventoryService::Request &req,
                               rosdemo_mp3::MP3InventoryService::Response &res) {
  string strDirectory = "albums";
  ROS_INFO("request string: %s", req.request_string.c_str());

  if(strcmp(req.request_string.c_str(), "album_list") == 0) {
    string str_temp;
    stringstream ss;

    DIR *dp;
    struct dirent *dirp;
    if((dp = opendir(strDirectory.c_str())) != NULL) {
      while((dirp = readdir(dp)) != NULL) {
        string strTempFilename = string(dirp->d_name);

        if(strcmp(strTempFilename.c_str(), ".") != 0 && strcmp(strTempFilename.c_str(), "..") != 0) {
          res.list_strings.push_back(string(dirp->d_name));
        }
      }
    }

    ss.str("");
    ss << req.request_string.c_str();
    res.response_string = ss.str();

    ROS_INFO("Sending back %ld album(s).", res.list_strings.size());
  } else if(strcmp(req.request_string.c_str(), "title_list") == 0) {
    string strAlbumDirectory = strDirectory + "/" + req.album.c_str();

    string str_temp;
    stringstream ss;

    DIR *dp;
    struct dirent *dirp;
    if((dp = opendir(strAlbumDirectory.c_str())) != NULL) {
      while((dirp = readdir(dp)) != NULL) {
        string strTempFilename = string(dirp->d_name);

        if(strcmp(strTempFilename.c_str(), ".") != 0 && strcmp(strTempFilename.c_str(), "..") != 0) {
          res.list_strings.push_back(string(dirp->d_name));
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


int main(int argc, char **argv) {
  ros::init(argc, argv, "mp3_inventory_node");
  ros::NodeHandle n;
  
  ros::ServiceServer service = n.advertiseService("mp3_inventory_interaction", mp3_inventory_interaction);
  
  ROS_INFO("MP3 Inventory up and running.");
  ros::spin();
  
  return EXIT_SUCCESS;
}
