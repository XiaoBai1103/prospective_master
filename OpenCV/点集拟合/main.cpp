/*
    ����: btx
    ����: 23-8-12
    ���ܣ��㼯���

    void cv::fitLine(
        cv::InputArray points, // ��ά��������vector
        cv::OutputArray line, // ���ֱ��,Vec4f (2d)��Vec6f (3d)��vector
        int distType, // ��������
        double param, // �������
        double reps, // ����ľ��Ȳ���
        double aeps // �ǶȾ��Ȳ���
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
    Vec4f lines;
    vector<Point2f> point;
    point.push_back(cv::Point(100., 58.));
    point.push_back(cv::Point(150., 70.));
    point.push_back(cv::Point(200., 90.));
    point.push_back(cv::Point(252., 140.));
    point.push_back(cv::Point(300., 220.));
    point.push_back(cv::Point(350., 400.));
    // ����
    double param = 0; // �������
    double rep = 0.01; // ���򾫶�
    double aeps = 0.01; // �ǶȾ���
    //ֱ�����
    fitLine(point, lines, DIST_L1, 0, 0.01, 0.01);
    double k = lines[1] / lines[0]; // ����б��
    cout << "ֱ��б��:" << k << endl;
    cout << "���� x:" << lines[2]<<", y:"<<lines[3] << endl;
    cout << "ֱ�߽���ʽ: y=" << k << "(x-"<<lines[2]<<")+"<<lines[3]<<endl;


    Mat img(500, 500, CV_8UC3, Scalar::all(0));
    RNG& rng = theRNG();// ���������
    while (1) {
        int i, count = rng.uniform(1, 101);
        vector<Point2f> points;
        //���������
        for (i = 0; i < count; i++) {
            Point pt;
            pt.x = rng.uniform(img.cols / 4, img.cols * 3 / 4);
            pt.y = rng.uniform(img.rows / 4, img.rows * 3 / 4);
            points.push_back(pt);
        }
        // ��Χ�㼯������
        vector<Point2f>triangle;// ��������
        double area = minEnclosingTriangle(points, triangle); // ��������С���������
        // ��Χ�㼯Բ��
        Point2f center;
        float radius = 0;
        minEnclosingCircle(points, center, radius); // ��������С���Բ
        // ���ͼ��
        Mat img_triangle = img.clone();
        Mat img_circle = img.clone();
        // ���Ƶ�
        for (i = 0; i < count; i++) {
            circle(img_triangle, points[i], 3, Scalar(255, 255, 255), FILLED, LINE_AA);
            circle(img_circle, points[i], 3, Scalar(255, 255, 255), FILLED, LINE_AA);
        }
        // ����������
        for (i = 0; i < count; i++) {
            if (i == 2) {
                line(img_triangle, triangle[i], triangle[0], Scalar(255, 255, 255), 1, 16);
                break;
            }
            line(img_triangle, triangle[i], triangle[i+1], Scalar(255, 255, 255), 1, 16);
        }
        // ����Բ��
        circle(img_circle, center, cvRound(radius), Scalar(255, 255, 255), 1, LINE_AA);
        // ���
        showImg("������", img_triangle);
        showImg("Բ��", img_circle);
        waitKey(0);
    }

    return 0;
}
