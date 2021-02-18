#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){
     VideoCapture capture("background.mp4");
    Mat sub,frame, frame_gray, result;
    
    vector<Mat> q_background;

    double fps = capture.get(CV_CAP_PROP_FPS);
    Mat element = getStructuringElement(MORPH_RECT,Size(30,30));       
    Mat element2 = getStructuringElement(MORPH_ELLIPSE,Size(7,7)); 
    while (true) {
    
    vector<vector<Point>> contours;
    vector<Vec4i>hierarchy;

    capture >> frame;
    
    if (frame.empty()) return -1;

    Mat background = Mat(frame.rows,frame.cols,CV_8UC1);
    result = frame.clone();
    cvtColor(frame,frame,CV_BGR2GRAY);
    medianBlur(frame,frame,3);

     if(q_background.size() < 10){
         q_background.insert(q_background.begin(),frame);
     }
   
     for(int i=0; i < q_background.size(); i++){
        add(q_background[i] / (i + 1.0), (background * i) / (i + 1.0), background);
     }
   
    absdiff(background,frame,sub);
    threshold(sub,sub,50,255,THRESH_BINARY);
    morphologyEx(sub,sub,MORPH_CLOSE,element);
    morphologyEx(sub,sub,MORPH_OPEN,element2);

    findContours(sub,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);

    vector<Rect> boundRect(contours.size());
    int people_num=0;
    
    for (int i = 0 ; i < contours.size() ; i++){
            boundRect[i] = boundingRect(Mat(contours[i]));
        }

    for (int i = 0 ; i < contours.size() ; i++){
            if (boundRect[i].area() > 500){ 
                 rectangle(result, boundRect[i].tl(),boundRect[i].br(), Scalar(255, 255, 255), 2, 8);
                 people_num++;  
            }
        }
        
    putText(result,format(" # Number of people: %d", people_num), Point2f(10,30),FONT_HERSHEY_PLAIN,2,Scalar(255,255,255),2);

    imshow("Number of people", result);
    waitKey(1000/fps);
   }

}