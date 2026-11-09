#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cstdlib>

// ==========================================
// 1. CROSS-PLATFORM INCLUDES
// ==========================================
#ifdef _WIN32
    // Windows (32-bit and 64-bit)
    #include <windows.h>
#else
    // Android, Linux, Mac
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

using namespace std;

// ==========================================
// 2. COLOR DEFINITIONS
// ==========================================
#define bk_white "\033[30;47m" 
#define w_bl "\033[0;40m"       
#define green "\033[32m"
#define red "\033[31m"
#define cyan "\033[36m"
#define yellow "\033[33m"   
#define bright_yellow "\033[93m" 

#define reset "\033[0m"
#define bold "\033[1m"
#define bg_blue "\033[0;44m"    
// ==========================================
// 3. DATA STRUCTURES
// ==========================================
struct Student {
    string id;
    string name;
    string dept;
    int year;
    float gpa;
};

struct Node {
    Student data;
    Node* next;
    Node* prev;
};

Node* head = nullptr;
Node* tail = nullptr;

// ==========================================
// 4. CROSS-PLATFORM HELPER FUNCTIONS
// ==========================================

void clearScreen() { 
    #ifdef _WIN32
        system("cls"); // Windows clear screen
    #else
        cout << "\033c" << "\033[2J\033[H" << flush; // Android/Linux clear screen
    #endif
}

int getScreenWidth() {
    #ifdef _WIN32
        // Windows way to get width
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    #else
        // Android/Linux way to get width
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_col > 0 ? w.ws_col : 80; // Fallback to 80
    #endif
}

void enableWindowsColors() {
    #ifdef _WIN32
        // Force Windows CMD to accept ANSI color codes
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    #endif
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

bool idExists(string id) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.id == id) return true;
        temp = temp->next;
    }
    return false;
}

int getListLength() {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

// ==========================================
// 5. UI FUNCTIONS
// ==========================================
void showHeader(int w) {
    string title = "STUDENTS MANAGEMENT SYSTEM.";
    int leftSpaceTitle = (w - title.length()) / 2;
    int rightSpaceTitle = w - title.length() - leftSpaceTitle;

    cout << bold << bg_blue << string(w, '=') << "\n";
    cout << setfill(' ') << setw(leftSpaceTitle) << "" << title << setw(rightSpaceTitle) << "" << "\n";
    cout << string(w, '=') << "\n" << reset;
}

void showMenu(int w) {
    string item1 = " 1. Student Record Management";
    string item2 = " 2. Student Operation History (Stack)";
    string item3 = " 3. Student Service Requests (Queue)";
    string item4 = " 4. Student Search and Indexing (BST)";
    string item5 = " 5. Display All Student Records";
    string item6 = " 6. System Statistics";
    string item0 = " 0. Exit";
    
    cout << bk_white;
    cout << item1 << setw(w - item1.length()) << "" << "\n";
    cout << item2 << setw(w - item2.length()) << "" << "\n";
    cout << item3 << setw(w - item3.length()) << "" << "\n";
    cout << item4 << setw(w - item4.length()) << "" << "\n";
    cout << item5 << setw(w - item5.length()) << "" << "\n";
    cout << item6 << setw(w - item6.length()) << "" << "\n";
    cout << item0 << setw(w - item0.length()) << "" << reset << "\n";
}

// --- STAGE 1: ADD STUDENT ---
void showItem1(int w) {
    clearScreen();
    showHeader(w);
    
    cout << "\n--- ADD STUDENT ---\n";
    cout << "1. Add at the Beginning\n";
    cout << "2. Add at the End\n";
    cout << "3. Insert at Specific Position\n";
    cout << "0. Back\n";
    
    int posChoice;
    cout << "Enter choice: ";
    cin >> posChoice;
    
    if (posChoice == 0) return;
    
    if (posChoice < 1 || posChoice > 3) {
        cout << red << "\n[ERROR] Invalid choice!\n" << reset;
        pauseScreen();
        return;
    }

    Student newStudent;
    cout<<yellow << "\nEnter Student ID: "<<reset;
    cin >> newStudent.id;
    
    if (idExists(newStudent.id)) {
        cout << red << "\n[ERROR] Student ID " << newStudent.id << " already exists!\n" << reset;
        pauseScreen();
        return;
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    
    cout<<yellow << "Enter Full Name: "<<reset;
    getline(cin, newStudent.name);
    cout<<yellow << "Enter Department: "<<reset;
    getline(cin, newStudent.dept);
    
    // --- YEAR VALIDATION (1 to 5) ---
    while (true) {
        cout<<yellow << "Enter Year of Study (1-5): "<<reset;
        cin >> newStudent.year;
        
        // Check if input failed (e.g., user typed a letter)
        if (cin.fail()) {
            cin.clear(); // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
            cout << red << "[ERROR] Invalid input. Please enter a number.\n" << reset;
        } 
        else if (newStudent.year < 1 || newStudent.year > 5) {
            cout << red << "[ERROR] Year must be between 1 and 5.\n" << reset;
        } 
        else {
            break; // Valid input, exit the loop
        }
    }

    // --- GPA VALIDATION (1.0 to 4.0) ---
    while (true) {
        cout<<yellow << "Enter GPA (1.0 - 4.0): "<<reset;
        cin >> newStudent.gpa;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << red << "[ERROR] Invalid input. Please enter a decimal number.\n" << reset;
        } 
        else if (newStudent.gpa < 1.0 || newStudent.gpa > 4.0) {
            cout << red << "[ERROR] GPA must be between 1.0 and 4.0.\n" << reset;
        } 
        else {
            break; // Valid input, exit the loop
        }
    }

    Node* newNode = new Node;
    newNode->data = newStudent;
    
    if (posChoice == 1) {
        newNode->prev = nullptr;
        newNode->next = head;
        if (head != nullptr) head->prev = newNode;
        else tail = newNode; 
        head = newNode;
        cout << green << "\n[SUCCESS] Student added at the beginning.\n" << reset;
    } 
    else if (posChoice == 2) {
        newNode->next = nullptr;
        newNode->prev = tail;
        if (tail != nullptr) tail->next = newNode;
        else head = newNode; 
        tail = newNode;
        cout << green << "\n[SUCCESS] Student added at the end.\n" << reset;
    } 
    else if (posChoice == 3) {
        int pos;
        int len = getListLength();
        cout << "\nCurrent List Size: " << len;
        cout << "\nEnter Position (1 to " << len + 1 << "): ";
        cin >> pos;
        
        if (pos < 1 || pos > len + 1) {
            cout << red << "\n[ERROR] Invalid position!\n" << reset;
            delete newNode; 
            pauseScreen();
            return;
        }
        
        if (pos == 1) {
            newNode->prev = nullptr;
            newNode->next = head;
            if (head != nullptr) head->prev = newNode;
            else tail = newNode;
            head = newNode;
        } else if (pos == len + 1) {
            newNode->next = nullptr;
            newNode->prev = tail;
            if (tail != nullptr) tail->next = newNode;
            else head = newNode;
            tail = newNode;
        } else {
            Node* temp = head;
            for (int i = 1; i < pos - 1; i++) temp = temp->next;
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
            temp->next = newNode;
        }
        cout << green << "\n[SUCCESS] Student inserted at position " << pos << ".\n" << reset;
    }
    
    pauseScreen();
}

// --- NEW FUNCTION FOR OPTION 5: DISPLAY ALL RECORDS ---
void showItem5(int w) {
    clearScreen();
    showHeader(w);
    
    if (head == nullptr) {
        cout << red << "\n[INFO] The student list is currently empty.\n" << reset;
        pauseScreen();
        return;
    }

    cout << "\n--- DISPLAY STUDENT RECORDS ---\n";
    cout << "1. Display Forward (Head to Tail)\n";
    cout << "2. Display Backward (Tail to Head)\n";
    cout << "0. Back\n";
    
    int dirChoice;
    cout << "Enter choice: ";
    cin >> dirChoice;
    
    if (dirChoice == 0) return;
    
    if (dirChoice < 1 || dirChoice > 2) {
        cout << red << "\n[ERROR] Invalid choice!\n" << reset;
        pauseScreen();
        return;
    }

    // --- UNIVERSAL COLOR SETUP ---
    string bg_gray  = "\033[100m"; 
    string text_wht = "\033[97m";  
    string text_cyan= "\033[96m";  
    string text_bold= "\033[1m";   

    cout << "\n";
    
    // --- EXACT UNIVERSAL MATH ---
    // We use exactly 5 columns. 
    // Each column has "| " (2 chars) on the left.
    // The last column has "|" (1 char) on the right.
    // Total border characters = (5 * 2) + 1 = 11 characters.
    int borderSpaces = 11; 
    int usableWidth = w - borderSpaces;
    
    // Just in case the screen is incredibly tiny, prevent negative numbers
    if (usableWidth < 10) usableWidth = 10;

    // Distribute widths perfectly based on percentages
    int wID   = usableWidth * 0.12; // 12% for ID
    int wYear = usableWidth * 0.10; // 10% for Year
    int wGPA  = usableWidth * 0.12; // 12% for GPA
    // Name and Dept share the remaining 66%
    int wName = usableWidth * 0.30; // 30% for Name
    int wDept = usableWidth - wID - wName - wYear - wGPA; // The rest goes to Dept

    // 1. Print Top Border
    cout << bg_gray << text_wht << string(w, '-') << "\n";
    
    // 2. Print Header
    cout << bg_gray << text_bold << text_cyan;
    cout << left 
         << "| " << setw(wID)   << "ID" 
         << "| " << setw(wName) << "Name" 
         << "| " << setw(wDept) << "Dept" 
         << "| " << setw(wYear) << "Yr" 
         << "| " << setw(wGPA)  << "GPA" << "|\n"; 
         
    // 3. Print Header Divider
    cout << bg_gray << text_wht << string(w, '-') << "\n";

    // 4. Print Rows
    cout << bg_gray << text_wht; 
    
    Node* temp = (dirChoice == 1) ? head : tail;
    while (temp != nullptr) {
        // Ensure strings don't overflow columns (safely cut them)
        string safeID = temp->data.id.length() > wID ? temp->data.id.substr(0, wID) : temp->data.id;
        string safeName = temp->data.name.length() > wName ? temp->data.name.substr(0, wName) : temp->data.name;
        string safeDept = temp->data.dept.length() > wDept ? temp->data.dept.substr(0, wDept) : temp->data.dept;
        
        cout << left 
             << "| " << setw(wID)   << safeID
             << "| " << setw(wName) << safeName
             << "| " << setw(wDept) << safeDept
             << "| " << setw(wYear) << temp->data.year 
             << "| " << setw(wGPA)  << fixed << setprecision(1) << temp->data.gpa << "|\n";
             
        temp = (dirChoice == 1) ? temp->next : temp->prev;
    }
    
    // 5. Print Bottom Border
    cout << string(w, '-') << "\n" << reset;
    
    cout << green << "\n[SUCCESS] Displayed " << getListLength() << " student(s).\n" << reset;
    pauseScreen();
}
void showItem6(int w) {
    clearScreen();
    showHeader(w);
    
    cout << "\n--- SYSTEM STATISTICS ---\n\n";
    
    int totalStudents = getListLength();
    int pendingRequests = 0; 
    int historyEntries = 0;
    int bstHeight = 0;

    cout << cyan << "Main Data Structures:" << reset << "\n";
    cout << left << setw(30) << "Total Students (DLL):" << totalStudents << "\n\n";
    
    cout << cyan << "System Status:" << reset << "\n";
    cout << left << setw(30) << "Pending Requests (Queue):" << pendingRequests << "\n";
    cout << left << setw(30) << "History Entries (Stack):" << historyEntries << "\n";
    cout << left << setw(30) << "BST Height:" << bstHeight << "\n";
    
    cout << "\n" << string(w, '-') << "\n";
    cout << green << "[INFO] Stage 2 and 3 structures will appear here once integrated.\n" << reset;
    
    pauseScreen();
}


// ==========================================
// 6. MAIN PROGRAM
// ==========================================
int main() {
    // 1. Enable colors if on Windows
    enableWindowsColors();
    
    // 2. Get screen width automatically based on OS
    int screenWidth = getScreenWidth();
    
    int prompt;
     
    do {
        clearScreen();
        showHeader(screenWidth);
        showMenu(screenWidth);
        
        cout << "\nEnter your choice: ";
        cin >> prompt;
        
        switch(prompt) {
            case 1: showItem1(screenWidth); break;
            case 5: showItem5(screenWidth); break;
            case 6: showItem6(screenWidth); break;
            case 0: cout << green << "Exiting system...\n" << reset; break;
            default:
                cout << red << "\n[ERROR] Invalid choice! (Feature coming soon)\n" << reset;
                pauseScreen();
                break;
        }
        
    } while(prompt != 0);
    
    return 0;
}