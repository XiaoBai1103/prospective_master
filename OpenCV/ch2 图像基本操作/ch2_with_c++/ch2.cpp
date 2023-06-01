/*
    作者: btx
    日期: 23-6-1
    功能：第二章的c++实现
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

int main()
{
    /*
        图像对象的基本操作
    */
    // 读取图像
    Mat img = imread("./test1.jpg");
    if (img.empty()) {
        printf("读入图片异常");
        return 0;
    }
    // 显示原始图像
    showImg("显示原始图像",img);
    //颜色空间转换
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    showImg("灰度图像",gray);
    /*
        图像的算术操作
        ·saturate_cast：防止溢出
        ·add  加
        ·subtract   减
        ·multiply   乘
        ·divide   除
    */
    //反转图像
    Mat img_r = img.clone(); 
    reverse(img);
    //图像
    Mat rst,rst1,rst2,img1;
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
    /*
        矩阵操作    
    */
    //MAT创建
    Mat m1, m2, m3, m4;
    //克隆图像
    m1 = img.clone();
    //空白图像
    m2 = Mat::zeros(Size(8, 8), CV_8UC1);//8UC1:8位无符号，通道数为1
    std::cout << m2 << std::endl;
    //获取宽高以及通道数
    std::cout << "width:" << m2.cols << "height:" << m2.rows << "channels:" << m2.channels() << std::endl;
    m3 = Mat::zeros(Size(128, 128), CV_8UC3);
    m3 = 127;//只会将第一个通道赋值为127！
    std::cout << m3 << std::endl;
    m3 = Scalar(127,200,80);
    std::cout << m3 << std::endl;
    showImg("生成的矩阵图像显示效果", m3);
    m4 = m3.clone();//克隆会申请新的地址空间
    //m4 = m3; //最终的输出m3和m4是一样的，直接赋值相当于只复制了内存地址，所操作的对象相同
    m4 = Scalar(17, 220, 120);
    m3 = Scalar(27, 12, 20);
    showImg("m4", m4);
    showImg("m3", m3);

    // 等待用户按下键盘
    waitKey(0);

    // 销毁所有窗口
    destroyAllWindows();

    return 0;
}
