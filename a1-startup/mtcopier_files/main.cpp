/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include "writer.h"
#include <cstdlib>
/**
 * these need to be global variables as you'll need handle cleaning them up in
 *cleanup which will automatically be called on program exit
 **/
reader* readers;
writer* writers;

pthread_cond_t readerCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t readerMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t writerCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t writerMutex = PTHREAD_MUTEX_INITIALIZER;

void cleanup() {
    /**
     * perform any cleanup you need to do here for global pointers
     **/
    delete[] readers;
    delete[] writers;
    pthread_cond_destroy(&writerCond);
    pthread_cond_destroy(&readerCond);
    pthread_mutex_destroy(&readerMutex);
    pthread_mutex_destroy(&writerMutex);
}

int main(int argc, char** argv) {

    bool enableTiming = false;
    if (argc == 4 && std::string(argv[3]) == "-t") {
        enableTiming = true;
    }

    clock_t start, end;
    double duration;

    if (enableTiming) {
        start = clock();

    atexit(cleanup);
    /**
     * check command line arguments
     **/
    if(argc != 3){
        std::cerr <<"Usage: "<<argv[0]<<"<input_file><output_file>"<<std::endl;
        return EXIT_FAILURE;
    }
    /**
     * process command line arguments
     **/
    std::string input_file(argv[1]);
    std::string output_file(argv[2]);
    /**
     * initiliaze the reader and writer classes
     **/
    readers = new reader[NUM_READERS];
    writers = new writer [NUM_WRITERS];
    /**
     * initialize the running of each thread. Note you just call run() on each
     * object here, you'll call pthread_create itself in the run function.
     **/
    for (int i=0; i< NUM_READERS; i++){
        readers[i].init(input_file);
        readers[i].run();
    }
    for (int i=0; i< NUM_WRITERS; i++){
        writers[i].init(output_file);
        writers[i].run();
    }
    /**
     *
     * have loop here waiting for the threads to bomplete. Please see
     * section on avoiding busy waiting on the assignment specification to see
     * what need to be done here
      **/
    std::cout << "Program completed successfully!" << std::endl;
    
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken for distinct part: " << duration << " seconds" << std::endl;
    }
    
    return EXIT_SUCCESS;
}
