
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	VideoCapture capture("background.mp4");
	Mat background, image, gray, result, foregroundMask, foregroundImg;
	double fps = capture.get(CAP_PROP_FPS);
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(15, 15));

	//set the first frame as background
	capture >> background;
	cvtColor(background, background, CV_BGR2GRAY);

	while (waitKey(1000 / fps) != 27) {
		if (capture.grab() == 0) break;
		capture.retrieve(image);

		cvtColor(image, gray, CV_BGR2GRAY);

		absdiff(background, gray, foregroundMask);
		morphologyEx(foregroundMask,foregroundMask,MORPH_CLOSE, element);
		threshold(foregroundMask, foregroundMask, 50, 255, CV_THRESH_BINARY);

		//foregroundMask.copyTo(foregroundImg);
		foregroundImg.setTo(Scalar(0));
		gray.copyTo(foregroundImg, foregroundMask);

		imshow("foregroundImg", foregroundImg);
		imshow("foregroundMask", foregroundMask);
		imshow("background", background);
		imshow("original", gray);
	}
	return 0;
}