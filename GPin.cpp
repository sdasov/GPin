/*
 * GPin.cpp
 */

#include "GPin.h"

GPin::GPin(int pinNuber) {
	this->pinNumber=pinNuber;
	fdirection=0;
	fvalue=0;
	sprintf(valuePath,"//sys//class//gpio//gpio%u//value",pinNumber);
}
GPin::~GPin() {
	int funexport;
	char pinNameStr[16];

	setPinIn();

	close(fdirection);
	close(fvalue);

	sprintf(pinNameStr,"%d",pinNumber);
	funexport=open("//sys//class//gpio//unexport",O_WRONLY);
	if(funexport!=0)
	{
		write(funexport,pinNameStr,strlen(pinNameStr));
		close(funexport);
	}
	else {printf("The system does not support sysfs\n");}
}
bool GPin::init()
{
	char dirPath[64];
	char pinNameStr[16];
	int fexport;
	int funexport;

	sprintf(pinNameStr,"%d",pinNumber);
	funexport=open("//sys//class//gpio//unexport",O_WRONLY);
	if(funexport!=0)
	{
		write(funexport,pinNameStr,strlen(pinNameStr));
		close(funexport);
	}
	else {printf("The system does not support sysfs\n");return false;}

	fexport=open("//sys//class//gpio//export",O_WRONLY);
	if(fexport!=0)
	{
		write(funexport,pinNameStr,strlen(pinNameStr));
		close(funexport);

	}
	else {printf("The system does not support sysfs\n");return false;}

	if(fdirection==0)
	{
		sprintf(dirPath,"//sys//class//gpio//gpio%u//direction",pinNumber);
		fdirection=open(dirPath,O_WRONLY);
		if(fdirection==0)return false;
	}

	setPinIn();

	return true;
}
bool GPin::setPinOut()
{
	if(write(fdirection,"out",3)<=0) return false;

	if(fvalue!=0){close(fvalue);fvalue=0;}
	fvalue=open(valuePath,O_WRONLY);
	if(fvalue==0)return false;
	return true;
}
bool GPin::setPinIn()
{
	if(write(fdirection,"in",2)<=0) return false;

	if(fvalue!=0){close(fvalue);fvalue=0;}
	fvalue=open(valuePath,O_RDONLY);
	if(fvalue==0)return false;
	return true;
}
bool GPin::setPinOne()
{
	if(write(fvalue,"1",1)<=0) return false; else return true;
}
bool GPin::setPinZero()
{
	if(write(fvalue,"0",1)<=0) return false; else return true;
}
int GPin::getPin()
{
	char readData[4];
	if(pread(fvalue,readData,1,0)<=0) return -1;
	if(readData[0]=='0')return 0;
	if(readData[0]=='1')return 1;
	return -1;
}
