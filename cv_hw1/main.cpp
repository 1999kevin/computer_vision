#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define W 1080
#define H 720

const char *path = "C:/Users/a/Desktop/courses/computer_vision/cv_hw1/test1.avi";//输入文件路径 
Mat image;
VideoWriter writer;

/* 写入一帧 */
void putPicture(Mat img)
{
    writer.write(Mat(img));
}

/* 延迟k帧 */
void delay(int k)
{
    for (int i = 0; i <= k; i++)
    {
        putPicture(image);
    }
}


void drawSubPhoto(const char *path, int loc_w, int loc_h)
{
    Mat roi = imread(path, IMREAD_COLOR);
    Rect roi_rect = Rect(loc_w, loc_h, roi.cols, roi.rows);
    roi.copyTo(image(roi_rect));
}

void drawFirstFrame()
{
    String name = "name    :   Liuke";
    String number = "Student ID: 12021232";

    putText(image, number, Point(W / 3, H/3), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0));
    putText(image, name, Point(W/3, H/3*2), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));

    drawSubPhoto("zheda(1).jpg", 128, 64);
}



/* 清空图片，true则写入一帧，false不写入 */
void drawBackground(bool flag)
{
    rectangle(image,
        Point(0, 0),
        Point(W, H),
        Scalar(255, 255, 255),
        -1,
        8);
    if (flag == true)
    {
        putPicture(image);
    }
}

void drawLine(Mat mat, Point start, Point end,Scalar color,int thick, int rate)
{
    int x1, y1,step;
    Point center=start;
    x1 = start.x;
    y1 = start.y;
    double footx,footy;
    int dx = end.x - start.x;
    int dy = end.y - start.y;
    circle(mat, center,thick,color,-1, 8, 0);
    putPicture(mat);
    if (abs(dx) > abs(dy))
    {
        step = abs(dx);
    }
    else 
    {
        step = abs(dy);
    }
    footx = (double)dx / step;
    footy = (double)dy / step;
    //printf("footy = %f\n", footy);
    for (int i = 0; i<step; i++)
    {
        if (footx > 0) {
            x1 += int(footx + 0.5);
        }
        if (footx < 0)
        {
            x1 += int(footx - 0.5);
        }
        if (footy > 0)
        {
            y1 += int(footy + 0.5);
        }
        if (footy < 0)
        {
            y1 += int(footy - 0.5);
        }
        center.x = x1;
        center.y = y1;
        circle(mat, center,thick,color,-1, 8, 0);
        if(i % rate == 0){
            putPicture(mat);
        }
            
    }
}

void drawCartoon(){
    drawLine(image, Point(0,0), Point(512,512), Scalar(255, 0, 0), 1, 5);
}


int main()
{
    printf("making up video\n");
    writer = VideoWriter(path, 0, 30, Size(W, H));
    image= Mat::zeros(H, W, CV_8UC3);
    drawBackground(false);
    delay(30);
    drawFirstFrame();
    delay(30);
    drawBackground(false);
    drawCartoon();
    return 0;
}


