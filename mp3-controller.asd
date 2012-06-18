(defsystem mp3-controller
  :depends-on (cram-language roslisp rosdemo_mp3-srv)
  :components
  ((:module "src"
            :components
            ((:file "package")
             (:file "mp3-controller" :depends-on ("package"))))))