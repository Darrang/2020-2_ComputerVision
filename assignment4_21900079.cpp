#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat drawHistogram(Mat src);

int main(){

    Mat input_image = imread("moon.png",0);
    Mat hist_equalization;
    Mat hist_graph;
    Mat hist_equalized_graph;

    int w = input_image.cols;
    int h = input_image.rows;

     if(!input_image.data) exit(1);

    equalizeHist(input_image,hist_equalization);

    hist_graph = drawHistogram(input_image);
    hist_equalized_graph = drawHistogram(hist_equalization);
    
    imshow("before",input_image);
    imshow("after",hist_equalization);
    imshow("h1",hist_graph);
    imshow("h2",hist_equalized_graph);
    waitKey(0);
    
    return 0;
}


Mat drawHistogram(Mat src){

Mat hist, histImage;
//establish the number of bins
int i, y, hist_w,bin_w, hist_h, histSize;
float range[] = { 0, 256 };
const float* histRange = { range };

float sum = 0;

hist_w = 512;
hist_h = 512;
histSize = 16;
bin_w = cvRound((double)hist_w / histSize);//draw the histogram

histImage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));// compute the histograms

calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);
normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

for (i= 0; i< histSize; i++)
 {
    rectangle(histImage, Point(bin_w* i, hist_h), Point(bin_w* i+hist_w/histSize, hist_h-cvRound(hist.at<float>(i))), Scalar(0, 0, 0), -1);
    sum += hist.at<float>(i);
 }

int x=1;
for (i = 0,y = 20; i < histSize; i++, y = y+15)
 {
   if(i%2==1){
        putText(src,format("bin %d : %f",x++, hist.at<float>(i)/sum + hist.at<float>(i-1)/sum),Point(10,y),FONT_HERSHEY_SIMPLEX,1,Scalar(255,255,255),2);
   }
    
 }
 
 return histImage;

}

