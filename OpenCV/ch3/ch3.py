'''
    作者: btx
    日期: 23-5-20
-opencv第三章    
-图像阈值
    ·ret,dst = cv2.threshold(src,thresh,maxval,type) 
    src:图像,只允许单通道 dst:输出图像 ret为阈值
    thresh:阈值
    maxval:超过阈值后的赋值
    type类型:
    THRESH_BINARY 超过阈值取maxval，否则取0
    THRESH_BINARY_INV 上条方法的反转
    THRESH_TRUNC  大于阈值的部分设为阈值，否则不变
    THRESH_TOZERO 大于阈值的部分不变，否则取0
    THRESH_TOZERO_INV 上条方法的反转
-图像平滑
    ·均值滤波 cv2.blur(src,ksize) 参数为图像、卷积核大小
        对于一个3x3的均值滤波器，每个中心像素的新值都是它周围3x3邻域内像素的平均值
        滤波器权重为1 
        小的滤波器可以提供较好的平滑效果，但是也会导致图像细节的丢失
    ·方框滤波 cv2.boxFilter(src,ddepth,ksize[,normalize[)
        滤波器权重为1 
        ddepth：输出图像深度
        normalize：是否进行方框卷积核的归一化处理。以(3,3)卷积核为例，若为False,内积后不除以9,容易越界
    ·高斯滤波 cv2.GaussianBlur(src, ksize, sigmaX)
        滤波器中的权重考虑离中心像素的权重，其权重服从高斯分布
        sigmaX表示高斯核在x方向的标准差，sigmaY表示高斯核在y方向的标准差，如果sigmaY为0，则在y方向上也等于sigmaX，这时只需指定一个参数sigmaX即可
    ·中值滤波 cv2.medianBlur(src,ksize)
        一种非线性滤波，对噪声的去除效果非常好，并且不会产生图像模糊的问题

'''
import cv2
import matplotlib.pyplot as plt
import numpy as np

img = cv2.imread('img.jpg')
# 添加高斯噪声
mean = 0
var = 100
sigma = var ** 0.5
gaussian = np.random.normal(mean, sigma, img.shape)
img = img.astype(np.float32)
img += gaussian
img = np.clip(img, 0, 255)
img = img.astype(np.uint8)
cv2.imshow('image with noise', img)

# 均值滤波
blur = cv2.blur(img, (3, 3))
# 方框滤波
box = cv2.boxFilter(img,-1,(3,3),normalize=True)
# 高斯滤波
GaussianBlur = cv2.GaussianBlur(img,(5,5),1)
# 中值滤波
medianBlur = cv2.medianBlur(img,5)

# 输出
res = np.hstack((blur,box,GaussianBlur,medianBlur))
# 缩放
h, w = res.shape[:2]
scale_percent = 50
new_h = int(h * scale_percent / 100)
new_w = int(w * scale_percent / 100)
dim = (new_w, new_h)
res = cv2.resize(res, dim, interpolation=cv2.INTER_AREA)
print(res)
cv2.imshow('blur,box,GaussianBlur,medianBlur',res)
cv2.waitKey(0)
