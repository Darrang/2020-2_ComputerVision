#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    
    ///////////////Average filtering//////////////
    Mat lena_origin = imread("lena.png"); 
    Mat lena_image = lena_origin.clone();

    int width = lena_image.size().width; //cols
    int height = lena_image.size().height; //rows

    Rect rect(0,0,width/2,height); //왼쪽 블러처리
    Mat output(lena_image, rect);
    blur(output, output, Size(7,7));

    imshow("lena",lena_origin);
    imshow("lena_filtered",lena_image);

  ///////////////////////////sharping///////////////
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
   Laplacian(image,laplacian,CV_16S);//이차미분
   convertScaleAbs(laplacian,convert);  
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

   imshow("moon",image);
   imshow("moon_filtered",dst);
   
  /////////////////////medianBlur////////////////////
  Mat salt_image = imread("saltnpepper.png");
  Mat salt_filterd;
  medianBlur(salt_image,salt_filterd,9);
  
  imshow("saltnpepper",salt_image);
  imshow("saltnpepper_filterd",salt_filterd);
  waitKey(0);

}