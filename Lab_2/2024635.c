#include <stdio.h>
#include <string.h>

typedef struct {
    int rollNo;
    char firstName[50];
    char lastName[50];
    float marks;
} Student;

int main() {
    FILE *fp, *temp;
    Student student;
    int rollNo, found;
    int choice;

    printf("\nStudent Record Management System\n");
    printf("1. Add a new student record\n");
    printf("2. Display all student records\n");
    printf("3. Search for a student record\n");
    printf("4. Update a student record\n");
    printf("5. Delete a student record\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        fp = fopen("students.txt", "a");
        if (fp == NULL) {
            printf("Error opening file.\n");
            return 1;
        }
        printf("Enter Roll Number: ");
        scanf("%d", &student.rollNo);
        printf("Enter First Name: ");
        scanf("%s", student.firstName);
        printf("Enter Last Name: ");
        scanf("%s", student.lastName);
        printf("Enter Marks: ");
        scanf("%f", &student.marks);
        fprintf(fp, "%d %s %s %.2f\n", student.rollNo, student.firstName, student.lastName, student.marks);
        fclose(fp);
        printf("Record added successfully.\n");
    } else if (choice == 2) {
        fp = fopen("students.txt", "r");
        if (fp == NULL) {
            printf("Error opening file.\n");
            return 1;
        }
        printf("All Student Records:\n");
        printf("Roll Number\tFirst Name\tLast Name\tMarks\n");
        while (fscanf(fp, "%d %s %s %f", &student.rollNo, student.firstName, student.lastName, &student.marks) != EOF) {
            printf("%d\t%s\t%s\t%.2f\n", student.rollNo, student.firstName, student.lastName, student.marks);
        }
        fclose(fp);
    } else if (choice == 3) {
        fp = fopen("students.txt", "r");
        if (fp == NULL) {
            printf("Error opening file.\n");
            return 1;
        }
        printf("Enter Roll Number to search: ");
        scanf("%d", &rollNo);
        found = 0;
        while (fscanf(fp, "%d %s %s %f", &student.rollNo, student.firstName, student.lastName, &student.marks) != EOF) {
            if (student.rollNo == rollNo) {
                found = 1;
                printf("Record Found: %d %s %s %.2f\n", student.rollNo, student.firstName, student.lastName, student.marks);
            }
        }
        if (!found) {
            printf("Record not found.\n");
        }
        fclose(fp);
    } else if (choice == 4) {
        fp = fopen("students.txt", "r");
        temp = fopen("temp.txt", "w");
        if (fp == NULL || temp == NULL) {
            printf("Error opening file.\n");
            return 1;
        }
        printf("Enter Roll Number to update: ");
        scanf("%d", &rollNo);
        found = 0;
        while (fscanf(fp, "%d %s %s %f", &student.rollNo, student.firstName, student.lastName, &student.marks) != EOF) {
            if (student.rollNo == rollNo) {
                found = 1;
                printf("Enter new First Name: ");
                scanf("%s", student.firstName);
                printf("Enter new Last Name: ");
                scanf("%s", student.lastName);
                printf("Enter new Marks: ");
                scanf("%f", &student.marks);
            }
            fprintf(temp, "%d %s %s %.2f\n", student.rollNo, student.firstName, student.lastName, student.marks);
        }
        fclose(fp);
        fclose(temp);
        remove("students.txt");
        rename("temp.txt", "students.txt");
        if (found) {
            printf("Record updated successfully.\n");
        } else {
            printf("Record not found.\n");
        }
    } else if (choice == 5) {
        fp = fopen("students.txt", "r");
        temp = fopen("temp.txt", "w");
        if (fp == NULL || temp == NULL) {
            printf("Error opening file.\n");
            return 1;
        }
        printf("Enter Roll Number to delete: ");
        scanf("%d", &rollNo);
        found = 0;
        while (fscanf(fp, "%d %s %s %f", &student.rollNo, student.firstName, student.lastName, &student.marks) != EOF) {
            if (student.rollNo != rollNo) {
                fprintf(temp, "%d %s %s %.2f\n", student.rollNo, student.firstName, student.lastName, student.marks);
            } else {
                found = 1;
            }
        }
        fclose(fp);
        fclose(temp);
        remove("students.txt");
        rename("temp.txt", "students.txt");
        if (found) {
            printf("Record deleted successfully.\n");
        } else {
            printf("Record not found.\n");
        }
    } else if (choice == 6) {
        printf("Exiting program.\n");
        return 0;
    } else {
        printf("Invalid choice. Please try again.\n");
    }

    return 0;
}