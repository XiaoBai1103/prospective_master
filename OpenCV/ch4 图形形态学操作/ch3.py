'''
    作者: btx
    日期: 23-5-29
-opencv第四章  图形形态学操作  
-腐蚀操作
·cv2.erode(img,kernel,iterations)
    腐蚀是一种用于图像处理的基本形态学操作，它可以使图像中的前景对象（通常是白色）变小，并且通常会消除噪声
    结构元素的每个像素都与图像中对应位置的像素进行比较，如果结构元素中的所有像素都与图像中的像素匹配，则该
    像素保持不变，否则该像素被置为0
    iterations是迭代次数

-膨胀操作
·cv2.dilate(img,kernel,iterations)
它可以使图像中的前景对象（通常是白色）变大，并且可以填补前景对象之间的空隙。

-开运算&闭运算
·cv2.morphologyEx()是OpenCV中的一个通用形态学操作函数，可以进行开运算、闭运算、梯度计算等多种操作
·开运算（先腐蚀再膨胀）
    ·cv2.morphologyEx(img, cv2.MORPH_OPEN, kernel)
    开运算的作用是去除小物体并平滑较大物体的边界。它的实现方式是先进行腐蚀操作，再进行膨胀操作。这样可以消除小物体，
    并使较大物体的边界更加平滑。开运算通常用于去噪、分离物体以及减少细节。
·闭运算（先膨胀再腐蚀）
    ·cv2.morphologyEx(img, cv2.MORPH_CLOSE, kernel)
    闭运算的作用是填充小孔并平滑物体的边界。它的实现方式是先进行膨胀操作，再进行腐蚀操作。这样可以填充小孔，并使物体
    的边界更加平滑。闭运算通常用于连接物体、填充空洞以及平滑边界。

-梯度计算
    ·cv2.morphologyEx(img, cv2.MORPH_GRADIENT, kernel)
    计算方法：膨胀-腐蚀
    梯度运算可以通过计算膨胀和腐蚀操作之间的差异来检测图像中的边缘。梯度运算常常被用于图像分割、目标检测、轮廓提取等领域。

-礼帽与黑帽
·礼帽：原始输入-开运算结果
    ·cv2.morphologyEx(img, cv2.MORPH_TOPHAT, kernel)
    这个操作可以用来突出图像中的亮点或者细节信息，例如图像中的微小颗粒或者血管。
·黑帽：闭运算-原始输入
    ·cv2.morphologyEx(img, cv2.MORPH_BLACKHAT, kernel)
    这个操作可以用来突出图像中的暗点或者阴影区域，例如图像中的皱纹或者缝隙。
'''
import cv2
import numpy as np
img = cv2.imread('img.webp')
cv2.imshow('Original Image', img)
# 定义结构元素
kernel = np.ones((3,3),np.uint8)


# 腐蚀操作
erode = cv2.erode(img,kernel,iterations = 1)
cv2.imshow('erode', erode)
# 膨胀操作
dilate = cv2.dilate(img,kernel,iterations = 1)
cv2.imshow('dilate', dilate)
# 执行开运算操作
opening = cv2.morphologyEx(img, cv2.MORPH_OPEN, kernel)
cv2.imshow('opening', opening)
# 执行闭运算操作
closing = cv2.morphologyEx(img, cv2.MORPH_CLOSE, kernel)
cv2.imshow('closing', closing)


# 梯度运算
gradient = cv2.morphologyEx(img, cv2.MORPH_GRADIENT, kernel)
cv2.imshow('gradient', gradient)
# 实现礼帽操作
tophat = cv2.morphologyEx(img, cv2.MORPH_TOPHAT, kernel)
cv2.imshow('tophat', tophat)
# 实现黑帽操作
blackhat = cv2.morphologyEx(img, cv2.MORPH_BLACKHAT, kernel)
cv2.imshow('blackhat', blackhat)
# 显示结果
cv2.waitKey(0)
cv2.destroyAllWindows()