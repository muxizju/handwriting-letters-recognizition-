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
	//Mat a = imread("��� 1_ҳ��_037.jpg");
	//imshow("a", a);
	////��ֵ��
	//Mat dst;
	//double thresh = 190.0;
	//double maxValue = 255;
	//threshold(a, dst, thresh, maxValue, 0);
	//imshow("", dst);
	//waitKey(10000);
	///*system("pause");*/
	//return 0;



	
	//��������
	Mat calcGradientFeat(const Mat& imgsrc);
	Mat resizeChar(const Mat& image);
	Mat binaryFeature(const Mat& imgsrc);
	float sumMatValue(const Mat& image);
	float FullValue(Mat& image);

/////////����������
	CvANN_MLP myNN;
	int ar[] = { inNum,hid, outNum };
	Mat layerSizes(1, 3, CV_32S, ar);
	myNN.create(layerSizes,CvANN_MLP::SIGMOID_SYM);

///////����ѵ������
	CvANN_MLP_TrainParams myTrainParams;
	myTrainParams.train_method = CvANN_MLP_TrainParams::BACKPROP;
	myTrainParams.bp_dw_scale = 0.1;
	myTrainParams.bp_moment_scale = 0.1;
	
//////ѵ������׼��
	Mat inputsForTrain(nSmplesForTrain, inNum, CV_32FC1);
	Mat outputsForTrain(nSmplesForTrain, outNum, CV_32FC1);

///////�˴����ѵ������inputs��outputs��ֵ
	int letterClass = 11;
	int letterID = 1;
	for (int i = 0; i < nSmplesForTrain; i++){
		cout << "train input num:" << i << endl;

		letterClass = 11+i / (nSmplesForTrain/4);
		cout << letterClass << endl;
		
	
		// ����һ��ͼƬimg0(letterClass)-0(letterID).png
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

		
		//��һ����С
		Mat tem = resizeChar(imgsrc);

		//�������ݣ���ȡ��ֵ�ֲ�����
		Mat tempMat(1, inNum, CV_32FC1);
		tempMat= binaryFeature(tem);
		//tempMat=calcGradientFeat(imgsrc);

		//cout << tempMat << endl;
		//��ֵinput
		tempMat.copyTo(inputsForTrain.row(i));
		
		//��ֵoutput
	
		for (int j = 0; j < 4; j++){
			outputsForTrain.at<float>(i, j) = 0.0;
		}
		outputsForTrain.at<float>(i, letterClass-11) = 1.0;
//		cout << "output is"<<outputsForTrain.row(0) << endl;
	}	
	/////////


////////ѵ��
	myNN.train(inputsForTrain, outputsForTrain, Mat(), Mat(), myTrainParams, 0);

////////ʶ��
	Mat inputsForPredict(1, inNum, CV_32FC1);
	Mat outputsForPredict(1, outNum, CV_32FC1);

	//cout << "δ��ʼ��"<<outputsForPredict.row(0) << endl;


//����sample for prediction
//////////�˴����Ԥ������inputs��ֵ
	//	letterClass = 11;
	//	letterID = 41;
	//for (int i = 0; i < nSmplesForPredict; i++){
	//	cout << "predict input num:" << i << endl;
	//	letterClass =11+ i / 15;
	//	// ����һ��ͼƬimg0(letterClass)-0(letterID).png
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

	//	//��һ����С
	//	Mat tem = resizeChar(imgsrc);
	//	//�������ݣ���ȡ��ֵ�ֲ�����
	//	inputsForPredict = binaryFeature(tem);

	//	//cout << inputsForPredict.row(0) << endl;
	//	myNN.predict(inputsForPredict, outputsForPredict);
	//	cout << "output of " << i << " is:" << outputsForPredict.row(0) << endl;
	//}



/////����ĳ�Ծ�
	//�Ծ���ȷ��
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
//��ѡ��
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
	//��ѡ��
	for (int i = 2; i < 41; i=i+2)
	{
		Minerror = 2.0;
		char file[255];
		sprintf(file, "E:\\desk document\\lessons\\datamining\\project 2_code\\ConsoleApplication1\\ConsoleApplication1\\corrected results\\%d.jpg", i);
		Mat imgsrc = imread(file, 1);
		if (!imgsrc.empty()){

			//��Է���ͼƬ�ؼӵĲ��裺�����ֵ��
			double thresh = 50.0;
			double maxValue = 255;
			threshold(imgsrc, imgsrc, thresh, maxValue, THRESH_BINARY_INV);
			imshow("", imgsrc);
			waitKey(500);
			//system("pause");
			//��һ����С
			Mat tem = resizeChar(imgsrc);
			//�������ݣ���ȡ��ֵ�ֲ�����
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
				cout << "��" << i / 2 << "��ش�" << temStr << ",��ȷ����" << Sanswer.at(i / 2 - 1) << ".�ش���ȷ" << "���÷֣�" << score << endl;
				
			}
			else
			{
				cout << "��" << i / 2 << "��ش�" << temStr << ",��ȷ����" << Sanswer.at(i / 2 - 1) << ".�ش����" << "���÷֣�" << score << endl;
			}
		}

	}
	int singleScore = score;

	cout << "��ѡ��÷֣�" << singleScore << endl;
	//��ѡ��

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
				//��һ����С
				Mat tem = resizeChar(imgsrc);
				//�������ݣ���ȡ��ֵ�ֲ�����
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
			cout << "��" << i << "��ش�" << multiAnswer << ",��ȷ����" << Manswer.at(i - 1) << ".�ش���ȷ" << "���÷֣�" << score << endl;
		}
		else
		{
			cout << "��" << i << "��ش�" << multiAnswer << ",��ȷ����" << Manswer.at(i - 1) << ".�ش����" << "���÷֣�" << score << endl;
		}
	}

	cout << "��ѡ�������" << score - singleScore << endl;
	cout << "�ܷ֣�" << score<< endl;

//cout << "the character counts is :" << counts << endl;


//////ʵ��ʶ����ĸ

//Mat imgsrc = imread("408.jpg", 1);
//	//cout << imgsrc << endl;
//	//��һ����С
//	Mat tem = resizeChar(imgsrc);
//	imwrite("test.jpg", tem);
//	waitKey(500);
//	//�������ݣ���ȡ��ֵ�ֲ�����
//	inputsForPredict = binaryFeature(tem);
//	myNN.predict(inputsForPredict, outputsForPredict);
//	cout << "special output of " << "" << " is:" << outputsForPredict.row(0) << endl;

	system("pause");

}











