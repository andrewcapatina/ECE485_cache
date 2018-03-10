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
    tag = 0;
    cache_line = NULL;

}

// Destructor for struct members.
cache_set::~cache_set(void)
{
    mru = 0;            // Deallocating struct members.
    valid = 0;
    dirty = 0;
    tag = 0;
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
    cache_writebacks = 0;
    access_type = 0;
    tag_bits = 0;
    index_bits = 0;
    sets_per_way = 0;
    associativity = 0;
    line_size = 0;

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
    cache_writebacks = 0;
    access_type = 0;
    tag_bits = 0;
    index_bits = 0;
    sets_per_way = 0;
    associativity = 0;
    line_size = 0;

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


    return 0;
}

int cache_class::parse_request(char* cache_request, int byte_b_temp, int index_b_temp, int tag_b_temp)
{
    string binary_address;

    if (cache_request == NULL)
        return 1;

    char type_temp;
    char address_temp[9] = {0};
    char tag_temp[32] = {0};
    char index_temp[32] = {0};
    char byte_temp[32] = {0};

    index_bits = index_b_temp;
    byte_bits = byte_b_temp;
    tag_bits = tag_b_temp;
    
    
    type_temp = cache_request[0];

    int j = 0;


    for(int i = 2; i < 10; ++i)         // Storing address to temp array.
    {
        address_temp[j] = cache_request[i];
        j++;
    }

    for(int i = 0; i < 8; ++i)
    {
        binary_address += hex_to_bin(address_temp[i]);  // Converting address to binary string. 
    }

    j = 0;
    int k = 0;

    for(int i = 0; i < 32; ++i)         // Loop through entire address.
    {
        if(i < tag_bits)    // Get the tag bits in a temp array.          
            tag_temp[i] = binary_address[i];   
        else if(i >= tag_bits && i < tag_bits + index_bits)     // Get the index bits in a temp array.
        {
            index_temp[j] = binary_address[i];  
            j++;
        }
        else if(i >= tag_bits + index_bits && i < 32)   // Get the tag bits in a temp array.
        {
            byte_temp[k] = binary_address[i];
            k++;
        }

    }


    // The variables below hold the current access request.
    tag_request = strtol(tag_temp,NULL,2);      // Convert temp arrays to integers. 
    index_request = strtol(index_temp,NULL,2);
    byte_request = strtol(byte_temp,NULL,2);


    if(type_temp == '0')
        access_type = 0;        // if zero, set to read value.
    else
        access_type = 1;        // if one, set to write value.


    return 0;
}


// Function to return hexadecimal and binary conversions.
const char* cache_class::hex_to_bin(char to_convert)
{

    switch(to_convert)  // Return hex to binary conversion string.
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";

    }

    return NULL;
}


// Function to service a read request.
int cache_class::cache_read_policy()
{
    cache_accesses = cache_accesses+1;  // Increment total accesses.
    cache_reads = cache_reads+1;        // Increment total reads.
    int to_evict = -1;                  // Integer to hold eviction candidate.

    for(int j = 0; j < associativity; ++j)      // Look through entire set
    {
        if(cache_ptr[index_request][j].valid == 1)       // Check only valid indices
        {
            if(cache_ptr[index_request][j].tag == tag_request)  // Checking if tag requested and tag in cache match. If true, this is a cache hit.
            {
                cache_hits = cache_hits + 1;    // Increment hit count.
                //cout << "cache_hit!" << endl;
                //cout << "Stored: " << index_request << " " << j << endl;
                cache_ptr[index_request][to_evict].mru = 1;      // Set MRU bit on access. 

                return 0;
            }

        }
        else if(cache_ptr[index_request][j].valid == 0)       // Check only valid indices
        {

            // If we enter this portion of function that means the tag requested wasn't found.
            cache_misses = cache_misses + 1;    // Increment total cache misses.

            cache_ptr[index_request][j].tag = tag_request;      // Fill cache line with tag requested. 
            cache_ptr[index_request][j].mru = 1;                // Set MRU bit on data being brought into the cache. 
            cache_ptr[index_request][j].valid = 1;                // Setting valid bit on line fill. 


            return 1;

        }

    }
    // If we enter this portion, this means all sets at current index are full.
    // Therefore we need to evict a certain cache line chosen by LRU policy.
    
    to_evict = cache_check_mru();                               // Call function to find eviction candidate.    
    cache_misses = cache_misses +1;                             // Incrementing miss counter.
    cache_evictions = cache_evictions +1;                       // Incrementing evictions counter
    if(cache_ptr[index_request][to_evict].dirty == 1)
        cache_writebacks = cache_writebacks + 1;                // Increment write back counter if data has been modified.

    cache_ptr[index_request][to_evict].tag = tag_request;       // Fill cache line with tag requested. 
    cache_ptr[index_request][to_evict].mru = 1;                 // Set mru bit since line being brought into cache. 
    cache_ptr[index_request][to_evict].valid = 1;               // Setting valid bit on line fill. 


    return 1;
}


// Function to service a write request.
int cache_class::cache_write_policy()
{
    cache_accesses = cache_accesses+1;          // Increment total accesses.
    cache_writes = cache_writes+1;              // Increment total writes.
    int to_evict = -1;                          // Integer to hold eviction candidate.

    for(int j = 0; j < associativity; ++j)
    {
        if(cache_ptr[index_request][j].valid == 0)      // Checking for empty set
        {
            cache_misses = cache_misses+1;              // Increment miss count.

            cache_ptr[index_request][j].valid = 1;      // Set valid bit to one.

            cache_ptr[index_request][j].mru = 1;        // Set valid bit to one.

            cache_ptr[index_request][j].tag = tag_request;  // Setting tag address.
            
            cache_ptr[index_request][j].dirty = 1;      // Set the dirty bit.
            // What to do with byte request????
            
            return 0;

        }
        else if(cache_ptr[index_request][j].valid ==1)
        {
            if(cache_ptr[index_request][j].tag == tag_request) 
            {
                cache_hits = cache_hits + 1;                 // Increment cache hit counter.
                cache_ptr[index_request][j].mru = 1;         // Set mru bit due to access.
                cache_ptr[index_request][j].dirty = 1;       // Setting dirty bit.
                // Does anything need to be done to the cache line???
                
                return 0;
            
            }
        }
    }

    // if no matches found, look for eviction candidate.
    to_evict = cache_check_mru();                       // Calling function to find eviction candidate.
    cache_misses = cache_misses + 1;                    // Increasing miss counter.
    cache_evictions = cache_evictions +1;               // Incrementing evictions counter
    if(cache_ptr[index_request][to_evict].dirty == 1)
        cache_writebacks = cache_writebacks + 1;        // Increment write back counter if data has been modified.

    cache_ptr[index_request][to_evict].tag = tag_request;       // Fill cache line with tag requested. 
    cache_ptr[index_request][to_evict].mru = 1;                 // Set mru bit since line being brought into cache. 
    cache_ptr[index_request][to_evict].valid = 1;               // Setting valid bit on line fill. 
    cache_ptr[index_request][to_evict].dirty = 1;               // Setting dirty bit.




    return 0;
}


// Function to find eviction candidate. Returns the index of where to evict. 
int cache_class::cache_check_mru()
{
    int mru_count = 0;          // Tracks how many MRU bits are equal to one.
    int to_evict = -1;          // Holds eviction candidate index.

    for(int j = 0; j < associativity; ++j) // Check entire cache set
    {
        if(cache_ptr[index_request][j].mru == 1)        // Increment count when mru bits are equal to one.
            ++mru_count;
        else if(cache_ptr[index_request][j].mru == 0)     // Get the index where the mru bit is first zero.
        {
            to_evict = j;        // Eviction candidate index.
            return to_evict;    // Return eviction candidate.
        }
    }
    if(mru_count == associativity)      // If all MRU bits are 1 in the set, do the following:
    {
        to_evict = 0;   // Evict the first cache line in the set.
        for(int j = 0; j < associativity; ++j)   // Reset MRU bits 
            cache_ptr[index_request][j].mru = 0;
    } 


    return to_evict;    // Return eviction candidate index.
}

// Function that displays all access results
int cache_class::display_results()
{
    float hits_temp = cache_hits;             
    float accesses_temp = cache_accesses;        
    hit_ratio = (hits_temp/accesses_temp);      // Calculating hit ratio.
    miss_ratio = 1-hit_ratio;                   // Calculating miss ratio.

    // Displaying all results.
    cout << "Total accesses:    " << cache_accesses << endl;
    cout << "Total reads:       " << cache_reads << endl;
    cout << "Total writes:      " << cache_writes << endl;
    cout << "Total hits:        " << cache_hits << endl;
    cout << "Total misses:      " << cache_misses << endl;
    cout << "Hit ratio:         " << (hit_ratio)*100 << "%" << endl;
    cout << "Miss ratio:        " << (miss_ratio)*100 <<  "%" << endl;
    cout << "Number evictions:  " << cache_evictions << endl;
    cout << "Number writebacks: " << cache_writebacks << endl;

    return 0;
}

// Function to call write or read policy functions.
int cache_class::cache_handler()
{

    if(access_type == 0)
        cache_read_policy();
    else
        cache_write_policy();

    return 0;

}
