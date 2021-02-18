#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    CascadeClassifier face_classifier;
    VideoCapture cap(0);
    vector<Rect> faces;
    Mat frame, grayframe, result, bgModel, fgModel, background;
    double fps = cap.get(CV_CAP_PROP_FPS);
    bool tracking = false;

    if(!cap.isOpened()){
        cout << "Cannot open cap" << endl;
        return -1;
    }

    face_classifier.load("haarcascade_frontalface_alt.xml");

    while(1){
        cap >> frame;
        background = imread("background.jpeg");
        resize(frame, frame, Size(300, 200));
        resize(background, background, Size(300, 200));

        if(frame.empty()) break;

        cvtColor(frame, grayframe, COLOR_BGR2GRAY);

        face_classifier.detectMultiScale(grayframe, faces, 1.1, 3, 0, Size(30,30));

        for(int i=0; i<faces.size(); i++){
            Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
            Point tr(faces[i].x, faces[i].y);
            Rect rectangle(lb, tr);
            grabCut(frame, result, rectangle, bgModel, fgModel, 10, GC_INIT_WITH_RECT);
            compare(result, GC_PR_FGD, result, CMP_EQ);
        }
        frame.copyTo(background, result);

        imshow("Face Detection", frame);
        imshow("Result", result);
        imshow("Foreground", background);

        if(waitKey(33) == 27) break;
    }

    return 0;
}