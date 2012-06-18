#include <iostream>
#include "ros/ros.h"
#include "rosdemo_mp3/MP3InventoryService.h"

using namespace std;


int main(int argc, char **argv) {
  ros::init(argc, argv, "mp3_inventory_client");
  
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<rosdemo_mp3::MP3InventoryService>("mp3_inventory_interaction");
  
  rosdemo_mp3::MP3InventoryService srv;

  std::stringstream ss;
  ss << "album_list";
  srv.request.request_string = ss.str();

  if(client.call(srv)) {
    ROS_INFO("OK, sent. Here is the answer:");
    ROS_INFO(" - Response string: '%s'", srv.response.response_string.c_str());

    if(strcmp(srv.response.response_string.c_str(), "album_list") == 0) {
      ROS_INFO(" - Albums:");
      for(vector<string>::iterator itStrings = srv.response.list_strings.begin(); itStrings != srv.response.list_strings.end(); itStrings++) {
        ROS_INFO("   * %s", (*itStrings).c_str());

        // Call server for information about this album (i.e. titles).
        std::stringstream ss;
        ss << "title_list";
        rosdemo_mp3::MP3InventoryService srv_titles;
        srv_titles.request.request_string = ss.str();
        ss.str("");
        ss << (*itStrings).c_str();
        srv_titles.request.album = ss.str();

        if(client.call(srv_titles)) {
          ROS_INFO("     Titles:");

          for(vector<string>::iterator itTitles = srv_titles.response.list_strings.begin(); itTitles != srv_titles.response.list_strings.end(); itTitles++) {
            ROS_INFO("       o %s", (*itTitles).c_str());
          }
        } else {
          ROS_INFO("Failed to retrieve album titles for album '%s'", (*itStrings).c_str());
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
