#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {

    //Global thresholding(basic method)
    Mat image2, thresh;
	int thresh_T, low_cnt, high_cnt, low_sum, high_sum, i, j, th;
	
	thresh_T = 200; // 초기 T값
	th = 10; // 초기 T값과 다시 구해진 T값의 차이가 일정크기 이하면 멈추는데 사용하는값
	low_cnt = high_cnt = low_sum = high_sum = 0;
	
    image2 = imread("finger_print.png", 0);
	
    while (1) {
		for (j = 0; j < image2.rows; j++) {
			for (i = 0; i < image2.cols; i++) {
				if (image2.at<uchar>(j, i) < thresh_T) {
					low_sum += image2.at<uchar>(j, i);
					low_cnt++;
				}
				else {
					high_sum += image2.at<uchar>(j, i);
					high_cnt++;
				}
			}
		}
		if (abs(thresh_T - (low_sum / low_cnt + high_sum / high_cnt) / 2.0f) < th) { // 새로운 T값 < th일때 
			break; // 멈춤
		}
		else {
			thresh_T = (low_sum / low_cnt + high_sum / high_cnt) / 2.0f;
			low_cnt = high_cnt = low_sum = high_sum = 0;
		}
	}
	threshold(image2, thresh, thresh_T, 255, THRESH_BINARY);
	imshow("finger_print", thresh);


    //Local Thresholding
    //adaptive_1(Adaptive)
    Mat adaptive_1, at1_binary, at1_adaptive_binary;
    adaptive_1 = imread("adaptive_1.jpg", 0);
    threshold(adaptive_1, at1_binary, 150, 255, THRESH_BINARY);
    adaptiveThreshold(adaptive_1, at1_adaptive_binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 85, 15);
	imshow("adaptive_1", at1_adaptive_binary);
   

    //adaptive(Adaptive)    
    Mat adaptive, at_binary, adaptive_binary;
    adaptive = imread("adaptive.png", 0);
    threshold(adaptive, at_binary, 0, 255,THRESH_BINARY | THRESH_OTSU);
    adaptiveThreshold(adaptive, adaptive_binary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, 4);

    imshow("adaptive",adaptive_binary);
    waitKey(0);

}
