#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum number of students
#define MAX_STUDENTS 100

// Structure to represent a student
struct Student {
    int rollNumber;
    char name[50];
    char course[50];
};

// Function prototypes
void displayMenu();
void addStudent(struct Student students[], int *count);
void displayStudents(struct Student students[], int count);
void searchStudent(struct Student students[], int count, int rollNumber);
void updateStudent(struct Student students[], int count, int rollNumber);
void deleteStudent(struct Student students[], int *count, int rollNumber);

int main() {
    struct Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &studentCount);
                break;
            case 2:
                displayStudents(students, studentCount);
                break;
            case 3: {
                int rollNumber;
                printf("Enter the roll number to search: ");
                scanf("%d", &rollNumber);
                searchStudent(students, studentCount, rollNumber);
                break;
            }
            case 4: {
                int rollNumber;
                printf("Enter the roll number to update: ");
                scanf("%d", &rollNumber);
                updateStudent(students, studentCount, rollNumber);
                break;
            }
            case 5: {
                int rollNumber;
                printf("Enter the roll number to delete: ");
                scanf("%d", &rollNumber);
                deleteStudent(students, &studentCount, rollNumber);
                break;
            }
            case 6:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}

void displayMenu() {
    printf("\n==== Student Record Management System ====\n");
    printf("1. Add Student\n");
    printf("2. Display Students\n");
    printf("3. Search Student\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");
    printf("6. Exit\n");
}

void addStudent(struct Student students[], int *count) {
    if (*count < MAX_STUDENTS) {
        printf("Enter details for student %d:\n", *count + 1);
        printf("Roll Number: ");
        scanf("%d", &students[*count].rollNumber);

        // Consume the newline character left in the buffer
        while (getchar() != '\n');

        printf("Name: ");
        scanf("%[^\n]", students[*count].name);

        // Consume the newline character left in the buffer
        while (getchar() != '\n');

        printf("Course: ");
        scanf("%[^\n]", students[*count].course);

        (*count)++;
        printf("Student added successfully!\n");
    } else {
        printf("Maximum number of students reached. Cannot add more.\n");
    }
}


void displayStudents(struct Student students[], int count) {
    if (count > 0) {
        printf("\n==== List of Students ====\n");
        printf("Roll Number\tName\t\tCourse\n");
        for (int i = 0; i < count; i++) 
		{
            printf("%d\t\t%s\t\t%s\n", students[i].rollNumber, students[i].name, students[i].course);
        }
    } else {
        printf("No students to display.\n");
    }
}

void searchStudent(struct Student students[], int count, int rollNumber) {
    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("\n==== Student Details ====\n");
            printf("Roll Number: %d\n", students[i].rollNumber);
            printf("Name: %s\n", students[i].name);
            printf("Course: %s\n", students[i].course);
            return;
        }
    }
    printf("Student with roll number %d not found.\n", rollNumber);
}

void updateStudent(struct Student students[], int count, int rollNumber) {
    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("Enter updated details for student with roll number %d:\n", rollNumber);
            printf("Name: ");
            scanf("%s", students[i].name);
            printf("Course: ");
            scanf("%s", students[i].course);
            printf("Student details updated successfully!\n");
            return;
        }
    }
    printf("Student with roll number %d not found.\n", rollNumber);
}

void deleteStudent(struct Student students[], int *count, int rollNumber) {
    for (int i = 0; i < *count; i++) {
        if (students[i].rollNumber == rollNumber) {
            // Move the last student in the array to the position of the deleted student
            students[i] = students[*count - 1];
            (*count)--;
            printf("Student with roll number %d deleted successfully!\n", rollNumber);
            return;
        }
    }
    printf("Student with roll number %d not found.\n", rollNumber);
}
