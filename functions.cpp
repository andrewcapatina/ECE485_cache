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
    cout << binary_address << endl;

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

    cout << tag_temp << endl;
    cout << index_temp << endl;
    cout << byte_temp << endl;

    // The variables below hold the current access request.
    tag_request = strtol(tag_temp,NULL,2);      // Convert temp arrays to integers. 
    index_request = strtol(index_temp,NULL,2);
    byte_request = strtol(byte_temp,NULL,2);


    if(type_temp == '0')
        access_type = 0;        // if zero, set to false.
    else
        access_type = 1;        // if one, set to true.


    // Start implementing replacement policies.

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


/*
int cache_class::replacement_policy(int access_type, int memory_address)
{
              
//  still working on high level algorithm. taking longer than expected
	
} */