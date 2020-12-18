/** 
 * @author 刘柯
 * @date 2020/12/18
 * @description: cv第二次作业
 * @function: Harris角点检测器
*/

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/shape/shape.hpp>

#include "harris.h"
using namespace cv;
using namespace std;
int main(int argc, char* argv[])
{
    update();

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
        // char key = waitKey(3);
        char c = waitKey(20);    //延时30
        if(c == 'q')
        {
            break;
        }
        // if(key == ' '){     //
        //     //  cut(frame);
        //      char key2; //阻塞暂停
        //      do{
        //          key2 = waitKey();
        //          if(key2 == 27) return 1;
        //      }while(key2 != ' ');
        // }else if(key == 27){ //esc键退出
        //     return 1;
        // }
    }
    return 0;
}
