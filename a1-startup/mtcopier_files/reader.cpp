/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include "writer.h"

/**
 * implement the functions needed for this class
 **/
std::ifstream reader::in;
pthread_cond_t readerCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t readerMutex = PTHREAD_MUTEX_INITIALIZER;
extern pthread_mutex_t writerMutex;
extern pthread_cond_t writerCond;

void reader::init(const std::string& name) {
    in.open(name);
    if (!in.is_open()) {
        std::cout << "Error opening input file: " << name << std::endl;
    }
}

void* reader::runner(void* arg) {
    reader* r = static_cast<reader*>(arg); 

    std::string line;
    while (std::getline(r->in, line)) {
        pthread_mutex_lock(&writerMutex);
        writer::append(line);
        pthread_cond_signal(&writerCond); // Signal writer's condition variable
        pthread_mutex_unlock(&writerMutex);

        pthread_mutex_lock(&readerMutex);
        pthread_cond_signal(&readerCond); // Signal reader's condition variable
        pthread_mutex_unlock(&readerMutex);
    }
    pthread_exit(nullptr); 
}

void reader::run() {
    pthread_t threads[NUM_READERS];  

    for (int i = 0; i < NUM_READERS; ++i) {
        pthread_create(&threads[i], nullptr, &runner, this);
    }

    for (int i = 0; i < NUM_READERS; ++i) {
        pthread_join(threads[i], nullptr);
    }
    
    pthread_cond_broadcast(&readerCond); // Signal the condition variable for termination

    in.close();  
}