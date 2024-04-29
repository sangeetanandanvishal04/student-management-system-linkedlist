#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TOTAL_PAIRS_REGULAR 50

int main() {

    clock_t start_time_regular = clock();
    
    srand(time(NULL));
    FILE* queueFile;

    for (int i = 0; i < TOTAL_PAIRS_REGULAR; i++) {
        int studentId = rand() % 100 + 1;
        int operationId = rand() % 4;

        time_t currentTime = time(NULL);
        struct tm* timeInfo = localtime(&currentTime);
        int hour = timeInfo->tm_hour;
        int minute = timeInfo->tm_min;
        int second = timeInfo->tm_sec;

        queueFile= fopen("operation_queue.txt", "a+");

        if (operationId == 2) {
            int hostelRoom = rand() % 100;
            printf("Generated: regular %d %d (%d) %02d:%02d:%02d\n", studentId, operationId, hostelRoom,hour, minute, second);
            fprintf(queueFile, "regular %d %d %d %02d:%02d:%02d\n", studentId, operationId , hostelRoom , hour, minute, second);
            fflush(queueFile);
        } 
        else {
            printf("Generated: regular %d %d %02d:%02d:%02d\n", studentId, operationId,hour, minute, second);
            fprintf(queueFile, "regular %d %d %d %02d:%02d:%02d\n", studentId, operationId , 0, hour, minute, second);
            fflush(queueFile);
        }

        sleep(1);
    }

    clock_t end_time_regular = clock();
    double time_taken_regular = (double)(end_time_regular - start_time_regular) / CLOCKS_PER_SEC;
    printf("Time taken by generateRegularRequests: %f seconds\n", time_taken_regular);


    return 0;
}