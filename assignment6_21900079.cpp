#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    Mat canny; //input image
    Mat canny_left; 
    Mat canny_right; 
    Mat left_roi; //roi 왼쪽
    Mat right_roi; //roi 오른쪽
    Mat blur_left,blur_right; //블러
    Mat left_dst, right_dst; //아웃풋

    VideoCapture cap("Road.mp4"); // 동영상 받는 클래스

    if(cap.open("Road.mp4") == 0){
        cout << "no such file!" << endl;
        waitKey(0);
    }

    double fps = cap.get(CAP_PROP_FPS);
    int delay = 1000 / fps;
        
    namedWindow("Left canny");
    moveWindow("Left canny", 200,0);

    namedWindow("Right canny");
    moveWindow("Right canny",600,0);

    while(1){
       
        cap >> canny;

        if(canny.empty()){
            cout << "end of video" << endl;
            break;
        }
    
        Rect rect1(200,400,400,200); //왼쪽
        Rect rect2(600,400,400,200); //오른쪽

        left_roi = canny(rect1); //왼쪽 자르기
        right_roi = canny(rect2); //오른쪽 자르기

        cvtColor(left_roi,canny_left,CV_BGR2GRAY); // 왼쪽 그레이변환
        cvtColor(right_roi,canny_right,CV_BGR2GRAY); //오른쪽 그레이변환
        
        blur(canny_left,blur_left,Size(5,5)); //왼쪽 블러
        blur(canny_right,blur_right,Size(5,5)); //오른쪽 블러
        
        //캐니함수 사용
        Canny(blur_left,left_dst,10,60); //왼쪽 캐니
        Canny(blur_right,right_dst,10,60); //오른쪽 캐니

        imshow("Left canny",left_dst);
        imshow("Right canny",right_dst);

        int key = waitKey(delay);
        if(key==27) break;

    }

}