#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


char path[100];//输入文件路径 


void init(string filename)
{
    //image= Mat::zeros(W, W, CV_8UC3);//创建一张空图像
    image = Mat(H, W, CV_8UC3);
    temp = Mat(H, W, CV_8UC3);
    strcpy(path, filename);
    writer = VideoWriter(path, CV_FOURCC('X', 'V', 'I', 'D'), 30, Size(W, H));
}



void play()
{
    VideoCapture capture(path);
    if (!capture.isOpened())
        cout << "fail to open!" << endl;
    ////获取整个帧数
    //long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
    //cout << "整个视频共" << totalFrameNumber << "帧" << endl;

    //设置开始帧()
    long frameToStart = 0;
    capture.set(CV_CAP_PROP_POS_FRAMES, frameToStart);
    cout << "从第" << frameToStart << "帧开始读" << endl;

    //获取帧率
    double rate = capture.get(CV_CAP_PROP_FPS);
    cout << "帧率为:" << rate << endl;
    //承载每一帧的图像
    Mat frame;
    //显示每一帧的窗口
    namedWindow("Viedo");
    //两帧间的间隔时间:
    int delay = 1000 / rate;
    long currentFrame = frameToStart;

    while (1)
    {
        //读取下一帧
        if (!capture.read(frame))
        {
            break;
            return;
        }
        //这里加滤波程序
        imshow("Extracted frame", frame);
        int c = waitKey(delay);
        //按下按键后会停留在当前帧，等待下一次按键
        if (c >= 0)
        {
            waitKey(0);
        }
        currentFrame++;
    }
    //关闭视频文件
    capture.release();
}


int main()
{
    printf("正在生成视频，请稍后");
    init("C:/Users/a/Desktop/course/computer_vision/cv_hw1/test.avi");
    // drawBackground(true);
    // drawText();
    // drawBear();
    // drawRh();
    // drawStar(image, Point(0, 300), 40, Scalar(255, 255, 0), 2);
    // drawStar(image, Point(300, 300), 50, Scalar(255, 0, 255), 2);
    // drawStar(image, Point(0, 0), 35, Scalar(255, 0, 0), 2);
    // drawStar(image, Point(-350, 250), 35, Scalar(255, 0, 255), 2);
    imshow("pig", image);
    // play();
    waitKey();
    return 0;
}