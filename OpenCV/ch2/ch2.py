'''
    作者: btx
    日期: 23-5-19
-opencv第二章    
-图像读取
    ·cv2.imread
    IMREAD_COLOR      彩色(default)
    IMREAD_GRAYSCALE  灰度
-图像存储
    ·cv2.imwrite
-ROI(感兴趣区域)
    ·部分截取
        img[:,:]
    ·颜色通道
        b,g,r = cv2.split(img)  *注意颜色顺序
        b = img[:,:,0] (1为g, 2为r)
-边界填充
    ·cv2.copyMakeBorder(img,top,bottom,left,right,boderType)
        BORDER_REPLICATE 复制边缘像素
        BORDER_REFLECT  反射法 像素在两边复制
        BORDER_REFLECT_101 反射法 以最边缘像素为轴
        BORDER_WRAP 外包装
        BORDER_CONSTANT 常数填充
-数值计算
    ·cv2.add
        数值范围0~255 (越界则取自身)
    ·图像融合
        需要大小相同的图像，可以用resize方法
    ·cv2.addWeighted(img1,w1,img2,w2,b) w为权重,b为偏置用于调节亮度
'''
import cv2
import matplotlib.pyplot as plt
import numpy as np
img1 =  cv2.imread("./1.jpg")#颜色通道顺序为BGR
print(img1.shape)
img2 =  cv2.imread("./2.jpg")
print(img2.shape)
img3 = cv2.resize(img2,(1080,1080))
print(img3.shape)


# img3 = cv2.blur(img3,(5,5)) #均值滤波
# img3 = cv2.GaussianBlur(img3,(5,5),0,0) #高斯滤波
# img3 = cv2.medianBlur(img3, 3)#中值滤波
img3 = cv2.bilateralFilter(img3,15,50,50)#双边滤波
cv2.imwrite("./3.jpg",img3)
# img3 = img1 +img2
cv2.imshow('img',img3)
cv2.waitKey(0)