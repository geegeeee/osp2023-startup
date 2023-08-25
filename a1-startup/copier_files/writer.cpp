/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/

#include "writer.h"

/**
 * provide your implementation for the writer functions here
 **/
writer::writer(const std::string& name) {
    out.open(name);
    if (!out.is_open()) {
        std::cout << "Error opening output file: " << name << std::endl;
    }
    pthread_mutex_init(&mutex, nullptr);
}

void writer::run() {}

void writer::append(const std::string& line) {
    if (out.is_open()) {
        out << line << std::endl;
    } else {
        std::cout << "Output file is not open. Cannot write: " << line << std::endl;
    }
    pthread_mutex_unlock(&mutex);
}

writer::~writer() {
    pthread_mutex_destroy(&mutex);
}

