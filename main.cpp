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

    void addEmployee(int id,string name,string des, double sal)
    {
        Employee *newEmp = new Employee{id, name, des, sal, nullptr};

        if(head==nullptr)
        {
            head = newEmp;
        }
        else
        {
            Employee *temp = head;
            while(temp->next!=nullptr)
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
            
           cout << "ID: " << temp->id << " | " << temp->name << " (" << temp->designation << ")\n"
                 << "   Gross: Rs." << temp->salary << " | Tax (10%): Rs." << tax 
                 << " | Net Pay: Rs." << netSalary << "\n\n";
        }
    }
};

int main()
{
    return 0;
}