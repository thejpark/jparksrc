(flyspell-prog-mode)


;; 


;; 
;; this is another world...


(if (equal (directory-file-name "/User/jpark")
"/User/jpark") (message "yes"))



(defun bar (n) (+ n 2))

(bar 3)


(fboundp 'bar)




(bar 3)




(defun zoo ()
  (interactive)
  (let ((arg "cd ~/wrk/test/cpp; g++ ctci.cpp"))
    (compile arg)
    ))



(fboundp 'zoo)

(symbol-function 'zoo)

(zoo)

(message "this is test")


;; this does not take arguments
(global-set-key (kbd "<f6>") 'zoo)


(fboundp 'bar)

(fboundp 'zoo)

(symbol-function 'zoo)

(setq compile-command "nmake")

(global-set-key (kbd "<f7>") 'compile)

(defun scons-unit ()
  (interactive)
  (let ((arg (format "cd %s; scons --unit-test-run" "~")))
    (compile arg)
))


(global-set-key (kbd "<f8>") 'scons-unit)

(setq proj "~")

(defun go-dir ()
  (interactive)
  (dired proj))

(global-set-key (kbd "<f2>") 'go-dir)

(defun go-vc-dir ()
  (interactive)
  (vc-dir proj))

(global-set-key (kbd "<f3>") 'go-vc-dir)

(find-file "~/.emacs")

(setq prj_bookmark (list (cons "name" "relative-directory")))

(setq prj_bookmarks
      (list
	 (cons "output-dir" "Build/RxDebug")
	 (cons "integtest" "IntegTests")
	 (cons "feature-file-dir" "IntegTests/features")
	 (cons "step-file-dir" "IntegTests/steps")
	 (cons "phantom" "Phantom/phantom")
	 (cons "hal-rx" "Hal/Rx")
	 (cons "hal-integ" "Hal/Integ")
	 ))

(defun goto-bookmark ()
  (interactive)
  (progn
    (setq keywords
	  (mapcar 'car prj_bookmarks))
    (setq keyword (ido-completing-read "goto:" keywords))
    (setq bookmark (assoc keyword prj_bookmarks))
    (setq file (cdr bookmark))
    (setq file (concat project "/" file))
    (find-file file)))

	  
(global-set-key (kbd "<f4>") 'goto-bookmark)
