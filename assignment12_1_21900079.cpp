#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void Near(VideoCapture);
void Middle(VideoCapture);
void Far(VideoCapture);

int main(){
	char ch;
	char userinput;
	bool is_middle = false;
	bool is_far = false;
	bool is_near = false;

	Mat frame, gray_frame;
	vector<Rect> faces;

	CascadeClassifier face_classifier;
	VideoCapture cap("Faces.mp4");
	double fps = cap.get(CAP_PROP_FPS);

	if(!cap.isOpened()){
		cout << "could not open file";
		exit(-1);
	}

  face_classifier.load("haarcascade_frontalface_alt.xml");	
	
	while(ch!=27){

		cap >> frame;
		if (frame.empty()) break;
		
		//resize
		resize(frame, frame, Size(frame.cols / 2, frame.rows / 2));

		cvtColor(frame, gray_frame, COLOR_BGR2GRAY);

		// face detection
		face_classifier.detectMultiScale(gray_frame, faces,
			1.1,		
			3,			
			0			
		);
		
		if(ch == 110 || is_near){
			for (int i = 0; i < faces.size(); i++) {
				Point lb(faces[i].x, faces[i].y);
				Point tr(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
				int size = (tr.x - lb.x) * (tr.y - lb.y);

				if(size > 1000 && size < 2000)
					rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
			}
			
			if(ch==102 || ch==109){
				is_near = false;
			}

			is_near = true;
			is_middle = false;
			is_far = false;
			
		}

		if(ch == 102 || is_far){
			for (int i = 0; i < faces.size(); i++) {
				Point lb(faces[i].x, faces[i].y);
				Point tr(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
				int size = (tr.x - lb.x) * (tr.y - lb.y);
				
				if(size > 400 && size < 500)
					rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
			}
			if(ch == 110||ch == 109)
				is_far = false;	

			is_near = false;
			is_middle = false;
			is_far = true;
		}
	

		if(ch == 109 || is_middle){
			for (int i = 0; i < faces.size(); i++) {
				Point lb(faces[i].x, faces[i].y);
				Point tr(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
				int size = (tr.x - lb.x) * (tr.y - lb.y);

				if(size > 600 && size < 900)
					rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
			}
			
			if(ch==110||ch==102)
			is_middle = false;
			
			is_near = false;
			is_middle = true;
			is_far = false;

		}

		imshow("Faces", frame);
		ch = waitKey(1000/fps);
	}

}

