#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define MAX_SUBJECT_LENGTH 50
#define DATABASE_FILE "student_database.txt"

// Struct to hold student information
struct Student {
    int id;
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char subject_code[10];  // Assuming subject code is short
    char subject[MAX_SUBJECT_LENGTH];
    int score;
    char grade;
    char semester[20];
};

// Global array to store student records
struct Student students[MAX_STUDENTS];
int num_students = 0;  // Current number of students in the database

// Function prototypes
void loadDatabase();
void saveDatabase();
void addStudent();
void displayStudents();
void searchStudentById();
void searchStudentByName();
void updateStudent();
void deleteStudent();

int main() {
    int choice;
    loadDatabase();  // Load existing data from file (if any)

    do {
        // Menu
        printf("\nStudent Database Management System\n");
        printf("1. Add New Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Search Student by Name\n");
        printf("5. Update Student Information\n");
        printf("6. Delete Student\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudentById();
                break;
            case 4:
                searchStudentByName();
                break;
            case 5:
                updateStudent();
                break;
            case 6:
                deleteStudent();
                break;
            case 7:
                saveDatabase();  // Save data to file before exiting
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 7.\n");
        }
    } while(choice != 7);

    return 0;
}

// Function to load student data from file into array
void loadDatabase() {
    FILE *fp = fopen(DATABASE_FILE, "r");
    if (fp == NULL) {
        printf("No existing database found. Starting with an empty database.\n");
        return;
    }

    // Read data from file into students array
    while (fscanf(fp, "%d %s %s %s %s %d %c %s\n", &students[num_students].id, students[num_students].first_name,
                  students[num_students].last_name, students[num_students].subject_code, students[num_students].subject,
                  &students[num_students].score, &students[num_students].grade, students[num_students].semester) == 8) {
        num_students++;
        if (num_students >= MAX_STUDENTS) {
            printf("Maximum number of students reached. Some data may not be loaded.\n");
            break;
        }
    }

    fclose(fp);
}

// Function to save student data from array to file
void saveDatabase() {
    FILE *fp = fopen(DATABASE_FILE, "w");
    if (fp == NULL) {
        printf("Error saving database.\n");
        return;
    }

    // Write data from students array to file
    for (int i = 0; i < num_students; i++) {
        fprintf(fp, "%d %s %s %s %s %d %c %s\n", students[i].id, students[i].first_name,
                students[i].last_name, students[i].subject_code, students[i].subject,
                students[i].score, students[i].grade, students[i].semester);
    }

    fclose(fp);
}

// Function to add a new student
void addStudent() {
    if (num_students >= MAX_STUDENTS) {
        printf("Database is full. Cannot add more students.\n");
        return;
    }

    struct Student new_student;
    printf("Enter student details:\n");
    printf("ID: ");
    scanf("%d", &new_student.id);
    printf("First Name: ");
    scanf("%s", new_student.first_name);
    printf("Last Name: ");
    scanf("%s", new_student.last_name);
    printf("Subject Code: ");
    scanf("%s", new_student.subject_code);
    printf("Subject: ");
    scanf("%s", new_student.subject);
    printf("Score: ");
    scanf("%d", &new_student.score);
    printf("Grade: ");
    scanf(" %c", &new_student.grade);  // Note the space before %c to consume newline character
    printf("Semester: ");
    scanf("%s", new_student.semester);

    students[num_students] = new_student;
    num_students++;

    printf("Student added successfully.\n");
}

// Function to display all students
void displayStudents() {
    if (num_students == 0) {
        printf("No students found in the database.\n");
        return;
    }

    printf("\nList of Students:\n");
    printf("-------------------------------------------------\n");
    printf("ID\tFirst Name\tLast Name\tSubject\t\tScore\tGrade\tSemester\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < num_students; i++) {
        printf("%d\t%s\t\t%s\t\t%s\t\t%d\t%c\t%s\n", students[i].id, students[i].first_name,
               students[i].last_name, students[i].subject, students[i].score, students[i].grade,
               students[i].semester);
    }
    printf("-------------------------------------------------\n");
}

// Function to search for a student by ID
void searchStudentById() {
    int search_id;
    printf("Enter ID to search for: ");
    scanf("%d", &search_id);

    for (int i = 0; i < num_students; i++) {
        if (students[i].id == search_id) {
            printf("\nStudent found:\n");
            printf("-------------------------------------------------\n");
            printf("ID\tFirst Name\tLast Name\tSubject\t\tScore\tGrade\tSemester\n");
            printf("-------------------------------------------------\n");
            printf("%d\t%s\t\t%s\t\t%s\t\t%d\t%c\t%s\n", students[i].id, students[i].first_name,
                   students[i].last_name, students[i].subject, students[i].score, students[i].grade,
                   students[i].semester);
            printf("-------------------------------------------------\n");
            return;
        }
    }

    printf("Student with ID %d not found.\n", search_id);
}

// Function to search for a student by name (first name)
void searchStudentByName() {
    char search_name[MAX_NAME_LENGTH];
    printf("Enter First Name to search for: ");
    scanf("%s", search_name);

    int found = 0;
    printf("\nSearch Results:\n");
    printf("-------------------------------------------------\n");
    printf("ID\tFirst Name\tLast Name\tSubject\t\tScore\tGrade\tSemester\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < num_students; i++) {
        if (strcmp(students[i].first_name, search_name) == 0) {
            printf("%d\t%s\t\t%s\t\t%s\t\t%d\t%c\t%s\n", students[i].id, students[i].first_name,
                   students[i].last_name, students[i].subject, students[i].score, students[i].grade,
                   students[i].semester);
            found = 1;
        }
    }
    printf("-------------------------------------------------\n");

    if (!found) {
        printf("No students found with First Name %s.\n", search_name);
    }
}

// Function to update student information
void updateStudent() {
    int update_id;
    printf("Enter ID of student to update: ");
    scanf("%d", &update_id);

    for (int i = 0; i < num_students; i++) {
        if (students[i].id == update_id) {
            printf("Enter updated details for student with ID %d:\n", update_id);
            printf("First Name: ");
            scanf("%s", students[i].first_name);
            printf("Last Name: ");
            scanf("%s", students[i].last_name);
            printf("Subject Code: ");
            scanf("%s", students[i].subject_code);
            printf("Subject: ");
            scanf("%s", students[i].subject);
            printf("Score: ");
            scanf("%d", &students[i].score);
            printf("Grade: ");
            scanf(" %c", &students[i].grade);  // Note the space before %c to consume newline character
            printf("Semester: ");
            scanf("%s", students[i].semester);

            printf("Student information updated successfully.\n");
            return;
        }
    }

    printf("Student with ID %d not found.\n", update_id);
}

// Function to delete a student
void deleteStudent() {
    int delete_id;
    printf("Enter ID of student to delete: ");
    scanf("%d", &delete_id);

    for (int i = 0; i < num_students; i++) {
        if (students[i].id == delete_id) {
            // Shift all elements after the deleted student one position to the left
            for (int j = i; j < num_students - 1; j++) {
                students[j] = students[j + 1];
            }
            num_students--;
            printf("Student with ID %d deleted successfully.\n", delete_id);
            return;
        }
    }

    printf("Student with ID %d not found.\n", delete_id);
}
