CC = g++
INCLUDE_PATH =-I/usr/local/include/opencv4
LIB_PATH =-L/usr/local/lib
ADD_LIB = -lopencv_highgui.4.4.0 -lopencv_core.4.4.0 -lopencv_imgcodecs -lopencv_imgproc.4.4.0 -lopencv_videoio.4.4.0
SRC = main.cpp harris.cpp

APP = harris
all: $(SRC)
	$(CC) $(SRC) -std=c++1z $(INCLUDE_PATH) $(LIB_PATH) $(ADD_LIB) -o $(APP)

clean:
	rm -f *.o $(APP)