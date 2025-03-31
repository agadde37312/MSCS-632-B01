#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

// Constants
const int MAX_WORK_DAYS = 5;
const int MIN_EMPLOYEES_PER_SHIFT = 2;
const vector<string> DAYS = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
const vector<string> SHIFTS = {"Morning", "Afternoon", "Evening"};

// Data structures
struct Employee {
    string name;
    map<string, map<string, int>> preferences;   // Day -> Shift -> Priority (1, 2, 3)
    int daysWorked = 0;
};

map<string, map<string, vector<string>>> schedule;    // Final schedule: Day -> Shift -> Employees
vector<Employee> employees;                           // List of employees

// Function to initialize the schedule with empty shifts
void initializeSchedule() {
    for (const string& day : DAYS) {
        schedule[day] = {};
        for (const string& shift : SHIFTS) {
            schedule[day][shift] = {};
        }
    }
}

// Function to add employee with shift preferences
void addEmployee() {
    Employee emp;
    cout << "Enter employee name: ";
    cin >> emp.name;

    for (const string& day : DAYS) {
        cout << "Enter " << emp.name << "'s shift preferences for " << day << " (1 = highest, 2 = Medium, 3 = lowest):\n";

        int morning, afternoon, evening;
        cout << "  Morning priority: ";
        cin >> morning;
        cout << "  Afternoon priority: ";
        cin >> afternoon;
        cout << "  Evening priority: ";
        cin >> evening;

        emp.preferences[day]["Morning"] = morning;
        emp.preferences[day]["Afternoon"] = afternoon;
        emp.preferences[day]["Evening"] = evening;
    }

    employees.push_back(emp);
    cout << emp.name << " added successfully with preferences.\n";
}

// Function to assign shifts based on employee preferences
void assignShifts() {
    srand(time(0));  // Seed for randomness

    for (const string& day : DAYS) {
        for (const string& shift : SHIFTS) {
            vector<Employee*> availableEmployees;

            // Collect employees who prefer this shift and have not worked 5 days
            for (auto& emp : employees) {
                if (emp.daysWorked < MAX_WORK_DAYS && find(schedule[day][shift].begin(), schedule[day][shift].end(), emp.name) == schedule[day][shift].end()) {
                    availableEmployees.push_back(&emp);
                }
            }

            // Sort by preference for the current shift
            sort(availableEmployees.begin(), availableEmployees.end(), [&](Employee* a, Employee* b) {
                return a->preferences[day][shift] < b->preferences[day][shift];
            });

            // Assign employees based on preference
            for (auto* emp : availableEmployees) {
                if (emp->daysWorked < MAX_WORK_DAYS && schedule[day][shift].size() < MIN_EMPLOYEES_PER_SHIFT) {
                    schedule[day][shift].push_back(emp->name);
                    emp->daysWorked++;
                }
            }
        }
    }
    cout << "\nShifts assigned successfully.\n";
}

// Function to resolve conflicts by manager
void resolveConflicts() {
    random_device rd;
    mt19937 g(rd());  // Use Mersenne Twister for better randomization

    cout << "\n=== Conflict Resolution Required ===\n";

    for (const string& day : DAYS) {
        for (const string& shift : SHIFTS) {
            if (schedule[day][shift].size() < MIN_EMPLOYEES_PER_SHIFT) {
                cout << "\nConflict detected: " << day << " - " << shift;
                cout << "\nCurrent employees: ";
                for (const string& emp : schedule[day][shift]) {
                    cout << emp << " ";
                }
                cout << "\nInsufficient employees for this shift." << endl;

                // Ask the manager if they want to resolve the conflict
                char choice;
                cout << "Do you want to randomly assign available employees? (y/n): ";
                cin >> choice;

                if (choice == 'y' || choice == 'Y') {
                    vector<Employee*> available;

                    for (auto& emp : employees) {
                        if (emp.daysWorked < MAX_WORK_DAYS) {
                            available.push_back(&emp);
                        }
                    }

                    if (available.size() < 2) {
                        cout << "Not enough employees available.\n";
                        continue;
                    }

                    // Use std::shuffle instead of deprecated random_shuffle
                    shuffle(available.begin(), available.end(), g);

                    // Add missing employees randomly
                    while (schedule[day][shift].size() < MIN_EMPLOYEES_PER_SHIFT && !available.empty()) {
                        Employee* randomEmp = available.back();
                        available.pop_back();
                        schedule[day][shift].push_back(randomEmp->name);
                        randomEmp->daysWorked++;
                        cout << "Assigned " << randomEmp->name << " to fill the empty slot." << endl;
                    }
                } else {
                    cout << "\nSkipping conflict resolution for this shift." << endl;
                }
            }
        }
    }
}

// Function to display the final weekly schedule
void displaySchedule() {
    cout << "\n===== Weekly Employee Schedule =====\n";

    for (const auto& day : schedule) {
        cout << "\n" << day.first << ":\n";
        for (const auto& shift : day.second) {
            cout << "  " << shift.first << ": ";
            if (shift.second.empty()) {
                cout << "No Employees Assigned\n";
            } else {
                for (const string& emp : shift.second) {
                    cout << emp << " ";
                }
                cout << "\n";
            }
        }
    }
}

// Function to let manager add employees
void addEmployees() {
    int numEmployees;
    cout << "Enter the number of employees: ";
    cin >> numEmployees;

    for (int i = 0; i < numEmployees; ++i) {
        addEmployee();
    }
}

// Main program menu
int main() {
    initializeSchedule();

    int choice;

    do {
        cout << "\n===== Employee Shift Scheduler Menu =====\n";
        cout << "1. Add Employees\n";
        cout << "2. Assign Shifts\n";
        cout << "3. Resolve Conflicts\n";
        cout << "4. Display Schedule\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployees();
                break;
            case 2:
                assignShifts();
                break;
            case 3:
                resolveConflicts();
                break;
            case 4:
                displaySchedule();
                break;
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
