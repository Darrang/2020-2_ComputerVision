#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    /*
    int kernel_size = 7;
    cv::Mat in_img, out_img;
    in_img = imread("lena.png");
    cv::Mat kernel = Mat::ones( kernel_size, kernel_size, CV_32F )/ (float)(kernel_size*kernel_size);       
    cv::filter2D(in_img, out_img, -1 , kernel); //filtering

    cv::Size size = in_img.size();
    cv::Rect roi(kernel_size, kernel_size,size.width - 2*kernel_size, size.height - 2*kernel_size);
    cv::Mat cropped = in_img(roi).clone(); //cropping
    imshow("original",in_img);
    imshow("test", cropped);
    waitKey(0);
    */

   Mat image = imread("moon.jpg");
   Mat poly_roi1;
   Mat poly_mask = Mat::zeros(image.size(),image.type());
   Point poly1[1][4];
   poly1[0][0] = Point(0,0);
   poly1[0][1] = Point(image.size().width/2,0);
   poly1[0][2] = Point(image.size().width/2,image.size().height);
   poly1[0][3] = Point(0,image.size().height);

   const Point * ppt1[1] = {poly1[0]};
   int npt1[]={4};
   fillPoly(poly_mask,ppt1,npt1,1,Scalar(255,255,255),8);
    //왼쪽자르기

    image.copyTo(poly_roi1,poly_mask);

   Mat laplacian,convert,sharpening; 
   //filtering
   Laplacian(image,laplacian,CV_16S); //필터링
   convertScaleAbs(laplacian,convert);  //이차미분
   sharpening = convert + image; //원본더해주기

   Mat poly_roi2,dst;
   Mat poly_mask2 = Mat::zeros(sharpening.size(),sharpening.type());
   Point poly2[1][4];
   poly2[0][0] = Point(sharpening.size().width/2+1,0);
   poly2[0][1] = Point(sharpening.size().width,0);
   poly2[0][2] = Point(sharpening.size().width,sharpening.size().height);
   poly2[0][3] = Point(sharpening.size().width/2+1,sharpening.size().height);

   const Point * ppt2[1] = {poly2[0]};
   int npt2[]={4};
   fillPoly(poly_mask2,ppt2,npt2,1,Scalar(255,255,255),0);
    //오른쪽자르기
   sharpening.copyTo(poly_roi2,poly_mask2);

  add(poly_roi1,poly_roi2,dst); //이미지 합치기
 

   imshow("polyROI1",poly_roi1);
   imshow("polyROI2",poly_roi2);
   imshow("sharp",sharpening);
   imshow("add",dst);
   waitKey(0);
}