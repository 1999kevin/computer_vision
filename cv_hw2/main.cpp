/** 
 * @author 刘柯
 * @date 2020/12/18
 * @description: cv第二次作业
 * @function: Harris角点检测器
*/

#include "harris.h"
using namespace cv;
using namespace std;

void cut(Mat image){
    Harris harris;
    Mat min;
    Mat max;
    Mat R;

    Mat result = image.clone();
    harris.update(image);
    // printf("one cut\n");
    vector<Point> corners = harris.getCorners();
    int size = corners.size();
    for(int i=0;i<size;i++){
        int x = corners[i].x;
        int y = corners[i].y;
        rectangle(result,cv::Point(x-4,y-4),cv::Point(x+4,y+4),cv::Scalar(0,255,0),2);
    }

    min = harris.getMin();
    max = harris.getMax();
    R   = harris.getR();

    //保存图片
    imwrite("result.jpg",result);
    imwrite("min.jpg",min);
    imwrite("max.jpg",max);
    imwrite("R.jpg",R);

    //展示中间结果
    imshow("result",result);
    imshow("min",min);
    imshow("max",max);
    imshow("R",R);
}


int main(int argc, char* argv[])
{
    VideoCapture cap(0);
    if(!cap.isOpened()){
        cout<<"error: can't open the camera"<<endl;
        return -1;
    }
    
    Mat frame;
    namedWindow("frame",1);

    while(true){
        cap>>frame;
        imshow("frame",frame);
        char key = waitKey(30);    //延时30
        
        if(key == ' '){
            cut(frame);
            char key2 = waitKey(30);   //这个延时后期可以删掉
            while(key2 != ' '){
                key2 = waitKey(30);
                if(key2 == 27) return 1;
            }
        }else if(key == 27){ //esc键退出
            return 1;
        }
    }
    return 0;
}
