#include "Random.h"

namespace Engine
{

Random::Random() : Random(std::_Random_device())
{
}

Random::Random(uint_least32_t seed)
{
    m_randomNumberGenerator = std::mt19937(seed);

    m_realDistribution = std::uniform_real_distribution<double>();
}

int Random::next()
{
    return next(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

int Random::next(int maxValue)
{
    return next(std::numeric_limits<int>::min(), maxValue);
}

int Random::next(int minValue, int maxValue)
{
    std::uniform_int_distribution<int> distribution(minValue, maxValue);

    return distribution(m_randomNumberGenerator);
}

double Random::nextDouble()
{
    return m_realDistribution(m_randomNumberGenerator);
}

double Random::nextDouble(double minValue, double maxValue)
{
    std::uniform_real_distribution<double> distribution(minValue, maxValue);
    return distribution(m_randomNumberGenerator);
}

}
