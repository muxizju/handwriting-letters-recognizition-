#include<iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
//#include <cv.h>
#include <opencv2\imgproc\imgproc.hpp>
#include <vector>
#include <opencv2\ml\ml.hpp>

using namespace std;
using namespace cv;


//计算向量元素和
int sumVector(Mat& vect,int Cols){
	int sum = 0;

	for (int i = 0; i<Cols; i++)
	{
		//cout << vect.at<float>(0,i) << endl;
		sum += vect.at<uchar>(0,i);
	}
	return sum;
}