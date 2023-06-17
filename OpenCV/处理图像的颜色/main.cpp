/*
    ����: btx
    ����: 23-6-9
    ���ܣ�����ͼ�����ɫ
*/
#include <opencv2/opencv.hpp>
#include "ColorDetector.h"
#include "grabCut.h"
using namespace cv;
using namespace std;

Mat colorDet(Mat img) {
    // ����ColorDetector��������Ŀ����ɫΪ��ɫ
    ColorDetector cd(150);
    cd.setTargetColor(80, 160, 200);

    // ����ͼ���е�ÿ�����ز��������Ŀ����ɫ������
    cv::Mat result(img.rows, img.cols, CV_8U);
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            if (cd(img.at<cv::Vec3b>(i, j))) {
                result.at<unsigned char>(i, j) = 255;
            }
            else {
                result.at<unsigned char>(i, j) = 0;
            }
        }
    }
    return result;
}
int main()
{
    /*
        ��ȡͼ�����Ļ�������
    */
    Mat img = imread("./img.webp");
    if (img.empty()) {
        printf("����ͼƬ�쳣");
        return 0;
    }
    showImg("��ʾԭʼͼ��",img);

 
  
    Mat result;
    //�ò������ģʽ�Ƚ���ɫ
    //result = colorDet(img);
    // GrabCut �㷨�ָ�ͼ��
    result = grabCut(img);
    showImg("���ͼ��", result);
    waitKey(0);
    destroyAllWindows();
    return 0;
}
