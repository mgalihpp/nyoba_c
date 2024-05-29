#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int id;
    int grades[5];
    float average;
} Student;

Student* readStudents(FILE *file, int *count);
void calculateAverages(Student *students, int count);
void writeStudents(FILE *file, Student *students, int count);
void sortStudentsByAverage(Student *students, int count);

Student* readStudents(FILE *file, int *count) {
    *count = 0;
    int capacity = 2;
    Student *students = (Student*)malloc(capacity * sizeof(Student));
    if (!students) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    
    while (fscanf(file, "%49s %d %d %d %d %d %d", students[*count].name, &students[*count].id,
                  &students[*count].grades[0], &students[*count].grades[1], &students[*count].grades[2],
                  &students[*count].grades[3], &students[*count].grades[4]) == 7) {
        (*count)++;
        if (*count >= capacity) {
            capacity *= 2;
            students = (Student*)realloc(students, capacity * sizeof(Student));
            if (!students) {
                perror("Failed to reallocate memory");
                exit(EXIT_FAILURE);
            }
        }
    }

    return students;
}

void calculateAverages(Student *students, int count) {
    for (int i = 0; i < count; i++) {
        int sum = 0;
        for (int j = 0; j < 5; j++) {
            sum += students[i].grades[j];
        }
        students[i].average = sum / 5.0;
    }
}

void writeStudents(FILE *file, Student *students, int count) {
    for (int i = 0; i < count; i++) {
        fprintf(file, "Name: %s, ID: %d, Average: %.2f\n", students[i].name, students[i].id, students[i].average);
    }
}

void sortStudentsByAverage(Student *students, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (students[j].average < students[j + 1].average) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

int main() {
    FILE *inputFile = fopen("students.txt", "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    FILE *outputFile = fopen("averages.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    int count;
    Student *students = readStudents(inputFile, &count);
    calculateAverages(students, count);
    sortStudentsByAverage(students, count);
    writeStudents(outputFile, students, count);

    free(students);
    fclose(inputFile);
    fclose(outputFile);

    printf("Processing completed. Check 'averages.txt' for results.\n");

    return 0;
}
