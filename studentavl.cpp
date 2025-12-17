#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* ================= STUDENT DIRECTORY (BST) ================= */
struct Student {
    int reg;          
    int password;     
    Student* left;
    Student* right;

    Student(int r, int p) {
        reg = r;
        password = p;
        left = right = NULL;
    }
};

class StudentAVL {
private:
    Student* root;

    Student* insert(Student* node, int reg, int password) {
        if (node == NULL)
            return new Student(reg, password);

        if (reg < node->reg)
            node->left = insert(node->left, reg, password);
        else if (reg > node->reg)
            node->right = insert(node->right, reg, password);

        return node; // simple BST, no rotations
    }

    Student* search(Student* node, int reg) {
        if (node == NULL || node->reg == reg)
            return node;

        if (reg < node->reg)
            return search(node->left, reg);
        else
            return search(node->right, reg);
    }

public:
    StudentAVL() {
        root = NULL;
    }

    void addStudent(int reg, int password) {
        root = insert(root, reg, password);
    }

    bool verifyStudent(int reg) {
        return (search(root, reg) != NULL);
    }

    bool verifyLogin(int reg, int password) {
        Student* s = search(root, reg);
        if (s == NULL)
            return false;
        return (s->password == password);
    }

    void displayStudent(int reg) {
        Student* s = search(root, reg);
        if (s == NULL)
            cout << "Student not found" << endl;
        else
            cout << "Reg: " << s->reg << ", Password: " << s->password << endl;
    }

    void loadFromFile(string filename) {
        ifstream fin(filename);
        if (!fin) {
            cout << filename << " not found!" << endl;
            return;
        }

        int r, p;
        while (fin >> r >> p)
            addStudent(r, p);

        fin.close();
    }
};

/* ================= STOPS (DOUBLY LINKED LIST) ================= */
struct Stop {
    string stopID;
    string stopName;
    int usageCount;
    Stop* next;
    Stop* previous;

    Stop(string id, string name) {
        stopID = id;
        stopName = name;
        usageCount = 0;
        next = previous = NULL;
    }
};

class StopDLL {
private:
    Stop* head;
    Stop* tail;

    Stop* findStop(string id) {
        Stop* temp = head;
        while (temp != NULL) {
            if (temp->stopID == id)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }

public:
    StopDLL() {
        head = tail = NULL;
    }

    void addStop(string id, string name) {
        Stop* temp = new Stop(id, name);

        if (head == NULL) {
            head = tail = temp;
            return;
        }

        temp->next = head;
        head->previous = temp;
        head = temp;
    }

    bool validateStop(string id) {
        return (findStop(id) != NULL);
    }

    string getStopName(string id) {
        Stop* temp = findStop(id);
        if (temp == NULL)
            return "Invalid Stop";
        return temp->stopName;
    }

    void incrementStopUsage(string id) {
        Stop* temp = findStop(id);
        if (temp != NULL)
            temp->usageCount++;
    }

    void displayAllStops() {
        Stop* temp = head;
        while (temp != NULL) {
            cout << "Stop ID: " << temp->stopID
                 << ", Name: " << temp->stopName
                 << ", Usage: " << temp->usageCount << endl;
            temp = temp->next;
        }
    }

    int calculateDistance(string id1, string id2) {
        Stop* start = findStop(id1);
        Stop* end   = findStop(id2);

        if (start == NULL || end == NULL)
            return -1;

        int distance = 0;
        Stop* temp = start;
        while (temp != NULL) {
            if (temp == end)
                return distance;
            temp = temp->next;
            distance++;
        }

        distance = 0;
        temp = start;
        while (temp != NULL) {
            if (temp == end)
                return distance;
            temp = temp->previous;
            distance++;
        }

        return -1;
    }
};

/* ================= MAIN FUNCTION ================= */
int main() {
    StudentAVL students;
    StopDLL stops;

    // Load students from file
    students.loadFromFile("students.txt");

    // Add stops
    stops.addStop("S1", "Library");
    stops.addStop("S2", "FCSE");
    stops.addStop("S3", "FBS");
    stops.addStop("S4", "Girls Hostel");

    // Test student login
    int reg, pass;
    cout << "Enter Registration Number: ";
    cin >> reg;
    cout << "Enter Password: ";
    cin >> pass;

    if (students.verifyLogin(reg, pass))
        cout << "Login Successful!" << endl;
    else
        cout << "Invalid Registration or Password!" << endl;

    // Display all stops
    cout << "\nAll Stops:\n";
    stops.displayAllStops();

    // Test distance
    cout << "\nDistance from Library to Girls Hostel: "
         << stops.calculateDistance("S1", "S4") << " stops" << endl;

    // Increment usage test
    stops.incrementStopUsage("S1");
    stops.incrementStopUsage("S3");

    cout << "\nStops after incrementing usage:\n";
    stops.displayAllStops();

    return 0;
}
