/*
    作者: btx
    日期: 23-6-9
    功能：处理图像的颜色
*/
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
//显示图像
void showImg(String name,Mat img) {
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

int main()
{
    /*
        读取图像对象的基本操作
    */
    Mat img = imread("./img.webp");
    if (img.empty()) {
        printf("读入图片异常");
        return 0;
    }
    showImg("显示原始图像",img);

    // 创建ColorDetector对象并设置目标颜色为红色
    ColorDetector cd(150);
    cd.setTargetColor(80, 160, 200);

    // 处理图像中的每个像素并标记属于目标颜色的像素
    cv::Mat result(img.rows, img.cols, CV_8U);
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            if (cd(img.at<cv::Vec3b>(i, j))) {
                result.at<unsigned char>(i, j) = 255;
            }
            else {
                result.at<unsigned char>(i, j) = 0;
            }
        }
    }
    //("pause");

    showImg("结果图像", result);
    waitKey(0);
    destroyAllWindows();
    return 0;
}
