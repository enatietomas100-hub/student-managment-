
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>
using namespace std;

// ========================================
// CONSOLE COLORS
// ========================================

const int COLOR_WHITE = 15;
const int COLOR_CYAN = 11;
const int COLOR_GREEN = 10;
const int COLOR_RED = 12;
const int COLOR_YELLOW = 14;
const int COLOR_BLUE = 9;

void color(int c)
{
    switch(c)
    {
        case COLOR_GREEN:  cout << "\033[32m"; break;
        case COLOR_RED:    cout << "\033[31m"; break;
        case COLOR_CYAN:   cout << "\033[36m"; break;
        case COLOR_YELLOW: cout << "\033[33m"; break;
        case COLOR_BLUE:   cout << "\033[34m"; break;
        default:           cout << "\033[0m"; break;
    }
}

// ========================================
// CLEAR SCREEN
// ========================================

void clearScreen()
{
    color(COLOR_WHITE);
    cout << "\033[2J\033[H" << flush;
}

// ========================================
// INPUT VALIDATION
// ========================================

string readText(string message)
{
    string value;

    do
    {
        color(COLOR_YELLOW);
        cout << message;
        color(COLOR_WHITE);

        getline(cin, value);

        if(value.empty())
        {
            color(COLOR_RED);
            cout << "Input cannot be empty!\n";
            color(COLOR_WHITE);
        }

    } while(value.empty());

    return value;
}

int readInt(string message, int min, int max)
{
    string input;
    int value;
    char extra;

    while(true)
    {
        color(COLOR_YELLOW);
        cout << message;
        color(COLOR_WHITE);

        getline(cin, input);

        stringstream ss(input);

        if(ss >> value && !(ss >> extra)
           && value >= min && value <= max)
        {
            return value;
        }

        color(COLOR_RED);
        cout << "Invalid input! Enter a number from "
             << min << " to " << max << ".\n";
        color(COLOR_WHITE);
    }
}

double readDouble(string message, double min, double max)
{
    string input;
    double value;
    char extra;

    while(true)
    {
        color(COLOR_YELLOW);
        cout << message;
        color(COLOR_WHITE);

        getline(cin, input);

        stringstream ss(input);

        if(ss >> value && !(ss >> extra)
           && value >= min && value <= max)
        {
            return value;
        }

        color(COLOR_RED);
        cout << "Invalid GPA! Enter a value from "
             << min << " to " << max << ".\n";
        color(COLOR_WHITE);
    }
}

// ========================================
// STUDENT STRUCTURE - 11 ATTRIBUTES
// ========================================

struct Student
{
    int id;
    string fullName;
    string gender;
    int age;
    string department;
    string program;
    int yearOfStudy;
    int semester;
    double gpa;
    string phone;
    string email;
};

// ========================================
// INPUT STUDENT INFORMATION
// ========================================

Student inputStudent()
{
    Student s;

    color(COLOR_CYAN);
    cout << "\n============================================\n";

    color(COLOR_YELLOW);
    cout << "          ENTER STUDENT INFORMATION\n";

    color(COLOR_CYAN);
    cout << "============================================\n";

    color(COLOR_WHITE);

    s.id = readInt("Student ID       : ", 1, 999999999);
    s.fullName = readText("Full Name        : ");
    s.gender = readText("Gender           : ");
    s.age = readInt("Age              : ", 15, 100);
    s.department = readText("Department       : ");
    s.program = readText("Program          : ");
    s.yearOfStudy = readInt("Year of Study    : ", 1, 10);
    s.semester = readInt("Semester         : ", 1, 3);
    s.gpa = readDouble("GPA              : ", 0, 4);
    s.phone = readText("Phone Number     : ");
    s.email = readText("Email Address    : ");

    return s;
}

// ========================================
// DOUBLY LINKED LIST NODE
// ========================================

struct Node
{
    Student data;
    Node *next;
    Node *prev;

    Node(Student s)
    {
        data = s;
        next = nullptr;
        prev = nullptr;
    }
};

// ========================================
// STUDENT MANAGEMENT SYSTEM
// ========================================

class StudentList
{
private:

    Node *head;
    Node *tail;
    int count;

    // Search node by ID
    Node* findNode(int id)
    {
        Node *current = head;

        while(current != nullptr)
        {
            if(current->data.id == id)
                return current;

            current = current->next;
        }

        return nullptr;
    }

    // ====================================
    // DISPLAY STUDENT TABLE
    // ====================================

    void printStudent(Student s)
    {
        color(COLOR_CYAN);

        cout << "+----------------+--------------------------+\n";

        cout << "| " << left << setw(14) << "ATTRIBUTE"
             << " | " << setw(24) << "INFORMATION" << " |\n";

        cout << "+----------------+--------------------------+\n";

        color(COLOR_WHITE);

        cout << "| " << setw(14) << "Student ID"
             << " | " << setw(24) << s.id << " |\n";

        cout << "| " << setw(14) << "Full Name"
             << " | " << setw(24) << s.fullName.substr(0,24) << " |\n";

        cout << "| " << setw(14) << "Gender"
             << " | " << setw(24) << s.gender.substr(0,24) << " |\n";

        cout << "| " << setw(14) << "Age"
             << " | " << setw(24) << s.age << " |\n";

        cout << "| " << setw(14) << "Department"
             << " | " << setw(24) << s.department.substr(0,24) << " |\n";

        cout << "| " << setw(14) << "Program"
             << " | " << setw(24) << s.program.substr(0,24) << " |\n";

        cout << "| " << setw(14) << "Study Year"
             << " | " << setw(24) << s.yearOfStudy << " |\n";

        cout << "| " << setw(14) << "Semester"
             << " | " << setw(24) << s.semester << " |\n";

        cout << "| " << setw(14) << "GPA"
             << " | " << setw(24) << fixed
             << setprecision(2) << s.gpa << " |\n";

        cout << "| " << setw(14) << "Phone"
             << " | " << setw(24) << s.phone.substr(0,24) << " |\n";

        cout << "| " << setw(14) << "Email"
             << " | " << setw(24) << s.email.substr(0,24) << " |\n";

        color(COLOR_CYAN);
        cout << "+----------------+--------------------------+\n";

        color(COLOR_WHITE);
    }

public:

    // Constructor
    StudentList()
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    // Destructor
    ~StudentList()
    {
        Node *current = head;

        while(current != nullptr)
        {
            Node *nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    int getCount()
    {
        return count;
    }

    bool idExists(int id)
    {
        return findNode(id) != nullptr;
    }

    // ====================================
    // ADD AT BEGINNING
    // ====================================

    void addBeginning(Student s)
    {
        if(idExists(s.id))
        {
            color(COLOR_RED);
            cout << "\nERROR: Student ID already exists!\n";
            color(COLOR_WHITE);
            displayForward();
            return;
        }

        Node *newNode = new Node(s);

        if(isEmpty())
        {
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        count++;

        color(COLOR_GREEN);
        cout << "\nSUCCESS: Student added at beginning!\n";
        color(COLOR_WHITE);

        displayForward();
    }

    // ====================================
    // ADD AT END
    // ====================================

    void addEnd(Student s)
    {
        if(idExists(s.id))
        {
            color(COLOR_RED);
            cout << "\nERROR: Student ID already exists!\n";
            color(COLOR_WHITE);
            displayForward();
            return;
        }

        Node *newNode = new Node(s);

        if(isEmpty())
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        count++;

        color(COLOR_GREEN);
        cout << "\nSUCCESS: Student added at end!\n";
        color(COLOR_WHITE);

        displayForward();
    }

    // ====================================
    // INSERT AT POSITION
    // ====================================

    void insertAtPosition(Student s, int position)
    {
        if(position < 1 || position > count + 1)
        {
            color(COLOR_RED);
            cout << "\nERROR: Invalid position!\n";
            color(COLOR_WHITE);
            displayForward();
            return;
        }

        if(idExists(s.id))
        {
            color(COLOR_RED);
            cout << "\nERROR: Student ID already exists!\n";
            color(COLOR_WHITE);
            displayForward();
            return;
        }

        Node *newNode = new Node(s);

        if(position == 1)
        {
            if(isEmpty())
            {
                head = tail = newNode;
            }
            else
            {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
        }
        else if(position == count + 1)
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        else
        {
            Node *current = head;

            for(int i = 1; i < position; i++)
                current = current->next;

            Node *previousNode = current->prev;

            newNode->next = current;
            newNode->prev = previousNode;

            previousNode->next = newNode;
            current->prev = newNode;
        }

        count++;

        color(COLOR_GREEN);
        cout << "\nSUCCESS: Student inserted successfully!\n";
        color(COLOR_WHITE);

        displayForward();
    }

    // ====================================
    // DISPLAY FORWARD
    // ====================================

    void displayForward()
    {
        if(isEmpty())
        {
            color(COLOR_YELLOW);
            cout << "\nNo student records available!\n";
            color(COLOR_WHITE);
            return;
        }

        color(COLOR_CYAN);
        cout << "\n============================================\n";
        cout << "          UNIVERSITY STUDENT RECORDS\n";
        cout << "============================================\n";
        color(COLOR_WHITE);

        Node *current = head;
        int number = 1;

        while(current != nullptr)
        {
            color(COLOR_YELLOW);
            cout << "\nSTUDENT RECORD NUMBER: " << number << "\n";
            color(COLOR_WHITE);

            printStudent(current->data);

            current = current->next;
            number++;
        }

        color(COLOR_CYAN);
        cout << "\n============================================\n";

        color(COLOR_GREEN);
        cout << "TOTAL STUDENTS: " << count << "\n";

        color(COLOR_CYAN);
        cout << "============================================\n";

        color(COLOR_WHITE);
    }

    // ====================================
    // DISPLAY BACKWARD
    // ====================================

    void displayBackward()
    {
        if(isEmpty())
        {
            color(COLOR_YELLOW);
            cout << "\nNo student records available!\n";
            color(COLOR_WHITE);
            return;
        }

        color(COLOR_CYAN);
        cout << "\n============================================\n";
        cout << "          STUDENT RECORDS - REVERSE\n";
        cout << "============================================\n";
        color(COLOR_WHITE);

        Node *current = tail;
        int number = count;

        while(current != nullptr)
        {
            color(COLOR_YELLOW);
            cout << "\nSTUDENT RECORD NUMBER: " << number << "\n";
            color(COLOR_WHITE);

            printStudent(current->data);

            current = current->prev;
            number--;
        }

        color(COLOR_GREEN);
        cout << "\nTOTAL STUDENTS: " << count << "\n";
        color(COLOR_WHITE);
    }

    // ====================================
    // SEARCH STUDENT
    // ====================================

    void searchStudent(int id)
    {
        Node *found = findNode(id);

        if(found == nullptr)
        {
            color(COLOR_RED);
            cout << "\nStudent record not found!\n";
            color(COLOR_WHITE);
            return;
        }

        color(COLOR_GREEN);
        cout << "\nSUCCESS: STUDENT RECORD FOUND!\n";
        color(COLOR_WHITE);

        printStudent(found->data);
    }

    // ====================================
    // UPDATE STUDENT
    // ====================================

    void updateStudent(int id)
    {
        Node *found = findNode(id);

        if(found == nullptr)
        {
            color(COLOR_RED);
            cout << "\nStudent record not found!\n";
            color(COLOR_WHITE);
            return;
        }

        color(COLOR_YELLOW);
        cout << "\nUPDATE STUDENT INFORMATION\n";
        color(COLOR_WHITE);

        cout << "Student ID remains: " << id << "\n";

        found->data.fullName = readText("New Full Name     : ");
        found->data.gender = readText("New Gender        : ");
        found->data.age = readInt("New Age           : ", 15, 100);
        found->data.department = readText("New Department    : ");
        found->data.program = readText("New Program       : ");
        found->data.yearOfStudy = readInt("New Study Year    : ", 1, 10);
        found->data.semester = readInt("New Semester      : ", 1, 3);
        found->data.gpa = readDouble("New GPA           : ", 0, 4);
        found->data.phone = readText("New Phone Number  : ");
        found->data.email = readText("New Email Address : ");

        color(COLOR_GREEN);
        cout << "\nSUCCESS: Student updated successfully!\n";
        color(COLOR_WHITE);

        displayForward();
    }

    // ====================================
    // REMOVE FROM BEGINNING
    // ====================================

    void removeBeginning()
    {
        if(isEmpty())
        {
            color(COLOR_RED);
            cout << "\nNo student records to remove!\n";
            color(COLOR_WHITE);
            return;
        }

        Node *target = head;
        if(head == tail)
        {
            head = tail = nullptr;
        }
        else
        {
            head = head->next;
            head->prev = nullptr;
        }

        delete target;
        count--;

        color(COLOR_GREEN);
        cout << "\nSUCCESS: First student removed!\n";
        color(COLOR_WHITE);
        displayForward();
    }

    // ====================================
    // REMOVE FROM END
    // ====================================

    void removeEnd()
    {
        if(isEmpty())
        {
            color(COLOR_RED);
            cout << "\nNo student records to remove!\n";
            color(COLOR_WHITE);
            return;
        }

        Node *target = tail;
        if(head == tail)
        {
            head = tail = nullptr;
        }
        else
        {
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete target;
        count--;

        color(COLOR_GREEN);
        cout << "\nSUCCESS: Last student removed!\n";
        color(COLOR_WHITE);
        displayForward();
    }

    // ====================================
    // CLEAR ALL STUDENT RECORDS
    // ====================================

    void clearAll()
    {
        Node *current = head;
        while(current != nullptr)
        {
            Node *nextNode = current->next;
            delete current;
            current = nextNode;
        }

        head = tail = nullptr;
        count = 0;

        color(COLOR_GREEN);
        cout << "\nSUCCESS: All student records cleared!\n";
        color(COLOR_WHITE);
    }

    // ====================================
    // DELETE STUDENT
    // ====================================

    void deleteStudent(int id)
    {
        Node *target = findNode(id);

        if(target == nullptr)
        {
            color(COLOR_RED);
            cout << "\nStudent record not found!\n";
            color(COLOR_WHITE);
            displayForward();
            return;
        }

        if(target == head && target == tail)
        {
            head = tail = nullptr;
        }
        else if(target == head)
        {
            head = head->next;
            head->prev = nullptr;
        }
        else if(target == tail)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
        {
            target->prev->next = target->next;
            target->next->prev = target->prev;
        }

        delete target;
        count--;

        color(COLOR_GREEN);
        cout << "\nSUCCESS: Student deleted successfully!\n";
        color(COLOR_WHITE);

        displayForward();
    }

    // ====================================
    // COUNT STUDENTS
    // ====================================

    void displayCount()
    {
        color(COLOR_CYAN);
        cout << "\n============================================\n";
        cout << "          STUDENT RECORD SUMMARY\n";
        cout << "============================================\n";

        color(COLOR_GREEN);
        cout << "TOTAL STUDENTS: " << count << "\n";

        color(COLOR_CYAN);
        cout << "============================================\n";

        color(COLOR_WHITE);
    }
};

// ========================================
// BAHIR DAR UNIVERSITY TEXT LOGO
// ========================================

void displayLogo()
{
    color(COLOR_CYAN);
    cout << "                   .-----------------.\n";
    cout << "               .-''  BAHIR DAR UNIV.  ''-.\n";
    cout << "             .'   Wisdom at the source    '.\n";
    cout << "            /                                 \\\n";
    cout << "           |      ";
    color(COLOR_YELLOW);
    cout << "\\  |  /  \\  |  /";
    color(COLOR_CYAN);
    cout << "      |\n";
    cout << "           |       ";
    color(COLOR_YELLOW);
    cout << "\\ | /   \\ | /";
    color(COLOR_CYAN);
    cout << "       |\n";
    cout << "           |    ";
    color(COLOR_YELLOW);
    cout << "---\\|/-----\\|/---";
    color(COLOR_CYAN);
    cout << "    |\n";
    cout << "           |    ";
    color(COLOR_GREEN);
    cout << "~~~~~~ LAKE TANA ~~~~~~";
    color(COLOR_CYAN);
    cout << "    |\n";
    cout << "           |       ";
    color(COLOR_GREEN);
    cout << "  /\\  /\\  /\\";
    color(COLOR_CYAN);
    cout << "       |\n";
    cout << "           |         ";
    color(COLOR_WHITE);
    cout << " __     __";
    color(COLOR_CYAN);
    cout << "          |\n";
    cout << "           |        ";
    color(COLOR_WHITE);
    cout << " /  \\___/  \\";
    color(COLOR_CYAN);
    cout << "         |\n";
    cout << "            \\     BAHIR DAR UNIVERSITY     /\n";
    cout << "             '.   Wisdom at the source   .'\n";
    cout << "               '-._____________________.-'\n";
    color(COLOR_WHITE);
    cout << "============================================\n";
}

// ========================================
// MAIN MENU
// ========================================

void displayMenu()
{
    color(COLOR_CYAN);

    cout << "\n============================================\n";
    cout << "       UNIVERSITY MANAGEMENT SYSTEM\n";
    cout << "          STUDENT RECORD MODULE\n";
    cout << "============================================\n";

    color(COLOR_YELLOW);

    cout << "1.  Add Student at Beginning\n";
    cout << "2.  Add Student at End\n";
    cout << "3.  Insert Student Between Records\n";
    cout << "4.  Remove Student from Beginning\n";
    cout << "5.  Remove Student from End\n";
    cout << "6.  Display Students (Forward)\n";
    cout << "7.  Display Students (Backward)\n";
    cout << "8.  Search Student by ID\n";
    cout << "9.  Update Student Information\n";
    cout << "10. Delete Student by ID\n";
    cout << "11. Count Total Students\n";
    cout << "12. Display All Student Records\n";
    cout << "13. Clear All Student Records\n";
    cout << "0.  Exit Application\n";

    color(COLOR_CYAN);
    cout << "--------------------------------------------\n";

    color(COLOR_WHITE);
}

// ========================================
// MAIN FUNCTION
// ========================================

int main()
{
    StudentList students;

    int choice;
    int id;
    int position;

    do
    {
        // Clear previous operation
        clearScreen();

        // Display fresh menu
        displayMenu();

        choice = readInt("Enter your choice: ", 0, 13);

        switch(choice)
        {
            case 1:
            {
                Student s = inputStudent();
                students.addBeginning(s);
                break;
            }

            case 2:
            {
                Student s = inputStudent();
                students.addEnd(s);
                break;
            }

            case 3:
            {
                if(students.getCount() < 2)
                {
                    color(COLOR_RED);
                    cout << "\nAt least two students are needed to insert between records.\n";
                    color(COLOR_WHITE);
                    break;
                }

                position = readInt(
                    "Enter insertion position (between existing records): ",
                    2,
                    students.getCount()
                );

                Student s = inputStudent();
                students.insertAtPosition(s, position);
                break;
            }

            case 4:
                students.removeBeginning();
                break;

            case 5:
                students.removeEnd();
                break;

            case 6:
                students.displayForward();
                break;

            case 7:
                students.displayBackward();
                break;

            case 8:
                id = readInt(
                    "Enter Student ID to search: ",
                    1, 999999999
                );
                students.searchStudent(id);
                break;

            case 9:
                id = readInt(
                    "Enter Student ID to update: ",
                    1, 999999999
                );
                students.updateStudent(id);
                break;

            case 10:
                id = readInt(
                    "Enter Student ID to delete: ",
                    1, 999999999
                );
                students.deleteStudent(id);
                break;

            case 11:
                students.displayCount();
                break;

            case 12:
                students.displayForward();
                break;

            case 13:
                students.clearAll();
                break;

            case 0:
            {
                color(COLOR_CYAN);
                cout << "\n============================================\n";
                cout << "          FINAL STUDENT RECORDS\n";
                cout << "============================================\n";

                students.displayForward();

                color(COLOR_GREEN);
                cout << "\nThank you for using the system!\n";
                cout << "Application closed successfully!\n";

                color(COLOR_WHITE);
                break;
            }
        }

        // Wait before clearing screen
        if(choice != 0)
        {
            color(COLOR_YELLOW);
            cout << "\n\nPress ENTER to continue...";
            color(COLOR_WHITE);

            cin.get();
        }

    } while(choice != 0);

    return 0;
}
