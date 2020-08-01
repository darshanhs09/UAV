#include<opencv\cv.h>
#include<opencv\highgui.h>
#include <iostream>
using namespace cv;
using namespace std;
void area()
{
	IplImage *veg = cvLoadImage("bin_veg.jpg");
	 IplImage *bar = cvLoadImage("bin_bar.jpg");
	 IplImage *img = cvLoadImage("filter.jpg");
	long int veg_count=0,bl_count=0,bar_count=0;
	CvScalar s;
	for(int i=0;i<veg->height;i++)
	{
		for(int j=0;j<veg->width;j++)
		{
			s=cvGet2D(veg,i,j);
			 if(s.val[0]==0&&s.val[1]==0&&s.val[2]==0)
			{
				continue;
			}
			 else
				 veg_count++;

		}
	}
	for(int i=0;i<img->height;i++)
	{
		for(int j=0;j<img->width;j++)
		{
			s=cvGet2D(img,i,j);
			 if(s.val[0]==0&&s.val[1]==1&&s.val[2]==2)
			{
				bl_count++;
			}

		}
	}

	for(int i=0;i<bar->height;i++)
	{
		for(int j=0;j<bar->width;j++)
		{
			s=cvGet2D(bar,i,j);
			 if(s.val[1]==0&&s.val[0]==0&&s.val[2]==0)
			{
				continue;
			}
			 else
				 bar_count++;

		}
	}
	long int area=(veg->height*veg->width)-bl_count;
	float perc_veg=(float)veg_count/area;
	float perc_bar=(float)bar_count/area;
	//cout<<"area="<<area<<endl<<"count="<<count<<endl;
	//cout<<bl_count<<endl;
	cout<<"Area="<<area<<"px\n";
	cout<<"Vegetation="<<veg_count<<"px\n";
	cout<<"Barren Land="<<bar_count<<"px\n";
	cout<<"vegetation="<<perc_veg*100<<"%\n";
	cout<<"barren land="<<perc_bar*100<<"%\n";

}