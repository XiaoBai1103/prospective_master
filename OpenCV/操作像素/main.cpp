/*
    ����: btx
    ����: 23-6-8
    ���ܣ����ز���
*/
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
//��ʾͼ��
void showImg(String name,Mat img) {
    //ͨ��namedWindowʵ�ִ��ڴ�С�ɵ��ڣ�ע��name����һ��
    namedWindow(name, WINDOW_FREERATIO);
    imshow(name, img);
}
//ָ��ɨ�� �Խ���ͼƬɫ��Ϊ��
void colorReduce_pointer(cv::Mat image, int div = 64) {
    int nl = image.rows; // ���� 
    int nc = image.cols * image.channels();// ÿ�е�Ԫ������ 
    //isContinuous �����������������
    //Ҳ���Լ���еĳ��ȣ��ֽ������롰�еĸ������������ء����ֽ����Ƿ���� 
    //image.step == image.cols * image.elemSize();
    /*
        �ڴ����У��������ͼ���������ģ���ô��û���������أ�
        �������ǿ��Խ�ͼ������һά�����������������Լ򻯳�
        ���ʵ�֣����ұ��⴦���������ʱ�Ķ��⿪������ˣ�����
        ��ͼ������������������õ���ͼ������������nc��Ȼ����
        ������Ϊ1���������ǾͿ���ʹ�õ���ѭ�������������������顣
    */
    if (image.isContinuous()) {       
        // û���������� 
        nc = nc * nl;
        nl = 1; // �����ڳ���һ��һά���� 
    }
    //����һ�����Ķ����Ʊ�ʾ�����λ��λ��
    //static_cast��һ��ǿ������ת��������
    int n = static_cast<int>(
        log(static_cast<double>(div)) / log(2.0) + 0.5);
    // ������ȡ����ֵ������ 
    uchar mask = 0xFF << n; //����nλ ��� div=16, ��ô mask= 0xF0 
    uchar div2 = div >> 1; // div2 = div/2 
    // ��������ͼ�����ѭ��ִֻ��һ�� 
    for (int j = 0; j < nl; j++) {
        uchar* data = image.ptr<uchar>(j);//��ȡ��j�е���ʼ��ַ
        for (int i = 0; i < nc; i++) {
            *data &= mask; //���ݺ��������������
            *data++ += div2; //��ָ��data��ָ�������ֵ����div2������ָ��data�ƶ�����һ������
        } // һ��ͼ��Ĵ������ 
    }
}
void colorReduce_iter(cv::Mat image, int div = 64) {
// div ������ 2 ����
    int n = static_cast<int>(
        log(static_cast<double>(div)) / log(2.0) + 0.5);
    // ������ȡ����ֵ������
    uchar mask = 0xFF << n; // ��� div=16, mask=0xF0 
    uchar div2 = div >> 1; // div2 = div/2 
    // ������
    cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>();
    // ɨ��ȫ������
    for (; it != itend; ++it) {
        (*it)[0] &= mask;
        (*it)[0] += div2;
        (*it)[1] &= mask;
        (*it)[1] += div2;
        (*it)[2] &= mask;
        (*it)[2] += div2;
    }
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
    //colorReduce_pointer(img);
    colorReduce_iter(img);
    
    showImg("����ɫ�ʺ��ͼ��", img);
 
    waitKey(0);
    destroyAllWindows();
    return 0;
}
