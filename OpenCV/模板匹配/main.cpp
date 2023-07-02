/*
    ����: btx
    ����: 23-7-1
    ���ܣ�ģ��ƥ��

    cv::matchTemplate��
          cv::InputArray image, //��Ҫƥ���ͼ��
          cv::InputArray temp,  //ģ��ͼ��
          cv::OutArray  result, //�洢�ļ���õ��Ľ��
          int           method,  //ƥ��ķ���
          cv::InputArray mask    //ƥ��ģ������룬Ĭ�ϲ�����
    ��
        
    ģ��ƥ�䷽����־��
    ��־����        ���   ����
    TM_SQDIFF        0    ����ƥ�䷨

    TM_SQDIFF_NORMED 1    ��һ����ƥ�䷨

    TM_CCORR         2    �����ƥ�䷽��

    TM_CCORR_NORMED  3    ��һ���Ļ����ƥ�䷨

    TM_CCOEFF        4    ���ϵ��ƥ�䷨

    TM_CCOEFF_NORMED 5    ��һ�����ϵ��ƥ�䷽��



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
    // ԭͼ
    Mat img = imread("./img.webp");
    if (img.empty()) {
        printf("����ͼƬ�쳣");
        return 0;
    }
    showImg("ԭͼ", img);
    // Ŀ��ͼ��
    Mat img_template = imread("./template.png");
    if (img.empty()) {
        printf("����ͼƬ�쳣");
        return 0;
    }
    showImg("ģ��ͼ��", img_template);
    // ģ��ƥ��
    Mat res;
    matchTemplate(img, img_template, res, TM_CCOEFF_NORMED);
    showImg("ƥ��ϵ������", res);
    // �ҵ�������ص�
    double maxVal, minVal;
    Point maxLoc, minLoc;
    minMaxLoc(res,&minVal,&maxVal,&minLoc,& maxLoc);
    // �����ֵλ�û��ƾ���
    rectangle(img, Point(maxLoc.x, maxLoc.y), Point(maxLoc.x + img_template.cols, maxLoc.y + img_template.rows), Scalar(0, 0, 255), 2);

    showImg("���", img);
    waitKey(0);
    destroyAllWindows();
    return 0;
}
