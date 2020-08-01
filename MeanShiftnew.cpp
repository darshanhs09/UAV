#include "MeanShiftnew.h"
RAList::RAList( void )
{
	label			= -1;
	next			= 0;
}

RAList::~RAList( void )
{}

int RAList::Insert(RAList *entry)
{
	if(!next)
	{
		next		= entry;
		entry->next = 0;
		return 0;
	}
	if(next->label > entry->label)
	{
		entry->next	= next;
		next		= entry;
		return 0;
	}
	exists	= 0;
	cur		= next;
	while(cur)
	{
		if(entry->label == cur->label)
		{
			exists = 1;
			break;
		}
		else if((!(cur->next))||(cur->next->label > entry->label))
		{
			entry->next	= cur->next;
			cur->next	= entry;
			break;
		}
		cur = cur->next;
	}
	return (int)(exists);
}
void MeanShift(const IplImage* img, int **labels)
{
	DECLARE_TIMING(timer);
	START_TIMING(timer);
	int level = 1;
	double color_radius2=color_radius*color_radius;
	int minRegion = 50;
    IplImage *result = cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
	cvCvtColor(img, result, CV_RGB2Lab);
   for(int i=0;i<img->height;i++) 
		for(int j=0;j<img->width;j++)
		{
			int ic = i;
			int jc = j;
			int icOld, jcOld;
			float LOld, UOld, VOld;
			float L = (float)((uchar *)(result->imageData + i*img->widthStep))[j*result->nChannels + 0];
			float U = (float)((uchar *)(result->imageData + i*img->widthStep))[j*result->nChannels + 1];
			float V = (float)((uchar *)(result->imageData + i*img->widthStep))[j*result->nChannels + 2];
			L = L*100/255;
			U = U-128;
			V = V-128;
			double shift = 5;
			for (int iters=0;shift > 3 && iters < 100;iters++) 
			{
				icOld = ic;
				jcOld = jc;
				LOld = L;
				UOld = U;
				VOld = V;
				float mi = 0;
				float mj = 0;
				float mL = 0;
				float mU = 0;
				float mV = 0;
				int num=0;
				int i2from = max(0,i-spatial_radius), i2to = min(img->height, i+spatial_radius+1);
				int j2from = max(0,j-spatial_radius), j2to = min(img->width, j+spatial_radius+1);
				for (int i2=i2from; i2 < i2to;i2++) {
					for (int j2=j2from; j2 < j2to; j2++) {
						float L2 = (float)((uchar *)(result->imageData + i2*img->widthStep))[j2*result->nChannels + 0],
							U2 = (float)((uchar *)(result->imageData + i2*img->widthStep))[j2*result->nChannels + 1],
							V2 = (float)((uchar *)(result->imageData + i2*img->widthStep))[j2*result->nChannels + 2];
						L2 = L2*100/255;
						U2 = U2-128;
						V2 = V2-128;
						double dL = L2 - L;
						double dU = U2 - U;
						double dV = V2 - V;
						if (dL*dL+dU*dU+dV*dV <= color_radius2) {
							mi += i2;
							mj += j2;
							mL += L2;
							mU += U2;
							mV += V2;
							num++;
						}
					}
				}
				float num_ = 1.f/num;
				L = mL*num_;
				U = mU*num_;
				V = mV*num_;
				ic = (int) (mi*num_+0.5);
				jc = (int) (mj*num_+0.5);
				int di = ic-icOld;
				int dj = jc-jcOld;
				double dL = L-LOld;
				double dU = U-UOld;
				double dV = V-VOld;
				shift = di*di+dj*dj+dL*dL+dU*dU+dV*dV; 
			}
			L = L*255/100;
			U = U+128;
			V = V+128;	
			((uchar *)(result->imageData + i*img->widthStep))[j*result->nChannels + 0] = (uchar)L;
			((uchar *)(result->imageData + i*img->widthStep))[j*result->nChannels + 1] = (uchar)U;
			((uchar *)(result->imageData + i*img->widthStep))[j*result->nChannels + 2] = (uchar)V;
		}
		IplImage *tobeshow = cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
		cvCvtColor(result, tobeshow, CV_Lab2RGB);
		//cvNamedWindow("MeanShift",CV_WINDOW_AUTOSIZE);
	
		//cvShowImage("meanshift",tobeshow);

		cvSaveImage("filter.jpg", tobeshow);
		//cvWaitKey();
		cvReleaseImage(&tobeshow);
			//cvDestroyWindow("MeanShift");
		STOP_TIMING(timer);
		std::cout<<"Mean Shift(ms):"<<GET_TIMING(timer)<<std::endl;
		cvReleaseImage(&result);
		
  
}