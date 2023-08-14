/*
    作者: btx
    日期: 23-8-12
    功能：点集拟合

    void cv::fitLine(
        cv::InputArray points, // 二维点的数组或vector
        cv::OutputArray line, // 输出直线,Vec4f (2d)或Vec6f (3d)的vector
        int distType, // 距离类型
        double param, // 距离参数
        double reps, // 径向的精度参数
        double aeps // 角度精度参数
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
    Vec4f lines;
    vector<Point2f> point;
    point.push_back(cv::Point(100., 58.));
    point.push_back(cv::Point(150., 70.));
    point.push_back(cv::Point(200., 90.));
    point.push_back(cv::Point(252., 140.));
    point.push_back(cv::Point(300., 220.));
    point.push_back(cv::Point(350., 400.));
    // 参数
    double param = 0; // 距离参数
    double rep = 0.01; // 径向精度
    double aeps = 0.01; // 角度精度
    //直线拟合
    fitLine(point, lines, DIST_L1, 0, 0.01, 0.01);
    double k = lines[1] / lines[0]; // 计算斜率
    cout << "直线斜率:" << k << endl;
    cout << "坐标 x:" << lines[2]<<", y:"<<lines[3] << endl;
    cout << "直线解析式: y=" << k << "(x-"<<lines[2]<<")+"<<lines[3]<<endl;


    Mat img(500, 500, CV_8UC3, Scalar::all(0));
    RNG& rng = theRNG();// 随机点生成
    while (1) {
        int i, count = rng.uniform(1, 101);
        vector<Point2f> points;
        //随机点生成
        for (i = 0; i < count; i++) {
            Point pt;
            pt.x = rng.uniform(img.cols / 4, img.cols * 3 / 4);
            pt.y = rng.uniform(img.rows / 4, img.rows * 3 / 4);
            points.push_back(pt);
        }
        // 包围点集三角形
        vector<Point2f>triangle;// 顶点坐标
        double area = minEnclosingTriangle(points, triangle); // 轮廓的最小外接三角形
        // 包围点集圆形
        Point2f center;
        float radius = 0;
        minEnclosingCircle(points, center, radius); // 轮廓的最小外接圆
        // 深拷贝图像
        Mat img_triangle = img.clone();
        Mat img_circle = img.clone();
        // 绘制点
        for (i = 0; i < count; i++) {
            circle(img_triangle, points[i], 3, Scalar(255, 255, 255), FILLED, LINE_AA);
            circle(img_circle, points[i], 3, Scalar(255, 255, 255), FILLED, LINE_AA);
        }
        // 绘制三角形
        for (i = 0; i < count; i++) {
            if (i == 2) {
                line(img_triangle, triangle[i], triangle[0], Scalar(255, 255, 255), 1, 16);
                break;
            }
            line(img_triangle, triangle[i], triangle[i+1], Scalar(255, 255, 255), 1, 16);
        }
        // 绘制圆形
        circle(img_circle, center, cvRound(radius), Scalar(255, 255, 255), 1, LINE_AA);
        // 结果
        showImg("三角形", img_triangle);
        showImg("圆形", img_circle);
        waitKey(0);
    }

    return 0;
}
