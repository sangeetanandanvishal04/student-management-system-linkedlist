#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TOTAL_PAIRS_RANDOM 20

int main() {

    clock_t start_time_random = clock();
    FILE* queueFile;
    srand(time(NULL));

    for (int i = 0; i < TOTAL_PAIRS_RANDOM; i++) {
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
            printf("Generated: random %d %d (%d) %02d:%02d:%02d\n", studentId, operationId, hostelRoom,hour, minute, second);
            fprintf(queueFile, "random %d %d %d %02d:%02d:%02d\n", studentId, operationId , hostelRoom , hour, minute, second);
            fflush(queueFile);
        } 
        else {
            printf("Generated: random %d %d %02d:%02d:%02d\n", studentId, operationId, hour, minute, second);
            fprintf(queueFile, "random %d %d %d %02d:%02d:%02d\n", studentId, operationId , 0, hour, minute, second);
            fflush(queueFile);
        }

        int waitTime = rand() % 3 + 1;
        sleep(waitTime);
    }

    clock_t end_time_random = clock();
    double time_taken_random = (double)(end_time_random - start_time_random) / CLOCKS_PER_SEC;
    printf("Time taken by generateRandomRequests: %f seconds\n", time_taken_random);

    return 0;
}