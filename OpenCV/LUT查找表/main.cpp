/*
    作者: btx
    日期: 23-6-29
    功能：二值化和LUT查找表

    固定阈值二值化
    cv::threshold(inputArray src, //输入图像矩阵，数据类型只能是CV_8U或CV_32F
                  outputArray dst, //输出
                  double thresh, //阈值
                  double maxval, //最大值，是否需要该参数取决于type
                  int type //二值化方法
                  )
    
    自适应阈值二值化
    cv::adaptiveThreshold( InputArray src, //输入图像矩阵，数据类型只能是单通道CV_8U
                           OutputArray dst,//输出
                           double maxValue, //预设满足条件的最大值
                           int adaptiveMethod,//指定自适应阈值算法。可选择ADAPTIVE_THRESH_MEAN_C 或 ADAPTIVE_THRESH_GAUSSIAN_C两种
                           int thresholdType,//指定阈值类型。可选择THRESH_BINARY或者THRESH_BINARY_INV两种
                           int blockSize,//邻域块大小，用来计算区域阈值
                           double C //参数C表示与算法有关的参数，它是一个从均值或加权均值提取的常数，可以是负数
                           )

    LUT查找表                
    cv::LUT(inputArray src,   //输入图像矩阵，数据类型只能是CV_8U
            inputArray lut,   //256个像素灰度值的查找表，单通道或与src通道数相同
            outputArray dst   //输出图像矩阵，尺寸与src相同，数据类型与lut相同
            )



*/
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
// 显示图像
void showImg(String name, Mat img) {
    // 通过namedWindow实现窗口大小可调节，注意name必须一致
    namedWindow(name, WINDOW_FREERATIO);
    imshow(name, img);
}


int main()
{
    Mat img = imread("./img.webp");
    if (img.empty()) {
        printf("读入图片异常");
        return 0;
    }
    showImg("显示原始图像", img);
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // 固定阈值二值化
    // 结果图像
    Mat out_BINARY, out_BINARY_INV,out_TOZERO, out_TOZERO_INV, out_TRUNC;

    // THRESH_BINARY:大于阈值的部分被置为255，小于部分被置为0
    // THRESH_BINARY_INV:大于阈值部分被置为0，小于部分被置为255
    threshold(gray, out_BINARY, 125, 255, THRESH_BINARY);
    threshold(gray, out_BINARY_INV, 125, 255, THRESH_BINARY_INV);
    showImg("BINARY变换", out_BINARY);
    showImg("BINARY反变换", out_BINARY_INV);

    // TOZERO变换:小于阈值部分被置为0，大于部分保持不变
    // TOZERO_INV变换:大于阈值部分被置为0，小于部分保持不变 
    threshold(gray,out_TOZERO,125,255,THRESH_TOZERO);
    threshold(gray, out_TOZERO_INV, 125, 255, THRESH_TOZERO_INV);
    showImg("TOZERO变换", out_TOZERO);
    showImg("TOZERO反变换", out_TOZERO_INV);

    // TRUNC变换:大于阈值部分被置为threshold，小于部分保持原样
    threshold(gray, out_TRUNC, 125, 255, THRESH_TRUNC);
    showImg("TRUNC变换", out_TRUNC);

    // 灰度图像大津法和三角形法二值化
    // OTSU算法对直方图有两个峰，中间有明显波谷的直方图对应图像二值化效果比较好
    // 基于纯几何方法来寻找最佳阈值，它的成立条件是假设直方图最大波峰在靠近最亮的一侧，然后通过三角形求得最大直线距离，根据最大直线距离对应的直方图灰度等级即为分割阈值
    Mat out_OTSU, out_TRIANGLE;
    Mat img_1 = imread("./test.jpg",0);
    if (img.empty()) {
        printf("读入图片异常");
        return 0;
    }
    showImg("显示原始图像img_1", img_1);
    

    threshold(img_1, out_OTSU, 125, 255, THRESH_BINARY | THRESH_OTSU);
    threshold(img_1, out_TRIANGLE, 125, 255, THRESH_BINARY | THRESH_TRIANGLE);
    showImg("大津法", out_OTSU);
    showImg("三角形法", out_TRIANGLE);
    
    // 自适应二值化
    Mat adapative_mean,adapative_gauss;
    // 均值法
    adaptiveThreshold(img_1, adapative_mean, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 55, 8);
    // 高斯法
    adaptiveThreshold(img_1, adapative_gauss, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY,55, 8);
    showImg("自适应二值化-均值法", adapative_mean);
    showImg("自适应二值化-高斯法", adapative_gauss);

    // LUT查找表
    // 定义查找表
    uchar lutFirst[256];
    for (int i = 0; i<256; i++) {
        if (i<=100)
            lutFirst[i] = 0;
        if (i>100 && i<=200)
            lutFirst[i] = 100;
        if (i>200)
            lutFirst[i] = 200;
    }
    Mat lut(1, 256, CV_8UC1, lutFirst);
    Mat LUTout;
    LUT(gray, lut, LUTout);
    showImg("LUT", LUTout);

    waitKey(0);
    destroyAllWindows();
    return 0;
}
