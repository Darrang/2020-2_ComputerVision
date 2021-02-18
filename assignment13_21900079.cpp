#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
//face detection Variable
Mat result, bgModel, fgModel, frame, gray_frame, foreground,background;
vector<Rect> faces;
CascadeClassifier face_classifier;

//face tracking Variable
Mat hsv, m_backproj;
Mat m_model3d;
Rect rect2;

float hrange[] = { 0,180 };
float vrange[] = { 0,255 };
const float* ranges[] = { hrange, vrange, vrange }; // hue, saturation, brightness
int channels[] = { 0, 1, 2 };
int hist_sizes[] = { 16, 16, 16 };

//open camera
	VideoCapture cap(0);
	float fps = cap.get(CV_CAP_PROP_FPS);

	if (!cap.isOpened()) {
		cout << "can't open file" << endl;
		return 0;
	}

face_classifier.load("haarcascade_frontalface_alt.xml");

while(1){
	//load background img
	background = imread("background.jpg");

	//get frame
    cap >> frame;

	if(frame.empty()){
				cout << "end of video" << endl;
				break;
			}
	
	//resize
	resize(background,background,Size(background.cols / 2,background.rows / 2));
	resize(frame,frame,Size(background.cols,background.rows));

	//convert to gray img
    cvtColor(frame, gray_frame, CV_BGR2GRAY);
	equalizeHist(gray_frame, gray_frame);

	//convert to HSV img
	cvtColor(frame,hsv,CV_BGR2HSV);

	//face detection
    face_classifier.detectMultiScale(
		gray_frame, 
		faces,
			1.1,		
			3,			
			0,
			Size(30,30)			
		);

		if(faces.size()!=0){
			//set roi
			Rect rectangle(faces[0].x,faces[0].y,faces[0].width,faces[0].height);
			rect2 = rectangle;

			Mat mask = Mat::zeros(faces[0].height, faces[0].width, CV_8U);
			ellipse(mask, Point(faces[0].width / 2, faces[0].height / 2), Size(faces[0].width / 2, faces[0].height / 2), 0, 0, 360, 255, CV_FILLED);
			Mat roi(hsv, rectangle);
			calcHist(&roi, 1, channels, mask, m_model3d, 3, hist_sizes, ranges);
		}

		calcBackProject(&hsv, 1, channels, m_model3d, m_backproj, ranges);
		CamShift(m_backproj, rect2, cvTermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 20,1));

		//get foreground img
		grabCut(frame, result, rect2, bgModel, fgModel, 10, GC_INIT_WITH_RECT);
		compare(result, GC_PR_FGD, result, CMP_EQ);
		
		//deep copy to background
 		frame.copyTo(background, result);
	
		// print the output
		imshow("Project3",background);
		char key = waitKey(33);
		if(key==27)break;
	}
}