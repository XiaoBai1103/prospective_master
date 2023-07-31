/*
    ����: btx
    ����: 23-7-28
    ���ܣ�͹�����

    - Sobel����
        void cv::convexHull(
                InputArray points,  // �����ά�㼯
			    OutputArray hull,  // ͹���㼯���
			    bool clockwise = false,  // ͹������ı�־λ(True��ʾ˳ʱ��)
			    bool returnPoints = true  // �����������(True��ʾ���������,False��ʾ�����������)

        );

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
    Mat img = imread("./img.png");
    if (img.empty()) {
        printf("����ͼƬ�쳣");
        return 0;
    }
    showImg("ԭͼ", img);
    Mat gray, binary;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    threshold(gray,binary,105,255,THRESH_BINARY);
    
    //������
    Mat k = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
    morphologyEx(binary, binary, MORPH_OPEN,k);
    showImg("��ֵ��", binary);
    // ��ȡ����
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, 0, 2, Point());
    for (int n = 0; n < contours.size(); n++) {
        // ͹������
        vector<Point> hull; //�洢͹�����������
        convexHull(contours[n], hull);
        //ͼ�����
        for (int i = 0; i < hull.size(); i++) {
            // �������
            circle(img, hull[i], 4, Scalar(255, 0, 0), 2, 8, 0);
            // �������߻���
            if (i == hull.size() - 1) {
                line(img, hull[i], hull[0], Scalar(255, 0, 0), 2, 8, 0);
                break;
            }
            line(img, hull[i], hull[i+1], Scalar(255, 0, 0), 2, 8, 0);
        }
        

    }
    showImg("���ͼ��", img);
    waitKey(0);
    return 0;
}
