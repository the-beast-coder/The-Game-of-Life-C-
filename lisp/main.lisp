(print "Hello world")
(defvar *name* (read))

(defun hello (*name*)
  (format t "Hello ~a! %n"))
