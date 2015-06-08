//============================================================================
// Name        : REK-CPP.cpp
// Author      : Anastasios Zouzias
// Version     :
// Copyright   : Apache 2.0 License
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include<vector>
#include<stdlib.h>

#include "samplers/AliasSampler.hpp"
using namespace std;

int main(void) {

	int n = 100, numSamples = 500;
	double std = 10.0;
	std::vector<double> prob(n);

	for(int i = 0; i <n ; i++){
		prob[i] = std * drand48();
	}

	AliasSampler alias(prob);
	alias.initSampler();
	std::vector<uint>* samples = alias.sample(numSamples);

	cout << "Checking if random samples are in range [0, " << n - 1 << "]"<<endl;
	for(int i = 0 ; i < samples->size(); i++){
		assert(samples->at(i) >= 0);
		assert(samples->at(i) < n);
	}
	cout << "Success..."<<endl;

	return 0;
}
