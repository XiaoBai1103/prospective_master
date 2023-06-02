/*
    ����: btx
    ����: 23-5-31
-opencv������  ͼ����̬ѧ���� (c����ʵ�֣�
*/
#include <opencv2/opencv.hpp>
using namespace cv;
//��ʾͼ��
void showImg(String name, Mat img) {
    //ͨ��namedWindowʵ�ִ��ڴ�С�ɵ��ڣ�ע��name����һ��
    namedWindow(name, WINDOW_FREERATIO);
    imshow(name, img);
}
int main()
{
    // ��ȡͼ��
    Mat img = imread("img.webp");

    // ��ʾԭʼͼ��
    showImg("ԭʼͼ��", img);

    // ����ṹԪ��
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

    // ��ʴ����
    Mat erode;
    cv::erode(img, erode, kernel, Point(-1, -1), 1);
    showImg("��ʴerode", erode);

    // ���Ͳ���
    Mat dilate;
    cv::dilate(img, dilate, kernel, Point(-1, -1), 1);
    showImg("����dilate", dilate);

    // ִ�п��������
    Mat opening;
    cv::morphologyEx(img, opening, MORPH_OPEN, kernel);
    showImg("������opening", opening);

    // ִ�б��������
    Mat closing;
    cv::morphologyEx(img, closing, MORPH_CLOSE, kernel);
    showImg("������closing", closing);

    // �ݶ�����
    Mat gradient;
    cv::morphologyEx(img, gradient, MORPH_GRADIENT, kernel);
    showImg("�ݶ�����gradient", gradient);

    // ʵ����ñ����
    Mat tophat;
    cv::morphologyEx(img, tophat, MORPH_TOPHAT, kernel);
    showImg("��ñtophat", tophat);

    // ʵ�ֺ�ñ����
    Mat blackhat;
    cv::morphologyEx(img, blackhat, MORPH_BLACKHAT, kernel);
    showImg("��ñblackhat", blackhat);

    // �ȴ��û����¼���
    waitKey(0);

    // �������д���
    destroyAllWindows();

    return 0;
}
