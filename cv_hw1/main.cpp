#include <iostream>
#include "helper.h"

const char *path = "C:/Users/a/Desktop/courses/computer_vision/cv_hw1/test1.avi";//文件保存路径 
extern VideoWriter writer;
extern Mat image;


void drawFirstFrame()
{
    String name = "name    :   Liuke";
    String number = "Student ID: 12021232";

    putText(image, number, Point(W / 3, H/3), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0));
    putText(image, name, Point(W/3, H/2), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));

    addSubPhoto("zheda(1).jpg", 128, 64);
    addCurrentTime(W/3, H/3*2);
    putPicture(writer, image);
}


void drawCartoon(){
    drawLine(image, Point(0,0), Point(512,670), Scalar(255, 0, 0), 1, 10);
    drawArc(image, Point(512, 512), 50, 0, PI, Scalar(255, 0, 0), 2, 5);
    drawEarc(image, Point(256, 512), 100, 0, PI, 20, 10, Scalar(255, 0, 0), 1, false, 3);
}


int main()
{
    printf("making up video\n");
    writer = VideoWriter(path, 0, 30, Size(W, H));
    image= Mat::zeros(H, W, CV_8UC3);
    drawBackground(image, false);
    // delay(30);
    drawFirstFrame();
    delay(30);
    drawBackground(image, false);
    drawCartoon();
    return 0;
}


