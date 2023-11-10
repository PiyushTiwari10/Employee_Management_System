#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>
#include <conio.h>

using namespace std;

class Employee {
private:
    string name; 
    string id;
    string designation;
    int age;
    long ctc;
    int experience;
    string address;

public:
    Employee(string n, string i, string d, int a, int c, int e,string addr)
        : name(n),  id(i), designation(d), age(a), ctc(c), experience(e),address(addr) {}

     const string& getId() const {
        return id;
    }

    const string& getName() const {
        return name;
    }

   
    const string& getaddress() const {
        return address;
    }

    const string& getDesignation() const {
        return designation;
    }

    void displayDetails() const {
        cout << "Name: " << name << "\n";
 
        cout << "ID: " << id << "\n";
       
        cout << "Designation: " << designation << "\n";
        cout << "Age(in Years): " << age << "\n";
        cout << "CTC(in LPA): " << ctc << "\n";
        cout << "Experience(in Years): " << experience << "\n";
         cout << "Address: " << address<< "\n";
    }

    void setDesignation(const string& newDesignation) {
        designation = newDesignation;
    }

    void setCtc(int newCtc) {
        ctc = newCtc;
    }
};

class EmployeeManagementSystem {
private:
    vector<Employee> employees;

    // Utility functions
     void waitForEnter() {
         
        cout << "\n\n\n Press enter to go back\n\n";
        cin.get();
        cin.get();
    }
     // Check if the employee ID is unique
    bool isUniqueID(const string& checkId) {
        for (const Employee& emp : employees) {
            if (emp.getId() == checkId) {
                return false;
            }
        }
        return true;
    }
    void sortEmployeesByName() {
        sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
            return a.getName() < b.getName();
        });
    }
    

    // Login procedure
    bool login() {
        string username = "user";
        string password = "1234";
        string enteredUsername, enteredPassword;

        clearScreen();
        animateText("\n\n\n\n\t\t\t\t\t**---------------EMPLOYEE MANAGEMENT SYSTEM---------------**");
        animateText("\n\n\t\t\t\t\tEnter Admin's Username: ");
        cin >> enteredUsername;
        animateText("\n\n\t\t\t\t\tEnter Your Password: ");

        enteredPassword = "";
        char ch;
        ch = _getch();
        while (ch != 13) {
            enteredPassword.push_back(ch);
            cout << '*';
            ch = _getch();
        }
        // Clear the newline character from the input stream
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');

        return (enteredUsername == username && enteredPassword == password);
    }

    void clearScreen() {
        system("cls");
    }


   


    void showDetails() {
        system("cls");
        string checkId;
        cout << "\n\nEnter Employee ID: ";
        cin >> checkId;

        for (const Employee& emp : employees) {
            if (emp.getId() == checkId) {
                emp.displayDetails();
                cout << "---------------------\n";
            }
        }
        waitForEnter();
    }

    void editExisting() {
          system("cls");
    cout << "\n\t    Modify Employee Details\n";
    cout << "---------------------------------------";
    string empId;
    cout << "\nEnter employee ID: ";
    cin >> empId;

    bool found = false;
    for (Employee& emp : employees) {
        if (emp.getId() == empId) {
            found = true;
            cout << "Enter new designation: ";
            string newDesignation;
            cin.ignore();
            getline(cin, newDesignation);
            cout << "Enter new CTC: ";
            int newCtc;
            cin >> newCtc;
            emp.setDesignation(newDesignation);
            emp.setCtc(newCtc);
            break;
        }
    }

    if (found) {
        cout << "\nEmployee details updated successfully";
    } else {
        cout << "\nEmployee not found";
    }

    waitForEnter();
}

    void addNewEmployee() {
        system("cls");
        cout << "\n----------------------------------------" ;
        cout << "\n Enter  Name of Employee: ";
        string name;
        cin.ignore();
        getline(cin,name);
 

        cout << "\n----------------------------------------";
        string id;
        do {
            cout << "\n Enter Employee ID [max 4 digits]: ";
            cin >> id;
            if (!isUniqueID(id)) {
                cout << "ID is not unique. Please choose a different one.\n";
            }
        } while (!isUniqueID(id));

        cout << "\n----------------------------------------";
        cout << "\n Enter Designation: ";
        string designation;
        cin.ignore();
        getline(cin, designation);


        cout << "\n----------------------------------------";
        cout << "\n Enter Employee Age(in Years): ";
        int age;
        cin >> age;

        cout << "\n----------------------------------------";
        cout << "\n Enter Employee CTC(in LPA): ";
        int ctc;
        cin >> ctc;

        cout << "\n----------------------------------------";
        cout << "\n Enter Employee Experience(in Years): ";
        int experience;
        cin >> experience;
         

        cout << "\n----------------------------------------";
        cout << "\n Enter Employee  Address: ";
        string address;
        cin.ignore();
        getline(cin,address);

        char ch;
        cout << "\nEnter 'y' to save the above information\n";
        cin >> ch;

        if (ch == 'y') {
            employees.emplace_back(name,  id, designation, age, ctc, experience,address);
            cout << "\nNew Employee has been added to the database\n";
        } else {
            addNewEmployee();
        }
        waitForEnter();
    }

    void deleteEmployeeDetails() {
        system("cls");
       
        string checkId;
        cout << "\nEnter Employee Id To Remove: ";
        cin >> checkId;

        char ch;
        cout << "\n\n\n\n\nCONFIRMATION\nEnter 'y' To Confirm Deletion \n";
        cin >> ch;

        if (ch == 'y') {
            employees.erase(
                remove_if(employees.begin(), employees.end(), [checkId](const Employee& emp) {
                    return emp.getId() == checkId;
                }),
                employees.end()
            );
            cout << "\nRemoved Successfully\n";
        } else {
            deleteEmployeeDetails();
        }
         waitForEnter();
        
    }

public:


     void animateText(const string& text) {
        for (char c : text) {
            cout << c;
            Sleep(50); 
            }
    }


     
    void options() {
         bool loggedIn = login();
        
        if (!loggedIn) {
            cout << "Access Denied\n";
            return;
        }
 

        while (true) {
            system("cls");

            cout << "\n\t\t\t>>>>>>>>>  EMPLOYEE MANAGEMENT SYSTEM  <<<<<<<<<";
            cout << "\n";
            cout << "\n\t\t\t------------------------------------------------";
            cout << "\n\t\t\tENTER   1:   To Add New Employee Details";
            cout << "\n\t\t\t------------------------------------------------";
            cout << "\n\t\t\tENTER   2:   To View List of Employees";
            cout << "\n\t\t\t------------------------------------------------";
            cout << "\n\t\t\tENTER   3:   To View Employee Details ";
            cout << "\n\t\t\t------------------------------------------------";
            cout << "\n\t\t\tENTER   4:   To Modify Existing Employee Details";
            cout << "\n\t\t\t------------------------------------------------";
            cout << "\n\t\t\tENTER   5:   To Remove an Employee Details";
            cout << "\n\t\t\t------------------------------------------------";
            cout << "\n\t\t\tENTER   0:   To Exit";
            cout << "\n\t\t\t------------------------------------------------";
            cout << "\n\n\t\t\t   Please Enter Your Choice: ";

            int choice;
            cin >> choice;
            switch (choice) {
                case 0:
                    system("CLS");
                    cout << "\n\nEMPLOYEE MANAGEMENT SYSTEM \n\n Brought To You By  SAP Developers\n\n ";
                    Sleep(10);
                    return;
                case 1:
                    addNewEmployee();
                    
                    break;
                case 2:
                    sortEmployeesByName();
                    listEmployees();
                    
                    break;
                case 3:
                    showDetails();
                    
                    break;
                case 4:
                    editExisting();
                    break;
                case 5:
                    deleteEmployeeDetails();
                    break;
                default:
                    cout << "\n Sorry! I don't understand that! \n";
                    break;
            }
        }
    }
    

    void listEmployees() {
    system("cls");
    cout << "\n\t      List of Employees\n";
    cout << "------------------------------------------------------";
    cout << "\n\t NAME        |     ID     |     DESIGNATION\n";
    cout << "------------------------------------------------------";
    for (const Employee& emp : employees) {
        cout << "\n" << emp.getName() << "\t\t" << emp.getId() << "\t\t" << emp.getDesignation();
    }
    waitForEnter();
}
};

 

int main() {
    EmployeeManagementSystem ems;

    ems.options();
      // Add a closing animation
    system("cls");
    ems.animateText("\n\n\n\n\n\t\t\t\t\t**------EXITING EMPLOYEE MANAGEMENT SYSTEM------**\n\n");
    ems.animateText("\n\n\n\n\n\t\t\t\t\t**------DEVELOPED BY SAP DEVELOPERS------**\n\n");
    Sleep(1000); // Wait for a moment to display the animation

    return 0;
}