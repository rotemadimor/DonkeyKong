#include "Results.h"
#include <limits>
#include <fstream>


Results Results::loadResults(const std::string& filename) {
	std::ifstream results_file(filename);
	Results results;
	size_t size;
	results_file >> size;
	while (!results_file.eof() && size-- != 0) {
		size_t iteration;
		int result;
		results_file >> iteration >> result;
		results.addResult(iteration, static_cast<ResultValue>(result));
	}
	return results;
}

void Results::saveResults(const std::string& filename) const {
	std::ofstream results_file(filename);
	results_file << results.size();
	for (const auto& result : results) {
		results_file << '\n' << result.first << ' ' << result.second;
	}
	results_file << '\n' << score;
	results_file.close();
}

size_t Results::getNextBombIteration() {
	if (!results.empty() && results.front().second == died) {
		return popResult().first;
	}
	else return std::numeric_limits<size_t>::max(); // a big number we will never reach
}

size_t Results::getWinIteration() const {
	if (!results.empty() && results.front().second == finished) {
		return results.front().first;
	}
	else return std::numeric_limits<size_t>::max(); // a big number we will never reach
}
