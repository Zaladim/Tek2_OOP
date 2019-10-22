/*
** EPITECH PROJECT, 2019
** PLAZZA
** File description:
** General Timer
*/

#ifndef	__TIMER_HH__
#define	__TIMER_HH__

#include <iostream>
#include <string>
#include <sys/time.h>

class Timer {
	public:
		Timer();
		~Timer();
		double getElapsedTime();
		void reset();
	private:
		double _elapsedTime;
		timeval _t1;
		timeval _t2;
};

#endif
