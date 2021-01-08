#ifndef _HARRIS_H_
#define _HARRIS_H_
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/shape/shape.hpp>
#include <vector>

#include <iostream>

using namespace cv;
using namespace std;

class Harris
{
private:
    const float k = 0.05; //计算R时用到的参数    /* 这个真的可以用int吗 */

    Mat Ix2;     //x方向的梯度(一阶导)
    Mat Iy2;     //y方向的梯度(一阶导)
    Mat Ixy;    //Ix * Iy

    Mat R;      //R矩阵
    Mat mmax;
    Mat mmin;

    int max_r;

    int image_w;
    int image_h;

    Mat calIx(Mat image);
    Mat calIy(Mat image);
    Mat calIxy(cv::Mat Ix,cv::Mat Iy);

    template<typename TYPE>
    void absMat(cv::Mat& mat);

    template<typename TYPE>
    Mat powMat(cv::Mat& mat,int n=2);

    void meanFilter(cv::Mat& image);

    void calR();

    template<typename IMGTYPE,typename FILTERTYPE>
    cv::Mat convolve(cv::Mat image,cv::Mat filter);
public:
    Harris();
    ~Harris();
    void update(Mat image);
    void getEigenvalue();
    cv::Mat getR();
    cv::Mat getMax();
    cv::Mat getMin();
    vector<cv::Point> getCorners(int threshold=0);

};


#endif