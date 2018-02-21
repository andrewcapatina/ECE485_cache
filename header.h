/*
 *
 * Andrew Capatina
 * David Y
 *
 * 2/16/2018
 *
 *	This is a header file for the cache program.
 *
 */


#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct block
{
    bool mru;           // mru bit, keeps track if block was recently accessed.

    bool valid;         // Bit which states if the block has been accessed.

    bool dirty_bit;     // Dirty bit variable. Keeps track if data modified.

    int tag;            // Tag address for cache data

    block();            // Constructor for struct
    ~block();           // Destructor for struct


};

class cache_class {

    public:
        cache_class();          // Constructor function.
        ~cache_class();         // Destructor function.
        int configure_cache(string parameters); // Function to configure the cache 

    private:
        
        block * cache_ptr;      // Pointer to entire cache structure
        int cache_accesses;     // Tracks number of cache accesses.
        int cache_reads;        // Tracks number of cache reads.
        int cache_writes;       // Tracks number of cache writes.
        int cache_hits;         // Tracks number of cache hits.
        int cache_misses;       // Tracks number of cache misses.
        float hit_ratio;        // Records hit ratio.
        float miss_ratio;       // Records miss ratio.
        int cache_evictions;    // Tracks number of evictions.
        int cache_writebacks;   // Tracks number of writebacks.
};





