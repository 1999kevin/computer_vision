#include "helper.h"
#include <math.h>
// #include <opencv2/opencv.hpp>

const char *wndname = "myCartoon"; 
VideoWriter writer;
Mat image;

/* 写入一帧, 显示一帧并停顿33ms，若按下空格键则暂停视频，再按一次继续 */
void putPicture(VideoWriter writer, Mat img)
{   
    writer.write(Mat(img));
    imshow(wndname, img);
    if(waitKey(33) == 32){
        while(1){
            if(waitKey(33) == 32){
                break;
            }
        }
    }
    // printf("%d\n",);
}


/* 延迟k帧 */
void delay(int k)
{
    for (int i = 0; i <= k; i++)
    {
        putPicture(writer, image);
    }
}

/* 清空图片，true则写入一帧，false不写入 */
void drawBackground(Mat img, bool flag)
{
    rectangle(img,
        Point(0, 0),
        Point(W, H),
        Scalar(255, 255, 255),
        -1,
        8);
    if (flag == true)
    {
        putPicture(writer, img);
    }
}

void drawSubPhoto(const char *path, int loc_w, int loc_h)
{
    Mat roi = imread(path, IMREAD_COLOR);
    Rect roi_rect = Rect(loc_w, loc_h, roi.cols, roi.rows);
    roi.copyTo(image(roi_rect));
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
    circle(mat, center, thick, color, -1, 8, 0);
    putPicture(writer, mat);
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
        circle(mat, center, thick, color, -1, 8, 0);
        if(i % rate == 0){
            putPicture(writer, mat);
        }
            
    }
}

void drawArc(Mat img, Point center, double radius, double start_angle, double end_angle, Scalar color,int thick, int rate)
{
    Point arc;
    double foot = 0.02;
    for (double r = start_angle; r <= end_angle; r = r + foot)
    {
        arc.x = int(center.x + radius*cos(r));
        arc.y = int(center.y + radius*sin(r));

        circle(img, arc, thick, color, -1, 8, 0);
        if(int(r/PI*180) % rate == 0){
            putPicture(writer, img);
        }
            
    }
}


void drawEarc(Mat img, Point center, double radius, double start_angle, double end_angle, float a,float b,Scalar color,int thick,bool is_x, int rate)
{
    Point arc;
    double foot=0.02;
    for (double r = start_angle; r <= end_angle; r = r + foot)
    {
        if (is_x)
        {
            arc.x = int(center.x + a*cos(r));
            arc.y = int(center.y + b*sin(r));
        }
        else
        {
            arc.x = int(center.x + b*cos(r));
            arc.y = int(center.y + a*sin(r));
        }
        
        circle(img, arc, thick, color, -1, 8, 0);
        if(int(r/PI*180) % rate == 0){
            putPicture(writer, img);
        }
    }
}