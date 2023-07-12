/*
    ����: btx
    ����: 23-7-12
    ���ܣ�ͼ�����任
    �����þ���
    CV_DIST_L1 ��������
    CV_DIST_L2��ŷʽ����
    CV_DIST_C�����̾���
    cv::distanceTransform��
          cv::InputArray image, // �����ֵͼ�񣬱����ǵ�ͨ����8λ�޷�������ͼ��
          cv::OutArray   result, // �洢�ļ���õ��Ľ��
          int            distanceType,  // �������Ͳ���
          int            maskSize, // ��ģ��С����
                                   //     CV_DIST_MASK_5��ʹ��5x5����ģ���м��㡣
                                   //     CV_DIST_MASK_3��ʹ��3x3����ģ���м��㡣
                                   //     CV_DIST_MASK_PRECISE��ʹ�þ�ȷ�㷨���м��㣬���ٶȽ�����
          int            dstType = CV_32F // ���ͼ���������ͣ�Ĭ��CV_32F����ѡCV_8U
    ��

*/
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
// ��ʾͼ��
void showImg(String name, Mat img) {
    // ͨ��namedWindowʵ�ִ��ڴ�С�ɵ��ڣ�ע��name����һ��
    namedWindow(name, WINDOW_FREERATIO);
    imshow(name, img);
}

int main()
{
    // ��������
    Mat a = (Mat_<uchar>(5, 5) << 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 0, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1);
    Mat dist_L1, dist_L2, dist_C;
    // �����������
    distanceTransform(a, dist_L1, 1, 3, CV_8U);
    cout << "��������:" << endl << dist_L1 << endl;
    // ����ŷʽ����
    distanceTransform(a, dist_L2, 2, 5, CV_8U);
    cout << "ŷʽ����:" << endl << dist_L2 << endl;
    // �������̾���
    distanceTransform(a, dist_C, 3, 5, CV_8U);
    cout << "���̾���:" << endl << dist_C << endl;
    // ��ͼ����б任
    // ԭͼ
    Mat img = imread("./img.png",0);
    if (img.empty()) {
        printf("����ͼƬ�쳣");
        return 0;
    }
    showImg("ԭͼ", img);
    Mat imgBW, imgBW_INV;
    // ��ֵ��
    threshold(img, imgBW, 50, 255, THRESH_BINARY);
    threshold(img, imgBW_INV, 50, 255, THRESH_BINARY_INV);
    // ����任
    Mat dist, dist_INV;
    distanceTransform(imgBW, dist, 1, 3, CV_32F);
    convertScaleAbs(dist,dist);
    distanceTransform(imgBW_INV, dist_INV, 1, 3, CV_8U);
    showImg("dist", dist);
    showImg("imgBW", imgBW);
    showImg("dist_INV", dist_INV);
    showImg("imgBW_INV", imgBW_INV);

    waitKey(0);
    destroyAllWindows();
    return 0;
}
