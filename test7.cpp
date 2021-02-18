#include "cv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    VideoCapture cap ("background.mp4");
    Mat image, sub, result;
    double fps = cap.get(CV_CAP_PROP_FPS);
    vector<Mat> Background_Queue; // 배경 10개를 저장하는 큐
   
    while(1){
        vector<vector<Point>> contours;
        vector<Vec4i>hierarchy;
        
        cap >> image; // 첫 프레임 넣기
        result = image.clone(); // 첫 프레임을 result에 저장
        if(image.empty()) return -1;
        
        Mat background = Mat::zeros(image.rows, image.cols, CV_8UC1); // 배경을 저장할 매트릭스 초기화
        cvtColor(image, image, CV_BGR2GRAY); //이미지를 크레이스케일로 변환
        
        if(Background_Queue.size() < 10){ // 10개가 안모였으면 계속 모으기
            Background_Queue.insert(Background_Queue.begin(), image);
        }
        else{
            Background_Queue.pop_back(); // 10개가 넘어가면 제일 마지막 꺼(제일 처음에 넣은 이미지)를 없애고 새로운 이미지를 맨 처음에 넣는다.
            Background_Queue.insert(Background_Queue.begin(), image);
        }
        
        for( int i=0 ; i < Background_Queue.size() ; i++){
            add(Background_Queue[i] / (i + 1.0), (background * i) / ( i + 1.0), background); //10개 프레임의 평균 얻기
        }
        
        absdiff(background, image, sub); // 배경에서 현재프레임 빼서 움직이는 물체 얻기
        threshold(sub, sub, 20, 255, THRESH_BINARY); // 바이너리로 변환
        
        findContours(sub, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE); // 움직이는 물체 찾아서 contours에 저장
        
        
        vector<Rect> boundRect(contours.size());
        int rect_num = 0;
        
        for (int i = 0 ; i < contours.size() ; i++){
            boundRect[i] = boundingRect(contours[i]); // 움직이는 물체 하나씩 꺼내서 바운딩 후 배열에 저장
            if (boundRect[i].area() > 200){ // 바운딩한 크기가 200 이상이면
                rectangle(result, boundRect[i], Scalar(255, 255, 255), 2, 8); // 그 위치에 사각형 그리기
                rect_num++; // 갯수 증가
            }
        }
        
        putText(result, format("# Rect: %d", rect_num), Point2f(10, 30), FONT_HERSHEY_PLAIN, 2, Scalar(255,255,255), 2);
        
        imshow ("result", result);
        waitKey(1000/fps);
    }
    return 0;
    
    
}