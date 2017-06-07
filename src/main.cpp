/*****************************************************************
 * Homework 5 solution to perform sorts based on what params are
 * passed.
 *
 * @author Evan Kiel
 * @version /2017
 *****************************************************************/

/** required includes for vector creation and random generation */
#include "Sorting.h"
#include <random>
#include <algorithm>
#include <iterator>
#include <functional>
#include <sstream>

/** use sort alg depending on argv inputs */
int main(int argc, char ** argv){
	/** get input from command line and convert to int */
	std::istringstream a(argv[1]);
	std::istringstream s(argv[2]);	
	int size, alg;
	a >> alg;
	s >> size;
	
	/* create rand dist and store to vector */
	std::random_device rd;
  	std::mt19937_64 rand_gen(rd());

	std::uniform_int_distribution<int> dis(1, 100000);
	std::vector<int> toSort(size);

	auto gen = std::bind(dis, rand_gen);
	generate(begin(toSort), end(toSort), gen);
	
	/** switch to choose type of sort */
	switch(alg){
		case 1: insertion(toSort);
			break;
		case 2: selection(toSort);
			break;
		case 3: bubble(toSort);
			break;
		case 4: shell(toSort);
			break;
		case 5: heap(toSort);
			break;
		case 6: mergeSort(toSort);
			break;
		case 7: quicksort(toSort);
			break;
	}
}
