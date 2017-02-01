#include<iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
//#include <cv.h>
#include <opencv2\imgproc\imgproc.hpp>
#include <vector>
#include <opencv2\ml\ml.hpp>

using namespace std;
using namespace cv;

float FullValue(Mat& image){
	float sumMatValue(const Mat& image);
	
	float value;
	Mat src ;
	image.copyTo(src);
	resize(src, src, Size(100, 100));
	threshold(src, src, 50, 255, THRESH_BINARY_INV);
	value = sumMatValue(src);
	return value;

}