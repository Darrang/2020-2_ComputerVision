#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){

    VideoCapture cap("background.mp4");
    Mat sub,frame, frame_gray, result;
    
    vector<Mat> q_background;
    vector<Rect> found;

    if(!cap.isOpened()){
        cout << "can't open video file" << endl;
        return 0;
    }

    double fps = cap.get(CV_CAP_PROP_FPS);
    Mat element = getStructuringElement(MORPH_RECT,Size(30,30));       
    
    HOGDescriptor hog(
            Size(48, 96),
            Size(16, 16),
            Size(8, 8),
            Size(8, 8),
            9);
        
    hog.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());

    while(1){
        cap >> frame;

        if(frame.empty()) break;

        hog.detectMultiScale(
            frame,
            found,
            1.2,
            Size(8,8),
            Size(32,32),
            1.05
        );

        for(int i=0; i<(int)found.size();i++)
            rectangle(frame, found[i],Scalar(0,255,0),2);

        imshow("Pedestrian Detection", frame);
        waitKey(1000/fps);
    }

}