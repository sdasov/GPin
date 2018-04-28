/*
 * GPin.cpp
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#ifndef GPIN_H_
#define GPIN_H_

class GPin {
public:
	GPin(int pinNuber);
	~GPin();
	bool init();
	bool setPinOut();
	bool setPinIn();
	bool setPinOne();
	bool setPinZero();
	int getPin();
private:
	int pinNumber;
	int fdirection;
	int fvalue;

	char valuePath[64];

	// copy and assignment prohibited
	GPin(const GPin&);
	void operator=(const GPin&);

};

#endif /* GPIN_H_ */
