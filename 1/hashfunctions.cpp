#include "hashfunctions.h"
#include <iostream>


uint32_t adler32( std::istream &file ){
    uint32_t s1 = 1;
    uint32_t s2 = 0;
    unsigned char ch;
    while( file.read((char *)(&ch), sizeof(unsigned char)) ){
        s1 = ( s1 + (ch) ) % 65521;
        s2 = ( s2 + s1 ) % 65521;
    }
    return ( s2 << 16 ) | s1;
}

uint64_t sum64( std::istream &file ){
    uint64_t sum = 0, end = 0, result = 0;
    unsigned char ch;
    while (file.read((char *) (&ch), sizeof(uint64_t))){
        result = (result << 8) | ch;
        end++;
        if(end == 8){
            sum += result;
            result = 0;
            end = 0;
        }
    }
    sum += result;
    return sum;
}
