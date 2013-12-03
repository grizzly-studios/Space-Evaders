#ifndef RANDOM_NUMBER_GENERATOR_HPP
#define	RANDOM_NUMBER_GENERATOR_HPP

#include <random>

namespace gs {

/**
 * A simple pseudo-random number generator.
 *
 * It's really not very good, honest.
 */
class RandomNumberGenerator {
public:
	/**
	 * Constructor.
	 * @param seed The generator seed
	 */
	RandomNumberGenerator(unsigned int seed);
	/**
	 * Generate a pseudo-random integer in a given range (inclusive).
	 * @param min The minimum possible value
	 * @param max The maximum possible value
	 * @return A pseudo-random integer
	 */
	int randomNumberInRange(int min, int max);

private:
	/** Mersenne twister engine */
	std::mt19937 randomEngine;
};

}

#endif	/* RANDOM_NUMBER_GENERATOR_HPP */
