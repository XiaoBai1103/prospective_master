/*
    ����: btx
    ����: 23-5-31
-opencv������  ͼ����̬ѧ���� (c����ʵ�֣�
*/
#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
    // ��ȡͼ��
    Mat img = imread("img.webp");

    // ��ʾԭʼͼ��
    imshow("Original Image", img);

    // ����ṹԪ��
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

    // ��ʴ����
    Mat erode;
    cv::erode(img, erode, kernel, Point(-1, -1), 1);
    imshow("erode", erode);

    // ���Ͳ���
    Mat dilate;
    cv::dilate(img, dilate, kernel, Point(-1, -1), 1);
    imshow("dilate", dilate);

    // ִ�п��������
    Mat opening;
    cv::morphologyEx(img, opening, MORPH_OPEN, kernel);
    imshow("opening", opening);

    // ִ�б��������
    Mat closing;
    cv::morphologyEx(img, closing, MORPH_CLOSE, kernel);
    imshow("closing", closing);

    // �ݶ�����
    Mat gradient;
    cv::morphologyEx(img, gradient, MORPH_GRADIENT, kernel);
    imshow("gradient", gradient);

    // ʵ����ñ����
    Mat tophat;
    cv::morphologyEx(img, tophat, MORPH_TOPHAT, kernel);
    imshow("tophat", tophat);

    // ʵ�ֺ�ñ����
    Mat blackhat;
    cv::morphologyEx(img, blackhat, MORPH_BLACKHAT, kernel);
    imshow("blackhat", blackhat);

    // �ȴ��û����¼���
    waitKey(0);

    // �������д���
    destroyAllWindows();

    return 0;
}
