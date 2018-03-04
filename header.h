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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <sstream>

using namespace std;

struct cache_set
{
    bool mru;           // mru bit, keeps track if block was recently accessed.

    bool valid;         // Bit which states if the block has been accessed.

    bool dirty;         // Dirty bit variable. Keeps track if data modified.

    string tag;         // Tag address for cache data

    int *cache_line;      // Array for line size in bytes.

    cache_set();              // Constructor for struct
    ~cache_set();             // Destructor for struct

    // Constructor with arguments.
    //set(int tag_bits);

};

class cache_class {

    public:
        // Constructor with integer arguments.
        cache_class(int sets_per_way_temp,int associativity_temp, int line_size); 

        // Destructor function.
        ~cache_class();         


        cache_set ** cache_ptr;       // Pointer to entire cache structure

        int sets_per_way;       // Records number of sets per way.
        int associativity;      // Records number of ways.
        int line_size;          // Records line size.

        int tag_bits;           // Records number of tag bits.
        int index_bits;         // Records number of index bits.
        int byte_bits;          // Records number of byte select bits.


    private:
        
};

class cache_helper {

    public:
        // Constructor
        cache_helper();
        // Destructor
        ~cache_helper();

        // Function prototype with string paramater.
        int parse_request(string cache_request);


        string address;

    private:
        int cache_accesses;     // Tracks number of cache accesses.
        int cache_reads;        // Tracks number of cache reads.
        int cache_writes;       // Tracks number of cache writes.
        int cache_hits;         // Tracks number of cache hits.
        int cache_misses;       // Tracks number of cache misses.
        float hit_ratio;        // Records hit ratio.
        float miss_ratio;       // Records miss ratio.
        int cache_evictions;    // Tracks number of evictions.
        int cache_writebacks;   // Tracks number of writebacks.
        bool access_type;       // Records access type for current requests.
        int tag_bits;           // Records number of tag bits.
        int index_bits;         // Records number of index bits.
        int byte_bits;          // Records number of byte select bits.

        

};



