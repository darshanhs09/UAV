#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "proj.h"
using namespace cv;
using namespace std;

void extractveg()
{
    Mat src = imread("filter.jpg");
 
    Mat hsv;
	cout<<"vegetation extraction in progress"<<endl;

    cvtColor(src, hsv, CV_BGR2HSV);

    Mat bw;
    inRange(hsv, Scalar(22,26,60), Scalar(52,150,153), bw);

    vector<vector<Point> > contours;
    findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    Mat dst = Mat::zeros(src.size(), src.type());
    drawContours(dst, contours, -1, Scalar::all(255), CV_FILLED);
	cout<<"vegetation extraction completed"<<endl;
	imwrite("bin_veg.jpg",dst);
	dst &= src;

	imwrite("veg.jpg",dst);	

  

  
}