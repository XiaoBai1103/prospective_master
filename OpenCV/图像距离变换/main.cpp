/*
    作者: btx
    日期: 23-7-12
    功能：图像距离变换
    ·常用距离
    CV_DIST_L1 街区距离
    CV_DIST_L2：欧式距离
    CV_DIST_C：棋盘距离
    cv::distanceTransform（
          cv::InputArray image, // 输入二值图像，必须是单通道的8位无符号整数图像。
          cv::OutArray   result, // 存储的计算得到的结果
          int            distanceType,  // 距离类型参数
          int            maskSize, // 掩模大小参数
                                   //     CV_DIST_MASK_5：使用5x5的掩模进行计算。
                                   //     CV_DIST_MASK_3：使用3x3的掩模进行计算。
                                   //     CV_DIST_MASK_PRECISE：使用精确算法进行计算，但速度较慢。
          int            dstType = CV_32F // 输出图像数据类型，默认CV_32F，可选CV_8U
    ）

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
    // 构建矩阵
    Mat a = (Mat_<uchar>(5, 5) << 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 0, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1);
    Mat dist_L1, dist_L2, dist_C;
    // 计算街区距离
    distanceTransform(a, dist_L1, 1, 3, CV_8U);
    cout << "街区距离:" << endl << dist_L1 << endl;
    // 计算欧式距离
    distanceTransform(a, dist_L2, 2, 5, CV_8U);
    cout << "欧式距离:" << endl << dist_L2 << endl;
    // 计算棋盘距离
    distanceTransform(a, dist_C, 3, 5, CV_8U);
    cout << "棋盘距离:" << endl << dist_C << endl;
    // 对图像进行变换
    // 原图
    Mat img = imread("./img.png",0);
    if (img.empty()) {
        printf("读入图片异常");
        return 0;
    }
    showImg("原图", img);
    Mat imgBW, imgBW_INV;
    // 二值化
    threshold(img, imgBW, 50, 255, THRESH_BINARY);
    threshold(img, imgBW_INV, 50, 255, THRESH_BINARY_INV);
    // 距离变换
    Mat dist, dist_INV;
    distanceTransform(imgBW, dist, 1, 3, CV_32F);
    convertScaleAbs(dist,dist);
    distanceTransform(imgBW_INV, dist_INV, 1, 3, CV_8U);
    showImg("dist", dist);
    showImg("imgBW", imgBW);
    showImg("dist_INV", dist_INV);
    showImg("imgBW_INV", imgBW_INV);

    waitKey(0);
    destroyAllWindows();
    return 0;
}
