/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include <functional>

reader::reader(const std::string& name, writer& mywriter): thewriter(mywriter){
    in.open(name);
    if (!in.is_open()) {
        std::cout << "Error opening input file: " << name << std::endl;
    }
        pthread_mutex_init(&thewriter.mutex, nullptr);
}

void reader::run() {
    std::string line;
    while(std::getline(in,line)){
        pthread_mutex_lock(&thewriter.mutex);
        thewriter.append(line);
        pthread_mutex_unlock(&thewriter.mutex);
    }
    in.close();
}

reader::~reader() {
    pthread_mutex_destroy(&mutex);
}
