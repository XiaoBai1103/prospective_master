/*
    ����: btx
    ����: 23-7-11
    ���ܣ���ͨ�����
����ͨ������connectivity
        cv::8��ʹ��8���򣬼����������ĸ����غ����ǵĶԽ��߷�������ء�
        cv::4��ʹ��4���򣬼����������ĸ����ء�
        cv::8U��ʹ��8���򣬷����޷����������͵ı�ǩ��
        cv::4U��ʹ��4���򣬷����޷����������͵ı�ǩ��
��ֻ�ָ���ͨ��ĺ���
    int cv::connectedComponents()��
          cv::InputArray image, // ����Ķ�ֵͼ��ͨ����һ����ά��uint8���;���
          cv::OutArray   labels, // �������ͨ�����ǩͼ��Ҳ��һ����ά��uint8���;���������ͼ�������ͬ�ĳߴ硣ÿ�����صı�ǩֵ��ʾ��������������ͨ������
          int            connectivity = 8,  // ��ͨ������
          int            Itype = CV_32S // ���ͼ����������,������CV_32S��CV_16U
    ��
    ����ֵ:��ͨ�������

    int cv::connectedComponentsWithStats(
          cv::InputArray image, // ����Ķ�ֵͼ��ͨ����һ����ά��uint8���;���
          cv::OutArray   labels, // �������ͨ�����ǩͼ�� 
          OutputArray    stats, //����ṹ�����飬ÿ���ṹ���ʾһ����ͨ�����ͳ����Ϣ������������ܳ������ζȡ���ֱ�ȡ�ˮƽ�ȵ�
          OutputArray    centroids, //������飬��ʾÿ����ͨ�������������
          int            connectivity = 8,  // ��ͨ������
          int            Itype = CV_32S // ���ͼ����������
          int            ccltype = CV_32S // ��ͨ����ͳ����Ϣ���������ͣ������� CV_32S��Ĭ��ֵ���� CV_64F
     )

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
    Mat imgOrigin = imread("./img.png");
    if (imgOrigin.empty()) {
        printf("����ͼƬ�쳣");
        return 0;
    }
    showImg("ԭͼ", imgOrigin);
    // ��ֵ��
    Mat img;
    cvtColor(imgOrigin, img, COLOR_BGR2GRAY);
    threshold(img, img, 50, 255, THRESH_BINARY);
    showImg("��ֵ��", img);
    // ���������ɫ
    // cv::RNG α�����������,���������������ɫֵ
    RNG rng(10086);
    Mat out;
    // ֻ�ָ���ͨ��ĺ���
    int number = connectedComponents(img, out, 8, CV_16U);
    // ��ɫ��
    vector<Vec3b> colors;
    for (int i = 0; i < number; i++) {
        Vec3b vec3 = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        colors.push_back(vec3);
    }
    // �����ͨ��
    Mat res = Mat::zeros(img.size(), imgOrigin.type());
    int w = res.cols;
    int h = res.rows;
    for (int row = 0; row < h; row++) {
        for (int col = 0; col < w; col++) {
            int label = out.at<uint16_t>(row, col);
            // ������ɫ����
            if (label == 0) {
                continue;
            }
            res.at<Vec3b>(row, col) = colors[label];
        }
    }
    showImg("��Ǻ��ͼ��", res);

   // ͳ����ͨ����Ϣ
    Mat stats, centroids;
    number = connectedComponentsWithStats(img, out, stats, centroids, 8, CV_16U);
    vector<Vec3b> colors_new;
    for (int i = 0; i < number; i++) {
        Vec3b vec3 = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        colors_new.push_back(vec3);
    }
    for (int i = 1; i < number; i++) {
        // ����λ��
        int center_x = centroids.at<double>(i, 0);
        int center_y = centroids.at<double>(i, 1);
        // ���α߿�
        int x = stats.at<int>(i, CC_STAT_LEFT);
        int y = stats.at<int>(i, CC_STAT_TOP);
        int w = stats.at<int>(i, CC_STAT_WIDTH);
        int h = stats.at<int>(i, CC_STAT_HEIGHT);
        int area = stats.at<int>(i, CC_STAT_AREA);
        // ����λ�û���
        circle(imgOrigin, Point(center_x, center_y), 2, Scalar(0, 255, 0), 2, 8, 0);
        // ��Ӿ���
        Rect rect(x, y, w, h);
        rectangle(imgOrigin, rect, colors_new[i], 1, 8, 0);
        putText(imgOrigin, format("%d", i), Point(center_x, center_y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
        cout << "number:" << i << ",area:" << area << endl;
    }
    showImg("��Ǻ��ͼ��_ͳ����ͨ����Ϣ", imgOrigin);
    waitKey(0);
    destroyAllWindows();
    return 0;
}
