#include<iostream>
#include<string>
#include<fstream>
using namespace std;
struct Employee
{
    int emp_id;
    string name;
    string designation;
    double salary;
    Employee *next;
};

class Payroll
{
    private:
        Employee *head;


    public:
    Payroll()
    {
        head = nullptr;
    }

  void addEmployee(int id, const string &name, const string &des, double sal)
{
    // 1. Check if an employee with this ID already exists
    Employee *temp = head;
    while (temp != nullptr)
    {
        if (temp->id == id)
        {
            cout << "Error: Employee with ID " << id << " already exists." << endl;
            return;
        }
        temp = temp->next;
    }

    // 2. Allocate memory for the new node
    Employee *newEmp = new Employee{id, name, des, sal, nullptr};

    // 3. Insert into the list
    if (head == nullptr)
    {
        head = newEmp;
    }
    else
    {
        temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newEmp;
    }
}
    void deleteEmployee(int id)
    {
        if(head==nullptr)
        {
            cout << "Error: No employee records found." << endl;
            return;
        }
        if(head->emp_id==id)
        {
            Employee *toDel = head;
            head = head->next;
            delete toDel;
            cout << "Employee with ID " << id << " deleted successfully." << endl;
            return;
        }
        Employee *temp = head;
        while(temp->next!=nullptr && temp->next->emp_id!=id)
        {
            temp = temp->next;
        }
        if(temp->next!=nullptr)
        {
            Employee *toDel = temp->next;
            temp->next = temp->next->next;
            delete toDel;
            cout << "Employee with ID " << id << " deleted successfully." << endl;
        }
        else
        {
            cout << "Error: Employee with ID" << id << " not found." << endl;
        }
    }
    void updateEmployee(int id, string name, string newdes, double newsal)
    {
        Employee *temp = head;
        while(temp!=nullptr)
        {
            if(temp->emp_id==id)
            {
                temp ->designation = newdes;
                temp ->salary = newsal;
                cout << "Employee with ID " << id << " updated successfully." << endl;
                return;
            }
            temp = temp->next;
        }
        cout<<"Error: Employee with ID " << id << " not found." << endl;
    }
    void viewEmployee(int id)
    {
        Employee *temp = head;
        while(temp!=nullptr)
        {
            if(temp->emp_id==id)
            {
                cout << "\n-----Employee Details-----\n";
                cout << "Emplpoyee ID: " << temp->emp_id << endl;
                cout << "Name: " << temp->name << endl;
                cout << "Designation: " << temp->designation << endl;
                cout << "Salary: " << temp->salary << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Error: Employee with ID " << id << " not found." << endl;
    }
    void generateReport()
    {
        if(head==nullptr)
        {
            cout << "Error: No employee records found." << endl;
            return;
        }
        cout << "\n=====Monthly Payroll Report=====\n";
        Employee *temp = head;
        double totalSalary = 0;

        while(temp!=nullptr)
        {
            double tax = temp->salary * 0.10;
            double netSalary = temp->salary - tax;
            totalSalary += netSalary;
            
           cout << "ID: " << temp->emp_id << " | " << temp->name << " (" << temp->designation << ")\n"
                 << "   Gross: Rs." << temp->salary << " | Tax (10%): Rs." << tax 
                 << " | Net Pay: Rs." << netSalary << "\n\n";

           temp = temp->next;
        }
        cout << "====================================\n";
        cout << "Total Net Salary is Rs. " << totalSalary << endl;
    }
    void saveToFile()
    {
        ofstream outFile("payroll_data.txt");
        if(!outFile)
        {
            cout << "Error: Unable to open file for writing." << endl;
            return;
        }
        Employee *temp = head;
        while(temp!=nullptr)
        {
            outFile << temp->emp_id << "," << temp->name << "," << temp->designation << "," << temp->salary << "\n";
            temp = temp->next;
        }
        outFile.close();
        cout << "Data successfully saved." << endl;
    }
    void loadFromFile()
    {
        ifstream inFile("payroll_data.txt");
        if(!inFile)
        {
            cout << "Error: No previous data found. Starting fresh." << endl;
            return;
        }
        int id;
        string name, des;
        double sal;
        while(inFile>>id)
        {
            inFile.ignore();
            getline(inFile, name, ',');
            getline(inFile, des, ',');
            inFile >> sal;

            addEmployee(id, name, des, sal);
        }
        inFile.close();
        cout << "\n----Data loaded successfully----\n";
    }
};

int main()
{
    Payroll company;
    int choice, id;
    string name, des;
    double sal;
    
    company.loadFromFile();

    while(true){
        cout <<"\n=== PAYROLL SYSTEM MENU ===\n";
        cout << "1. Add Employee\n";
        cout << "2. View Employee\n";
        cout << "3. Update Employee\n";
        cout << "4. Delete Employee\n";
        cout << "5. Generate Report\n";
        cout << "6. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
    
  switch (choice){
case 1:
cout << "Enter ID:";
cin >> id;
cin.ignore();

cout << "Enter Name :";
getline(cin, name);

cout << "Enter Designation :";
getline(cin, des);

cout << "Enter Salary :";
cin >> sal;

company.addEmployee(id, name , des , sal);
break;


case2:
cout << "Enter Employee ID to view: ";
cin >> id;
company.viewEmployee(id);
break;

case 3:
cout <<"Enter Employee ID to update: ";
cin >> id;
cin.ignore();

cout << "Enter New Designation: ";
getline(cin, des);

cout << "Enter New Salary: ";
cin >> sal;

company.updateEmployee(id, name, des, sal);

break;

case 4:
cout << "Enter Employee ID to delete: ";
cin >> id;
company.deleteEmployee(id);
break;

case 5:
company.generateReport();
break;

case 6:
company.saveToFile();
cout << "Exiting system. best of luck with your mini-project !\n";
return 0;

default:
cout << "Invalid choice. Please try again.\n";
    }
    }

    return 0;
}