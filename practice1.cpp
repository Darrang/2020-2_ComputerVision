#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void Middle();


int main(){

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

  while(1){
        cap >> frame;
		if (frame.empty()) break;
		
		//resize
		resize(frame, frame, Size(frame.cols / 2, frame.rows / 2));

		cvtColor(frame, gray_frame, COLOR_BGR2GRAY);

		// face detection
		face_classifier.detectMultiScale(gray_frame, faces,
			1.1,		// increase search scale by 10% each pass
			3,			// merge groups of three detection
			0			// not used for a new cascade
		);

		// draw the result
		for (int i = 0; i < faces.size(); i++) {
			Point lb(faces[i].x, faces[i].y);
			Point tr(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			int size = (tr.x - lb.x) * (tr.y - lb.y);
			
			cout << "size of " << i << " " << size << endl;

			// filter by size
	    	if(size < 2000 && size >1000)
				rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
		}
        imshow("Face detection", frame);
        waitKey(1000/fps);
  	}

		

}
