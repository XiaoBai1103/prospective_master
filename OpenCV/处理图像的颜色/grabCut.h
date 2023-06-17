/*
如果创建一个Rect对象rect(100, 50, 50, 100)，那么rect会有以下几个功能：
rect.area();     //返回rect的面积 5000
rect.size();     //返回rect的尺寸 [50 × 100]
rect.tl();       //返回rect的左上顶点的坐标 [100, 50]
rect.br();       //返回rect的右下顶点的坐标 [150, 150]
rect.width();    //返回rect的宽度 50
rect.height();   //返回rect的高度 100
rect.contains(Point(x, y));  //返回布尔变量，判断rect是否包含Point(x, y)点
*/


#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
Mat grabCut(Mat image){
//cv::Rect 矩形类
	cv::Rect rectangle(30, 0, 480, 480);
	cv::Mat result;
	cv::Mat bgModel, fgModel;

	//grabCut()最后一个参数为cv::GC_INIT_WITH_MASK时
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
