#include<iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
//#include <cv.h>
#include <opencv2\imgproc\imgproc.hpp>
#include <vector>
#include <opencv2\ml\ml.hpp>

using namespace std;
using namespace cv;

#define inNum 200

//预处理方法1--计算灰度梯度
Mat calcGradientFeat(const Mat& imgsrc){

	//imshow("", imgsrc);
	//waitKey(3000);

	//函数声明
	float sumMatValue(const Mat& image);

	Mat image;
	//cvtColor(imgsrc, image, CV_BGR2GRAY);
	image = imgsrc;

	//waitKey(1000);
	Mat tempMat(1, inNum, CV_32FC1);

	////test code
	//float ele;
	//ele = image.at<float>(1);
	//tempMat.at<float>(1) = 1.0;
	//cout << tempMat << endl;

	resize(image, image, Size(40, 40));


	imshow("", image);
	waitKey(1000);
	cout << image << endl;
	//在X,Y方向上sobel滤波，待理解！
	float mask[3][3] = { { 1, 2, 1 }, { 0, 0, 0 }, { -1, -2, -1 } };

	Mat y_mask = Mat(3, 3, CV_32F, mask) / 8;
	Mat x_mask = y_mask.t();

	//建立输出图像变量
	Mat sobelx, sobely;

	filter2D(image, sobelx, CV_32F, x_mask);
	filter2D(image, sobely, CV_32F, y_mask);
	sobelx = abs(sobelx);
	sobely = abs(sobely);


	//waitKey(1000);

	////显示
	//namedWindow("sobelx");
	//namedWindow("sobely");
	//imshow("sobelx", sobelx);
	//imshow("sobely", sobely);
	//waitKey(2000);
	//imwrite("sobelx.jpg", sobelx);
	//imwrite("sobely.jpg", sobely);

	float totalValueX = sumMatValue(sobelx);
	float totalValueY = sumMatValue(sobely);
	//cout << totalValueX << endl << totalValueY << endl;

	//将图像划分为4x4的小方格，计算方格中的灰度值占总和的的百分比
	int index = 0;
	for (int i = 0; i < image.rows; i = i + 4)
	{
		for (int j = 0; j < image.cols; j = j + 4)
		{

			Mat subImageX = sobelx(Rect(j, i, 4, 4));
			//cout << sumMatValue(subImageX) / totalValueX << endl;

			tempMat.at<float>(0, index) = (sumMatValue(subImageX) / totalValueX);
			//cout << sumMatValue(subImageX) << endl;
			index++;
			Mat subImageY = sobely(Rect(j, i, 4, 4));
			tempMat.at<float>(0, index) = (sumMatValue(subImageY) / totalValueY);
			//cout << tempMat.at<float>(index) << endl;
			index++;

		}
	}
	//cout << "capacity:"<<endl<<feat.capacity() << endl;
	//cout << tempMat.row(0) << endl;
	return tempMat;

}