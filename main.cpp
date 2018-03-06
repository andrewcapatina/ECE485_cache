/*
 *
 * Andrew Capatina
 * David Y
 *
 * 2/16/2018
 *
 * 	This file contains the main application.
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
    int sets = 0;
    int sets_per_way = 0;
    int associativity = 0;
    int line_size = 0;
    int index_bits =0;
    int address_bits = 0;
    string cache_request;

    cache_class cache;       // Cache object creation.

    ifstream fd;                // Initializing file descriptor.

    if(argc != 5)
    {
        cout << "Not enough input arguments." << endl;
        cout << "Must input file from the same directory." << endl;
        return 1;
    }
    sets = atoi(argv[2]);       // Converting arguments to int
    associativity = atoi(argv[3]);
    line_size = atoi(argv[4]);
    index_bits = log2(sets);
    address_bits = 32- index_bits;

    sets_per_way = sets/associativity;  // Getting sets per way.

    cache.cache_creator(sets_per_way,associativity,line_size);       // Cache object creation.

    fd.open(argv[1]);
    //while(getline(fd,cache_request) != -1)

        getline(fd,cache_request);

        cache.parse_request(cache_request, index_bits,address_bits);



    cache.cache_deletor();
    return 0;
}
