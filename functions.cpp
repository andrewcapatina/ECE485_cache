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
using namespace std;

// Constructor for struct members.
cache_set::cache_set()
{
    mru = 0;            // Initializing struct members.
    valid = 0;
    dirty = 0;
    tag = "";
    cache_line = NULL;

}

// Destructor for struct members.
cache_set::~cache_set(void)
{
    mru = 0;            // Deallocating struct members.
    valid = 0;
    dirty = 0;
    tag = "";
}

cache_class::cache_class(void)
{
    cache_accesses = 0;        
    cache_reads = 0;
    cache_writes = 0;
    cache_hits = 0;
    cache_misses = 0;
    hit_ratio = 0;
    miss_ratio = 0;
    cache_evictions = 0;
    access_type = 0;



}

cache_class::~cache_class(void)
{
    cache_accesses = 0;        
    cache_reads = 0;
    cache_writes = 0;
    cache_hits = 0;
    cache_misses = 0;
    hit_ratio = 0;
    miss_ratio = 0;
    cache_evictions = 0;
    access_type = 0;

}


int cache_class::cache_creator(int sets_per_way_temp, int associativity_temp, int line_size_temp)
{
    sets_per_way = sets_per_way_temp;   // Assigning sets per way.
    associativity = associativity_temp; // Assigning associativity.
    line_size = line_size_temp;

    
    // Initializing cache data structure
    cache_ptr = new cache_set*[sets_per_way];         // Allocating rows of cache
    for(int i = 0; i < sets_per_way; ++i)
        cache_ptr[i] = new cache_set[associativity];

    
    // Initializing line size of cache set.
    for(int i = 0; i < sets_per_way; ++i)
        for(int j = 0; j < associativity; ++j)
            cache_ptr[i][j].cache_line = new int[line_size];

    return 0;
}

int cache_class::cache_deletor(void)
{
    // Add code to deallocate cache structure
   
    // Deallocating cache_line member from cache_set struct. 
    for(int i = 0; i < sets_per_way; ++i)
        for(int j = 0; j < associativity; ++j)
            if(cache_ptr[i][j].cache_line)
                delete cache_ptr[i][j].cache_line;

    // Deallocating entire cache structure
    for(int i = 0; i < sets_per_way; ++i)
    {
          delete [] cache_ptr[i];
    }
    if(cache_ptr)
        delete[] cache_ptr;


    cache_ptr = NULL;

    sets_per_way = 0;
    associativity = 0;
    line_size = 0;
    return 0;
}

int cache_class::parse_request(string cache_request,int index_bits, int tag_bits)
{
    string type_temp;
    string address_temp;

    if(cache_request.empty())   // Checking if paramater empty.
        return 1;

    type_temp.push_back(cache_request[0]); // Getting access type.

    istringstream iss(cache_request);

    do                          // Code taken from online.
    {
        iss >> address_temp;    // Copying address to string.
    } while(iss);




    return 0;
}
