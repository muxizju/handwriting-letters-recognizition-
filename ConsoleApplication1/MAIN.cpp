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
#define hid1 83
#define hid2 34
#define hid3 11
#define outNum 4
#define nSmplesForTrain 200
#define nSmplesForPredict 60
#define hid 19

int main()
{
	//Mat a = imread("组合 1_页面_037.jpg");
	//imshow("a", a);
	////二值化
	//Mat dst;
	//double thresh = 190.0;
	//double maxValue = 255;
	//threshold(a, dst, thresh, maxValue, 0);
	//imshow("", dst);
	//waitKey(10000);
	///*system("pause");*/
	//return 0;



	
	//函数声明
	Mat calcGradientFeat(const Mat& imgsrc);
	Mat resizeChar(const Mat& image);
	Mat binaryFeature(const Mat& imgsrc);
	float sumMatValue(const Mat& image);
	float FullValue(Mat& image);

/////////建立神经网络
	CvANN_MLP myNN;
	int ar[] = { inNum,hid, outNum };
	Mat layerSizes(1, 3, CV_32S, ar);
	myNN.create(layerSizes,CvANN_MLP::SIGMOID_SYM);

///////设置训练参数
	CvANN_MLP_TrainParams myTrainParams;
	myTrainParams.train_method = CvANN_MLP_TrainParams::BACKPROP;
	myTrainParams.bp_dw_scale = 0.1;
	myTrainParams.bp_moment_scale = 0.1;
	
//////训练数据准备
	Mat inputsForTrain(nSmplesForTrain, inNum, CV_32FC1);
	Mat outputsForTrain(nSmplesForTrain, outNum, CV_32FC1);

///////此处需给训练数据inputs和outputs赋值
	int letterClass = 11;
	int letterID = 1;
	for (int i = 0; i < nSmplesForTrain; i++){
		cout << "train input num:" << i << endl;

		letterClass = 11+i / (nSmplesForTrain/4);
		cout << letterClass << endl;
		
	
		// 读入一张图片img0(letterClass)-0(letterID).png
		char file[255] = { };
		if (letterID < 10)
		{
			sprintf(file, "E:\\desk document\\lessons\\datamining\\project 2_code\\ConsoleApplication1\\ConsoleApplication1\\SampleForTrain\\img0%d-00%d.png", letterClass, letterID);
		}
		else
		{
			sprintf(file, "E:\\desk document\\lessons\\datamining\\project 2_code\\ConsoleApplication1\\ConsoleApplication1\\SampleForTrain\\img0%d-0%d.png", letterClass, letterID);
		}

		Mat imgsrc = imread(file, 1);

		letterID++;
		if (letterID > nSmplesForTrain/4)
		{
			letterID = 1;
		}

		
		//归一化大小
		Mat tem = resizeChar(imgsrc);

		//处理数据，提取二值分布特征
		Mat tempMat(1, inNum, CV_32FC1);
		tempMat= binaryFeature(tem);
		//tempMat=calcGradientFeat(imgsrc);

		//cout << tempMat << endl;
		//赋值input
		tempMat.copyTo(inputsForTrain.row(i));
		
		//赋值output
	
		for (int j = 0; j < 4; j++){
			outputsForTrain.at<float>(i, j) = 0.0;
		}
		outputsForTrain.at<float>(i, letterClass-11) = 1.0;
//		cout << "output is"<<outputsForTrain.row(0) << endl;
	}	
	/////////


////////训练
	myNN.train(inputsForTrain, outputsForTrain, Mat(), Mat(), myTrainParams, 0);

////////识别
	Mat inputsForPredict(1, inNum, CV_32FC1);
	Mat outputsForPredict(1, outNum, CV_32FC1);

	//cout << "未初始化"<<outputsForPredict.row(0) << endl;


//测试sample for prediction
//////////此处需给预测数据inputs赋值
	//	letterClass = 11;
	//	letterID = 41;
	//for (int i = 0; i < nSmplesForPredict; i++){
	//	cout << "predict input num:" << i << endl;
	//	letterClass =11+ i / 15;
	//	// 读入一张图片img0(letterClass)-0(letterID).png
	//	char file[255] = {};
	//		sprintf(file, "E:\\desk document\\lessons\\datamining\\project 2_code\\ConsoleApplication1\\ConsoleApplication1\\SampleForPredict\\img0%d-0%d.png", letterClass, letterID);
	//	Mat imgsrc = imread(file, 1);
	//	//namedWindow("ori");
	//	//imshow("ori", imgsrc);
	//	//waitKey(1000);

	//	letterID++;
	//	if (letterID > 55)
	//	{
	//		letterID = 41;
	//	}

	//	//归一化大小
	//	Mat tem = resizeChar(imgsrc);
	//	//处理数据，提取二值分布特征
	//	inputsForPredict = binaryFeature(tem);

	//	//cout << inputsForPredict.row(0) << endl;
	//	myNN.predict(inputsForPredict, outputsForPredict);
	//	cout << "output of " << i << " is:" << outputsForPredict.row(0) << endl;
	//}



/////测试某试卷
	//试卷正确答案
	vector<string> Sanswer;
	vector<string> Manswer;
	//1-5
	Sanswer.push_back("D");
	Sanswer.push_back("D");
	Sanswer.push_back("D");
	Sanswer.push_back("D");
	Sanswer.push_back("D");
	//6-10
	Sanswer.push_back("C");
	Sanswer.push_back("B");
	Sanswer.push_back("B");
	Sanswer.push_back("D");
	Sanswer.push_back("A");
//11-15
	Sanswer.push_back("C");
	Sanswer.push_back("A");
	Sanswer.push_back("B");
	Sanswer.push_back("C");
	Sanswer.push_back("B");
//16-20
	Sanswer.push_back("C");
	Sanswer.push_back("B");
	Sanswer.push_back("A");
	Sanswer.push_back("C");
	Sanswer.push_back("C");
//多选题
	//1-5
	Manswer.push_back("BCD");
	Manswer.push_back("ABD");
	Manswer.push_back("BCD");
	Manswer.push_back("AD");
	Manswer.push_back("ABC");
	//6-10
	Manswer.push_back("BCD");
	Manswer.push_back("AD");
	Manswer.push_back("ACD");
	Manswer.push_back("ABCD");
	Manswer.push_back("ABD");

	int score=0;
	int counts = 0;
	int charID;
	float error[5] = { };
	float Minerror;
	//单选题
	for (int i = 2; i < 41; i=i+2)
	{
		Minerror = 2.0;
		char file[255];
		sprintf(file, "E:\\desk document\\lessons\\datamining\\project 2_code\\ConsoleApplication1\\ConsoleApplication1\\corrected results\\%d.jpg", i);
		Mat imgsrc = imread(file, 1);
		if (!imgsrc.empty()){

			//针对反向图片特加的步骤：反向二值化
			double thresh = 50.0;
			double maxValue = 255;
			threshold(imgsrc, imgsrc, thresh, maxValue, THRESH_BINARY_INV);
			imshow("", imgsrc);
			waitKey(500);
			//system("pause");
			//归一化大小
			Mat tem = resizeChar(imgsrc);
			//处理数据，提取二值分布特征
			inputsForPredict = binaryFeature(tem);
			//cout << i << ":" << sumMatValue(tem) << endl;
			myNN.predict(inputsForPredict, outputsForPredict);
			
			bool IsChar=false;
			for (int j = 0; j < 4; j++)
			{
				error[j] = abs(outputsForPredict.at<float>(0, j) - 1.0);
				/*if ((error[j]<= 0.15)&&(error[j]<Minerror))*/
				if (error[j]<Minerror)
				{
					Minerror = error[j];
					IsChar = true;
					charID = 65+j;
					
				}
					
			}

			if (IsChar)
			{
				counts++;
				//cout << "output of " << i << ":" << outputsForPredict.row(0) << error[charID - 65 + 1]<<"  " <<  i << (char)charID << endl;
			}
			string temStr;
			if (charID == 65)
				temStr = "A";
				if (charID == 66)
					temStr = "B";
					if (charID == 67)
						temStr = "C";
						if (charID == 68)
							temStr = "D";
			
			if (Sanswer.at(i/2-1)==temStr)
			{
				score += 1;
				cout << "第" << i / 2 << "题回答" << temStr << ",正确答案是" << Sanswer.at(i / 2 - 1) << ".回答正确" << "。得分：" << score << endl;
				
			}
			else
			{
				cout << "第" << i / 2 << "题回答" << temStr << ",正确答案是" << Sanswer.at(i / 2 - 1) << ".回答错误" << "。得分：" << score << endl;
			}
		}

	}
	int singleScore = score;

	cout << "单选题得分：" << singleScore << endl;
	//多选题

	for (int i = 1; i < 11; i++)
	{
		string multiAnswer;
		for (int j = 2; j < 6; j++)
		{
			Minerror = 2.0;
			char file[255];
			sprintf(file, "E:\\desk document\\lessons\\datamining\\project 2_code\\ConsoleApplication1\\ConsoleApplication1\\corrected results\\%d_%d.jpg", i, j);
			Mat imgsrc = imread(file, 1);
			if (imgsrc.empty())
				continue;

			else{
				double thresh = 50.0;
				double maxValue = 255;
				threshold(imgsrc, imgsrc, thresh, maxValue, THRESH_BINARY_INV);
				imshow("", imgsrc);
				waitKey(500);
				//归一化大小
				Mat tem = resizeChar(imgsrc);
				//处理数据，提取二值分布特征
				inputsForPredict = binaryFeature(tem);
				//cout << i << ":" << sumMatValue(tem) << endl;
				myNN.predict(inputsForPredict, outputsForPredict);

				bool IsChar = false;
				for (int j = 0; j < 4; j++)
				{
					error[j] = abs(outputsForPredict.at<float>(0, j) - 1.0);

					/*if ((error[j]<= 0.15)&&(error[j]<Minerror))*/
					if (error[j] < Minerror)
					{
						Minerror = error[j];
						IsChar = true;
						charID = 65 + j;

					}

				}

				if (IsChar)
				{
					counts++;
					//cout << "output of " << i << "_" << j << ":" << outputsForPredict.row(0) << error[charID - 65 + 1] << "  " << i << "_" << j << (char)charID << endl;
				}
				string temStr;
				if (charID == 65)
					temStr = "A";
				if (charID == 66)
					temStr = "B";
				if (charID == 67)
					temStr = "C";
				if (charID == 68)
					temStr = "D";
				multiAnswer.append(temStr);
			}
		}

		if (multiAnswer == Manswer.at(i - 1))
		{
			score += 2;
			cout << "第" << i << "题回答" << multiAnswer << ",正确答案是" << Manswer.at(i - 1) << ".回答正确" << "。得分：" << score << endl;
		}
		else
		{
			cout << "第" << i << "题回答" << multiAnswer << ",正确答案是" << Manswer.at(i - 1) << ".回答错误" << "。得分：" << score << endl;
		}
	}

	cout << "多选题分数：" << score - singleScore << endl;
	cout << "总分：" << score<< endl;

//cout << "the character counts is :" << counts << endl;


//////实测识别字母

//Mat imgsrc = imread("408.jpg", 1);
//	//cout << imgsrc << endl;
//	//归一化大小
//	Mat tem = resizeChar(imgsrc);
//	imwrite("test.jpg", tem);
//	waitKey(500);
//	//处理数据，提取二值分布特征
//	inputsForPredict = binaryFeature(tem);
//	myNN.predict(inputsForPredict, outputsForPredict);
//	cout << "special output of " << "" << " is:" << outputsForPredict.row(0) << endl;

	system("pause");

}











