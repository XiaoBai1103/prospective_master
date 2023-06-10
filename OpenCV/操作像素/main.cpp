/*
    作者: btx
    日期: 23-6-8
    功能：像素操作
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
//指针扫描 以降低图片色彩为例
void colorReduce_pointer(cv::Mat image, int div = 64) {
    int nl = image.rows; // 行数 
    int nc = image.cols * image.channels();// 每行的元素总数 
    //isContinuous 方法检查矩阵的连续性
    //也可以检查行的长度（字节数）与“列的个数×单个像素”的字节数是否相等 
    //image.step == image.cols * image.elemSize();
    /*
        在代码中，如果输入图像是连续的，那么就没有填充的像素，
        所以我们可以将图像看作是一维数组来处理，这样可以简化程
        序的实现，并且避免处理填充像素时的额外开销。因此，我们
        将图像的列数乘以行数，得到了图像中像素总数nc，然后将行
        数设置为1，这样我们就可以使用单个循环来迭代整个像素数组。
    */
    if (image.isContinuous()) {       
        // 没有填充的像素 
        nc = nc * nl;
        nl = 1; // 它现在成了一个一维数组 
    }
    //计算一个数的二进制表示中最高位的位置
    //static_cast是一个强制类型转换操作符
    int n = static_cast<int>(
        log(static_cast<double>(div)) / log(2.0) + 0.5);
    // 用来截取像素值的掩码 
    uchar mask = 0xFF << n; //左移n位 如果 div=16, 那么 mask= 0xF0 
    uchar div2 = div >> 1; // div2 = div/2 
    // 对于连续图像，这个循环只执行一次 
    for (int j = 0; j < nl; j++) {
        uchar* data = image.ptr<uchar>(j);//获取第j行的起始地址
        for (int i = 0; i < nc; i++) {
            *data &= mask; //数据和掩码进行与运算
            *data++ += div2; //将指针data所指向的像素值加上div2，并将指针data移动到下一个像素
        } // 一行图像的处理结束 
    }
}
//迭代器扫描 以降低图片色彩为例
void colorReduce_iter(cv::Mat image, int div = 64) {
// div 必须是 2 的幂
    int n = static_cast<int>(
        log(static_cast<double>(div)) / log(2.0) + 0.5);
    // 用来截取像素值的掩码
    uchar mask = 0xFF << n; // 如果 div=16, mask=0xF0 
    uchar div2 = div >> 1; // div2 = div/2 
    // 迭代器
    cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>();
    // 扫描全部像素
    for (; it != itend; ++it) {
        (*it)[0] &= mask;
        (*it)[0] += div2;
        (*it)[1] &= mask;
        (*it)[1] += div2;
        (*it)[2] &= mask;
        (*it)[2] += div2;
    }
}
// 重映射图像，创建波浪形效果
void wave(const cv::Mat& image, cv::Mat& result) {
    // 映射参数
    cv::Mat srcX(image.rows, image.cols, CV_32F);
    cv::Mat srcY(image.rows, image.cols, CV_32F);
    // 创建映射参数
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            // (i,j)像素的新位置
            srcX.at<float>(i, j) = j; // 保持在同一列
            // 原来在第 i 行的像素，现在根据一个正弦曲线移动
            srcY.at<float>(i, j) = i + 5 * sin(j / 10.0);
        }
    }
    // 应用映射参数
    cv::remap(image, // 源图像
        result, // 目标图像
        srcX, // x 映射
        srcY, // y 映射
        cv::INTER_LINEAR); // 填补方法
}

int main()
{
    /*
        读取图像对象的基本操作
    */
    Mat img = imread("./test1.jpg");
    if (img.empty()) {
        printf("读入图片异常");
        return 0;
    }
    Mat res;
    showImg("显示原始图像",img);
    res = img.clone();
    //colorReduce_pointer(res);
    colorReduce_iter(res);
    showImg("减少色彩后的图像", res);
    res = img.clone();
    wave(img, res);
    showImg("图像重映射", res);
 
    waitKey(0);
    destroyAllWindows();
    return 0;
}
