/*
    ����: btx
    ����: 23-8-4
    ����: ֱ�߼��

    - ֱ�߼�⺯��
       cv::HoughLines( 
            InputArray image, // ����ͼ�� 8λ�ĵ�ͨ��������ͼ��
            OutputArray lines, // ���ֱ�� ÿһ�����ɾ�������Ԫ�ص�ʸ����r,t����ʾ��rΪ������ԭ��ľ��룬tΪ����������ת�Ƕ�
            double rho, // ������Ϊ��λ�ľ��뾫��
            double theta, // �Ի���Ϊ��λ�ĽǶȾ���
            int threshold,// �ۼ�ƽ�����ֵ����
            double srn = 0, // ���ڶ�߶ȵĻ���任�����ǵ���������rho�ĳ�������
            double stn = 0, // ���ڶ�߶ȵĻ���任�����ǵ��ĸ�����theta�ĳ�������
            double min_theta = 0, // ���ڱ�׼�Ͷ�߶Ȼ���任������ߵ���С�Ƕ�
            double max_theta = CV_PI // ���ڱ�׼�Ͷ�߶Ȼ���任������ߵ����Ƕ�
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
// ���ֱ��
void drawLine(Mat& img, vector<Vec2f> lines, double rows, double cols, Scalar scalar, int n) {
    Point pt1, pt2;
    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0]; // ֱ�߾�������ԭ��ľ���
        float theta = lines[i][1]; // ֱ�߹�����ԭ��Ĵ�����x��н�
        double a = cos(theta); // �н�����
        double b = sin(theta); // �н�����
        double x0 = a * rho, y0 = b * rho; // ֱ���������ԭ��Ĵ��ߵĽ���
        double length = max(rows, cols); // ͼ��߿�����ֵ
        // ����ֱ���ϵ�һ��
        // cv::line���Ƶ��߶� Ϊ�˱�֤����ֱ�߹ᴩͼ�� ��Ҫ����ͼ�����ֵ
        // ���ظ�������ӽ�������ֵ(��������)
        pt1.x = cvRound(x0 + length * (-b));
        pt1.y = cvRound(y0 + length * (a));
        // ����ֱ���ϵ���һ��
        pt2.x = cvRound(x0 - length * (-b));
        pt2.y = cvRound(y0 - length * (a));
        // ����ֱ��
        line(img, pt1, pt2, scalar, n);
    }
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
    Mat gray,binary,edge;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    Canny(gray, edge, 80,180,3,false);
    showImg("��Ե���", edge);
    // ֱ�߼��
    vector<Vec2f> lines1, lines2;
    HoughLines(edge, lines1, 1, CV_PI / 180, 140, 0, 0);
    HoughLines(edge, lines2, 1, CV_PI / 180, 180, 0, 0);
    //ֱ�߻���
    Mat img1, img2;
    img.copyTo(img1);
    img.copyTo(img2);
    drawLine(img1,lines1,edge.rows,edge.cols,Scalar(0,0,255),2);
    drawLine(img2,lines2, edge.rows, edge.cols, Scalar(0, 0, 255), 2);
    showImg("���ͼ��:��ֵΪ140", img1);
    showImg("���ͼ��:��ֵΪ180", img2);
    waitKey(0);
    return 0;
}
