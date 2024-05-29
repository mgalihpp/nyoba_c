#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[50];
    int id;
    int grades[5];
    float average;
} Student;

Student *readStudents(FILE *file, int *count);
void calculateAverages(Student *students, int count);
void writeStudents(FILE *file, Student *students, int count);
void sortStudentsByAverage(Student *students, int count);
void addStudent(Student **students, int *count, int *capacity);
void printStudents(Student *students, int count);
void deleteStudent(Student *students, int *count, int id);
void updateStudent(Student *students, int count, int id);
void searchStudent(Student *students, int count, char *name);
void searchStudentById(Student *students, int count, int id);

Student *readStudents(FILE *file, int *count)
{
    *count = 0;
    int capacity = 2;
    Student *students = (Student *)malloc(capacity * sizeof(Student));
    if (!students)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%49s %d %d %d %d %d %d", students[*count].name, &students[*count].id,
                  &students[*count].grades[0], &students[*count].grades[1], &students[*count].grades[2],
                  &students[*count].grades[3], &students[*count].grades[4]) == 7)
    {
        (*count)++;
        if (*count >= capacity)
        {
            capacity *= 2;
            students = (Student *)realloc(students, capacity * sizeof(Student));
            if (!students)
            {
                perror("Failed to reallocate memory");
                exit(EXIT_FAILURE);
            }
        }
    }

    return students;
}

void calculateAverages(Student *students, int count)
{
    for (int i = 0; i < count; i++)
    {
        int sum = 0;
        for (int j = 0; j < 5; j++)
        {
            sum += students[i].grades[j];
        }
        students[i].average = sum / 5.0;
    }
}

void writeStudents(FILE *file, Student *students, int count)
{
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "Name: %s, ID: %d, Average: %.2f\n", students[i].name, students[i].id, students[i].average);
    }
}

void sortStudentsByAverage(Student *students, int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (students[j].average < students[j + 1].average)
            {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

void addStudent(Student **students, int *count, int *capacity)
{
    if (*count >= *capacity)
    {
        *capacity *= 2;
        *students = (Student *)realloc(*students, *capacity * sizeof(Student));
        if (!*students)
        {
            perror("Failed to reallocate memory");
            exit(EXIT_FAILURE);
        }
    }

    printf("Enter student name: ");
    scanf("%49s", (*students)[*count].name);
    printf("Enter student ID: ");
    scanf("%d", &(*students)[*count].id);
    printf("Enter 5 grades: ");
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &(*students)[*count].grades[i]);
    }

    (*count)++;
}

void printStudents(Student *students, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("Name: %s, ID: %d, Grades: %d %d %d %d %d, Avarages: %.2f\n",
               students[i].name, students[i].id, students[i].grades[0], students[i].grades[1],
               students[i].grades[2], students[i].grades[3], students[i].grades[4], students[i].average);
    }
}

void deleteStudent(Student *students, int *count, int id)
{
    int found = 0;
    for (int i = 0; i < *count; i++)
    {
        if (students[i].id == id)
        {
            found = 1;
            for (int j = i; j < *count - 1; j++)
            {
                students[j] = students[j + 1];
            }
            (*count)--;
            break;
        }
    }

    if (!found)
    {
        printf("Student with ID %d not found.\n", id);
    }
    else
    {
        printf("Student with ID %d deleted successfully.\n", id);
    }
}

void updateStudent(Student *students, int count, int id)
{
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            found = 1;
            printf("Enter new grades for %s (5 grades): ", students[i].name);
            for (int j = 0; j < 5; j++)
            {
                scanf("%d", &students[i].grades[j]);
            }
            calculateAverages(students, count);
            sortStudentsByAverage(students, count);
            printf("Student with ID %d updated successfully.\n", id);
            break;
        }
    }

    if (!found)
    {
        printf("Student with ID %d not found.\n", id);
    }
}

void searchStudent(Student *students, int count, char *name)
{
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].name, name) == 0)
        {
            printf("Name: %s, ID: %d, Grades: %d %d %d %d %d, Avarages: %.2f\n",
                   students[i].name, students[i].id, students[i].grades[0], students[i].grades[1],
                   students[i].grades[2], students[i].grades[3], students[i].grades[4], students[i].average);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("No student found with name %s.\n", name);
    }
}

void searchStudentById(Student *students, int count, int id)
{
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            printf("Name: %s, ID: %d, Grades: %d %d %d %d %d, Avarages: %.2f\n",
                   students[i].name, students[i].id, students[i].grades[0], students[i].grades[1],
                   students[i].grades[2], students[i].grades[3], students[i].grades[4], students[i].average);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("No student found with ID %d.\n", id);
    }
}

int main()
{
    FILE *inputFile = fopen("students.txt", "r");
    if (inputFile == NULL)
    {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    int count;
    int capacity = 2;
    Student *students = readStudents(inputFile, &count);

    fclose(inputFile);
    calculateAverages(students, count);
    sortStudentsByAverage(students, count);

    int choice;

    do
    {
        printf("\nMenu:\n");
        printf("1. Add student\n");
        printf("2. Print students\n");
        printf("3. Delete student\n");
        printf("4. Update student\n");
        printf("5. Search student by name\n");
        printf("6. Search student by ID\n");
        printf("7. Save and exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent(&students, &count, &capacity);
            calculateAverages(students, count);
            sortStudentsByAverage(students, count);
            break;
        case 2:
            printStudents(students, count);
            break;
        case 3:
        {
            int id;
            printf("Enter student ID to delete: ");
            scanf("%d", &id);
            deleteStudent(students, &count, id);
            break;
        }
        case 4:
        {
            int id;
            printf("Enter student ID to update: ");
            scanf("%d", &id);
            updateStudent(students, count, id);
            break;
        }
        case 5:
        {
            char name[50];
            printf("Enter student name to search: ");
            scanf("%49s", name);
            searchStudent(students, count, name);
            break;
        }
        case 6:
        {
            int id;
            printf("Enter student ID to search: ");
            scanf("%d", &id);
            searchStudentById(students, count, id);
            break;
        }
        case 7:
        {
            FILE *outputFile = fopen("average.txt", "w");
            if (outputFile == NULL)
            {
                perror("Error opening output file");
                free(students);
                return EXIT_FAILURE;
            }
            writeStudents(outputFile, students, count);
            fclose(outputFile);
            printf("Processing completed. Check 'averages.txt' for results.\n");
        }
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    free(students);

    return 0;
}
