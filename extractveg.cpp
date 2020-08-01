#include <opencv\cv.h>
#include<iostream>
#include <opencv\cxcore.h>
#include <opencv\highgui.h>
#include "proj.h"
using namespace cv;
void extractveg()
{
	    IplImage *img1 = cvLoadImage("filter.jpg");
       /* cvNamedWindow("Image1:",1);
        cvShowImage("Image1:",img1);*/
		IplImage* img=cvCreateImage(cvSize(img1->width,img1->height),IPL_DEPTH_32F,3);
		CvScalar s;
		cout<<"vegetation extraction in progress"<<endl;
		for(int i=0;i<img1->height;i++)
		{
			for(int j=0;j<img1->width;j++)
			{
		       s=cvGet2D(img1,i,j); // get the (i,j) pixel value
		//printf("B=%f, G=%f, R=%f\n",s.val[0],s.val[1],s.val[2]);
			   if(s.val[1]<=s.val[0]||s.val[1]<=s.val[2])
			   {
					s.val[0]=0;
					s.val[1]=0;
					s.val[2]=0;
					cvSet2D(img,i,j,s); // set the (i,j) pixel value
			   }
			  /* else
			   {
				    s.val[0]=255;
					s.val[1]=255;
					s.val[2]=255;*/
					cvSet2D(img,i,j,s);
			  // }
			
			}

		}
		cvSaveImage("veg.jpg",img);
		 /*cvNamedWindow("Image2:",2);
        cvShowImage("Image2:",img);
		cvWaitKey();
        cvDestroyWindow("Image1:");*/

        cvReleaseImage(&img1);
        cvReleaseImage(&img);
}