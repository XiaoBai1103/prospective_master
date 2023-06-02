/*
    ����: btx
    ����: 23-6-2
    ���ܣ��ڶ��µ�c++ʵ��
    �ʼǺʹ�����ڿγ̣�OpenCV4 C++ ����������Ƶ30������https://www.bilibili.com/video/BV1i54y1m7tw
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
/*
     ͼ�����������
        ��saturate_cast����ֹ���
        ��add  ��
        ��subtract   ��
        ��multiply   ��
        ��divide   ��
     ͼ���λ����
        ��bitwise_and ��
        ��bitwise_or ��
        ��bitwise_not ��
        ��bitwise_xor ���
 */
void arithmetic(Mat& img) {
    //��ɫ�ռ�ת��
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    showImg("�Ҷ�ͼ��", gray);
    //��תͼ��
    Mat img_r = img.clone();
    reverse(img);
    //ͼ��
    Mat rst, rst1, rst2, img1;
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
}
/*
    ��ɫͨ��
*/
void channels(Mat& img) {
    //�½�����
    std::vector<Mat> mv;
    split(img, mv);
    showImg("��ɫ", mv[0]);
    showImg("��ɫ", mv[1]);
    showImg("��ɫ", mv[2]);
    //ͨ���ϲ�
    Mat dst;
    merge(mv, dst);
    showImg("ͨ���ϲ�", dst);
    //ֻ��ʾ��ɫͨ��
    mv[1] = 0;
    mv[2] = 0;
    merge(mv, dst);
    showImg("ͨ���ϲ�-��ɫ", dst);
    //ͨ������
    int from_to[] = { 0,2,1,1,2,0 };
    mixChannels(&img,1, &dst,1,from_to,3);
    showImg("ͨ������", dst);
}
/*
     �������
     -openCV�������ݽṹ��cv::Mat (����һ��ͷ����һ�����ݿ飩
        ��ͷ�������˾�������������Ϣ����С��ͨ���������������͵ȣ�
        �����ݿ������ͼ�����������ص�ֵ
        ��cv::Mat ��һ������Ҫ�����ԣ���ֻ������ȷҪ��ʱ���ڴ��Żᱻ���ơ�
      ʵ���ϣ�������������������� cv::Mat ��ͷ������˶�������ָ��ͬһ�����ݿ�,�����ڴ�й©��
      ����ͨ��clone����ʵ�����

      -cv::Scalar���ݽṹ�������ڵ��ú���ʱ��������ֵ
        ������BGR��˳�򹹽���ɫͼ���ֻ����һ��ֵ�����Ҷ�ͼ��
 */
void matrix(Mat &img) {
 
    //MAT����
    Mat m1, m2, m3, m4;
    //��¡ͼ��
    m1 = img.clone();
    //�հ�ͼ��
    m2 = Mat::zeros(Size(8, 8), CV_8UC1);//8UC1:8λ�޷���(8U)��ͨ����Ϊ1(C1)
    std::cout << m2 << std::endl;
    //��ȡ����Լ�ͨ����
    std::cout << "width:" << m2.cols << "height:" << m2.rows << "channels:" << m2.channels() << std::endl;
    m3 = Mat::zeros(Size(128, 128), CV_8UC3);
    m3 = 127;//ֻ�Ὣ��һ��ͨ����ֵΪ127��
    std::cout << m3 << std::endl;
    m3 = Scalar(127, 200, 80);
    std::cout << m3 << std::endl;
    showImg("���ɵľ���ͼ����ʾЧ��", m3);
    m4 = m3.clone();//��¡�������µĵ�ַ�ռ�
    //ֱ�Ӹ�ֵ������clone�����˻������յ����m3��m4��һ���ģ�ֱ�Ӹ�ֵ�൱��ֻ�������ڴ��ַ���������Ķ�����ͬ
    //m4 = m3; 
    m4 = Scalar(17, 220, 120);
    m3 = Scalar(27, 12, 20);
    showImg("m4", m4);
    showImg("m3", m3);
}
/*
    ROI(����Ȥ����)
    ROI ʵ���Ͼ���һ�� cv::Mat �����������ĸ�ͼ��ָ��ͬһ�����ݻ�������������ͷ��ָ���� ROI ������
    -ʹ�� cv::Rect ʵ��
        ��ǰ��������ΪROI���꣬���������Ͻǵ�λ��
        ������������ΪROI��С
        ��˳������cols��rows

*/
void ROI(Mat &img) {
    //����
    Mat object(100, 100, CV_8UC3, cv::Scalar(0, 0, 255));
    Mat imgROI(img, Rect(30, 30, 100, 100));
    object.copyTo(imgROI);
    showImg("ROI:�� Rect", img);
    //���к��е�ֵ��������
    imgROI = img.clone();
    imgROI = img(Range(img.rows - object.rows, img.rows),
                 Range(img.cols - object.cols, img.cols));
    showImg("ROI:���к��е�ֵ��������", img);
}
int main()
{
    /*
        ��ȡͼ�����Ļ�������
    */
    Mat img = imread("./test1.jpg");
    if (img.empty()) {
        printf("����ͼƬ�쳣");
        return 0;
    }
    showImg("��ʾԭʼͼ��",img);





    //channels(img);//��ɫͨ������
    


    //arithmetic(img);//��������
    //matrix(img);//�������
    ROI(img);




    waitKey(0);
    destroyAllWindows();
    return 0;
}
