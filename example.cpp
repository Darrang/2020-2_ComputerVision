#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string>

using namespace cv;
using namespace std;

int main() {
	Mat image = imread("lena.png");
	Mat after_convertTo, after_convertScaleAbs;
	imshow("original", image);
	image.convertTo(after_convertTo, CV_16SC1); // 16비트 short?로 변환됨 채널1개.
	cout << "Image Type :" << image.type() << "\n"; 
	imshow("after convertTo", after_convertTo); // imshow에서는 영상이 8비트라고 가정하기 때문에 회색조 영상 출력됨.
	
	convertScaleAbs(image, after_convertScaleAbs, 2, 3); // 각각 픽셀에 2 곱하고 3 더함
	cout << "Image Type :" << image.type() << "\n";
	imshow("after convertScaleAbs", after_convertScaleAbs);

	image.setTo(Scalar(0)); // 입력영상을 scalar(0), 즉 0으로 설정 -> 검은화면 나옴
	cout << "Image Type :" << image.type() << "\n";
	imshow("after setTo", image);
	waitKey(0);

}