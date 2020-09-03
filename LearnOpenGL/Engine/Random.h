#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <random>

namespace Engine
{

/*
* 
* ATTENTION:
* This random class was copied and adjusted from https://codereview.stackexchange.com/questions/83603/random-class-in-c
* Made by: Nathan Cooper - https://github.com/NathanLBCooper
* 
*/
class Random
{
public:
	Random();
	Random(uint_least32_t seed);

	int next();
	int next(int maxValue);
	int next(int minValue, int maxValue);

	double nextDouble();
	double nextDouble(double minValue, double maxValue);
private:
	std::mt19937 m_randomNumberGenerator;

	std::uniform_real_distribution<double> m_realDistribution;
};

}

#endif // !__RANDOM_H__
