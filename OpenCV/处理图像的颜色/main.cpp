/*
    作者: btx
    日期: 23-6-9
    功能：处理图像的颜色
*/
#include <opencv2/opencv.hpp>
#include "ColorDetector.h"
#include "grabCut.h"
using namespace cv;
using namespace std;

Mat colorDet(Mat img) {
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
    return result;
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

 
  
    Mat result;
    //用策略设计模式比较颜色
    //result = colorDet(img);
    // GrabCut 算法分割图像
    result = grabCut(img);
    showImg("结果图像", result);
    waitKey(0);
    destroyAllWindows();
    return 0;
}
