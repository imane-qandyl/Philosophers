#include <pthread.h>
#include <stdio.h>

pthread_mutex_t m_stop; // Declaring a mutex

void* thread_function(void* arg) {
    // Lock the mutex before accessing shared resources
    pthread_mutex_lock(&m_stop);
    
    // Critical section: shared resource access
    printf("Thread is running and has locked the mutex.\n");
    
    // Unlock the mutex after finishing work
    pthread_mutex_unlock(&m_stop);

    return NULL;
}

int main() {
    pthread_t thread;
    
    // Initialize the mutex
    pthread_mutex_init(&m_stop, NULL);
    
    // Create a thread
    pthread_create(&thread, NULL, thread_function, NULL);
    
    // Wait for the thread to finish
    pthread_join(thread, NULL);
    
    // Destroy the mutex
    pthread_mutex_destroy(&m_stop);

    printf("Thread has finished execution.\n");
    return 0;
}
