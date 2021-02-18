#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){

Mat input = imread("namecard.JPG");

if(input.empty()){
    cerr << "read fail!" << endl;
    exit(-1);
}
//load image

Mat HSV;
Mat canny;

resize(input,input,Size(input.cols/4,input.rows/4)); //resize
 
Mat origin = input.clone(); //copy 원본이미지 

GaussianBlur(input,input,Size(7,7),2);
cvtColor(input,HSV,CV_BGR2HSV);  //convert to hsv
inRange(HSV, Scalar(105, 0, 0), Scalar(135, 255, 255), HSV); //파란색 기준 이진화 

Mat element = getStructuringElement(MORPH_RECT,Size(10,10));       
Mat element2 = getStructuringElement(MORPH_ELLIPSE,Size(7,7)); 

morphologyEx(HSV,HSV,MORPH_CLOSE,element);  //morphology
morphologyEx(HSV,HSV,MORPH_OPEN,element2);  //morphology

vector<vector<Point>> contours;
vector<Vec4i>hierarchy;

findContours(HSV,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE); //find contours

vector<Point2f> poly;

//꼭짓점 찾기 
for (int i = 0 ; i < contours.size() ; i++){   
    
    approxPolyDP(Mat(contours[i]),poly,arcLength(Mat(contours[i]),true) * 0.02,true);
    
}
    //poly[0];  오른쪽 위  TopRight
    //poly[3];  오른쪽 아래  BottomRight

    //poly[1];  왼쪽 위  TopLeft
    //poly[2];  왼쪽 아래 BottomLeft

   double w1 = sqrt(pow(poly[3].x - poly[2].x,2) + pow(poly[3].x - poly[2].x,2));
   double w2 = sqrt(pow(poly[0].x - poly[1].x,2) + pow(poly[0].x - poly[1].x,2));
  
   double h1 = sqrt(pow(poly[0].y - poly[3].y ,2) + pow(poly[0].y - poly[3].y,2));
   double h2 = sqrt(pow(poly[1].y - poly[2].y,2) +pow(poly[1].y - poly[2].y,2));

   double maxWidth = (w1 < w2) ? w1 : w2;
   double maxHeight = (h1 < h2) ? h1 : h2;

   Point2f src[4], dst[4];
   src[0] = Point2f(poly[1].x,poly[1].y);
   src[1] = Point2f(poly[0].x,poly[0].y);
   src[2] = Point2f(poly[3].x,poly[3].y);
   src[3] = Point2f(poly[2].x , poly[2].y);

   dst[0] = Point2f(0,0);
   dst[1] = Point2f(maxWidth-1,0);
   dst[2] = Point2f(maxWidth-1,maxHeight-1);
   dst[3] = Point2f(0,maxHeight-1);

   Mat transform = getPerspectiveTransform(src,dst);

   warpPerspective(origin,origin, transform,Size(maxWidth,maxHeight));

   imshow("Project4",origin);

   waitKey(0);
   return 0;
}
