/*
    ����: btx
    ����: 23-7-3
    ���ܣ�ͼ����

    cv::cvFilter2D��
          cv::InputArray image, // ��Ҫƥ���ͼ��
          cv::OutArray   result, // �洢�ļ���õ��Ľ��
          int            ddepth = -1,  // ���ͼ������ͣ���ȣ�,Ĭ��������ͼ��������ͬ
          cv::InputArray kernel, // ����ˣ�CV_32FC1���;���
          cv::Point      anchor = (-1,-1), //�ں˻�׼�㣨ê�㣩��Ĭ����kernel������λ��
          double         delta = 0, // ƫֵ����ֱֵ�Ӽ��ڼ�������
          int            boderType = BORDER_DEFAULT //�������Ʒ���
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
    // ���ģ��
    Mat kernel = (Mat_<float>(3, 3) <<
        1, 2, 1,
        2, 0, 2,
        1, 2, 1);
    Mat kernel_norm = kernel / 12;// ��һ��

    /*
        ����������
    */
    // ���������
    uchar points[25];
    for (int i = 0; i < 25; i++) {
        points[i] = i;
    }
    Mat img1(5, 5, CV_8UC1, points);
    // �������
    Mat res, res_norm;
    filter2D(img1, res, CV_32F, kernel, Point(-1, -1), 2, BORDER_CONSTANT);
    cout << "������:" << endl << res << endl;
    filter2D(img1, res_norm, CV_32F, kernel_norm, Point(-1, -1), 2, BORDER_CONSTANT);
    cout << "��һ��������:" << endl << res_norm << endl;

    /*
        ͼ��������
    */
    // ԭͼ
    Mat img2 = imread("./img.webp");
    if (img2.empty()) {
        printf("����ͼƬ�쳣");
        return 0;
    }
    showImg("ԭͼ", img2);
    Mat res_img;
    filter2D(img2, res_img, -1, kernel_norm, Point(-1, -1), 2, BORDER_CONSTANT);
    showImg("ͼ����",res_img);
    waitKey(0);
    destroyAllWindows();
    return 0;
}
