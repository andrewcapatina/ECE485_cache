/*
 *
 * Andrew Capatina
 * David Y
 *
 * 2/16/2018
 *
 * 	This file contains the main application.
 * 	Takes input from STDIN, creates cache paramaters, reads from text file,
 * 	and calls handler function to run policies.
 *
 */
#include "header.h"
using namespace std;

// argv[1] = file input.
// argv[2] = Number of sets.
// argv[3] = Associativity.
// argv[4] = cache line size.
int main(int argc, char * argv[])
{
    int sets_per_way = 0;
    int associativity = 0;
    int line_size = 0;
    int index_bits =0;
    int address_bits = 0;
    int byte_bits = 0;
    string cache_request;
    char cache_request_char[20];

    cache_class cache;          // Cache object creation.

    ifstream fd;                // Initializing file descriptor.

    if(argc != 5)               // Prompt if not enough input args.
    {
        cout << "Not enough input arguments." << endl;
        cout << "Must input file from the same directory." << endl;
        return 1;
    }
    sets_per_way = atoi(argv[2]);               // Getting number of total sets.
    associativity = atoi(argv[3]);              // Getting set associativity size.

    line_size = atoi(argv[4]);                  // Getting line size.

    index_bits = log2(sets_per_way);            // Getting number of index bits.
    byte_bits = log2(line_size);                // Getting number of byte bits.
    address_bits = 32- byte_bits - index_bits;  // Getting number of address bits.

    cache.cache_creator(sets_per_way,associativity,line_size);       // Cache object creation.

    fd.open(argv[1]);                           // Opening file to be read.
    while(getline(fd,cache_request))            // Retrieve each line until done.
    {
        strcpy(cache_request_char,cache_request.c_str());       // Converting string to char.
        cache.parse_request(cache_request_char, byte_bits, index_bits, address_bits);   // Calling function to parse request.
        cache.cache_handler();                                  // Calling function to handle the request.

    }
    cache.display_results();            // Call to display all results.
    cache.cache_deletor();              // Call to de allocate.

    return 0;
}
