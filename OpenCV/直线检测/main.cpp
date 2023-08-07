/*
    作者: btx
    日期: 23-8-4
    功能: 直线检测

    - 直线检测函数
       cv::HoughLines( 
            InputArray image, // 输入图像 8位的单通道二进制图像
            OutputArray lines, // 输出直线 每一条线由具有两个元素的矢量（r,t）表示。r为离坐标原点的距离，t为弧度线条旋转角度
            double rho, // 以像素为单位的距离精度
            double theta, // 以弧度为单位的角度精度
            int threshold,// 累加平面的阈值参数
            double srn = 0, // 对于多尺度的霍夫变换，这是第三个参数rho的除数距离
            double stn = 0, // 对于多尺度的霍夫变换，这是第四个参数theta的除数距离
            double min_theta = 0, // 对于标准和多尺度霍夫变换，检查线的最小角度
            double max_theta = CV_PI // 对于标准和多尺度霍夫变换，检查线的最大角度
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
// 标记直线
void drawLine(Mat& img, vector<Vec2f> lines, double rows, double cols, Scalar scalar, int n) {
    Point pt1, pt2;
    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0]; // 直线距离坐标原点的距离
        float theta = lines[i][1]; // 直线过坐标原点的垂线与x轴夹角
        double a = cos(theta); // 夹角余弦
        double b = sin(theta); // 夹角正弦
        double x0 = a * rho, y0 = b * rho; // 直线与过坐标原点的垂线的交点
        double length = max(rows, cols); // 图像高宽的最大值
        // 计算直线上的一点
        // cv::line绘制的线段 为了保证所画直线贯穿图像 需要计算图像最大值
        // 返回跟参数最接近的整数值(四舍五入)
        pt1.x = cvRound(x0 + length * (-b));
        pt1.y = cvRound(y0 + length * (a));
        // 计算直线上的另一点
        pt2.x = cvRound(x0 - length * (-b));
        pt2.y = cvRound(y0 - length * (a));
        // 绘制直线
        line(img, pt1, pt2, scalar, n);
    }
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
    Mat gray,binary,edge;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    Canny(gray, edge, 80,180,3,false);
    showImg("边缘检测", edge);
    // 直线检测
    vector<Vec2f> lines1, lines2;
    HoughLines(edge, lines1, 1, CV_PI / 180, 140, 0, 0);
    HoughLines(edge, lines2, 1, CV_PI / 180, 180, 0, 0);
    //直线绘制
    Mat img1, img2;
    img.copyTo(img1);
    img.copyTo(img2);
    drawLine(img1,lines1,edge.rows,edge.cols,Scalar(0,0,255),2);
    drawLine(img2,lines2, edge.rows, edge.cols, Scalar(0, 0, 255), 2);
    showImg("结果图像:阈值为140", img1);
    showImg("结果图像:阈值为180", img2);
    waitKey(0);
    return 0;
}
