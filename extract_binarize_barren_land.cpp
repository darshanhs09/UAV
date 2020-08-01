#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "proj.h"

using namespace cv;
using namespace std;

void extract_bar()
{
    Mat src = imread("filter.jpg");
   

    Mat hsv;
    cvtColor(src, hsv, CV_BGR2HSV);
	cout<<"barren land extraction in progress"<<endl;

    Mat bw;
    inRange(hsv, Scalar(11, 62, 114), Scalar(18, 130, 215), bw);

    vector<vector<Point> > contours;
    findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    Mat dst = Mat::zeros(src.size(), src.type());
    drawContours(dst, contours, -1, Scalar::all(255), CV_FILLED);
	cout<<"barren land extraction completed"<<endl;
	imwrite("bin_bar.jpg",dst);
	dst &= src;
	imwrite("bar.jpg",dst);
}