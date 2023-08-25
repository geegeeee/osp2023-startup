/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include "writer.h"
#include <cstdlib>
#include <iostream>
/* global variables if needed go here */

int main(int argc, char** argv) {
    /* check command line arguments */
    /* load the file and copy it to the destination */
    if(argc != 3){
        std::cout<<"Usage: ./copier infile outfile" <<std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    std::ifstream infile(inputFile);
    if (!infile.is_open()) {
        std::cout << "Error opening input file: " << inputFile << std::endl;
        return 1;
    }

    writer myWriter(outputFile);
    std::string line;

    while (std::getline(infile, line)) {
        std::cout << "Reading line: " << line << std::endl;
        myWriter.append(line);
    }

    return 0;
}
