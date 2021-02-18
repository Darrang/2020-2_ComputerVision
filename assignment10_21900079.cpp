#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main(){

    VideoCapture capture("background.mp4");
    Mat sub,frame, frame_gray, result;
    
    vector<Mat> q_background;

    double fps = capture.get(CV_CAP_PROP_FPS);

    while (true) {
    
    vector<vector<Point>> contours;
    vector<Vec4i>hierarchy;

    capture >> frame;
    
    if (frame.empty()) return -1;

    Mat background = Mat(frame.rows,frame.cols,CV_8UC1);
    cvtColor(frame,frame,CV_BGR2GRAY);
    result = frame.clone();

    if(q_background.size() < 10){
        q_background.insert(q_background.begin(),frame);
    }
   
    for(int i=0; i < q_background.size(); i++){
        add(q_background[i] / (i + 1.0), (background * i) / (i + 1.0), background);
    }

    absdiff(background,frame,sub);
    threshold(sub,sub,20,255,THRESH_BINARY);

    findContours(sub,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);

    vector<Rect> boundRect(contours.size());
    int rect_num=0;
    
    for (int i = 0 ; i < contours.size() ; i++){
            boundRect[i] = boundingRect(Mat(contours[i])); 
            if (boundRect[i].area() > 400){ 
                rectangle(result, boundRect[i], Scalar(255, 255, 255), 2, 8); 
                rect_num++; 
            }
        }

    putText(result,format(" # Rect: %d", rect_num), Point2f(10,30),FONT_HERSHEY_PLAIN,2,Scalar(255,255,255),2);

    imshow("background subtraction", result);
    waitKey(1000/fps);
   }

}
