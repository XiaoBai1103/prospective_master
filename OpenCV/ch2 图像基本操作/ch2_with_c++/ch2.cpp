/*
    ����: btx
    ����: 23-6-1
    ���ܣ��ڶ��µ�c++ʵ��
*/
#include <opencv2/opencv.hpp>
using namespace cv;
//��ʾͼ��
void showImg(String name,Mat img) {
    //ͨ��namedWindowʵ�ִ��ڴ�С�ɵ��ڣ�ע��name����һ��
    namedWindow(name, WINDOW_FREERATIO);
    imshow(name, img);
}
/*
    ���ض�д�������Է�תͼ��Ϊ��
    rows: ��
    cols: ��
    ͼƬ�ı�ʾ�����Ͻ�Ϊԭ�㣬������Ϊcols��������Ϊrows
    Mat���ͱ�������ʱ�±�˳��Ϊ���к���
    img.ptr<uchar>(y)[x]; ��ʾ��y-1�У�x-1�����ص�ָ��
*/
void reverse(Mat &image)
{
    int w = image.cols;
    int h = image.rows;
    int dims = image.channels();
    for (int row = 0; row < h; row++) {
        uchar* current_row = image.ptr<uchar>(row);
        for (int col = 0; col < w; col++) {
            if (dims == 1) { // �Ҷ�ͼ��
                int pv = *current_row;
                *current_row++ = 255 - pv;
            }
            if (dims == 3) { // ��ɫͼ��
                *current_row++ = 255 - *current_row;
                *current_row++ = 255 - *current_row;
                *current_row++ = 255 - *current_row;
            }
        }
    }
    showImg("��תͼ��", image);
}

int main()
{
    /*
        ͼ�����Ļ�������
    */
    // ��ȡͼ��
    Mat img = imread("./test1.jpg");
    if (img.empty()) {
        printf("����ͼƬ�쳣");
        return 0;
    }
    // ��ʾԭʼͼ��
    showImg("��ʾԭʼͼ��",img);
    //��ɫ�ռ�ת��
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    showImg("�Ҷ�ͼ��",gray);
    /*
        ͼ�����������
        ��saturate_cast����ֹ���
        ��add  ��
        ��subtract   ��
        ��multiply   ��
        ��divide   ��
    */
    //��תͼ��
    Mat img_r = img.clone(); 
    reverse(img);
    //ͼ��
    Mat rst,rst1,rst2,img1;
    img1 = imread("./test2.jpg");
    add(img1, img, rst);
    showImg("ͼ��ӷ�����", rst);
    //���üӼ��˳���������
    Mat black = Mat::zeros(img.size(), img.type());
    black = Scalar(80, 80, 80);
    add(rst, black, rst1);
    showImg("��������", rst1);
    subtract(rst, black, rst2);
    showImg("��������", rst2);
    /*
        �������    
    */
    //MAT����
    Mat m1, m2, m3, m4;
    //��¡ͼ��
    m1 = img.clone();
    //�հ�ͼ��
    m2 = Mat::zeros(Size(8, 8), CV_8UC1);//8UC1:8λ�޷��ţ�ͨ����Ϊ1
    std::cout << m2 << std::endl;
    //��ȡ����Լ�ͨ����
    std::cout << "width:" << m2.cols << "height:" << m2.rows << "channels:" << m2.channels() << std::endl;
    m3 = Mat::zeros(Size(128, 128), CV_8UC3);
    m3 = 127;//ֻ�Ὣ��һ��ͨ����ֵΪ127��
    std::cout << m3 << std::endl;
    m3 = Scalar(127,200,80);
    std::cout << m3 << std::endl;
    showImg("���ɵľ���ͼ����ʾЧ��", m3);
    m4 = m3.clone();//��¡�������µĵ�ַ�ռ�
    //m4 = m3; //���յ����m3��m4��һ���ģ�ֱ�Ӹ�ֵ�൱��ֻ�������ڴ��ַ���������Ķ�����ͬ
    m4 = Scalar(17, 220, 120);
    m3 = Scalar(27, 12, 20);
    showImg("m4", m4);
    showImg("m3", m3);

    // �ȴ��û����¼���
    waitKey(0);

    // �������д���
    destroyAllWindows();

    return 0;
}
