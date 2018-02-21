/*
 * Andrew Capatina
 * David Y
 *
 * 2/16/2018
 *
 * 	This file contains the functions for our cache design.
 *
 */
 
#include "header.h"


// Constructor for struct members.
block::block(void)
{
    mru = 0;            // Initializing struct members.
    valid = 0;
    dirty_bit = 0;
    tag = 0;

}

// Destructor for struct members.
block::~block(void)
{
    mru = 0;            // Deallocating struct members.
    valid = 0;
    dirty_bit = 0;
    tag = 0;
}


cache_class::cache_class(void)
{
    cache_ptr = NULL;           // Initializing class private data members.
    cache_accesses = 0;
    cache_reads = 0;
    cache_writes = 0;
    hit_ratio = 0;
    miss_ratio = 0;
    cache_evictions = 0;
    cache_evictions = 0;
}

cache_class::~cache_class(void)
{
    // Add code to deallocate cache structure
    cache_accesses = 0;        
    cache_reads = 0;
    cache_writes = 0;
    hit_ratio = 0;
    miss_ratio = 0;
    cache_evictions = 0;
    cache_evictions = 0;
}

int cache_class::configure_cache(string parameters)
{
    string sets;
    string associativity;
    string line_size;
    if(parameters.empty())
        return 1;




    return 0;
}
