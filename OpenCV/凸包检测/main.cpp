/*
    作者: btx
    日期: 23-7-28
    功能：凸包检测

    - Sobel算子
        void cv::convexHull(
                InputArray points,  // 输入二维点集
			    OutputArray hull,  // 凸包点集输出
			    bool clockwise = false,  // 凸包方向的标志位(True表示顺时针)
			    bool returnPoints = true  // 函数输出类型(True表示输出点坐标,False表示输出坐标索引)

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
    Mat img = imread("./img.png");
    if (img.empty()) {
        printf("读入图片异常");
        return 0;
    }
    showImg("原图", img);
    Mat gray, binary;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    threshold(gray,binary,105,255,THRESH_BINARY);
    
    //开运算
    Mat k = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
    morphologyEx(binary, binary, MORPH_OPEN,k);
    showImg("二值化", binary);
    // 获取轮廓
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, 0, 2, Point());
    for (int n = 0; n < contours.size(); n++) {
        // 凸包计算
        vector<Point> hull; //存储凸包顶点的向量
        convexHull(contours[n], hull);
        //图像绘制
        for (int i = 0; i < hull.size(); i++) {
            // 顶点绘制
            circle(img, hull[i], 4, Scalar(255, 0, 0), 2, 8, 0);
            // 顶点连线绘制
            if (i == hull.size() - 1) {
                line(img, hull[i], hull[0], Scalar(255, 0, 0), 2, 8, 0);
                break;
            }
            line(img, hull[i], hull[i+1], Scalar(255, 0, 0), 2, 8, 0);
        }
        

    }
    showImg("结果图像", img);
    waitKey(0);
    return 0;
}
