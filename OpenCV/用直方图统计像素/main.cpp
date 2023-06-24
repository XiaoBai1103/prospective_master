/*
    ����: btx
    ����: 23-6-23
    ���ܣ�ֱ��ͼ
*/
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
//��ʾͼ��
void showImg(String name, Mat img) {
    //ͨ��namedWindowʵ�ִ��ڴ�С�ɵ��ڣ�ע��name����һ��
    namedWindow(name, WINDOW_FREERATIO);
    imshow(name, img);

}

/*
    cv::calcHist ͨ��ֱ��ͼ���㺯��
*/

// �����Ҷ�ͼ���ֱ��ͼ
class Histogram1D {
private:
    int histSize[1]; // ֱ��ͼ�����ӵ�����
    float hranges[2]; // ֵ��Χ
    const float* ranges[1]; // ֵ��Χ��ָ��
    int channels[1]; // Ҫ����ͨ������
public:
    //���캯��
    Histogram1D() {
        // ׼��һάֱ��ͼ��Ĭ�ϲ���
        histSize[0] = 256; // 256 ������
        hranges[0] = 0.0; // �� 0 ��ʼ������
        hranges[1] = 256.0; // �� 256��������
        ranges[0] = hranges;
        channels[0] = 0; // �ȹ�עͨ�� 0
    }
    // ����һάֱ��ͼ
    Mat getHistogram(const Mat& image) {
        Mat rst;
        // �� calcHist ��������һάֱ��ͼ
        calcHist(&image, 1, // ��Ϊһ��ͼ���ֱ��ͼ
            channels, // ʹ�õ�ͨ��
            Mat(), // ��ʹ������
            rst, // ��Ϊ�����ֱ��ͼ
            1, // ����һά��ֱ��ͼ
            histSize, // ��������
            ranges // ����ֵ�ķ�Χ
        );
        return rst;
    }
    /*
    ��״ͼ���Ʒ���
    */
    // ����һάֱ��ͼ������������ͼ��
    Mat getHistogramImage(const Mat& image, int zoom = 1) {
        // �ȼ���ֱ��ͼ
        Mat hist = getHistogram(image);
        // ����ͼ��
        return getImageOfHistogram(hist, zoom);
    }

    // ����һ����ʾֱ��ͼ��ͼ�񣨾�̬������
    static Mat getImageOfHistogram(const Mat& hist, int zoom) {
        // ȡ������ֵ�����ֵ����Сֵ
        double maxVal = 0;
        double minVal = 0;
        minMaxLoc(hist, &minVal, &maxVal, 0, 0);
        // ȡ��ֱ��ͼ�Ĵ�С
        int histSize = hist.rows;
        // ������ʾֱ��ͼ�ķ���ͼ��
        Mat histImg(histSize * zoom, histSize * zoom,
            CV_8U, Scalar(255));
        // ������ߵ�Ϊ 90%����ͼ��߶ȣ������Ӹ���
        int hpt = static_cast<int>(0.9 * histSize);
        // Ϊÿ�����ӻ���ֱ��
        for (int h = 0; h < histSize; h++) {
            float binVal = hist.at<float>(h);
            if (binVal > 0) {
                int intensity = static_cast<int>(binVal * hpt / maxVal);
                //cv:line ����ֱ�߷��� ���ƺ�ɫͼ���߿�Ϊzoom
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
    Mat img = imread("./img.webp",0);//�Ժڰ׵���ʽ��
    if (img.empty()) {
        printf("����ͼƬ�쳣");
        return 0;
    }
    showImg("��ʾԭʼͼ��",img);

    Histogram1D h;
    Mat rst = h.getHistogram(img);
    // ѭ������ÿ������
    for (int i = 0; i < 256; i++)
        cout << "Value " << i << " = "
        << rst.at<float>(i) << endl;
    namedWindow("Histogram");
    imshow("Histogram", h.getHistogramImage(img));
    waitKey(0);
    destroyAllWindows();
    return 0;
}
