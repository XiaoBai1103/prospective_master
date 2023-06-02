/*
    作者: btx
    日期: 23-6-2
    功能：第二章的c++实现
    笔记和代码基于课程（OpenCV4 C++ 快速入门视频30讲）：https://www.bilibili.com/video/BV1i54y1m7tw
*/
#include <opencv2/opencv.hpp>

using namespace cv;
//显示图像
void showImg(String name,Mat img) {
    //通过namedWindow实现窗口大小可调节，注意name必须一致
    namedWindow(name, WINDOW_FREERATIO);
    imshow(name, img);
}
/*
    像素读写方法，以反转图像为例
    rows: 行
    cols: 列
    图片的表示以左上角为原点，横坐标为cols，纵坐标为rows
    Mat类型变量访问时下标顺序为先行后列
    img.ptr<uchar>(y)[x]; 表示第y-1行，x-1的像素的指针
*/
void reverse(Mat &image)
{
    int w = image.cols;
    int h = image.rows;
    int dims = image.channels();
    for (int row = 0; row < h; row++) {
        uchar* current_row = image.ptr<uchar>(row);
        for (int col = 0; col < w; col++) {
            if (dims == 1) { // 灰度图像
                int pv = *current_row;
                *current_row++ = 255 - pv;
            }
            if (dims == 3) { // 彩色图像
                *current_row++ = 255 - *current_row;
                *current_row++ = 255 - *current_row;
                *current_row++ = 255 - *current_row;
            }
        }
    }
    showImg("反转图像", image);
}
/*
     图像的算术操作
        ·saturate_cast：防止溢出
        ·add  加
        ·subtract   减
        ·multiply   乘
        ·divide   除
     图像的位操作
        ·bitwise_and 与
        ·bitwise_or 或
        ·bitwise_not 非
        ·bitwise_xor 异或
 */
void arithmetic(Mat& img) {
    //颜色空间转换
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    showImg("灰度图像", gray);
    //反转图像
    Mat img_r = img.clone();
    reverse(img);
    //图像
    Mat rst, rst1, rst2, img1;
    img1 = imread("./test2.jpg");
    add(img1, img, rst);
    showImg("图像加法操作", rst);
    //利用加减乘除调节亮度
    Mat black = Mat::zeros(img.size(), img.type());
    black = Scalar(80, 80, 80);
    add(rst, black, rst1);
    showImg("增加亮度", rst1);
    subtract(rst, black, rst2);
    showImg("降低亮度", rst2);
}
/*
    颜色通道
*/
void channels(Mat& img) {
    //新建向量
    std::vector<Mat> mv;
    split(img, mv);
    showImg("蓝色", mv[0]);
    showImg("绿色", mv[1]);
    showImg("红色", mv[2]);
    //通道合并
    Mat dst;
    merge(mv, dst);
    showImg("通道合并", dst);
    //只显示蓝色通道
    mv[1] = 0;
    mv[2] = 0;
    merge(mv, dst);
    showImg("通道合并-蓝色", dst);
    //通道交换
    int from_to[] = { 0,2,1,1,2,0 };
    mixChannels(&img,1, &dst,1,from_to,3);
    showImg("通道交换", dst);
}
/*
     矩阵操作
     -openCV核心数据结构：cv::Mat (包含一个头部和一个数据块）
        ·头部包含了矩阵的所有相关信息（大小、通道数量、数据类型等）
        ·数据块包含了图像中所有像素的值
        ·cv::Mat 有一个很重要的属性，即只有在明确要求时，内存块才会被复制。
      实际上，大多数操作仅仅复制了 cv::Mat 的头部，因此多个对象会指向同一个数据块,避免内存泄漏。
      可以通过clone方法实现深拷贝

      -cv::Scalar数据结构：用于在调用函数时传递像素值
        ·按照BGR的顺序构建彩色图像或只传入一个值构建灰度图像
 */
void matrix(Mat &img) {
 
    //MAT创建
    Mat m1, m2, m3, m4;
    //克隆图像
    m1 = img.clone();
    //空白图像
    m2 = Mat::zeros(Size(8, 8), CV_8UC1);//8UC1:8位无符号(8U)，通道数为1(C1)
    std::cout << m2 << std::endl;
    //获取宽高以及通道数
    std::cout << "width:" << m2.cols << "height:" << m2.rows << "channels:" << m2.channels() << std::endl;
    m3 = Mat::zeros(Size(128, 128), CV_8UC3);
    m3 = 127;//只会将第一个通道赋值为127！
    std::cout << m3 << std::endl;
    m3 = Scalar(127, 200, 80);
    std::cout << m3 << std::endl;
    showImg("生成的矩阵图像显示效果", m3);
    m4 = m3.clone();//克隆会申请新的地址空间
    //直接赋值而不用clone方法了话，最终的输出m3和m4是一样的，直接赋值相当于只复制了内存地址，所操作的对象相同
    //m4 = m3; 
    m4 = Scalar(17, 220, 120);
    m3 = Scalar(27, 12, 20);
    showImg("m4", m4);
    showImg("m3", m3);
}
/*
    ROI(感兴趣区域)
    ROI 实际上就是一个 cv::Mat 对象，它与它的父图像指向同一个数据缓冲区，并且在头部指明了 ROI 的坐标
    -使用 cv::Rect 实例
        ·前两个参数为ROI坐标，坐标是左上角的位置
        ·后两个参数为ROI大小
        ·顺序都是先cols再rows

*/
void ROI(Mat &img) {
    //插入
    Mat object(100, 100, CV_8UC3, cv::Scalar(0, 0, 255));
    Mat imgROI(img, Rect(30, 30, 100, 100));
    object.copyTo(imgROI);
    showImg("ROI:用 Rect", img);
    //用行和列的值域来描述
    imgROI = img.clone();
    imgROI = img(Range(img.rows - object.rows, img.rows),
                 Range(img.cols - object.cols, img.cols));
    showImg("ROI:用行和列的值域来描述", img);
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
    showImg("显示原始图像",img);





    //channels(img);//颜色通道分离
    


    //arithmetic(img);//算术操作
    //matrix(img);//矩阵操作
    ROI(img);




    waitKey(0);
    destroyAllWindows();
    return 0;
}
