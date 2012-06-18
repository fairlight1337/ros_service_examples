(in-package :mp3-controller)

(defun mp3-inventory-interaction ()
  (with-ros-node ("mp3_controller_client_lisp")
    (if (not (wait-for-service "mp3_inventory_interaction" 10))
        (ros-warn nil "Timed out waiting for service")
        (with-fields (;;(response-string response_string)
                      (album-list list_strings))
            (call-service "mp3_inventory_interaction"
                          "rosdemo_mp3/MP3InventoryService"
                          :request_string "album_list")
          (loop for album across album-list do
            (format t "album: ~a~%" album)
            (format t " - titles:~%")
            (with-fields ((title-list list_strings))
                (call-service "mp3_inventory_interaction"
                              "rosdemo_mp3/MP3InventoryService"
                              :request_string "title_list"
                              :album album)
              (loop for title across title-list do
                (format t "    * ~a~%" title))))))))

(defun mp3-inventory-interaction-client-main ()
  (mp3-inventory-interaction))