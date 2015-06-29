/* 
 * File:   AliasSampler.h
 * Author: Anastasios Zouzias
 *
 * Created on October 30, 2013, 1:45 PM
 */

#ifndef _ALIASSAMPLER_HPP
#define _ALIASSAMPLER_HPP

#include<stdlib.h>		// malloc
#include<assert.h>		// assert

// Needed for Walker sampling
#define real double
#ifndef uint
#define uint unsigned
#endif


struct aliasStruct
{
  size_t n; /*!< Support of distribution */		
  uint *A; /*!< Auxiliary array */
  uint *B; /*!< Auxiliary array */
  double *Y;  /*!< Auxiliary array */	
};

typedef struct aliasStruct ALIAS;

/**
 * Initialize Alias Sampler
 *
 * Initializes the alias sampling method
 *
 * @param  prob Probability mass (un-normalized)
 * @param  n Support of probability distribution
 * @return ALIAS struct containing info about sampler
 */
ALIAS *createAliasSampler (const double *prob, uint n);

/**
 * Destructor for alias samlping struct
 *
 *
 * @param as Pointer to alias struct
 * @return none
 */
void freeSampler (ALIAS * as);

/**
 * Get i.i.d. samples from finite distribution using alias method
 *
 * Assumes that an ALIAS struct has been initialized
 *
 * @param  samples    (Output) Generated samples over {1,2,... as->n}
 * @param  numSamples (Input)  Number of i.i.d. sampless
 * @param  as (Input) ALIAS struct
 * @return none
 */
void mySampler (unsigned int *samples, uint numSamples, const ALIAS * as);

uint WalkerSample (const double *Y, uint N, const uint * A);

void BuildSampler (double *X, uint N, uint * A, uint * B);


#endif  /* ALIASSAMPLER_H */

