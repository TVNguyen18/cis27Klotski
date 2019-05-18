/**
* Program Name: KlotSki Game
* Discussion  : Declaration File --
*				  time.h
* Written by  : Anh Tran
* Date        : 2019/05/17
*/

#ifndef TIME_H
#define TIME_H

#include "include.h"

class Timer
{
public:
	Timer() : beg_(clock_::now()) {}
	void reset() { beg_ = clock_::now(); }
	double elapsed() const {
		return std::chrono::duration_cast<second_>
			(clock_::now() - beg_).count();
	}

private:
	typedef std::chrono::high_resolution_clock clock_;
	typedef std::chrono::duration<double, std::ratio<1> > second_;
	std::chrono::time_point<clock_> beg_;
};

#endif