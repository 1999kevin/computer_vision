#pragma once
#ifndef __HELPER_H__
#define __HELPER_H__
#include <opencv2/opencv.hpp>  

using namespace std;
using namespace cv;

#define W 1080
#define H 720
#define PI 3.1415926


void putPicture(VideoWriter writer, Mat img);
void delay(int k);
void drawBackground(Mat img, bool flag);
void addSubPhoto(const char *path, int loc_w, int loc_h);
void addCurrentTime(int loc_w, int loc_h);
void drawLine(Mat mat, Point start, Point end,Scalar color,int thick, int rate, bool Draw);
void drawArc(Mat img, Point center, double radius, double start_angle, double end_angle, Scalar color,int thick, int rate, bool Draw);
void drawEarc(Mat img, Point center, double radius, double start_angle, double end_angle, float a,float b,Scalar color,int thick,bool is_x, int rate);


#endif
