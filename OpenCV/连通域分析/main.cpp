/*
    作者: btx
    日期: 23-7-11
    功能：连通域分析
·连通性类型connectivity
        cv::8：使用8邻域，即上下左右四个像素和它们的对角线方向的像素。
        cv::4：使用4邻域，即上下左右四个像素。
        cv::8U：使用8邻域，返回无符号整数类型的标签。
        cv::4U：使用4邻域，返回无符号整数类型的标签。
·只分割连通域的函数
    int cv::connectedComponents()（
          cv::InputArray image, // 输入的二值图像，通常是一个二维的uint8类型矩阵
          cv::OutArray   labels, // 输出的连通区域标签图像，也是一个二维的uint8类型矩阵，与输入图像具有相同的尺寸。每个像素的标签值表示该像素所属的连通区域编号
          int            connectivity = 8,  // 连通性类型
          int            Itype = CV_32S // 输出图像数据类型,可以是CV_32S和CV_16U
    ）
    返回值:连通域的数量

    int cv::connectedComponentsWithStats(
          cv::InputArray image, // 输入的二值图像，通常是一个二维的uint8类型矩阵
          cv::OutArray   labels, // 输出的连通区域标签图像 
          OutputArray    stats, //输出结构体数组，每个结构体表示一个连通区域的统计信息，包括面积、周长、矩形度、垂直度、水平度等
          OutputArray    centroids, //输出数组，表示每个连通区域的质心坐标
          int            connectivity = 8,  // 连通性类型
          int            Itype = CV_32S // 输出图像数据类型
          int            ccltype = CV_32S // 连通区域统计信息的数据类型，可以是 CV_32S（默认值）或 CV_64F
     )

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
    Mat imgOrigin = imread("./img.png");
    if (imgOrigin.empty()) {
        printf("读入图片异常");
        return 0;
    }
    showImg("原图", imgOrigin);
    // 二值化
    Mat img;
    cvtColor(imgOrigin, img, COLOR_BGR2GRAY);
    threshold(img, img, 50, 255, THRESH_BINARY);
    showImg("二值化", img);
    // 生成随机颜色
    // cv::RNG 伪随机数生成器,用于生成随机的颜色值
    RNG rng(10086);
    Mat out;
    // 只分割连通域的函数
    int number = connectedComponents(img, out, 8, CV_16U);
    // 颜色表
    vector<Vec3b> colors;
    for (int i = 0; i < number; i++) {
        Vec3b vec3 = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        colors.push_back(vec3);
    }
    // 标记连通域
    Mat res = Mat::zeros(img.size(), imgOrigin.type());
    int w = res.cols;
    int h = res.rows;
    for (int row = 0; row < h; row++) {
        for (int col = 0; col < w; col++) {
            int label = out.at<uint16_t>(row, col);
            // 跳过黑色背景
            if (label == 0) {
                continue;
            }
            res.at<Vec3b>(row, col) = colors[label];
        }
    }
    showImg("标记后的图像", res);

   // 统计连通域信息
    Mat stats, centroids;
    number = connectedComponentsWithStats(img, out, stats, centroids, 8, CV_16U);
    vector<Vec3b> colors_new;
    for (int i = 0; i < number; i++) {
        Vec3b vec3 = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        colors_new.push_back(vec3);
    }
    for (int i = 1; i < number; i++) {
        // 中心位置
        int center_x = centroids.at<double>(i, 0);
        int center_y = centroids.at<double>(i, 1);
        // 矩形边框
        int x = stats.at<int>(i, CC_STAT_LEFT);
        int y = stats.at<int>(i, CC_STAT_TOP);
        int w = stats.at<int>(i, CC_STAT_WIDTH);
        int h = stats.at<int>(i, CC_STAT_HEIGHT);
        int area = stats.at<int>(i, CC_STAT_AREA);
        // 中心位置绘制
        circle(imgOrigin, Point(center_x, center_y), 2, Scalar(0, 255, 0), 2, 8, 0);
        // 外接矩形
        Rect rect(x, y, w, h);
        rectangle(imgOrigin, rect, colors_new[i], 1, 8, 0);
        putText(imgOrigin, format("%d", i), Point(center_x, center_y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
        cout << "number:" << i << ",area:" << area << endl;
    }
    showImg("标记后的图像_统计连通域信息", imgOrigin);
    waitKey(0);
    destroyAllWindows();
    return 0;
}
