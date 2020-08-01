#include<stdio.h>
#include<iostream>
#include "proj.h"
#include "MeanShiftnew.h"
using namespace std;
int main(int argc,char* argv[])
{
	int stat=stitch(argc,argv);
	if(stat==-1)
		cout<<"cannot stitch images"<<endl;
	else
	{
		meanshift();
		extractveg();
		extract_bar();
		area();

	}
	return 0;

}