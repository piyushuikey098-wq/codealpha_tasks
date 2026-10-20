#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

struct Course {
    string name;
    double grade;
    double credits;
    double gradePoints;
};

int main() {
    cout << "========================================\n";
    cout << "          CGPA CALCULATOR\n";
    cout << "========================================\n";

    double previousCGPA, previousCredits;
    int numCourses;

    // Input previous academic details
    cout << "Enter previous CGPA (0 if none): ";
    cin >> previousCGPA;

    cout << "Enter previously completed credits: ";
    cin >> previousCredits;

    // Input number of courses
    cout << "\nEnter number of courses: ";
    cin >> numCourses;

    if (numCourses <= 0 || previousCGPA < 0 ||
        previousCGPA > 10 || previousCredits < 0) {
        cout << "Invalid input. Please enter valid values.\n";
        return 1;
    }

    vector<Course> courses;

    double totalCredits = 0;
    double totalGradePoints = 0;

    // Input details for each course
    for (int i = 0; i < numCourses; i++) {
        Course course;

        cout << "\nCourse " << i + 1 << "\n";

        cout << "Enter course name: ";
        cin >> ws;
        getline(cin, course.name);

        cout << "Enter grade points (0 to 10): ";
        cin >> course.grade;

        cout << "Enter credit hours: ";
        cin >> course.credits;

        if (course.grade < 0 || course.grade > 10 ||
            course.credits <= 0) {
            cout << "Invalid grade or credits. Please restart the program.\n";
            return 1;
        }

        // Calculate grade points
        course.gradePoints = course.grade * course.credits;

        // Update totals
        totalCredits += course.credits;
        totalGradePoints += course.gradePoints;

        // Store course information
        courses.push_back(course);
    }

    // Calculate semester GPA
    double semesterGPA = totalGradePoints / totalCredits;

    // Calculate updated overall CGPA
    double overallCredits = previousCredits + totalCredits;

    double overallCGPA =
        (previousCGPA * previousCredits + totalGradePoints)
        / overallCredits;

    // Display course details
    cout << "\n========================================\n";
    cout << "             COURSE DETAILS\n";
    cout << "========================================\n";

    cout << fixed << setprecision(2);

    cout << left << setw(25) << "Course"
         << setw(12) << "Grade"
         << setw(12) << "Credits"
         << "Grade Points\n";

    cout << string(60, '-') << "\n";

    for (const Course& course : courses) {
        cout << left << setw(25) << course.name
             << setw(12) << course.grade
             << setw(12) << course.credits
             << course.gradePoints << "\n";
    }

    // Display final results
    cout << "\n========================================\n";
    cout << "              FINAL RESULTS\n";
    cout << "========================================\n";

    cout << "Total Semester Credits: " << totalCredits << "\n";
    cout << "Total Grade Points:     " << totalGradePoints << "\n";
    cout << "Semester GPA:           " << semesterGPA << "\n";
    cout << "Updated Overall CGPA:   " << overallCGPA << "\n";

    cout << "========================================\n";
    cout << "Thank you for using the CGPA Calculator!\n";

    return 0;
}