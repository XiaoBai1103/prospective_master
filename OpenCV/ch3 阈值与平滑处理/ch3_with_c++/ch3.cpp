/*
    ����: btx
    ����: 23-6-2
    ���ܣ������� ��ֵ��ƽ������
*/
#include <opencv2/opencv.hpp> 
#include <iostream>
using namespace cv; 
using namespace std;
//��ʾͼ��
void showImg(String name, Mat img) {
    //ͨ��namedWindowʵ�ִ��ڴ�С�ɵ��ڣ�ע��name����һ��
    namedWindow(name, WINDOW_FREERATIO);
    imshow(name, img);
}
int main() {
    Mat img = imread("img.jpg");
    if (img.empty()) {
        cerr << "�޷���ȡͼƬ" << endl;
        return -1;
    }
    // ��Ӹ�˹����
    double mean = 0;
    double var = 100;
    double sigma = sqrt(var);
    Mat gaussian(img.size(), CV_32FC3);
    randn(gaussian, Scalar::all(mean), Scalar::all(sigma));
    img.convertTo(img, CV_32FC3);
    img += gaussian;
    img = max(img, Scalar::all(0));
    img = min(img, Scalar::all(255));
    img.convertTo(img, CV_8UC3);
    showImg("��˹����", img);
    // ��ֵ�˲�
    Mat res;
    res = img.clone();
    Size kernelSize(3, 3);
    boxFilter(img, res, -1, kernelSize);
    showImg("��ֵ�˲�", res);
    // �����˲�
    res = img.clone();
    boxFilter(img, res, -1, kernelSize, Point(-1, -1), true);
    showImg("�����˲�", res);
    // ��˹�˲�
    res = img.clone();
    GaussianBlur(img, res, Size(5, 5), 1);
    showImg("��˹�˲�", res);
    // ��ֵ�˲�
    res = img.clone();
    medianBlur(img, res, 5);
    showImg("��ֵ�˲�", res);

    waitKey(0);
    return 0;
}
