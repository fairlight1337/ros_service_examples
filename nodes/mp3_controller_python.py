#!/usr/bin/env python
import roslib
roslib.load_manifest('rosdemo_mp3')

import sys

from rosdemo_mp3.srv import *
import rospy


def mp3_inventory_client():
  rospy.wait_for_service('mp3_inventory_interaction')

  try:
    mp3invserv = rospy.ServiceProxy('mp3_inventory_interaction', MP3InventoryService)
    albums = mp3invserv("album_list", "")

    print " - Albums:"
    for album_item in albums.list_strings:
      print "   * %s"%album_item
      
      try:
        titles = mp3invserv("title_list", album_item)
        
        print "     Titles:"
        for title_item in titles.list_strings:
          print "       o %s"%title_item
      except rospy.ServiceException, e:
        print "Service call failed: %s"%e
  except rospy.ServiceException, e:
    print "Service call failed: %s"%e

if __name__ == "__main__":
  mp3_inventory_client()
