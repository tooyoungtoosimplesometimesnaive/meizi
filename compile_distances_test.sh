
clang++ -Wall -std=c++14 -I/usr/local/include/opencv -I/usr/local/include -L/usr/local/lib grid.cpp cell.cpp distances.cpp distances_test.cpp -o distances_test.o -lopencv_dnn -lopencv_ml -lopencv_objdetect -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core

