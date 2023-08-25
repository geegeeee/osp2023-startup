/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "writer.h"
#include <mutex>
#include <pthread.h>

#define NUM_WRITERS 2

std::ofstream writer::out;  
std::deque<std::string> writer::queue;  
pthread_mutex_t lock;
pthread_cond_t writerCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t writerMutex = PTHREAD_MUTEX_INITIALIZER;

extern pthread_mutex_t readerMutex;
extern pthread_cond_t readerCond;

void writer::init(const std::string& name) {
    out.open(name);  
    if (!out.is_open()) {
        std::cout << "Error opening output file: " << name << std::endl;
    }
}

void* writer::runner(void* arg) {
    while (true) {
        std::string line;
        {
            pthread_mutex_lock(&lock);  
            while(queue.empty()){   // Use a while loop to wait for the condition
                pthread_cond_wait(&writerCond,&lock); // Wait for the condition to be signaled
            }
            line = queue.front();
            queue.pop_front();
            pthread_mutex_unlock(&lock);  
        }
        out << line << std::endl;
    }

    pthread_exit(nullptr);  
}

void writer::run() {
    pthread_t threads[NUM_WRITERS];  

    // Create threads
    for (int i = 0; i < NUM_WRITERS; ++i) {
        pthread_create(&threads[i], nullptr, &runner, nullptr);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_WRITERS; ++i) {
        pthread_join(threads[i], nullptr);
    }

    out.close();  
}

void writer::append(const std::string& line) {
    pthread_mutex_lock(&lock); 
    queue.push_back(line);
    pthread_mutex_unlock(&lock);  
    
    pthread_mutex_lock(&readerMutex);
    pthread_cond_signal(&readerCond);
    pthread_mutex_unlock(&readerMutex);
}