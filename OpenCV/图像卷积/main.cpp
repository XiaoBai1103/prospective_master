/*
    作者: btx
    日期: 23-7-3
    功能：图像卷积

    cv::cvFilter2D（
          cv::InputArray image, // 需要匹配的图像
          cv::OutArray   result, // 存储的计算得到的结果
          int            ddepth = -1,  // 输出图像的类型（深度）,默认与输入图像的深度相同
          cv::InputArray kernel, // 卷积核，CV_32FC1类型矩阵
          cv::Point      anchor = (-1,-1), //内核基准点（锚点），默认是kernel的中心位置
          double         delta = 0, // 偏值，该值直接加在计算结果中
          int            boderType = BORDER_DEFAULT //像素外推方法
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
    // 卷积模板
    Mat kernel = (Mat_<float>(3, 3) <<
        1, 2, 1,
        2, 0, 2,
        1, 2, 1);
    Mat kernel_norm = kernel / 12;// 归一化

    /*
        矩阵卷积运算
    */
    // 待卷积矩阵
    uchar points[25];
    for (int i = 0; i < 25; i++) {
        points[i] = i;
    }
    Mat img1(5, 5, CV_8UC1, points);
    // 卷积运算
    Mat res, res_norm;
    filter2D(img1, res, CV_32F, kernel, Point(-1, -1), 2, BORDER_CONSTANT);
    cout << "卷积结果:" << endl << res << endl;
    filter2D(img1, res_norm, CV_32F, kernel_norm, Point(-1, -1), 2, BORDER_CONSTANT);
    cout << "归一化卷积结果:" << endl << res_norm << endl;

    /*
        图像卷积运算
    */
    // 原图
    Mat img2 = imread("./img.webp");
    if (img2.empty()) {
        printf("读入图片异常");
        return 0;
    }
    showImg("原图", img2);
    Mat res_img;
    filter2D(img2, res_img, -1, kernel_norm, Point(-1, -1), 2, BORDER_CONSTANT);
    showImg("图像卷积",res_img);
    waitKey(0);
    destroyAllWindows();
    return 0;
}
