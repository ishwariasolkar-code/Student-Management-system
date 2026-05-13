#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student {
public:
    int id;
    char name[50];
    int age;
    char course[50];

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Course: ";
        cin.ignore();
        cin.getline(course, 50);
    }

    void display() {
        cout << "\nID: " << id
             << "\nName: " << name
             << "\nAge: " << age
             << "\nCourse: " << course << endl;
    }
};

// Function to add student
void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    s.input();
    file.write((char*)&s, sizeof(s));

    file.close();
    cout << "Student added successfully!\n";
}

// Function to display all students
void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    if (!file) {
        cout << "No records found.\n";
        return;
    }

    while (file.read((char*)&s, sizeof(s))) {
        s.display();
    }

    file.close();
}

// Function to search student
void searchStudent() {
    int searchId;
    Student s;
    bool found = false;

    cout << "Enter ID to search: ";
    cin >> searchId;

    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == searchId) {
            s.display();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Student not found.\n";
}

// Function to update student
void updateStudent() {
    int searchId;
    Student s;
    bool found = false;

    cout << "Enter ID to update: ";
    cin >> searchId;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == searchId) {
            cout << "Existing record:";
            s.display();

            cout << "\nEnter new details:\n";
            s.input();

            int pos = -1 * sizeof(s);
            file.seekp(pos, ios::cur);
            file.write((char*)&s, sizeof(s));

            cout << "Record updated!\n";
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Student not found.\n";
}

// Function to delete student
void deleteStudent() {
    int searchId;
    Student s;
    bool found = false;

    cout << "Enter ID to delete: ";
    cin >> searchId;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == searchId) {
            found = true;
        } else {
            temp.write((char*)&s, sizeof(s));
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Record deleted successfully!\n";
    else
        cout << "Student not found.\n";
}

// Main menu
int main() {
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
