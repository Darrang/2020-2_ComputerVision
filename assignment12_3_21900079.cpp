#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	// variable for face detection
	CascadeClassifier face_clasifier;
	Mat frame, gray_frame;
	vector<Rect> faces;
	VideoCapture cap(0);
	double fps = cap.get(CAP_PROP_FPS);
	bool initialization = true;
	face_clasifier.load("haarcascade_frontalface_alt.xml");

	// variable for tracking
	Mat m_backproj, hsv;
	vector<Mat> m_model3d;
	vector<Rect> m_rc;
	float hrange[] = { 0,180 };
	float vrange[] = { 0,255 };
	float srange[] = { 0,255 };
	const float* ranges[] = { hrange, srange, vrange }; // hue, saturation, brightness
	int channels[] = { 0, 1, 2 };
	int hist_sizes[] = { 16, 16, 16 };
	bool tracking = false;

	Mat background;


	while (true) {
		background = imread("background.jpeg");
		cap >> frame;
		if (frame.empty()) 
			break;
		resize(frame, frame, Size(frame.cols / 2, frame.rows / 2));
		cvtColor(frame, hsv, COLOR_BGR2HSV);

		if (!initialization)
			tracking = true;

		// if first frame than detect face
		if (initialization) {
			// detect face
			cvtColor(frame, gray_frame, COLOR_BGR2GRAY);
			face_clasifier.detectMultiScale(gray_frame, faces,
				1.2,		// increase search scale by 10% each pass
				3,			// merge groups of three detection
				0			// not used for a new cascade
			);

			// set roi
			for (int i = 0; i < faces.size(); i++) {
				Rect rc = faces[i];
				Mat m_model3d_tmp;

				Mat mask = Mat::zeros(rc.height, rc.width, CV_8U);
				ellipse(mask, Point(rc.width / 2, rc.height / 2), Size(rc.width / 2, rc.height / 2), 0, 0, 360, 255,CV_FILLED);
				Mat roi(hsv, rc);
				calcHist(&roi, 1, channels, mask, m_model3d_tmp, 3, hist_sizes, ranges); // calculate histogram -> get feature
				
				m_rc.push_back(rc);
				m_model3d.push_back(m_model3d_tmp);
			}

			initialization = false;
			// draw the result
			for (int i = 0; i < faces.size(); i++) {
				Point lt(faces[i].x, faces[i].y);
				Point rb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);

				rectangle(frame, lt, rb, Scalar(0, 255, 0), 2, 4, 0);
			}
		}

		// if it is not first frame than tracking face by roi
		if (tracking) {
			for (int i = 0; i < faces.size(); i++) {
				calcBackProject(&hsv, 1, channels, m_model3d[i], m_backproj, ranges); // calculate back project to m_backproj with m_model3d
				CamShift(m_backproj, m_rc[i], TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1));
				rectangle(frame, m_rc[i], Scalar(0,255,0), 2,4,0);
			}
		}


		// image display
		imshow("face detection with tracking", frame);

		// user input
		char ch = waitKey(1000 / fps);
		if (ch == 27) break; // ESC Key (exit)
		else if (ch == 32) { // SPACE Key (pause)
			while ((ch = waitKey(1000 / fps)) != 32 && ch != 27);
			if (ch == 27) break;
		}
	}

}