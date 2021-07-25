#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2\imgproc\types_c.h>
 using namespace cv;
 using namespace std;
 Mat srcImg = imread("u=2046201233,201592934&fm=26&fmt=auto&gp=0.png");
 int main() {
     imshow("原图", srcImg);
     Mat dstImg2 = srcImg.clone();
     Mat dstImg(srcImg.rows, srcImg.cols, CV_8UC3, Scalar::all(0));  //用于绘制轮廓	 
	 Mat tempImg(dstImg.rows, dstImg.cols, CV_8UC3, Scalar::all(0));  //用于绘制凸包
	 cvtColor(srcImg, srcImg, CV_BGR2GRAY);
	 threshold(srcImg, srcImg, 175, 255, CV_THRESH_BINARY); //二值化
		     vector<vector<Point>> contours;
	     vector<Vec4i> hierarcy;
	     findContours(srcImg, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	     vector<vector<Point>> hull(contours.size());
	     for (int i = 0; i < contours.size(); i++)
		 {
		         convexHull(Mat(contours[i]), hull[i], true);     //查找凸包
				 drawContours(dstImg, contours, i, Scalar(255, 255, 255), -1, 8);  //绘制轮廓
				 //drawContours(dstImg, hull, i, Scalar(rand()%255, rand()%255, rand()%255), 2, 8);
			     drawContours(tempImg, hull, i, Scalar(255, 255, 255), -1, 8);
		     }
	     imshow("凸包", tempImg);
	     imshow("轮廓", dstImg);
		 waitKey(0);
		 return 0;
	 }