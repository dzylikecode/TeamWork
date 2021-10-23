include ../config_Makefile 

cc = g++

BuildPath ?=$(g_BuildPath)

IncludePath ?=$(g_IncludePath)

LibPath ?=$(g_LibPath)

CompileOption=-std=c++17 -m32

LibName = 		-lopencv_calib3d450   \
        		-lopencv_core450   \
                -lopencv_dnn450   \
                -lopencv_features2d450   \
                -lopencv_flann450   \
                -lopencv_highgui450   \
                -lopencv_imgcodecs450   \
                -lopencv_imgproc450   \
                -lopencv_ml450   \
                -lopencv_objdetect450   \
                -lopencv_photo450   \
                -lopencv_stitching450   \
                -lopencv_video450   \
                -lopencv_videoio450

exeOutput = $(BuildPath)/install_test.exe

$(exeOutput): install_test.cpp 
	$(cc) -o $(exeOutput) \
	install_test.cpp \
	$(CompileOption) \
	-I$(IncludePath) \
	-L$(LibPath) \
	$(LibName)
