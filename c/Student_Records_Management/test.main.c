#include <assert.h>

typedef struct
{
    char name[50];
    int id;
    int grades[5];
    float average;
} Student;

void testCalculateAverages();
void testSortStudentsByAverage();

void testCalculateAverages()
{
    Student students[2] = {
        {"Alice", 101, {85, 90, 78, 92, 88}, 0},
        {"Bob", 102, {70, 75, 80, 85, 90}, 0}};
    calculateAverages(students, 2);
    assert(students[0].average == 86.6);
    assert(students[1].average == 80.0);
    printf("testCalculateAverages passed.\n");
}

void testSortStudentsByAverage()
{
    Student students[3] = {
        {"Alice", 101, {85, 90, 78, 92, 88}, 86.6},
        {"Bob", 102, {70, 75, 80, 85, 90}, 80.0},
        {"Charlie", 103, {95, 100, 92, 98, 97}, 96.4}};
    sortStudentsByAverage(students, 3);
    assert(students[0].id == 103);
    assert(students[1].id == 101);
    assert(students[2].id == 102);
    printf("testSortStudentsByAverage passed.\n");
}
