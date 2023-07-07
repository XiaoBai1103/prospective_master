/*
    ����: btx
    ����: 23-7-5
    ���ܣ���Ե���

    - Sobel����
        void cv::Sobel(
            InputArray src, // �����Դͼ��
            OutputArray dst, // ����ı�Եͼ��
            int ddepth, // ���ͼ�����ȣ�ָ�����ͼ����������ͺ����
            int xorder, // Sobel������ˮƽ�����ϵĽ���
            int yorder, // Sobel�����ڴ�ֱ�����ϵĽ���
            int ksize = 3, // Sobel���ӵĴ�С
            double k = 0, // ��ֵ,���ڶԱ�Ե����ǿ����ȥ�������Ĳ���
            int borderType = BORDER_DEFAULT // �߽���䷽ʽ
        );

    - Scharry����
        void cv::Scharr(  
            InputArray src, // �����Դͼ��  
            OutputArray dst, // ����ı�Եͼ��  
            int ddepth, // ���ͼ������  
            int xorder, // Scharr������ˮƽ�����ϵĽ���  
            int yorder, // Scharr�����ڴ�ֱ�����ϵĽ���  
            int ksize = 3, // Scharr���ӵĴ�С  
            double scale = 1, // ��������  
            double delta = 0, // ƫ����  
            int borderType = BORDER_DEFAULT // �߽���䷽ʽ  
        );

    - Laplacian����
        void cv::Laplacian(
            InputArray src, // �����Դͼ��
            OutputArray dst, // ����ı�Եͼ��
            int ddepth, // ���ͼ�����ȣ�ָ�����ͼ����������ͺ����
            int ksize = 3, //������˹���ӵĴ�С��һ��Ϊ����
            double scale = 1, // �������ӣ����ڵ����������ֵ�ķ�Χ
            double delta = 0, //ƫ���������ڵ����������ֵ�����ƫ��
            int borderType = BORDER_DEFAULT //�߽���䷽ʽ
        );

    - Canny�㷨
        void cv::canny(
            InputArray src, // �����Դͼ��
            OutputArray dst, // ����ı�Եͼ��
            double threshold1, // ��һ����ֵ�������ڼ�⵽�ı�Ե�������������ص㡣ͨ������Ϊ��С��ֵ������50��100��
            double threshold2, // �ڶ�����ֵ������ȷ����Щ���ص���ǿ��Ե����Щ������Ե��ͨ������Ϊ�ϴ��ֵ������150��200��
            int apertureSize = 3, // Sobel���ӵĺ˴�С,ͨ������Ϊ3
            bool L2gradient = false // ����ͼ���ݶȷ�ֵ�ı�־
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
    Mat img = imread("./img.webp",0);
    if (img.empty()) {
        printf("����ͼƬ�쳣");
        return 0;
    }
    showImg("ԭͼ", img);
    
    Mat res_x, res_y, res_xy, res, res_Gaussian,res_high, res_low, res_G;
    //goto Sobel;
    //goto Scharr;
    //goto Laplacian; 
    goto Canny;
    /*
        Sobel����
    */
 Sobel:
    // x����һ�ױ�Ե���
    Sobel(img,res_x,CV_16S,1,0,1);
    // ת��Ϊ8 bit unsigned int
    convertScaleAbs(res_x, res_x);
    showImg("Sobel���� X����", res_x);
    // y����һ�ױ�Ե���
    Sobel(img, res_y, CV_16S, 1, 0, 1);
    // ת��Ϊ8 bit unsigned int
    convertScaleAbs(res_y, res_y);
    showImg("Sobel���� Y����", res_y);
    // �ϳ�ͼ��
    res_xy = res_x + res_y;
    showImg("Sobel���� �ϳ�ͼ��", res_xy);
    waitKey(0);
    return 0;
    /*
        Scharr����
    */
 Scharr:
    // x����һ�ױ�Ե���
    Scharr(img, res_x, CV_16S, 1, 0, 1);
    // ת��Ϊ8 bit unsigned int
    convertScaleAbs(res_x, res_x);
    showImg("Scharr���� X����", res_x);
    // y����һ�ױ�Ե���
    Scharr(img, res_y, CV_16S, 1, 0, 1);
    // ת��Ϊ8 bit unsigned int
    convertScaleAbs(res_y, res_y);
    showImg("Scharr���� Y����", res_y);
    // �ϳ�ͼ��
    res_xy = res_x + res_y;
    showImg("Scharr���� �ϳ�ͼ��", res_xy);
    waitKey(0);
    return 0;
    /*
        Laplacian����
    */
Laplacian:
    // δ�˲���ȡ��Ե
    Laplacian(img, res, CV_16S, 3, 1, 0);
    convertScaleAbs(res, res);
    showImg("Laplacian���� δ�˲���ȡ��Ե", res);
    // �˲�����ȡ��Ե
    GaussianBlur(img, res_Gaussian, Size(3,3),5,0);
    Laplacian(res_Gaussian, res, CV_16S, 3, 1, 0);
    convertScaleAbs(res, res);
    showImg("Laplacian���� �˲�����ȡ��Ե", res);
    waitKey(0);
    return 0;
    /*
        Canny��Ե���
    */
Canny:
    // ����ֵ���ͼ���Ե
    Canny(img, res_high,100,200,3);
    showImg("Canny��Ե��� ����ֵ���ͼ���Ե", res_high);
    // С��ֵ���ͼ���Ե
    Canny(img, res_low, 20, 40, 3);
    showImg("Canny��Ե��� С��ֵ���ͼ���Ե", res_low);
    // ��˹ģ������ͼ���Ե
    GaussianBlur(img, res_Gaussian, Size(3, 3), 5, 0);
    Canny(res_Gaussian,res_G, 100, 200, 3);
    showImg("Canny��Ե��� ��˹ģ������ͼ���Ե", res_G);
    waitKey(0);
    return 0;

}
