#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    
  VideoCapture capture("background.mp4");
    Mat sub,frame,background, result,foregroundImg,Img;
    
    double fps = capture.get(CV_CAP_PROP_FPS);
     Mat element = getStructuringElement(MORPH_RECT,Size(30,30));
    
    capture >> background;
    cvtColor(background, background, CV_BGR2GRAY);

    while (true) {
    vector<vector<Point>> contours;
    vector<Vec4i>hierarchy;
    capture >> frame;
    
    if (frame.empty()) return -1;

    cvtColor(frame,frame,CV_BGR2GRAY);
    result = frame.clone();

    


    absdiff(background, frame, sub);	
    threshold(sub, sub, 40, 255, THRESH_BINARY);
    morphologyEx(sub, sub, MORPH_CLOSE, element);
    findContours(sub,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);

     vector<Rect> boundRect(contours.size());
    int people_num=0;
    
    for (int i = 0 ; i < contours.size() ; i++){
            boundRect[i] = boundingRect(Mat(contours[i])); 
        }

for (int i = 0 ; i < contours.size() ; i++){
            if (boundRect[i].area() > 600){ 
                 rectangle(result, boundRect[i].tl(),boundRect[i].br(), Scalar(255, 255, 255), 2, 8);
                 people_num++;  
            }
            
        }
         
    putText(result,format(" # Number of people: %d", people_num), Point2f(10,30),FONT_HERSHEY_PLAIN,2,Scalar(255,255,255),2);

        imshow("Number of people",result);
        imshow("binary",sub);
        waitKey(1000/fps);
    }
    return 0;
}