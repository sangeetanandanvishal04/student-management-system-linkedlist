#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CACHE_SIZE 5
struct Member* cache_head = NULL;
#define MAX_NAME_LENGTH 30
#define MAX_HOSTEL_LENGTH 20
#define MAX_STUDENTS 100

struct Member {
    int id;
    char firstname[20];
    char lastname[20];
    char hostel[20];
    char course[10];
    int room_num;
    char dob[15];
    int year_of_study;

    struct Member* next;

}*head;

char hostels[5][5] = {"BH-1", "BH-2", "BH-3", "BH-4", "BH-5"};
char courses[5][10] = {"BTech", "MTech", "MS", "PhD", "MBA"};

void First_names(char firstNames[][MAX_NAME_LENGTH], int count) {
    FILE *file = fopen("first_names.txt", "r");
    if (file == NULL) {
        printf("Error opening file: first_names.txt\n");
      
    }

    for (int i = 0; i < count; i++) {
        fscanf(file, "%s", firstNames[i]);
    }

    fclose(file);
}

void Last_names(char lastNames[][MAX_NAME_LENGTH], int count) {
    FILE *file = fopen("last_names.txt", "r");
    if (file == NULL) {
        printf("Error opening file: last_names.txt\n");
        
    }

    for (int i = 0; i < count; i++) {
        fscanf(file, "%s", lastNames[i]);
    }

    fclose(file);
}

struct Member* generate_random_student() {
    struct Member* member = (struct Member*)malloc(sizeof(struct Member));
    if (member == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    int new_id;
    do {
        new_id = rand() % 100 + 1;
        struct Member* temp = head;
        while (temp != NULL) {
            if (temp->id == new_id) {
                new_id = 0;
                break;
            }
            temp = temp->next;
        }
    } while (new_id == 0);

    char first_names[20][MAX_NAME_LENGTH];
    char last_names[20][MAX_NAME_LENGTH];

    First_names(first_names,20);
    Last_names(last_names,20);

    member->id = new_id;
    strcpy(member->firstname, first_names[rand() % 20]);
    strcpy(member->lastname, last_names[rand() % 20]);
    strcpy(member->hostel, hostels[rand() % 5]);
    strcpy(member->course, courses[rand() % 5]);
    member->room_num = rand() % 100;
    sprintf(member->dob, "%02d-%02d-%04d", rand() % 29 + 1, rand() % 11 + 1, rand() % 10 + 1990);
    member->year_of_study = rand() % 10 + 1988;

    return member;
}

void insertInCache(struct Member* newMember) {

    if (cache_head == NULL) {
        cache_head = newMember;
    } 
    else {
        newMember->next = cache_head;
        cache_head = newMember;
    }
}

struct Member* searchInCache(int id) {

    struct Member* current = cache_head;
    while (current != NULL) {
        if (current->id == id)
            return current;
        current = current->next;
    }
    return NULL;
}

void removeFromCache(int id) {

    struct Member* current = cache_head;
    struct Member* prev = NULL;

    while (current != NULL) {
        if (current->id == id) {
            if (prev == NULL) {
                cache_head = current->next;
            } 
            else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void clearCache() {
    struct Member* current = cache_head;
    while (current != NULL) {
        struct Member* temp = current;
        current = current->next;
        free(temp);
    }
    cache_head = NULL;
}

void registerMember() {

    FILE* file = fopen("disk.txt", "w+");
    if (file == NULL) {
        printf("Error opening file");
        return;
    } 
    else {
        printf("File created/opened successfully\n");
    }
    
    head = NULL;
    clearCache();

    for (int i = 1; i <= 100; i++) {
        struct Member* member = generate_random_student();

        member->next = head;
        head = member;
        insertInCache(member);

        fprintf(file, "%d\t%s\t%s\t%s\t%s\t%d\t%s\t%d\n", member->id, member->firstname, member->lastname,
                member->hostel, member->course, member->room_num, member->dob, member->year_of_study);
    }
    
    fclose(file);

    printf("Student data has been generated and saved to disk.txt.\n");
}

void searchMember(int targetID) {
    
    struct Member* cachedMember = searchInCache(targetID);
    if (cachedMember != NULL) {
        printf("Member found in cache!\n");
        printf("ID: %d\n", cachedMember->id);
        printf("FirstName: %s\n", cachedMember->firstname);
        printf("LastName: %s\n", cachedMember->lastname);
        printf("Hostel: %s\n", cachedMember->hostel);
        printf("Course: %s\n", cachedMember->course);
        printf("Room Number: %d\n", cachedMember->room_num);
        printf("Date of Birth: %s\n", cachedMember->dob);
        printf("Year of Study: %d\n", cachedMember->year_of_study);
        return;
    } 
    else {
    struct Member* current = head;
    while (current != NULL) {
        if (current->id == targetID) {
            printf("Member found!\n");
            printf("ID: %d\n", current->id);
            printf("FirstName: %s\n", current->firstname);
            printf("LastName: %s\n", current->lastname);
            printf("Hostel: %s\n", current->hostel);
            printf("Course: %s\n", current->course);
            printf("Room Number: %d\n", current->room_num);
            printf("Date of Birth: %s\n", current->dob);
            printf("Year of Study: %d\n", current->year_of_study);
            return;
        }
        current = current->next;
      }
    }
    printf("Member with ID %d not found.\n", targetID);
}

void updateMember(int targetID,int new_room_num) {

    struct Member* cachedMember = searchInCache(targetID);
    if (cachedMember != NULL) {
        cachedMember->room_num = new_room_num;
    } 
    else {
        struct Member* current = head;
        while (current != NULL) {
        if (current->id == targetID) {
    
            current->room_num = new_room_num;

            FILE* file = fopen("disk.txt", "w");
            if (file == NULL) {
                printf("Error opening file");
                return;
            }

            struct Member* temp = head;
            while (temp != NULL) {
                fprintf(file, "%d\t%s\t%s\t%s\t%s\t%d\t%s\t%d\n", temp->id, temp->firstname, temp->lastname,
                        temp->hostel, temp->course, temp->room_num, temp->dob, temp->year_of_study);
                temp = temp->next;
            }

            fclose(file);

            printf("Member information updated!\n");
            return;
        }
        current = current->next;
      }
    }
    struct Member* current = head;
    while (current != NULL) {
        if (current->id == targetID) {
            current->room_num = cachedMember->room_num;

                FILE* file = fopen("disk.txt" , "w");
            if (file == NULL) {
            printf("Error opening file");
            return;
        }
        struct Member* current = head;
        while (current != NULL) {
        fprintf(file, "%d\t%s\t%s\t%s\t%s\t%d\t%s\t%d\n", current->id, current->firstname, current->lastname,
                current->hostel, current->course, current->room_num, current->dob, current->year_of_study);
        current = current->next;
        }

            fclose(file);

            printf("Member information updated!\n");
            return;
        }
        current = current->next;
    }

    printf("Member with ID %d not found.\n", targetID);
}

void deleteMember(int targetID) {

    struct Member* current = head;
    struct Member* prev = NULL;

    removeFromCache(targetID);

    while (current != NULL) {
        if (current->id == targetID) {
            if (prev == NULL) {
                head = current->next;
            } 
            else {
                prev->next = current->next;
            }

            FILE* file = fopen("disk.txt", "w");
            if (file == NULL) {
                printf("Error opening file");
                return;
            }

            struct Member* temp = head;
            while (temp != NULL) {
                fprintf(file, "%d\t%s\t%s\t%s\t%s\t%d\t%s\t%d\n", temp->id, temp->firstname, temp->lastname,
                        temp->hostel, temp->course, temp->room_num, temp->dob, temp->year_of_study);
                temp = temp->next;
            }

            fclose(file); 
            free(current);
            printf("Member with ID %d deleted.\n", targetID);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Member with ID %d not found.\n", targetID);
}

void server(int a,int b,int c){

    int op_id = a;
    int student_ID = b;
    int student_room_num = c;

    while (1) {
        if (op_id == 0) {
            registerMember();
            return;
        } 
        else if (op_id == 1) {
            searchMember(student_ID);
            return;
        } 
        else if (op_id == 2) {
            updateMember(student_ID,student_room_num);
            return;
        } 
        else if (op_id == 3) {
            deleteMember(student_ID);
            return;
        } 
    } 
}

int main() {

    FILE *queueFile = fopen("operation_queue.txt", "r+");
    if (queueFile == NULL) {
        printf("Error opening file");
        return 1;
    }
    else {
        printf("File created/opened successfully\n");
    }

    printf("Starting a function called 'server'........\n");
    
    char operation[10];
    int studentId, operationId,updated_room_num, hours, minutes, seconds;

    int requestsProcessed = 0;
    clock_t start = clock(); 

    while (fscanf(queueFile, "%s %d %d %d %d:%d:%d", operation, &studentId, &operationId , &updated_room_num, &hours, &minutes, &seconds) == 7) {
        server(operationId , studentId , updated_room_num);
        requestsProcessed++;
    }    
    
    clearCache();

    clock_t end = clock();
    double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;

    fclose(queueFile);
     
    if (timeTaken > 0) {
        double requestsPerSecond = requestsProcessed / timeTaken;
        printf("Processed %d requests in %.2f seconds.\n", requestsProcessed, timeTaken);
        printf("Requests per second: %.2f\n", requestsPerSecond);
    } else {
        printf("No requests processed or time taken was too short to measure.\n");
    }

    return 0;
}