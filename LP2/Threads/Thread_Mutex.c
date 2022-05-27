#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>

int mails = 0;
pthread_mutex_t mutex;

void* routine(){
    for (int i = 0; i < 1000000; i++){
        pthread_mutex_lock(&mutex);//read mails
        mails++;//increment
        pthread_mutex_unlock(&mutex);

    }

}

int main(char argc, int *argv){
    pthread_t t1;
    pthread_t t2;

    pthread_mutex_init(&mutex,NULL);

    if(pthread_create(&t1,NULL,(void*)routine,NULL)!= 0){
        return 1;
    };

    if(pthread_create(&t2,NULL,(void*)routine,NULL)!= 0){
        return 2;
    };

    if(pthread_join(t1,NULL)!=0){
        return 3;
    };

    if(pthread_join(t2,NULL)!=0){
        return 4;
    };


    pthread_mutex_destroy(&mutex);
    printf("NUMBER OF MAILS: %d\n", mails);


return 0;

}