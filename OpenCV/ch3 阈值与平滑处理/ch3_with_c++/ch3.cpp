/*
    作者: btx
    日期: 23-6-2
    功能：第三章 阈值与平滑处理
*/
#include <opencv2/opencv.hpp> 
#include <iostream>
using namespace cv; 
using namespace std;
//显示图像
void showImg(String name, Mat img) {
    //通过namedWindow实现窗口大小可调节，注意name必须一致
    namedWindow(name, WINDOW_FREERATIO);
    imshow(name, img);
}
int main() {
    Mat img = imread("img.jpg");
    if (img.empty()) {
        cerr << "无法读取图片" << endl;
        return -1;
    }
    // 添加高斯噪声
    double mean = 0;
    double var = 100;
    double sigma = sqrt(var);
    Mat gaussian(img.size(), CV_32FC3);
    randn(gaussian, Scalar::all(mean), Scalar::all(sigma));
    img.convertTo(img, CV_32FC3);
    img += gaussian;
    img = max(img, Scalar::all(0));
    img = min(img, Scalar::all(255));
    img.convertTo(img, CV_8UC3);
    showImg("高斯噪声", img);
    // 均值滤波
    Mat res;
    res = img.clone();
    Size kernelSize(3, 3);
    boxFilter(img, res, -1, kernelSize);
    showImg("均值滤波", res);
    // 方框滤波
    res = img.clone();
    boxFilter(img, res, -1, kernelSize, Point(-1, -1), true);
    showImg("方框滤波", res);
    // 高斯滤波
    res = img.clone();
    GaussianBlur(img, res, Size(5, 5), 1);
    showImg("高斯滤波", res);
    // 中值滤波
    res = img.clone();
    medianBlur(img, res, 5);
    showImg("中值滤波", res);

    waitKey(0);
    return 0;
}
