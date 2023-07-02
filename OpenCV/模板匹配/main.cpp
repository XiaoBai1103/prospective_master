/*
    作者: btx
    日期: 23-7-1
    功能：模板匹配

    cv::matchTemplate（
          cv::InputArray image, //需要匹配的图像
          cv::InputArray temp,  //模板图像
          cv::OutArray  result, //存储的计算得到的结果
          int           method,  //匹配的方法
          cv::InputArray mask    //匹配模板的掩码，默认不设置
    ）
        
    模板匹配方法标志：
    标志参数        简记   功能
    TM_SQDIFF        0    方差匹配法

    TM_SQDIFF_NORMED 1    归一方差匹配法

    TM_CCORR         2    相关性匹配方法

    TM_CCORR_NORMED  3    归一化的互相关匹配法

    TM_CCOEFF        4    相关系数匹配法

    TM_CCOEFF_NORMED 5    归一化相关系数匹配方法



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
    // 原图
    Mat img = imread("./img.webp");
    if (img.empty()) {
        printf("读入图片异常");
        return 0;
    }
    showImg("原图", img);
    // 目标图像
    Mat img_template = imread("./template.png");
    if (img.empty()) {
        printf("读入图片异常");
        return 0;
    }
    showImg("模板图像", img_template);
    // 模板匹配
    Mat res;
    matchTemplate(img, img_template, res, TM_CCOEFF_NORMED);
    showImg("匹配系数矩阵", res);
    // 找到最大像素点
    double maxVal, minVal;
    Point maxLoc, minLoc;
    minMaxLoc(res,&minVal,&maxVal,&minLoc,& maxLoc);
    // 在最大值位置绘制矩形
    rectangle(img, Point(maxLoc.x, maxLoc.y), Point(maxLoc.x + img_template.cols, maxLoc.y + img_template.rows), Scalar(0, 0, 255), 2);

    showImg("结果", img);
    waitKey(0);
    destroyAllWindows();
    return 0;
}
