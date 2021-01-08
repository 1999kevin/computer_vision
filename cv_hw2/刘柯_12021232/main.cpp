/** 
 * @author 刘柯
 * @date 2020/12/18
 * @description: cv第二次作业
 * @function: Harris角点检测器
*/

#include "harris.h"
using namespace cv;
using namespace std;

void detect(Mat image){
    Harris harrisCornerDetector;
    harrisCornerDetector.update(image);

    vector<Point> corners = harrisCornerDetector.getCorners();
    Mat result = image.clone();
    for(int i=0;i<corners.size();i++){
        int x = corners[i].x;
        int y = corners[i].y;
        rectangle(result,Point(x-4,y-4),Point(x+4,y+4),Scalar(0,255,0),2);
    }

    Mat min = harrisCornerDetector.getMin();
    Mat max = harrisCornerDetector.getMax();
    Mat R   = harrisCornerDetector.getR();

    imwrite("result.jpg",result);
    imwrite("min.jpg",min);
    imwrite("max.jpg",max);
    imwrite("R.jpg",R);
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
    
    Mat video;
    namedWindow("video",1);

    while(true){
        cap>>video;
        imshow("video",video);
        char key = waitKey(30);    //延时30
        
        if(key == ' '){
            detect(video);
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
