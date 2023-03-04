#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class Employee 
{

public:
    Employee(std::string _firstName, std::string _lastName, int _age)
        : firstName{ _firstName }, lastName{ _lastName }, age{ _age } {}

    // Getters and setters for the private fields
    std::string getFirstName() { return firstName; }

    void setFirstName(std::string _firstName) { firstName = _firstName; }

    std::string getLastName() { return lastName; }

    void setLastName(std::string _lastName) { lastName = _lastName; }

    int getAge() {  return age; }

    void setAge(int _age) { age = _age; }

    // ¬ывод данных
    friend std::ostream& operator<<(std::ostream& os, Employee& employee)
    {
        os << employee.getLastName() << ", " << employee.getFirstName() << " (" << employee.getAge() << ")" << std::endl;
        return os;
    }
protected:
    std::string firstName;
    std::string lastName;
    int age;
};

// „тение данных с файла
void readEmployeesFromFile(std::vector<Employee>& employees, std::string fileName)
{
    std::ifstream inputFile(fileName);
    if (inputFile.is_open())
    {
        while (!inputFile.eof())
        {
            std::string firstName, lastName;
            int age;
            inputFile >> firstName >> lastName >> age;
            employees.push_back(Employee(firstName, lastName, age));
        }
        inputFile.close();
    }
}

// запись данных о сотруднике в файл
void writeEmployeesToFile(std::vector<Employee>& employees, std::string fileName)
{
    std::ofstream outputFile(fileName);

    if (outputFile.is_open())
    {
        for (Employee employee : employees)
            outputFile << employee.getFirstName() << " "
            << employee.getLastName() << " "
            << employee.getAge() << std::endl;

        outputFile.close();
    }
}

// создание сотрудника
void addEmployee(std::vector<Employee>& employees) 
{
    std::string firstName, lastName;
    int age;
    std::cout << "Enter the employee's first name: ";
    std::cin >> firstName;
    std::cout << "Enter the employee's last name: ";
    std::cin >> lastName;
    std::cout << "Enter the employee's age: ";
    std::cin >> age;
    employees.push_back(Employee(firstName, lastName, age));
    std::cout << "Employee added successfully." << std::endl;
}

// редактирование информации о сотруднике
void editEmployee(std::vector<Employee>& employees)
{
    std::string lastName;
    std::cout << "Enter the employee's last name: ";
    std::cin >> lastName;
    for (Employee& employee : employees)
    {
        if (employee.getLastName() == lastName)
        {
            std::string firstName;
            int age;
            std::cout << "Enter the employee's new first name (or leave blank to keep the same): ";
            std::cin.ignore();
            getline(std::cin, firstName);
            if (!firstName.empty())
                employee.setFirstName(firstName);
            std::cout << "Enter the employee's new age (or leave blank to keep the same): ";
            std::cin >> age;
            if (age != 0)
                employee.setAge(age);
            std::cout << "Employee information updated successfully." << std::endl;
            return;
        }
    }
    std::cout << "Employee not found." << std::endl;
}

// удаление сотрудника
void deleteEmployee(std::vector<Employee>& employees) {
    std::string lastName;
    std::cout << "Enter the employee's last name: ";
    std::cin >> lastName;
    for (std::vector<Employee>::iterator it = employees.begin(); it != employees.end(); it++)
    {
        if (it->getLastName() == lastName)
        {
            employees.erase(it);
            std::cout << "Employee deleted successfully." << std::endl;
            return;
        }
    }
    std::cout << "Employee not found." << std::endl;
}

// поиск по фамилии
void searchByLastName(std::vector<Employee>& employees)
{
    std::string lastName;
    std::cout << "Enter the employee's last name: ";
    std::cin >> lastName;
    for (Employee employee : employees)
    {
        if (employee.getLastName() == lastName)
        {
            std::cout << employee << std::endl;
            return;
        }
    }
    std::cout << "Employee not found." << std::endl;
}

// поиск по возрасту
void searchByAge(std::vector<Employee>& employees)
{
    int age;
    std::cout << "Enter the employee's age: ";
    std::cin >> age;
    for (Employee employee : employees) 
        if (employee.getAge() == age)
            std::cout << employee << std::endl;
}

// поиск по первой букве фамилии
void searchByLetter(std::vector<Employee>& employees)
{
    char letter;
    std::cout << "Enter the first letter of the employee's last name: ";
    std::cin >> letter;
    for (Employee employee : employees)
        if (employee.getLastName()[0] == letter)
            std::cout << employee << std::endl;
}

int main()
{
    std::vector<Employee> employees;

    std::string fileName;
    std::cout << "Enter the name of the file to load employee data from: ";
    std::cin >> fileName;

    readEmployeesFromFile(employees, fileName);

    while (true) 
    {
        std::cout << "What would you like to do?" << std::endl;

        std::cout << "1. Add a new employee" << std::endl;
        std::cout << "2. Edit an existing employee's information" << std::endl;
        std::cout << "3. Delete an existing employee" << std::endl;
        std::cout << "4. Search for an employee by last name" << std::endl;
        std::cout << "5. Display information about all employees of a certain age" << std::endl;
        std::cout << "6. Display information about all employees whose last name starts with a certain letter" << std::endl;
        std::cout << "7. Save employee data to a file" << std::endl;
        std::cout << "8. Quit" << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice) 
        {
        case 1:
            addEmployee(employees);
            break;
        case 2:
            editEmployee(employees);
            break;
        case 3:
            deleteEmployee(employees);
            break;
        case 4:
            searchByLastName(employees);
            break;
        case 5:
            searchByAge(employees);
            break;
        case 6:
            searchByLetter(employees);
            break;
        case 7:
            std::cout << "Enter the name of the file to save employee data to: ";
            std::cin >> fileName;
            writeEmployeesToFile(employees, fileName);
            break;
        case 8:
            writeEmployeesToFile(employees, fileName);
            return 0;
        default:
            std::cout << "Invalid choice." << std::endl;
            break;
        }
    }
    return 0;
}
