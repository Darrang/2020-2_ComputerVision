#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    Mat image = imread("Lena.png");

    if(image.empty()){
        cerr << "read fail!" << endl;
        exit(-1);
    }

    imshow("image",image);
    waitKey(0);
    return 0;
}