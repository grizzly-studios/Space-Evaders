#include "RandomNumberGenerator.h"

using namespace gs;

RandomNumberGenerator::RandomNumberGenerator(unsigned int seed)
	: randomEngine(seed) {
}

int RandomNumberGenerator::randomNumberInRange(int min, int max) {
	std::uniform_int_distribution<int> distribution(min, max);

	return distribution(randomEngine);
}
