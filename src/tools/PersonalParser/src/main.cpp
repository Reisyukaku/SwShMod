#include <string>
#include <cstdio>
#include "Personal.hpp"

int main(int argc, char **argv) {
    if(argc != 4){
        printf("Usage: %s [option] <infile> <outfile>\n", argv[0]);
        return 1;
    }
    
    Personal p = Personal(std::string(argv[2]));
    if(std::string(argv[1]) == "-d")
        p.ExportJson(std::string(argv[3]));
    else if(std::string(argv[1]) == "-c")
        p.ExportBinary(std::string(argv[3]));
    
    return 0;
}