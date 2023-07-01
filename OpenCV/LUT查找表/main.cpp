/*
    ����: btx
    ����: 23-6-29
    ���ܣ���ֵ����LUT���ұ�

    �̶���ֵ��ֵ��
    cv::threshold(inputArray src, //����ͼ�������������ֻ����CV_8U��CV_32F
                  outputArray dst, //���
                  double thresh, //��ֵ
                  double maxval, //���ֵ���Ƿ���Ҫ�ò���ȡ����type
                  int type //��ֵ������
                  )
    
    ����Ӧ��ֵ��ֵ��
    cv::adaptiveThreshold( InputArray src, //����ͼ�������������ֻ���ǵ�ͨ��CV_8U
                           OutputArray dst,//���
                           double maxValue, //Ԥ���������������ֵ
                           int adaptiveMethod,//ָ������Ӧ��ֵ�㷨����ѡ��ADAPTIVE_THRESH_MEAN_C �� ADAPTIVE_THRESH_GAUSSIAN_C����
                           int thresholdType,//ָ����ֵ���͡���ѡ��THRESH_BINARY����THRESH_BINARY_INV����
                           int blockSize,//������С����������������ֵ
                           double C //����C��ʾ���㷨�йصĲ���������һ���Ӿ�ֵ���Ȩ��ֵ��ȡ�ĳ����������Ǹ���
                           )

    LUT���ұ�                
    cv::LUT(inputArray src,   //����ͼ�������������ֻ����CV_8U
            inputArray lut,   //256�����ػҶ�ֵ�Ĳ��ұ���ͨ������srcͨ������ͬ
            outputArray dst   //���ͼ����󣬳ߴ���src��ͬ������������lut��ͬ
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
    Mat img = imread("./img.webp");
    if (img.empty()) {
        printf("����ͼƬ�쳣");
        return 0;
    }
    showImg("��ʾԭʼͼ��", img);
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // �̶���ֵ��ֵ��
    // ���ͼ��
    Mat out_BINARY, out_BINARY_INV,out_TOZERO, out_TOZERO_INV, out_TRUNC;

    // THRESH_BINARY:������ֵ�Ĳ��ֱ���Ϊ255��С�ڲ��ֱ���Ϊ0
    // THRESH_BINARY_INV:������ֵ���ֱ���Ϊ0��С�ڲ��ֱ���Ϊ255
    threshold(gray, out_BINARY, 125, 255, THRESH_BINARY);
    threshold(gray, out_BINARY_INV, 125, 255, THRESH_BINARY_INV);
    showImg("BINARY�任", out_BINARY);
    showImg("BINARY���任", out_BINARY_INV);

    // TOZERO�任:С����ֵ���ֱ���Ϊ0�����ڲ��ֱ��ֲ���
    // TOZERO_INV�任:������ֵ���ֱ���Ϊ0��С�ڲ��ֱ��ֲ��� 
    threshold(gray,out_TOZERO,125,255,THRESH_TOZERO);
    threshold(gray, out_TOZERO_INV, 125, 255, THRESH_TOZERO_INV);
    showImg("TOZERO�任", out_TOZERO);
    showImg("TOZERO���任", out_TOZERO_INV);

    // TRUNC�任:������ֵ���ֱ���Ϊthreshold��С�ڲ��ֱ���ԭ��
    threshold(gray, out_TRUNC, 125, 255, THRESH_TRUNC);
    showImg("TRUNC�任", out_TRUNC);

    // �Ҷ�ͼ���򷨺������η���ֵ��
    // OTSU�㷨��ֱ��ͼ�������壬�м������Բ��ȵ�ֱ��ͼ��Ӧͼ���ֵ��Ч���ȽϺ�
    // ���ڴ����η�����Ѱ�������ֵ�����ĳ��������Ǽ���ֱ��ͼ��󲨷��ڿ���������һ�࣬Ȼ��ͨ��������������ֱ�߾��룬�������ֱ�߾����Ӧ��ֱ��ͼ�Ҷȵȼ���Ϊ�ָ���ֵ
    Mat out_OTSU, out_TRIANGLE;
    Mat img_1 = imread("./test.jpg",0);
    if (img.empty()) {
        printf("����ͼƬ�쳣");
        return 0;
    }
    showImg("��ʾԭʼͼ��img_1", img_1);
    

    threshold(img_1, out_OTSU, 125, 255, THRESH_BINARY | THRESH_OTSU);
    threshold(img_1, out_TRIANGLE, 125, 255, THRESH_BINARY | THRESH_TRIANGLE);
    showImg("���", out_OTSU);
    showImg("�����η�", out_TRIANGLE);
    
    // ����Ӧ��ֵ��
    Mat adapative_mean,adapative_gauss;
    // ��ֵ��
    adaptiveThreshold(img_1, adapative_mean, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 55, 8);
    // ��˹��
    adaptiveThreshold(img_1, adapative_gauss, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY,55, 8);
    showImg("����Ӧ��ֵ��-��ֵ��", adapative_mean);
    showImg("����Ӧ��ֵ��-��˹��", adapative_gauss);

    // LUT���ұ�
    // ������ұ�
    uchar lutFirst[256];
    for (int i = 0; i<256; i++) {
        if (i<=100)
            lutFirst[i] = 0;
        if (i>100 && i<=200)
            lutFirst[i] = 100;
        if (i>200)
            lutFirst[i] = 200;
    }
    Mat lut(1, 256, CV_8UC1, lutFirst);
    Mat LUTout;
    LUT(gray, lut, LUTout);
    showImg("LUT", LUTout);

    waitKey(0);
    destroyAllWindows();
    return 0;
}
