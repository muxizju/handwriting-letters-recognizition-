#include<iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
//#include <cv.h>
#include <opencv2\imgproc\imgproc.hpp>
#include <vector>
#include <opencv2\ml\ml.hpp>

using namespace std;
using namespace cv;

//计算图形矩阵元素和
float sumMatValue(const Mat& image){

	float sumValue = 0;
	int row = image.rows;
	int col = image.cols;
	float tem=-10;
	//cout << image << endl;
	//if (image.isContinuous())
	//{
	//	row = 1;
	//	col = row*col;

	//}
	for (int i = 0; i < row; i++)
	{
		//cout << image.at<float>(12, 16)<<endl;
		//const uchar* linePtr = image.ptr<uchar>(i);
		//cout << linePtr[536]<<endl;
		for (int j = 0; j < col; j++){

			sumValue += image.at<uchar>(i, j);		
		}

	}
	return sumValue;
}