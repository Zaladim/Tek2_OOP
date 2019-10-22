/*
** EPITECH PROJECT, 2019
** PLAZZA
** File description:
** General timer
*/

#include	"Timer.hpp"

Timer::Timer()
{
	gettimeofday(&_t1, NULL);
	gettimeofday(&_t2, NULL);
}

Timer::~Timer()
{
}

void Timer::reset()
{
  	gettimeofday(&_t1, NULL);
}

double Timer::getElapsedTime()
{
	gettimeofday(&_t2, NULL);
	long seconds = (_t2.tv_sec - _t1.tv_sec);
	long micro = (_t2.tv_usec - _t1.tv_usec);
	return (seconds * 1000 + micro/1000.0);
}
