#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat load_lena();
Mat load_colorful();
Mat load_balancing();
Mat Gamma(Mat input_image);
Mat Histogram(Mat input_image);
Mat WhiteBalancing(Mat input_image);
Mat AverageFiltering(Mat input_image);
Mat ColorConversion(Mat input_image);
Mat ColorSlice(Mat input_image);
Mat Histogram(Mat input_image);


int main(){
    char input_key;
    Mat lena;
    Mat colorful;
    Mat balancing;
    Mat lena_nagative;

    Mat ycrcb;
    Mat output;
    vector<Mat> v(3);

    lena = load_lena();
    colorful = load_colorful();
    balancing = load_balancing();

    cout << "\t------lena.png------\n";
    cout << "\tn - Negative transformation\n";
    cout << "\tg - Gamma transformation(gamma:2.5)\n";
    cout << "\th - Histogram equalization\n";
    cout << "\tr - Reset image\n";

    cout << "\n\t------colorful.jpg------\n";
    cout << "\ts - Color slicing\n";
    cout << "\tc - Color conversion\n";
    cout << "\tr - Reset image\n";

    cout << "\n\t------balancing.jpg------\n";
    cout << "\ta - Average filtering\n";
    cout << "\tw - White balancing\n";
    cout << "\tr - Reset image\n";

    imshow("lena",lena);
    imshow("colorful",colorful);
    imshow("balancing",balancing);
    waitKey(0);

 cvtColor(lena,ycrcb,CV_BGR2HSV);
 split(ycrcb,v);

while(1){
  int key = waitKey(0);

  if(key == 27)
    break;

    switch ((char)key){ 
         
    case 'r': //reset
        
        lena = load_lena();
        colorful = load_colorful();
        balancing = load_balancing();
        imshow("lena",lena);
        imshow("colorful",colorful);
        imshow("balancing",balancing); 
        break;

    case 'n':   //Negative

      for (int y = 0; y < lena.rows; y++)
        for (int x = 0; x < lena.cols; x++)
            v[2].at<uchar>(y, x) = 255 - v[2].at<uchar>(y, x);
   
    merge(v,output);
    cvtColor(output,lena,CV_HSV2BGR);
    imshow("lena",lena); 

        break;

    case 'g':   //Gamma
        lena = Gamma(lena);
        imshow("lena",lena); 
        
        break;

    case 'h':   //Histogram
        lena = Histogram(lena);
        imshow("lena",lena); 
        
        break;

    case 's':   //Color slicing
        colorful = ColorSlice(colorful);
        imshow("colorful",colorful);
        break;

    case 'c':   //Color conversion
        colorful = ColorConversion(colorful);
        imshow("colorful",colorful);
        break;

    case 'a':   //Average filtering
    balancing = AverageFiltering(balancing);
    imshow("balancing",balancing);
        break;

    case 'w':   //white balancing
    balancing = WhiteBalancing(balancing);
    imshow("balancing",balancing);
       break;
    }

}

    return 0;
}

Mat load_lena(){
    Mat lena = imread("lena.png");

    if(lena.empty()){
        cerr << "read fail!" << endl;
        exit(-1);
    } 
    return lena;
}

Mat load_colorful(){
    Mat colorful = imread("colorful.jpg");

    if(colorful.empty()){
        cerr << "read fail!" << endl;
        exit(-1);
    }
    return colorful;
}

Mat load_balancing(){
    Mat balancing = imread("balancing.jpg");

    if(balancing.empty()){
        cerr << "read fail!" << endl;
        exit(-1);
    } 

    return balancing;
}

/*
Mat Negative(Mat input_image){
    Mat ycrcb;
    Mat output;
    vector<Mat> v(3);

    cvtColor(input_image,ycrcb,CV_BGR2HSV);
    
    split(ycrcb,v);

     for (int y = 0; y < input_image.rows; y++)
        for (int x = 0; x < input_image.cols; x++)
            v[2].at<uchar>(y, x) = 255 - v[2].at<uchar>(y, x);
    
    merge(v,output);

    cvtColor(output,output,CV_HSV2BGR);

    return output;
}
*/

Mat Gamma(Mat input_image){
    Mat ycrcb;
    Mat v[3];

    float gamma_trans[256];
    float gamma_value = 2.5;

    cvtColor(input_image,ycrcb,CV_BGR2HSV);
    split(ycrcb,v);

    MatIterator_<uchar> it, end; 

for(int i=0;i<256;i++){
    gamma_trans[i] =  saturate_cast<uchar>(pow((i/255.0),gamma_value) * 255.0f); //감마 계산하기
}

for(it = v[2].begin<uchar>(),end = v[2].end<uchar>(); it != end; ++it){
   (*it) =  gamma_trans[*it];
}

    merge(v,3,input_image);
    cvtColor(input_image,input_image,CV_HSV2BGR);
    return input_image;
}

Mat Histogram(Mat input_image){
    Mat hist_equalization;
    Mat dst;
    Mat ycrcb;
    Mat yuv_channels[3];
    cvtColor(input_image,ycrcb,CV_BGR2YCrCb);
    split(ycrcb,yuv_channels);
    equalizeHist(yuv_channels[0],yuv_channels[0]);
    merge(yuv_channels,3,hist_equalization);
    cvtColor(hist_equalization,dst,CV_YCrCb2BGR);
    return dst;    
}

Mat ColorSlice(Mat input_image){
    Mat slice;
    Mat x[3];
    uchar *h;
    uchar *s;
    Mat Hue;
    cvtColor(input_image,Hue,CV_BGR2HSV);
    split(Hue, x);

    for (int i = 0; i < input_image.rows; i++) {
		h = x[0].ptr<uchar>(i);
		s = x[1].ptr<uchar>(i);
		for (int j = 0; j < input_image.cols; j++) {
			if (h[j] > 9 && h[j] < 23) s[j] = s[j];
			else s[j] = 0; 
		}
	}

    merge(x,3,slice);
    cvtColor(slice,slice,CV_HSV2BGR);

    return slice;

}


Mat ColorConversion(Mat input_image){
Mat color_conversion;
Mat Hue;
Mat x[3];
uchar *h;
uchar *s;
cvtColor(input_image,Hue,CV_BGR2HSV);
split(Hue,x);
for (int i = 0; i < input_image.rows; i++) {
		h = x[0].ptr<uchar>(i);
		s = x[1].ptr<uchar>(i);
		for (int j = 0; j < input_image.cols; j++) {
			if (h[j] > 129) h[j] = h[j] - 129;
			else h[j] += 50;
		}
	}

    merge(x,3,color_conversion);
    cvtColor(color_conversion,color_conversion,CV_HSV2BGR);
    return color_conversion;
}

Mat AverageFiltering(Mat input_image){

 blur(input_image, input_image, Size(9,9));
  return input_image;
}

Mat WhiteBalancing(Mat input_image){
    Mat whiteBalance;
    Mat x[3];

    uchar *r;
    uchar *g;
    uchar *b;
    int sum_r = 0, sum_g = 0, sum_b = 0;
    int bt,gt,rt;

    int xy = input_image.rows * input_image.cols;
    split(input_image,x);

    for(int i=0;i<input_image.rows;i++){
        b = x[0].ptr<uchar>(i);
        g = x[1].ptr<uchar>(i);
        r = x[2].ptr<uchar>(i);
        for(int j=0;j<input_image.cols;j++){
            sum_b += b[j];
            sum_g += g[j];
            sum_r += r[j];
        }
    }

   int average_b = sum_b / (input_image.rows * input_image.cols);
   int average_g = sum_g / (input_image.rows * input_image.cols);
   int average_r = sum_r / (input_image.rows * input_image.cols);
   
   for(int i=0;i<input_image.rows;i++){
        b = x[0].ptr<uchar>(i);
        g = x[1].ptr<uchar>(i);
        r = x[2].ptr<uchar>(i);

        for(int j=0;j<input_image.cols;j++){
            bt = (128 * b[j]) /average_b;
            if(bt < 255) b[j] = bt;
            else b[j] = 255;
            gt = (128 * g[j]) /average_g;
            if(gt < 255) g[j] = gt;
            else g[j] = 255;
            rt = (128 * r[j]) /average_r; 
            if(rt < 255) r[j] = rt;
            else r[j] = 255;
        }
    } 

    merge(x,3,whiteBalance);
    return whiteBalance;
}