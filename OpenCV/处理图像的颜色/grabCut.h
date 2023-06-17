/*
�������һ��Rect����rect(100, 50, 50, 100)����ôrect�������¼������ܣ�
rect.area();     //����rect����� 5000
rect.size();     //����rect�ĳߴ� [50 �� 100]
rect.tl();       //����rect�����϶�������� [100, 50]
rect.br();       //����rect�����¶�������� [150, 150]
rect.width();    //����rect�Ŀ�� 50
rect.height();   //����rect�ĸ߶� 100
rect.contains(Point(x, y));  //���ز����������ж�rect�Ƿ����Point(x, y)��
*/


#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
Mat grabCut(Mat image){
//cv::Rect ������
	cv::Rect rectangle(30, 0, 480, 480);
	cv::Mat result;
	cv::Mat bgModel, fgModel;

	//grabCut()���һ������Ϊcv::GC_INIT_WITH_MASKʱ
	result = cv::Mat(image.rows, image.cols, CV_8UC1, cv::Scalar(cv::GC_BGD));
	cv::Mat roi(result, rectangle);
	roi = cv::Scalar(cv::GC_PR_FGD);
	cv::grabCut(image, result, rectangle, bgModel, fgModel, 15,
		cv::GC_INIT_WITH_MASK);


	cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);
	//result = result & 1 ;
	cv::Mat foreground(image.size(), CV_8UC3,
		cv::Scalar(128, 128, 128));
	image.copyTo(foreground, result);



return foreground;
}
