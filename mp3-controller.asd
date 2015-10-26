(defsystem mp3-controller
  :depends-on (cram-language roslisp ros_service_examples-srv)
  :components
  ((:module "src"
            :components
            ((:file "package")
             (:file "mp3-controller" :depends-on ("package"))))))
