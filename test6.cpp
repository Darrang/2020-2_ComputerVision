#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// Mat drawHistogram(Mat src);

int main(){

Mat adaptive, at_binary, adaptive_binary;
adaptive = imread("adaptive.png", 0);
threshold(adaptive, at_binary, 0, 255,THRESH_BINARY | THRESH_OTSU);
adaptiveThreshold(adaptive, adaptive_binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 8);
imshow("binary",at_binary);
imshow("adaptvie",adaptive_binary);
waitKey(0);


// Mat image, thresh;
//  	int thresh_T, low_cnt, high_cnt, low_sum, high_sum, i, j, th;
	
// 	thresh_T = 200; // 초기 T값
//  	th = 10; // 초기 T값과 다시 구해진 T값의 차이가 일정크기 이하면 멈추는데 사용하는값
//  	low_cnt = high_cnt = low_sum = high_sum = 0;
	

    //   while (1) {
 	// 	for (j = 0; j < image.rows; j++) {
 	// 		for (i = 0; i < image.cols; i++) {
 	// 			if (image.at<uchar>(j, i) < thresh_T) {
 	// 				low_sum += image.at<uchar>(j, i);
 	// 				low_cnt++;
 	// 			}
 	// 			else {
 	// 				high_sum += image.at<uchar>(j, i);
 	// 				high_cnt++;
 	// 			}
 	// 		}
 	// 	}
 	// 	if (abs(thresh_T - (low_sum / low_cnt + high_sum / high_cnt) / 2.0f) < th) { // 새로운 T값 < th일때 
 	// 		break; // 멈춤
 	// 	}
 	// 	else {
 	// 		thresh_T = (low_sum / low_cnt + high_sum / high_cnt) / 2.0f;
 	// 		cout << "threshold value:" << thresh_T << endl;
 	// 		low_cnt = high_cnt = low_sum = high_sum = 0;
 	// 	}
 	// }
 	// threshold(image, thresh, thresh_T, 255, THRESH_BINARY);
	
 	// imshow("Input image", image);
 	// imshow("thresholding", thresh);

    // waitKey(0); 

}

//     Mat input_image = imread("moon.png",0);
//     Mat hist_equalization;
//     Mat hist_graph;
//     Mat hist_equalized_graph;

//     int w = input_image.cols;
//     int h = input_image.rows;

//      if(!input_image.data) exit(1);

//     equalizeHist(input_image,hist_equalization);

//     hist_graph = drawHistogram(input_image);
//     hist_equalized_graph = drawHistogram(hist_equalization);
    
//     imshow("before",input_image);
//     imshow("after",hist_equalization);
//     imshow("h1",hist_graph);
//     imshow("h2",hist_equalized_graph);
//     waitKey(0);
    
//     return 0;
// }


// Mat drawHistogram(Mat src){

// Mat hist, histImage;
// //establish the number of bins
// int i, y, hist_w,bin_w, hist_h, histSize;
// float range[] = { 0, 256 };
// const float* histRange = { range };

// float sum = 0;

// hist_w = 512;
// hist_h = 512;
// histSize = 200;
// bin_w = cvRound((double)hist_w / histSize);//draw the histogram

// histImage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));// compute the histograms

// calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);
// normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

// for (i= 0; i< histSize; i++)
//  {
//     rectangle(histImage, Point(bin_w* i, hist_h), Point(bin_w* i+hist_w/histSize, hist_h-cvRound(hist.at<float>(i))), Scalar(0, 0, 0), -1);
//     sum += hist.at<float>(i);
//  }

// int x=1;
// for (i = 0,y = 20; i < histSize; i++, y = y+15)
//  {
//    if(i%2==1){
//         putText(src,format("bin %d : %f",x++, hist.at<float>(i)/sum + hist.at<float>(i-1)/sum),Point(10,y),FONT_HERSHEY_SIMPLEX,1,Scalar(255,255,255),2);
//    }
    
//  }
 
//  return histImage;




// Mat image, thresh;
// 	int thresh_T, low_cnt, high_cnt, low_sum, high_sum, i, j, th;
	
// 	thresh_T = 200; // 초기 T값
// 	th = 10; // 초기 T값과 다시 구해진 T값의 차이가 일정크기 이하면 멈추는데 사용하는값
// 	low_cnt = high_cnt = low_sum = high_sum = 0;
	
// 	image = imread("finger_print.png", 0);
// 	cout << "threshold value:" << thresh_T << endl;
	
// 	while (1) {
// 		for (j = 0; j < image.rows; j++) {
// 			for (i = 0; i < image.cols; i++) {
// 				if (image.at<uchar>(j, i) < thresh_T) {
// 					low_sum += image.at<uchar>(j, i);
// 					low_cnt++;
// 				}
// 				else {
// 					high_sum += image.at<uchar>(j, i);
// 					high_cnt++;
// 				}
// 			}
// 		}
// 		if (abs(thresh_T - (low_sum / low_cnt + high_sum / high_cnt) / 2.0f) < th) { // 새로운 T값 < th일때 
// 			break; // 멈춤
// 		}
// 		else {
// 			thresh_T = (low_sum / low_cnt + high_sum / high_cnt) / 2.0f;
// 			cout << "threshold value:" << thresh_T << endl;
// 			low_cnt = high_cnt = low_sum = high_sum = 0;
// 		}
// 	}
// 	threshold(image, thresh, thresh_T, 255, THRESH_BINARY);
	
// 	imshow("Input image", image);
// 	imshow("thresholding", thresh);