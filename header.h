/*
 *
 * Andrew Capatina
 * David Yakovlev
 *
 * 2/16/2018
 *
 *	This is a header file for the cache program.
 *
 */


#include <string.h>
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

    int tag;            // Tag address for cache data

    int *cache_line;    // Array for line size in bytes.

    cache_set();        // Constructor for struct
    ~cache_set();       // Destructor for struct

};

class cache_class {

    public:
        // Constructor with no arguments.
        cache_class(); 
        // Destructor function.
        ~cache_class();         
        // Function to create data structure.
        int cache_creator(int sets_per_way_temp,int associativity_temp, int line_size); 
        // Function to delete data structure.
        int cache_deletor();

        // Function prototype with string paramater.
        int parse_request(char* cache_request,int byte_b_temp, int index_b_temp, int tag_b_temp);

        // Function prototype with char paramater.
        const char* hex_to_bin(char to_convert);

        // Function prototype with integer return.
        int cache_write_policy();

        // Function prototype with integer return.
        int cache_read_policy();

        // Function prototype with integer return.
        int cache_check_mru();

        // Function prototype with integer return.
        int display_results();

        // Function prototype with integer return.
        int cache_handler();


    private:
        cache_set ** cache_ptr;       // Pointer to entire cache structure

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
        int byte_bits;          // Records nymber of byte select bits.
        int sets_per_way;       // Records number of sets per way.
        int associativity;      // Records number of ways.
        int line_size;          // Records line size.

        int tag_request;        // Tracks current tag request.
        int index_request;      // Tracks current index request.
        int byte_request;       // Tracks current byte request.

};
