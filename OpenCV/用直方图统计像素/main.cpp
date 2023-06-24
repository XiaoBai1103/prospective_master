/*
    作者: btx
    日期: 23-6-23
    功能：直方图
*/
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
//显示图像
void showImg(String name, Mat img) {
    //通过namedWindow实现窗口大小可调节，注意name必须一致
    namedWindow(name, WINDOW_FREERATIO);
    imshow(name, img);

}

/*
    cv::calcHist 通用直方图计算函数
*/

// 创建灰度图像的直方图
class Histogram1D {
private:
    int histSize[1]; // 直方图中箱子的数量
    float hranges[2]; // 值范围
    const float* ranges[1]; // 值范围的指针
    int channels[1]; // 要检查的通道数量
public:
    //构造函数
    Histogram1D() {
        // 准备一维直方图的默认参数
        histSize[0] = 256; // 256 个箱子
        hranges[0] = 0.0; // 从 0 开始（含）
        hranges[1] = 256.0; // 到 256（不含）
        ranges[0] = hranges;
        channels[0] = 0; // 先关注通道 0
    }
    // 计算一维直方图
    Mat getHistogram(const Mat& image) {
        Mat rst;
        // 用 calcHist 函数计算一维直方图
        calcHist(&image, 1, // 仅为一幅图像的直方图
            channels, // 使用的通道
            Mat(), // 不使用掩码
            rst, // 作为结果的直方图
            1, // 这是一维的直方图
            histSize, // 箱子数量
            ranges // 像素值的范围
        );
        return rst;
    }
    /*
    柱状图绘制方法
    */
    // 计算一维直方图，并返回它的图像
    Mat getHistogramImage(const Mat& image, int zoom = 1) {
        // 先计算直方图
        Mat hist = getHistogram(image);
        // 创建图像
        return getImageOfHistogram(hist, zoom);
    }

    // 创建一个表示直方图的图像（静态方法）
    static Mat getImageOfHistogram(const Mat& hist, int zoom) {
        // 取得箱子值的最大值和最小值
        double maxVal = 0;
        double minVal = 0;
        minMaxLoc(hist, &minVal, &maxVal, 0, 0);
        // 取得直方图的大小
        int histSize = hist.rows;
        // 用于显示直方图的方形图像
        Mat histImg(histSize * zoom, histSize * zoom,
            CV_8U, Scalar(255));
        // 设置最高点为 90%（即图像高度）的箱子个数
        int hpt = static_cast<int>(0.9 * histSize);
        // 为每个箱子画垂直线
        for (int h = 0; h < histSize; h++) {
            float binVal = hist.at<float>(h);
            if (binVal > 0) {
                int intensity = static_cast<int>(binVal * hpt / maxVal);
                //cv:line 绘制直线方法 绘制黑色图像，线宽为zoom
                line(histImg, Point(h * zoom, histSize * zoom),
                    Point(h * zoom, (histSize - intensity) * zoom),
                    Scalar(0), zoom);
            }
        }
        return histImg;
    }
};




int main()
{
    Mat img = imread("./img.webp",0);//以黑白的形式打开
    if (img.empty()) {
        printf("读入图片异常");
        return 0;
    }
    showImg("显示原始图像",img);

    Histogram1D h;
    Mat rst = h.getHistogram(img);
    // 循环遍历每个箱子
    for (int i = 0; i < 256; i++)
        cout << "Value " << i << " = "
        << rst.at<float>(i) << endl;
    namedWindow("Histogram");
    imshow("Histogram", h.getHistogramImage(img));
    waitKey(0);
    destroyAllWindows();
    return 0;
}
