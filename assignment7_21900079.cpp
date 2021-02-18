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

    vector<Vec2f> linesL, linesR;

    float a1=0,b1=0,x0=0,y0=0,a2=0,b2=0,x1=0,y1=0,rho_left=0,
     rho_right=0,rho_left_avg=0,rho_right_avg=0,theta_left=0, theta_right=0,theta_left_avg=0,theta_right_avg=0;

    VideoCapture cap("Road.mp4"); // 동영상 받는 클래스

    if(cap.open("Road.mp4") == 0){
        cout << "no such file!" << endl;
        waitKey(0);
    }

    double fps = cap.get(CAP_PROP_FPS);
    double framecount = cap.get(CAP_PROP_POS_FRAMES);
    
    int delay = 1000 / fps;


    while(1){
       
        cap >> canny;

        fps = cap.get(CAP_PROP_FPS);

        framecount = cap.get(CAP_PROP_POS_FRAMES);
        if(framecount == 660) break;

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

       HoughLines(left_dst,linesL,1,CV_PI / 180, 100, 0, 0, CV_PI/6, CV_PI/3); //왼쪽 직선 검출
       HoughLines(right_dst,linesR,1,CV_PI / 180, 100, 0, 0, (CV_PI/3) * 2, (CV_PI/6) * 5); //오른쪽 직선 검출     
      
        rho_left = 0;
        theta_left = 0;
        for(int i = 0; i< linesL.size(); i++){
            rho_left += linesL[i][0];
            theta_left += linesL[i][1];
        }

        if(linesL.size() > 0){
            rho_left_avg = rho_left / linesL.size();
            theta_left_avg = theta_left / linesL.size();
        
            a1 = cos(theta_left_avg);
            b1 = sin(theta_left_avg);
            x0 = a1*rho_left_avg + 200;
            y0 = b1*rho_left_avg + 400;

            Point p1_left(cvRound(x0 + 1000 * (-b1)), cvRound(y0 + 1000 * a1));
            Point p2_left(cvRound(x0 - 1000 * (-b1)), cvRound(y0 - 1000 * a1));

            line(canny, p1_left, p2_left, Scalar(0,0,255), 3, 8);
       
       }

        rho_right = 0;
        theta_right=0;

        for(int i = 0; i< linesR.size(); i++){
            rho_right += linesR[i][0];
            theta_right += linesR[i][1];
        }
        
        if(linesR.size() > 0){
            rho_right_avg = rho_right / linesR.size();
            theta_right_avg = theta_right / linesR.size();

            a2 = cos(theta_right_avg);
            b2 = sin(theta_right_avg);
            x1 = a2*rho_right_avg+600;
            y1 = b2*rho_right_avg+400;

            Point p1(cvRound(x1 + 1000 * (-b2)), cvRound(y1 + 1000 * a2));
            Point p2(cvRound(x1 - 1000 * (-b2)), cvRound(y1 - 1000 * a2));

            line(canny, p1, p2, Scalar(0,0,255), 3, 8);
       }
    
         imshow("Frame",canny);
         waitKey(delay);
       
    }
}