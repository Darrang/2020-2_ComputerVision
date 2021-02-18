#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){
        Mat image,negative_img;
        image = imread("lena.png", '0');
        imshow("original",image);
//negative transformation
  
    negative_img = image.clone();

    for (int y = 0; y < image.rows; y++)
        for (int x = 0; x < image.cols; x++)
            negative_img.at<uchar>(y, x) = 255 - negative_img.at<uchar>(y, x);

        imshow("Negative transformation", negative_img);
       
//log transformation
    Mat log_img, float_img;
    image.convertTo(float_img,CV_32F);
    
    log(abs(float_img)+1, float_img);

    normalize(float_img, float_img, 0, 255, NORM_MINMAX);
    convertScaleAbs(float_img,log_img,1.5);
    imshow("Log transformation",log_img);

//gamma transformation

Mat gamma_img = image.clone();
float gamma_trans[256];
float gamma_value = 0.5;
MatIterator_<uchar> it, end; 

for(int i=0;i<256;i++){
    gamma_trans[i] =  saturate_cast<uchar>(pow((i/255.0),gamma_value) * 255.0f); //감마 계산하기
}

for(it = gamma_img.begin<uchar>(),end = gamma_img.end<uchar>(); it != end; ++it){
   (*it) =  gamma_trans[*it];
}
  imshow("Gamma transformation",gamma_img);
    waitKey(0);
   return 0;
 
}
