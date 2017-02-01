#include<iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
//#include <cv.h>
#include <opencv2\imgproc\imgproc.hpp>
#include <vector>
#include <opencv2\ml\ml.hpp>

using namespace std;
using namespace cv;

#define virtulCols 300
#define virtualRows 100

//找出边界，归一化大小
Mat resizeChar(const Mat& image){

	int sumVector(Mat& vect, int Cols);
	int sumCol(Mat& vect,int col);
	//二值化
	Mat dst;
	double thresh = 50.0;
	double maxValue = 255;
	threshold(image, dst, thresh, maxValue,THRESH_BINARY);
	
	Mat tem;
	dst.copyTo(tem);
	resize(tem, tem, Size(100, 100));
	//寻找边界
	//检测字符上下左右边缘
	int upEdge, lowEdge, leftEdge, rightEdge,gap;
	int upEdgeTem, lowEdgeTem, leftEdgeTem, rightEdgeTem ;
	upEdgeTem = lowEdgeTem = leftEdgeTem = rightEdgeTem = 0;
	upEdge = leftEdge =gap= 0;
	lowEdge = tem.rows;
	rightEdge = tem.cols;

	//判断条件
	int alpha = 2;//置信系数
	const int expand = 3;
	bool isLineEmpty;
	int flag = 0;
	//寻找上下极限
	for (int i = 0; i < tem.rows; i++)
	{

		//cout << tem.row(i) << endl;
		isLineEmpty = (sumVector(tem.row(i),virtulCols)> 255 * (virtulCols - alpha));
		
		if (!isLineEmpty&(flag == 0))
		{
			upEdgeTem = i;
			flag = 1;
		}
		if (isLineEmpty&flag == 1)
		{
			lowEdgeTem = i - 1;
			flag = 0;
		}
		if (lowEdgeTem - upEdgeTem > gap)
		{
			lowEdge = lowEdgeTem;
			upEdge = upEdgeTem;
			gap = lowEdge - upEdge;
		}

	}

	if (upEdge - expand >= 0)
	{
		upEdge = upEdge - expand;
	}
	else
	{
		upEdge = 0;
	}

	if (lowEdge + expand <= tem.rows - 1)
	{
		lowEdge = lowEdge + expand;
	}
	else
	{
		lowEdge = tem.rows - 1;
	}

//寻找左右极限
	flag = 0;
	gap = 0;
	for (int i = 0; i < 3*tem.cols; i=i+3)
	{
		isLineEmpty = sumCol(tem,i) > 255 * (tem.rows - alpha);

		if (!isLineEmpty&(flag == 0))
		{
			leftEdgeTem = i/3;
			flag = 1;
		}

		if (isLineEmpty&flag == 1)
		{
			rightEdgeTem = i/3 - 1;
			flag = 0;
		}

		if (rightEdgeTem - leftEdgeTem > gap)
		{
			rightEdge = rightEdgeTem;
			leftEdge = leftEdgeTem;
			gap = rightEdge - leftEdge;
		}

	}

	if (leftEdge - expand >= 0)
	{
		leftEdge = leftEdge - expand;
	}
	else
	{
		leftEdge = 0;
	}

	if (rightEdge + expand <= tem.cols - 1)
	{
		rightEdge += expand;
	}
	else
	{
		rightEdge = tem.cols - 1;
	}

	////test code
	//for (int jj = 0; jj <100; jj++)
	//{
	//	for (int j = 90; j < 300; j++)
	//	{
	//	tem.at<uchar>(jj, j) = 0;
	//	}
	//}

	//imwrite("test.jpg", tem);
	//waitKey(1000);

	//imshow("",tem(Rect(leftEdge, upEdge, rightEdge - leftEdge, lowEdge - upEdge)));
	//waitKey(1000);


	Mat ROIMat;
	ROIMat = tem(Rect(leftEdge, upEdge, rightEdge - leftEdge, lowEdge - upEdge));
	resize(ROIMat, ROIMat, Size(40, 40));

	//反向二值化
	threshold(ROIMat, ROIMat, thresh, maxValue, THRESH_BINARY_INV);

	return ROIMat;

}

