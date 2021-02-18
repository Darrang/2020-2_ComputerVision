#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    Mat frame;
    VideoCapture cap;

    if(cap.open("Road.mp4")==0){
        cout << "no such file!" << endl;
        waitKey(0);
    }
    
     double fps = cap.get(CAP_PROP_FPS);
     double framecount = cap.get(CAP_PROP_POS_FRAMES);
     double time_in_msec = cap.get(CAP_PROP_POS_MSEC);
     double total_frames = cap.get(CAP_PROP_FRAME_COUNT);
     
     int delay = cvRound(1000 / fps);

    while(1){
       
        cap >> frame;
        framecount = cap.get(CAP_PROP_POS_FRAMES);
        time_in_msec = cap.get(CAP_PROP_POS_MSEC);

        cout << "frame: " << framecount << " / " << total_frames << endl;
        //if(time_in_msec == 20000) break;
		if(framecount == 660) break;

        if(frame.empty()){
            cout << "end of video" << endl;
            break;
        }
        
        imshow("video",frame);
        waitKey(delay);
    }

}