#include <iostream>
#include "helper.h"

const char *path = "test1.avi";//文件保存路径 
extern VideoWriter writer;
extern Mat image;
extern const char *wndname;

void drawFirstFrame()
{
    String name = "name     :    Ke Liu";
    String number = "Student ID: 12021232";

    putText(image, number, Point(W / 3, H/3), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0));
    putText(image, name, Point(W/3, H/2), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));

    addSubPhoto("zheda(1).jpg", 128, 64);
    addSubPhoto("me(1).png", W/2-53, H/3*2+20);
    addCurrentTime(W/3, H/3*2);
    putPicture(writer, image);
}

void drawZJUPhoto(){
    image = imread("yq(1).png", IMREAD_COLOR);
    // putPicture(writer, image);
    delay(40);
    image = imread("zjui(1).png", IMREAD_COLOR);
    // putPicture(writer, image);
    delay(40);
    image = imread("zjg(1).png", IMREAD_COLOR);
    // putPicture(writer, image);
    delay(40);
}




void drawTank(){
    drawLine(image, Point(100,600), Point(500,600), Scalar(255, 0, 0), 2, 10, true);
    drawLine(image, Point(500,600), Point(500,500), Scalar(255, 0, 0), 2, 10, true);
    drawLine(image, Point(500,500), Point(100,500), Scalar(255, 0, 0), 2, 10, true);
    drawLine(image, Point(100,500), Point(100,600), Scalar(255, 0, 0), 2, 10, true);
    // drawLine(image, Point(200,500), Point(350,500), Scalar(255, 0, 0), 2, 10);
    drawLine(image, Point(150,500), Point(150,400), Scalar(255, 0, 0), 2, 10, true);
    drawLine(image, Point(150,400), Point(300,400), Scalar(255, 0, 0), 2, 10, true);
    drawLine(image, Point(300,400), Point(300,500), Scalar(255, 0, 0), 2, 10, true);

    drawLine(image, Point(300,420), Point(350,420), Scalar(255, 0, 0), 2, 10, true);
    drawLine(image, Point(350,420), Point(350,480), Scalar(255, 0, 0), 2, 10, true);
    drawLine(image, Point(350,480), Point(300,480), Scalar(255, 0, 0), 2, 10, true);

    drawArc(image, Point(225,400), 50.0, PI, 2*PI, Scalar(255, 0, 0), 2, 10, true);

    drawLine(image, Point(350,440), Point(510,440), Scalar(255, 0, 0), 2, 10, true);
    drawLine(image, Point(510,440), Point(510,460), Scalar(255, 0, 0), 2, 10, true);
    drawLine(image, Point(510,460), Point(350,460), Scalar(255, 0, 0), 2, 10, true);
}

void drawMan(){
    drawArc(image, Point(755, 450), 30, 0 , 2*PI, Scalar(0, 255, 0), 1, 10, true);
    drawLine(image, Point(755,480), Point(755,520), Scalar(0, 255, 0), 2, 5, true);
    drawLine(image, Point(755,520), Point(730,540), Scalar(0, 255, 0), 2, 5, true);
    drawLine(image, Point(755,520), Point(780,540), Scalar(0, 255, 0), 2, 5, true);

    drawLine(image, Point(755,490), Point(740,510), Scalar(0, 255, 0), 2, 5, true);
    drawLine(image, Point(755,490), Point(765,510), Scalar(0, 255, 0), 2, 5, true);
}

void deleteMan(){
    drawArc(image, Point(755, 450), 30, 0 , 2*PI, Scalar(255, 255, 255), 1, 10, false);
    drawLine(image, Point(755,480), Point(755,520), Scalar(255, 255, 255), 2, 5, false);
    drawLine(image, Point(755,520), Point(730,540), Scalar(255, 255, 255), 2, 5, false);
    drawLine(image, Point(755,520), Point(780,540), Scalar(255, 255, 255), 2, 5, false);

    drawLine(image, Point(755,490), Point(740,510), Scalar(255, 255, 255), 2, 5, false);
    drawLine(image, Point(755,490), Point(765,510), Scalar(255, 255, 255), 2, 5, false);
}

void drawMan2(){
    drawArc(image, Point(775, 455), 30, 0 , 2*PI, Scalar(0, 255, 0), 1, 10, false);
    drawLine(image, Point(765,483), Point(745,520), Scalar(0, 255, 0), 2, 3, false);
    drawLine(image, Point(755,501), Point(743,501), Scalar(0, 255, 0), 2, 3, false);
    drawLine(image, Point(743,501), Point(743,485), Scalar(0, 255, 0), 2, 3, false);
    drawLine(image, Point(755,501), Point(765,521), Scalar(0, 255, 0), 2, 3, false);

    drawLine(image, Point(745,520), Point(725,525), Scalar(0, 255, 0), 2, 3, false);
    drawLine(image, Point(745,520), Point(760,535), Scalar(0, 255, 0), 2, 3, false);
    delay(60);
}

void drawBullet(){
    drawArc(image, Point(520, 450), 3, 0 , 2*PI, Scalar(0, 0, 255), 1, 8, true);
    drawArc(image, Point(520, 450), 3, 0 , 2*PI, Scalar(255, 255, 255), 1, 8, false);

    for (int center_x=525; center_x<725; center_x+=5){
        drawArc(image, Point(center_x, 450), 3, 0 , 2*PI, Scalar(0, 0, 255), 1, 10, false);
        delay(1);
        drawArc(image, Point(center_x, 450), 3, 0 , 2*PI, Scalar(255, 255, 255), 1, 10, false);
    }
    drawArc(image, Point(725, 450), 3, 0 , 2*PI, Scalar(0, 0, 255), 1, 10, false);
    delay(1);
}

void drawCartoon(){
    drawTank();
    drawMan();
    drawBullet();
    delay(60);
    deleteMan();
    drawMan2();

}


void drawEnding(){
    // drawBackground(image, false);
    Size textsize = getTextSize("I love OpenCV!", FONT_HERSHEY_COMPLEX, 3, 5, 0);
    Point org((W - textsize.width)/2, (H - textsize.height)/2);

    Mat image2;
    for(int i = 0; i < 255; i += 2)
    {
        image2 = image - Scalar::all(i);
        putText(image2, "I love OpenCV!", org, FONT_HERSHEY_COMPLEX, 3, Scalar(i, i, 255));
        putPicture(writer, image2);
    }
}

int main()
{
    printf("making up video\n");
    writer = VideoWriter(path, 0, 30, Size(W, H));
    image= Mat::zeros(H, W, CV_8UC3);
    drawBackground(image, false);
    drawFirstFrame();
    delay(60);
    drawZJUPhoto();
    drawBackground(image, false);
    drawCartoon();
    drawBackground(image, false);
    drawEnding();

    return 0;
}


