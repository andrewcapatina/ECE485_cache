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

int main(int argc, char * argv[])
{
    cache_class class_ptr;      // Pointer class.
    string cache_request;

    ifstream fd;                // Initializing file descriptor.

    if(argc != 2)
    {
        cout << "Not enough input arguments." << endl;
        cout << "Must input file from the same directory." << endl;

    }

    fd.open(argv[1]);
    getline(fd,cache_request);

    class_ptr.configure_cache(cache_request);

    return 0;
}
