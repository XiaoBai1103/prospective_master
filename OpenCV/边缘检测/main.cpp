/*
    作者: btx
    日期: 23-7-5
    功能：边缘检测

    - Sobel算子
        void cv::Sobel(
            InputArray src, // 输入的源图像
            OutputArray dst, // 输出的边缘图像
            int ddepth, // 输出图像的深度，指定输出图像的像素类型和深度
            int xorder, // Sobel算子在水平方向上的阶数
            int yorder, // Sobel算子在垂直方向上的阶数
            int ksize = 3, // Sobel算子的大小
            double k = 0, // 阈值,用于对边缘进行强化或去除噪声的操作
            int borderType = BORDER_DEFAULT // 边界填充方式
        );

    - Scharry算子
        void cv::Scharr(  
            InputArray src, // 输入的源图像  
            OutputArray dst, // 输出的边缘图像  
            int ddepth, // 输出图像的深度  
            int xorder, // Scharr算子在水平方向上的阶数  
            int yorder, // Scharr算子在垂直方向上的阶数  
            int ksize = 3, // Scharr算子的大小  
            double scale = 1, // 缩放因子  
            double delta = 0, // 偏移量  
            int borderType = BORDER_DEFAULT // 边界填充方式  
        );

    - Laplacian算子
        void cv::Laplacian(
            InputArray src, // 输入的源图像
            OutputArray dst, // 输出的边缘图像
            int ddepth, // 输出图像的深度，指定输出图像的像素类型和深度
            int ksize = 3, //拉普拉斯算子的大小，一般为奇数
            double scale = 1, // 缩放因子，用于调整输出像素值的范围
            double delta = 0, //偏移量，用于调整输出像素值的零点偏移
            int borderType = BORDER_DEFAULT //边界填充方式
        );

    - Canny算法
        void cv::canny(
            InputArray src, // 输入的源图像
            OutputArray dst, // 输出的边缘图像
            double threshold1, // 第一个阈值，用于在检测到的边缘上消除弱的像素点。通常设置为较小的值，例如50或100。
            double threshold2, // 第二个阈值，用于确定哪些像素点是强边缘，哪些是弱边缘。通常设置为较大的值，例如150或200。
            int apertureSize = 3, // Sobel算子的核大小,通常设置为3
            bool L2gradient = false // 计算图像梯度幅值的标志
        );

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
    Mat img = imread("./img.webp",0);
    if (img.empty()) {
        printf("读入图片异常");
        return 0;
    }
    showImg("原图", img);
    
    Mat res_x, res_y, res_xy, res, res_Gaussian,res_high, res_low, res_G;
    //goto Sobel;
    //goto Scharr;
    //goto Laplacian; 
    goto Canny;
    /*
        Sobel算子
    */
 Sobel:
    // x方向一阶边缘检测
    Sobel(img,res_x,CV_16S,1,0,1);
    // 转换为8 bit unsigned int
    convertScaleAbs(res_x, res_x);
    showImg("Sobel算子 X方向", res_x);
    // y方向一阶边缘检测
    Sobel(img, res_y, CV_16S, 1, 0, 1);
    // 转换为8 bit unsigned int
    convertScaleAbs(res_y, res_y);
    showImg("Sobel算子 Y方向", res_y);
    // 合成图像
    res_xy = res_x + res_y;
    showImg("Sobel算子 合成图像", res_xy);
    waitKey(0);
    return 0;
    /*
        Scharr算子
    */
 Scharr:
    // x方向一阶边缘检测
    Scharr(img, res_x, CV_16S, 1, 0, 1);
    // 转换为8 bit unsigned int
    convertScaleAbs(res_x, res_x);
    showImg("Scharr算子 X方向", res_x);
    // y方向一阶边缘检测
    Scharr(img, res_y, CV_16S, 1, 0, 1);
    // 转换为8 bit unsigned int
    convertScaleAbs(res_y, res_y);
    showImg("Scharr算子 Y方向", res_y);
    // 合成图像
    res_xy = res_x + res_y;
    showImg("Scharr算子 合成图像", res_xy);
    waitKey(0);
    return 0;
    /*
        Laplacian算子
    */
Laplacian:
    // 未滤波提取边缘
    Laplacian(img, res, CV_16S, 3, 1, 0);
    convertScaleAbs(res, res);
    showImg("Laplacian算子 未滤波提取边缘", res);
    // 滤波后提取边缘
    GaussianBlur(img, res_Gaussian, Size(3,3),5,0);
    Laplacian(res_Gaussian, res, CV_16S, 3, 1, 0);
    convertScaleAbs(res, res);
    showImg("Laplacian算子 滤波后提取边缘", res);
    waitKey(0);
    return 0;
    /*
        Canny边缘检测
    */
Canny:
    // 大阈值检测图像边缘
    Canny(img, res_high,100,200,3);
    showImg("Canny边缘检测 大阈值检测图像边缘", res_high);
    // 小阈值检测图像边缘
    Canny(img, res_low, 20, 40, 3);
    showImg("Canny边缘检测 小阈值检测图像边缘", res_low);
    // 高斯模糊后检测图像边缘
    GaussianBlur(img, res_Gaussian, Size(3, 3), 5, 0);
    Canny(res_Gaussian,res_G, 100, 200, 3);
    showImg("Canny边缘检测 高斯模糊后检测图像边缘", res_G);
    waitKey(0);
    return 0;

}
