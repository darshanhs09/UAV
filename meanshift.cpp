#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"

#include "MeanShiftnew.h"
#include "proj.h"

using namespace cv;



void meanshift()
{
	IplImage *img = cvLoadImage("result.jpg");

	// Mean shift
	int **ilabels = new int *[img->height];
	cout<<"Image filtering in progress"<<endl;
	for(int i=0;i<img->height;i++) ilabels[i] = new int [img->width];
	MeanShift(img, ilabels);
	

	cvReleaseImage(&img);
	cout<<"image filtered"<<endl;

}