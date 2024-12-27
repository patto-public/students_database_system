#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 100
#define MAX_SUBJECT_LENGTH 100
#define MAX_SUBJECTS 5
#define DATABASE_FILE "student_database.txt"

// Struct to hold subject information
struct Subject
{
    char subject_code[10];
    char subject_name[MAX_SUBJECT_LENGTH];
    int credits;
    int score;
    char grade;
};

// Struct to hold student information
struct Student
{
    int id;
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char faculty[MAX_NAME_LENGTH];
    char discipline[MAX_NAME_LENGTH];
    int year_of_admission;
    struct Subject subjects[MAX_SUBJECTS];
    int num_subjects;
    char semester[20];
    float gpa; // store GPA
};

// Global array to store student records
struct Student students[MAX_STUDENTS];
int num_students = 0; // Current number of students in the database

// Function prototypes
void loadDatabase();
void saveDatabase();
void addStudent();
void displayStudents();
void searchStudentById();
void searchStudentByName();
void updateStudent();
void deleteStudent();
void displayDefaultSubjects(int year_of_admission, struct Subject subjects[], int *num_subjects);
float calculateGPA(struct Subject subjects[], int num_subjects);

int main()
{
    int choice;
    loadDatabase(); // Load existing data from file (if any)

    do
    {
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

        switch (choice)
        {
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
            saveDatabase(); // Save data to file before exiting
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please enter a number between 1 and 7.\n");
        }
    } while (choice != 7);

    return 0;
}

// Function to load student data from file into array
void loadDatabase()
{
    FILE *fp = fopen(DATABASE_FILE, "r");
    if (fp == NULL)
    {
        printf("No existing database found. Starting with an empty database.\n");
        return;
    }

    // Read data from file into students array
    while (fscanf(fp, "%d %s %s %s %s %d %d %s %f\n", &students[num_students].id, students[num_students].first_name,
                  students[num_students].last_name, students[num_students].faculty, students[num_students].discipline,
                  &students[num_students].year_of_admission, &students[num_students].num_subjects, students[num_students].semester, &students[num_students].gpa) == 9)
    {
        for (int j = 0; j < students[num_students].num_subjects; j++)
        {
            fscanf(fp, "%s %s %d %c\n", students[num_students].subjects[j].subject_code, students[num_students].subjects[j].subject_name,
                   &students[num_students].subjects[j].score, &students[num_students].subjects[j].grade);
        }
        num_students++;
        if (num_students >= MAX_STUDENTS)
        {
            printf("Maximum number of students reached. Some data may not be loaded.\n");
            break;
        }
    }

    fclose(fp);
}

// Function to save student data from array to file
void saveDatabase()
{
    FILE *fp = fopen(DATABASE_FILE, "w");
    if (fp == NULL)
    {
        printf("Error saving database.\n");
        return;
    }

    // Write data from students array to file
    for (int i = 0; i < num_students; i++)
    {
        fprintf(fp, "%d %s %s %s %s %d %d %s %f\n", students[i].id, students[i].first_name,
                students[i].last_name, students[i].faculty, students[i].discipline,
                students[i].year_of_admission, students[i].num_subjects, students[i].semester, students[i].gpa);
        for (int j = 0; j < students[i].num_subjects; j++)
        {
            fprintf(fp, "%s %s %d %c\n", students[i].subjects[j].subject_code, students[i].subjects[j].subject_name,
                    students[i].subjects[j].score, students[i].subjects[j].grade);
        }
    }

    fclose(fp);
}

// Function to add a new student
void addStudent()
{
    if (num_students >= MAX_STUDENTS)
    {
        printf("Database is full. Cannot add more students.\n");
        return;
    }

    struct Student new_student;
    new_student.id = num_students + 1; // Auto-generate ID

    printf("Enter student details:\n");
    printf("First Name: ");
    scanf("%s", new_student.first_name);
    printf("Last Name: ");
    scanf("%s", new_student.last_name);
    printf("Year of Admission: ");
    scanf("%d", &new_student.year_of_admission);

    printf("Choose Faculty:\n1. Engineering\n2. Science\nEnter choice: ");
    int faculty_choice;
    scanf("%d", &faculty_choice);

    if (faculty_choice == 1)
    {
        strcpy(new_student.faculty, "Engineering");
        printf("Choose Discipline:\n1. Computer Engineering\n2. Electrical Engineering\nEnter choice: ");
        int discipline_choice;
        scanf("%d", &discipline_choice);

        if (discipline_choice == 1)
        {
            strcpy(new_student.discipline, "Computer Engineering");
        }
        else
        {
            strcpy(new_student.discipline, "Electrical Engineering");
        }
    }
    else
    {
        strcpy(new_student.faculty, "Science");
        printf("Choose Discipline:\n1. Physics\n2. Chemistry\nEnter choice: ");
        int discipline_choice;
        scanf("%d", &discipline_choice);

        if (discipline_choice == 1)
        {
            strcpy(new_student.discipline, "Physics");
        }
        else
        {
            strcpy(new_student.discipline, "Chemistry");
        }
    }

    displayDefaultSubjects(new_student.year_of_admission, new_student.subjects, &new_student.num_subjects);

    printf("Semester: ");
    scanf("%s", new_student.semester);

    new_student.gpa = calculateGPA(new_student.subjects, new_student.num_subjects);

    students[num_students] = new_student;
    num_students++;

    printf("Student added successfully.\n");
}

// Function to display default subjects for the given year of admission
void displayDefaultSubjects(int year_of_admission, struct Subject subjects[], int *num_subjects)
{
    *num_subjects = 0;

    if (year_of_admission == 2014)
    {
        strcpy(subjects[*num_subjects].subject_code, "MATH101");
        strcpy(subjects[*num_subjects].subject_name, "Math");
        subjects[*num_subjects].score = 0;
        subjects[*num_subjects].grade = '-';
        (*num_subjects)++;

        strcpy(subjects[*num_subjects].subject_code, "CS102");
        strcpy(subjects[*num_subjects].subject_name, "Data Structure");
        subjects[*num_subjects].score = 0;
        subjects[*num_subjects].grade = '-';
        (*num_subjects)++;

        strcpy(subjects[*num_subjects].subject_code, "CS103");
        strcpy(subjects[*num_subjects].subject_name, "Algorithms");
        subjects[*num_subjects].score = 0;
        subjects[*num_subjects].grade = '-';
        (*num_subjects)++;
    }

    // Print the default subjects
    printf("Default subjects for Year %d:\n", year_of_admission);
    for (int i = 0; i < *num_subjects; i++)
    {
        printf("%s - %s\n", subjects[i].subject_code, subjects[i].subject_name);
    }
}

// Function to calculate GPA
float calculateGPA(struct Subject subjects[], int num_subjects)
{
    float total_points = 0.0;
    int total_credits = 0;

    for (int i = 0; i < num_subjects; i++)
    {
        char grade = subjects[i].grade;
        float grade_points;

        switch (grade)
        {
        case 'A':
            grade_points = 4.0;
            break;
        case 'B':
            grade_points = 3.0;
            break;
        case 'C':
            grade_points = 2.0;
            break;
        case 'D':
            grade_points = 1.0;
            break;
        case 'F':
            grade_points = 0.0;
            break;
        default:
            grade_points = 0.0; // In case of no valid grade
        }

        total_points += grade_points * subjects[i].credits;
        total_credits += subjects[i].credits;
    }

    if (total_credits == 0)
    {
        return 0.0; // Avoid division by zero
    }

    return total_points / total_credits;
}

// Function to display all students
void displayStudents()
{
    if (num_students == 0)
    {
        printf("No students found in the database.\n");
        return;
    }

    printf("\nList of Students:\n");
    printf("-------------------------------------------------\n");
    printf("ID\tFirst Name\tLast Name\tFaculty\t\tDiscipline\tYear\tSemester\tGPA\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < num_students; i++)
    {
        printf("%d\t%s\t\t%s\t\t%s\t%s\t%d\t%s\t%.2f\n", students[i].id, students[i].first_name,
               students[i].last_name, students[i].faculty, students[i].discipline,
               students[i].year_of_admission, students[i].semester, students[i].gpa);

        printf("Subjects:\n");
        for (int j = 0; j < students[i].num_subjects; j++)
        {
            printf("\t%s - %s - Score: %d, Grade: %c\n", students[i].subjects[j].subject_code,
                   students[i].subjects[j].subject_name, students[i].subjects[j].score,
                   students[i].subjects[j].grade);
        }
        printf("-------------------------------------------------\n");
    }
}

// Function to search for a student by ID
void searchStudentById()
{
    int search_id;
    printf("Enter ID to search for: ");
    scanf("%d", &search_id);

    for (int i = 0; i < num_students; i++)
    {
        if (students[i].id == search_id)
        {
            printf("\nStudent found:\n");
            printf("-------------------------------------------------\n");
            printf("ID\tFirst Name\tLast Name\tFaculty\t\tDiscipline\tYear\tSemester\tGPA\n");
            printf("-------------------------------------------------\n");
            printf("%d\t%s\t\t%s\t\t%s\t%s\t%d\t%s\t%.2f\n", students[i].id, students[i].first_name,
                   students[i].last_name, students[i].faculty, students[i].discipline,
                   students[i].year_of_admission, students[i].semester, students[i].gpa);

            printf("Subjects:\n");
            for (int j = 0; j < students[i].num_subjects; j++)
            {
                printf("\t%s - %s - Score: %d, Grade: %c\n", students[i].subjects[j].subject_code,
                       students[i].subjects[j].subject_name, students[i].subjects[j].score,
                       students[i].subjects[j].grade);
            }
            printf("-------------------------------------------------\n");
            return;
        }
    }

    printf("Student with ID %d not found.\n", search_id);
}

// Function to search for a student by name (first name)
void searchStudentByName()
{
    char search_name[MAX_NAME_LENGTH];
    printf("Enter First Name to search for: ");
    scanf("%s", search_name);

    int found = 0;
    printf("\nSearch Results:\n");
    printf("-------------------------------------------------\n");
    printf("ID\tFirst Name\tLast Name\tFaculty\t\tDiscipline\tYear\tSemester\tGPA\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < num_students; i++)
    {
        if (strcmp(students[i].first_name, search_name) == 0)
        {
            printf("%d\t%s\t\t%s\t\t%s\t%s\t%d\t%s\t%.2f\n", students[i].id, students[i].first_name,
                   students[i].last_name, students[i].faculty, students[i].discipline,
                   students[i].year_of_admission, students[i].semester, students[i].gpa);

            printf("Subjects:\n");
            for (int j = 0; j < students[i].num_subjects; j++)
            {
                printf("\t%s - %s - Score: %d, Grade: %c\n", students[i].subjects[j].subject_code,
                       students[i].subjects[j].subject_name, students[i].subjects[j].score,
                       students[i].subjects[j].grade);
            }
            found = 1;
        }
    }
    printf("-------------------------------------------------\n");

    if (!found)
    {
        printf("No students found with First Name %s.\n", search_name);
    }
}

// Function to update student information
void updateStudent()
{
    int update_id;
    printf("Enter ID of student to update: ");
    scanf("%d", &update_id);

    for (int i = 0; i < num_students; i++)
    {
        if (students[i].id == update_id)
        {
            printf("Enter updated details for student with ID %d:\n", update_id);
            printf("First Name: ");
            scanf("%s", students[i].first_name);
            printf("Last Name: ");
            scanf("%s", students[i].last_name);
            printf("Year of Admission: ");
            scanf("%d", &students[i].year_of_admission);

            printf("Choose Faculty:\n1. Engineering\n2. Science\nEnter choice: ");
            int faculty_choice;
            scanf("%d", &faculty_choice);

            if (faculty_choice == 1)
            {
                strcpy(students[i].faculty, "Engineering");
                printf("Choose Discipline:\n1. Computer Engineering\n2. Electrical Engineering\nEnter choice: ");
                int discipline_choice;
                scanf("%d", &discipline_choice);

                if (discipline_choice == 1)
                {
                    strcpy(students[i].discipline, "Computer Engineering");
                }
                else
                {
                    strcpy(students[i].discipline, "Electrical Engineering");
                }
            }
            else
            {
                strcpy(students[i].faculty, "Science");
                printf("Choose Discipline:\n1. Physics\n2. Chemistry\nEnter choice: ");
                int discipline_choice;
                scanf("%d", &discipline_choice);

                if (discipline_choice == 1)
                {
                    strcpy(students[i].discipline, "Physics");
                }
                else
                {
                    strcpy(students[i].discipline, "Chemistry");
                }
            }

            displayDefaultSubjects(students[i].year_of_admission, students[i].subjects, &students[i].num_subjects);
            printf("Semester: ");
            scanf("%s", students[i].semester);

            students[i].gpa = calculateGPA(students[i].subjects, students[i].num_subjects);

            printf("Student information updated successfully.\n");
            return;
        }
    }

    printf("Student with ID %d not found.\n", update_id);
}

// Function to delete a student
void deleteStudent()
{
    int delete_id;
    printf("Enter ID of student to delete: ");
    scanf("%d", &delete_id);

    for (int i = 0; i < num_students; i++)
    {
        if (students[i].id == delete_id)
        {
            // Shift all elements after the deleted student one position to the left
            for (int j = i; j < num_students - 1; j++)
            {
                students[j] = students[j + 1];
            }
            num_students--;
            printf("Student with ID %d deleted successfully.\n", delete_id);
            return;
        }
    }

    printf("Student with ID %d not found.\n", delete_id);
}
