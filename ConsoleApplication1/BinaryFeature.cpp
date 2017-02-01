#include<iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
//#include <cv.h>
#include <opencv2\imgproc\imgproc.hpp>
#include <vector>
#include <opencv2\ml\ml.hpp>

using namespace std;
using namespace cv;

#define inNum 101

//计算二值分布特征
Mat binaryFeature(const Mat& imgsrc){

	//函数声明
	float sumMatValue(const Mat& image);



	Mat tempMat(1, inNum, CV_32FC1);

	float totalValue = sumMatValue(imgsrc);

	//cout << totalValueX << endl << totalValueY << endl;

	//将图像划分为4x4的小方格，计算方格中的灰度值占总和的的百分比
	int index = 0;
	for (int i = 0; i < imgsrc.rows; i = i + 4)
	{
		for (int j = 0; j < imgsrc.cols; j = j + 4)
		{

			Mat subimgsrcX = imgsrc(Rect(j, i, 4, 4));
			//cout << sumMatValue(subimgsrcX) / totalValueX << endl;

			tempMat.at<float>(0, index) = (sumMatValue(subimgsrcX) / totalValue);
			//cout << sumMatValue(subimgsrcX) << endl;
			index++;

		}
	}
	tempMat.at<float>(0, inNum - 1) = totalValue;

	//cout << "capacity:"<<endl<<feat.capacity() << endl;
	//cout << tempMat.row(0) << endl;
	return tempMat;

}