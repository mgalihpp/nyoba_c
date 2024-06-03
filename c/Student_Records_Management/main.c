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
void saveStudentsToFile(char *filename, Student *students, int count);
void saveAveragesToFile(char *filename, Student *students, int count);

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
    while (scanf("%d", &(*students)[*count].id) != 1)
    {
        printf("Invalid input. Enter a valid student ID: ");
        while (getchar() != '\n')
            ; // clear input buffer
    }
    printf("Enter 5 grades: ");
    for (int i = 0; i < 5; i++)
    {
        while (1)
        {
            if (scanf("%d", &(*students)[*count].grades[i]) == 1)
            {
                break; // Valid input, exit the inner while loop
            }
            printf("Invalid input. Enter a valid grade: ");
            while (getchar() != '\n')
            {
                // Clear input buffer
            }
        }
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
                while (1)
                {
                    if (scanf("%d", &students[i].grades[j]) == 1)
                    {
                        break; // Valid input, exit the inner while loop
                    }
                    printf("Invalid input. Enter a valid grade: ");
                    while (getchar() != '\n')
                    {
                        // Clear input buffer
                    }
                }
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

void saveStudentsToFile(char *filename, Student *students, int count)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Error opening file for writting");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s %d %d %d %d %d %d\n", students[i].name, students[i].id,
                students[i].grades[0], students[i].grades[1], students[i].grades[2],
                students[i].grades[3], students[i].grades[4]);
    }
    fclose(file);
}

void saveAveragesToFile(char *filename, Student *students, int count)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Error opening file for writting");
        exit(EXIT_FAILURE);
    }

    writeStudents(file, students, count);
    fclose(file);
}

int main()
{
    char filename[] = "students.txt";
    char outputFilename[] = "average.txt";
    FILE *inputFile = fopen(filename, "r");
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
        printf("5. Search student by Name\n");
        printf("6. Search student by ID\n");
        printf("7. Save students to file\n");
        printf("8. Average of all students and exit\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        while (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Enter a valid choice: ");
            while (getchar() != '\n')
                ; // Clear the input buffer
        }
        printf("\n");

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
            while (scanf("%d", &id) != 1)
            {
                printf("Invalid input. Enter a valid ID: ");
                while (getchar() != '\n')
                    ; // Clear the input buffer
            }
            deleteStudent(students, &count, id);
            break;
        }
        case 4:
        {
            int id;
            printf("Enter student ID to update: ");
            while (scanf("%d", &id) != 1)
            {
                printf("Invalid input. Enter a valid ID: ");
                while (getchar() != '\n')
                    ; // Clear the input buffer
            }
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
            while (scanf("%d", &id) != 1)
            {
                printf("Invalid input. Enter a valid ID: ");
                while (getchar() != '\n')
                    ; // Clear the input buffer
            }
            searchStudentById(students, count, id);
            break;
        }
        case 7:
        {
            saveStudentsToFile(filename, students, count);
            printf("Changes saved. Check '%s' for results.\n", filename);
            break;
        }
        case 8:
        {
            saveAveragesToFile(outputFilename, students, count);
            printf("Changes saved. Check '%s' for results.\n", outputFilename);
            exit(EXIT_SUCCESS);
            break;
        }
        case 9:
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);

    free(students);

    return 0;
}
