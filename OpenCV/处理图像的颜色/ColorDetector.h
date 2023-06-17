#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
//显示图像
void showImg(String name, Mat img) {
    //通过namedWindow实现窗口大小可调节，注意name必须一致
    namedWindow(name, WINDOW_FREERATIO);
    imshow(name, img);
}

class ColorDetector {
public:
    ColorDetector(int value) {
        minDist = value;
        target[0] = target[1] = target[2] = 255;
    };
    void setColorDistanceThreshold(int distance);
    int getColorDistanceThreshold() const;
    void setTargetColor(unsigned char red, unsigned char green, unsigned char blue);
    void setTargetColor(cv::Vec3b color);
    cv::Vec3b getTargetColor() const;
    bool operator()(const cv::Vec3b& color) const;
private:
    int minDist;
    cv::Vec3b target;
};

void ColorDetector::setColorDistanceThreshold(int distance) {
    if (distance < 0) {
        distance = 0;
    }
    minDist = distance;
}

int ColorDetector::getColorDistanceThreshold() const {
    return minDist;
}

void ColorDetector::setTargetColor(unsigned char red, unsigned char green, unsigned char blue) {
    target[2] = red;
    target[1] = green;
    target[0] = blue;
}
// 设置颜色阈值
void ColorDetector::setTargetColor(cv::Vec3b color) {
    target = color;
}

cv::Vec3b ColorDetector::getTargetColor() const {
    return target;
}
//检测是否是目标颜色
bool ColorDetector::operator()(const cv::Vec3b& color) const {
    //norm函数用于计算距离
    int dist = static_cast<int>(cv::norm(target, color));
    if (dist < minDist) {
        return true;
    }
    else {
        return false;
    }
}