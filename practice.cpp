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

//for(int i=1;i<9;i++){
    // putText(input_image,format("bin %d : %f",i,bin),Point(10,10),FONT_HERSHEY_SIMPLEX,1,Scalar(255,255,255),4);
//}

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
int sum, total_bin;

hist_w = 512;
hist_h = 512;
histSize = 16;
bin_w = cvRound((double)hist_w / histSize);//draw the histogram

histImage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));// compute the histograms
// &src: input image, 1: #of srcimage, 0: #of channels numerated from 0 ~ channels()-1, Mat(): optional mask
// hist: output histogram, 1: histogram dimension, &histSize: array of histogram size,  &histRange: array of histogram’s boundaries
calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);
// Fit the histogram to [0, histImage.rows]
// hist: input Mat, hist: output Mat, 0: lower range boundary of range normalization, histImage.rows: upper range boundary
// NORM_MINMAX: normalization type, -1: when negative, the ouputarray has the same type as src, Mat(): optional mask
normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

for (int i = 0; i < hist.rows; i++)
{
        int idx = abs(histImage.at<float>(i) - i);
        if (hist.at<float>(idx) > 0)
           total_bin = idx * bin_w;
}


for (i= 0; i< histSize; i++)
 {
    rectangle(histImage, Point(bin_w* i, hist_h), Point(bin_w* i+hist_w/histSize, hist_h-cvRound(hist.at<float>(i))), Scalar(0, 0, 0), -1);
 }

for (i= 0,y = 50; i< 8; i++,y=y+30)
 {
    putText(src,format("bin %d : %f",i+1, total_bin),Point(10,y),FONT_HERSHEY_SIMPLEX,1,Scalar(255,255,255),2);
 }

 return histImage;
}

/*
 for (int y = 0; y < image.rows; y++)
        for (int x = 0; x < image.cols; x++)
            negative_img.at<uchar>(y, x) = 255 - negative_img.at<uchar>(y, x);

*/