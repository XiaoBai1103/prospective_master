/*
    作者: btx
    日期: 23-5-31
-opencv第四章  图形形态学操作 (c语言实现）
*/
#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
    // 读取图像
    Mat img = imread("img.webp");

    // 显示原始图像
    imshow("Original Image", img);

    // 定义结构元素
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

    // 腐蚀操作
    Mat erode;
    cv::erode(img, erode, kernel, Point(-1, -1), 1);
    imshow("erode", erode);

    // 膨胀操作
    Mat dilate;
    cv::dilate(img, dilate, kernel, Point(-1, -1), 1);
    imshow("dilate", dilate);

    // 执行开运算操作
    Mat opening;
    cv::morphologyEx(img, opening, MORPH_OPEN, kernel);
    imshow("opening", opening);

    // 执行闭运算操作
    Mat closing;
    cv::morphologyEx(img, closing, MORPH_CLOSE, kernel);
    imshow("closing", closing);

    // 梯度运算
    Mat gradient;
    cv::morphologyEx(img, gradient, MORPH_GRADIENT, kernel);
    imshow("gradient", gradient);

    // 实现礼帽操作
    Mat tophat;
    cv::morphologyEx(img, tophat, MORPH_TOPHAT, kernel);
    imshow("tophat", tophat);

    // 实现黑帽操作
    Mat blackhat;
    cv::morphologyEx(img, blackhat, MORPH_BLACKHAT, kernel);
    imshow("blackhat", blackhat);

    // 等待用户按下键盘
    waitKey(0);

    // 销毁所有窗口
    destroyAllWindows();

    return 0;
}
