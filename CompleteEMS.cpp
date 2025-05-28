//  Muhammad Bilal 2025(S)-CS-26
//  Semester Final project
//  Employee Management System
//  ---------------------------------------
//  Text files
//  users.txt  for username, password, role.
//  employees.txt for name, id, salary.
//  products.txt for name, price.

#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
using namespace std;

// Total Record
const int MAX_RECORDS = 20;
//=======================  Data Structures =====================

//  All users records
string usernameA[MAX_RECORDS];
string passwordsA[MAX_RECORDS];
string rolesA[MAX_RECORDS];
int userCount = 0;

//  Employees records
string employee_name[MAX_RECORDS];
int employee_id[MAX_RECORDS];
int employee_salary[MAX_RECORDS];
int employee_count = 0;

//  Products records
string product_name[MAX_RECORDS];
int product_price[MAX_RECORDS];
int product_count = 0;

//  Login and sales record
string loggedInUsername = "";
string loggedInRole = "";
int employeeSales = 0;

//  ====================  PROTOTYPES  ===========================
void mainHeader();
void clearScreen();
//  File Records
void loadUsers();
void loadEmployees();
void loadProducts();
// Sign In/ Sign Up
void signUp();
bool signIn();
//  Menus
char adminMenu();
char employeeMenu();
// User management
void addUser(string name, string pass, string role);
// Notifications
void sendNotificationToEmployee();
void showEmployeeNotifications(string loggedInUsername);
// Employee Operations
void addEmployee();
void addEmployeeIntoArray(string name, int id, int salary);
void removeEmployee();
void removeEmployeeFromArray(string name, int id);
void viewAllEmployees();
// Product operations
void addProducts();
void addProductIntoArray(string name, int price);
void removeProducts();
void removeProductFromArray(string name);
void viewAllProducts();
void productInOrder();
//  Employee-side features
void employeeSalary();
void sellProducts();
void employeeSell();
void productStocks();
int employeeInfo();
void searchProducts();
void updatePass();

//  =========================  MAIN  ============================
main()
{
    // These functions used to load data from files
    loadUsers();
    loadEmployees();
    loadProducts();

    int choice = 0;
    while (choice != 3)
    {
        mainHeader();
        cout << "1. Sign Up" << endl;
        cout << "2. Sign In" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            signUp();
        }
        else if (choice == 2 && signIn())
        // after successful login
        {
            //  --------------- ADMIN ---------------
            if (loggedInRole == "Admin")
            {
                char op;
                while (true)
                {
                    system("cls");
                    op = adminMenu();
                    if (op == '1')
                    {
                        addEmployee();
                    }
                    else if (op == '2')
                    {
                        removeEmployee();
                    }
                    else if (op == '3')
                    {
                        viewAllEmployees();
                    }
                    else if (op == '4')
                    {
                        addProducts();
                    }
                    else if (op == '5')
                    {
                        removeProducts();
                    }
                    else if (op == '6')
                    {
                        viewAllProducts();
                    }
                    else if (op == '7')
                    {
                        productInOrder();
                        viewAllProducts();
                    }
                    else if (op == '8')
                    {
                        employeeSalary();
                    }
                    else if (op == '9')
                    {
                        string user, pass, role;
                        cout << "New username : ";
                        cin >> user;
                        cout << "New password : ";
                        cin >> pass;
                        cout << "Role (Admin/Employee): ";
                        cin >> role;
                        addUser(user, pass, role);
                    }
                    else if (op == 'a')
                    {
                        sendNotificationToEmployee();
                    }
                    else if (op == '0')
                    {
                        break;
                    }
                    else
                    {
                        cout << "Invalid option." << endl;
                    }
                    clearScreen();
                }
            }
            //  ------------- EMPLOYEE ---------------
            else if (loggedInRole == "Employee")
            {
                char op;
                while (true)
                {
                    system("cls");
                    op = employeeMenu();
                    if (op == '1')
                    {
                        viewAllProducts();
                    }
                    else if (op == '2')
                    {
                        sellProducts();
                    }
                    else if (op == '3')
                    {
                        productStocks();
                    }
                    else if (op == '4')
                    {
                        viewAllProducts();
                    }
                    else if (op == '5')
                    {
                        employeeSell();
                    }
                    else if (op == '6')
                    {
                        showEmployeeNotifications(loggedInUsername);
                    }
                    else if (op == '7')
                    {
                        searchProducts();
                    }
                    else if (op == '8')
                    {
                        int idx = employeeInfo();
                        if (idx != -1)
                        {
                            cout << "Name\tID\tSalary" << endl;
                            cout << employee_name[idx] << '\t' << employee_id[idx] << '\t' << employee_salary[idx] << endl;
                        }
                        else
                        {
                            cout << "Employee record not found." << endl;
                        }
                    }
                    else if (op == '9')
                    {
                        updatePass();
                    }

                    else if (op == '0')
                    {
                        break;
                    }
                    else
                    {
                        cout << "Invalid option." << endl;
                    }
                    clearScreen();
                }
            }
            else
            {
                cout << "Unknown role." << endl;
            }
        }
        else if (choice == 3)
        {
            cout << "Thanks for using this application!" << endl;
        }
    }
}

//  ======================  Header =========================
void mainHeader()
{

    cout << "================================================" << endl;
    cout << "        EMPLOYEE  MANAGEMENT  SYSTEM           " << endl;
    cout << "================================================" << endl
         << endl;
}

void clearScreen()
{
    cout << "\nPress any key...";
    getch();
    system("cls");
}

// ======================  FILE LOADERS  =======================
void loadUsers()
{
    userCount = 0;
    fstream file;
    file.open("users.txt", ios::in);
    while (userCount < MAX_RECORDS &&
           file >> usernameA[userCount] >> passwordsA[userCount] >> rolesA[userCount])
    {
        userCount++;
    }
    file.close();
}
void loadEmployees()
{
    employee_count = 0;
    fstream file;
    file.open("employees.txt", ios::in);
    while (employee_count < MAX_RECORDS &&
           file >> employee_name[employee_count] >> employee_id[employee_count] >> employee_salary[employee_count])
    {
        employee_count++;
    }
    file.close();
}
void loadProducts()
{
    product_count = 0;
    fstream file;
    file.open("products.txt", ios::in);
    while (product_count < MAX_RECORDS &&
           file >> product_name[product_count] >> product_price[product_count])
    {
        product_count++;
    }
    file.close();
}

// ======================  Sign Up/ Sign In ===============================
void signUp()
{
    string user, pass, role;
    cout << "\n--- Sign Up ---" << endl;
    cout << "Username : ";
    cin >> user;
    cout << "Password : ";
    cin >> pass;
    cout << "Role (Admin/Employee): ";
    cin >> role;

    if (userCount >= MAX_RECORDS)
    {
        cout << "User list full." << endl;
        return;
    }

    //  store in arrays
    usernameA[userCount] = user;
    passwordsA[userCount] = pass;
    rolesA[userCount] = role;
    userCount++;

    //  append
    fstream file;
    file.open("users.txt", ios::app);
    file << user << ' ' << pass << ' ' << role << endl;
    file.close();

    cout << "Sign-up successful!" << endl;
}
bool signIn()
{
    string user, pass;
    cout << "\n--- Sign In ---" << endl;
    cout << "Username : ";
    cin >> user;
    cout << "Password : ";
    cin >> pass;

    fstream file;
    file.open("users.txt", ios::in);
    if (!file.is_open())
    {
        cout << "No users.txt file." << endl;
        return false;
    }

    string fileuser, filepass, filerole;
    while (file >> fileuser >> filepass >> filerole)
        if (fileuser == user && filepass == pass)
        {
            loggedInUsername = fileuser;
            loggedInRole = filerole;
            cout << "Login OK (Role: " << filerole << ")" << endl;
            file.close();
            return true;
        }
    file.close();
    cout << "Wrong credentials." << endl;
    return false;
}

// ======================  MENUS  ==============================
char adminMenu()
{
    mainHeader();
    cout << "[ADMIN]" << endl;
    cout << "1-  Add Employee" << endl;
    cout << "2-  Remove Employee" << endl;
    cout << "3-  View Employees" << endl;
    cout << "4-  Add Product" << endl;
    cout << "5-  Remove Product" << endl;
    cout << "6-  View Products" << endl;
    cout << "7-  Sort Products" << endl;
    cout << "8-  View Salaries" << endl;
    cout << "9-  Add User" << endl;
    cout << "a- Send Notification" << endl;
    cout << "0- Logout" << endl;
    cout << "Choice: ";
    char option;
    cin >> option;
    return option;
}
char employeeMenu()
{
    mainHeader();
    cout << "[EMPLOYEE]" << endl;
    cout << "1-  View Products" << endl;
    cout << "2-  Sell Product" << endl;
    cout << "3-  Product Stocks" << endl;
    cout << "4-  Price List" << endl;
    cout << "5-  My Sales Count" << endl;
    cout << "6-  Notifications" << endl;
    cout << "7-  Search Product" << endl;
    cout << "8-   My Info" << endl;
    cout << "9-  Change Password" << endl;
    cout << "0- Logout" << endl;
    cout << "Choice: ";
    char option;
    cin >> option;
    return option;
}

// ======================  USER (ADMIN)  =======================
void addUser(string name, string pass, string role)
{
    if (userCount >= MAX_RECORDS)
    {
        cout << "User list full." << endl;
        return;
    }

    // insert into arrays
    usernameA[userCount] = name;
    passwordsA[userCount] = pass;
    rolesA[userCount] = role;
    userCount++;

    // append to file
    fstream file;
    file.open("users.txt", ios::app);
    file << name << ' ' << pass << ' ' << role << endl;
    file.close();

    cout << "User added & saved." << endl;
}

// ==================  EMPLOYEE Operations  =================
void addEmployee()
{
    if (employee_count >= MAX_RECORDS)
    {
        cout << "Employee list full." << endl;
        return;
    }

    // employee data input
    string name;
    int id, salary;
    cout << "Employee name  : ";
    cin >> name;
    cout << "Employee ID    : ";
    cin >> id;
    cout << "Employee salary: ";
    cin >> salary;

    // login credentials for that employee
    string user, pass;
    cout << "Create login username for employee (no spaces): ";
    cin >> user;
    cout << "Create login password: ";
    cin >> pass;

    // Add to employee array & save to employees.txt
    addEmployeeIntoArray(name, id, salary);
    fstream fileEmployee;
    fileEmployee.open("employees.txt", ios::app);
    fileEmployee << name << ' ' << id << ' ' << salary << endl;
    fileEmployee.close();

    // user record (role = Employee)
    addUser(user, pass, "Employee");

    cout << "Employee + login added." << endl;
}
void addEmployeeIntoArray(string name, int id, int salary)
{
    employee_name[employee_count] = name;
    employee_id[employee_count] = id;
    employee_salary[employee_count] = salary;
    employee_count++;
}

void removeEmployee()
{
    if (employee_count == 0)
    {
        cout << "No employees." << endl;
        return;
    }
    string name;
    int id;
    cout << "Name to remove: ";
    cin >> name;
    cout << "ID   to remove: ";
    cin >> id;
    removeEmployeeFromArray(name, id);
}
void removeEmployeeFromArray(string name, int id)
{
    int idx = -1;
    for (int i = 0; i < employee_count; i++)
        if (employee_name[i] == name && employee_id[i] == id)
        {
            idx = i;
            break;
        }
    if (idx == -1)
    {
        cout << "Employee not found." << endl;
        return;
    }

    for (int j = idx; j < employee_count - 1; j++)
    {
        employee_name[j] = employee_name[j + 1];
        employee_id[j] = employee_id[j + 1];
        employee_salary[j] = employee_salary[j + 1];
    }
    employee_count--;

    // update employees.txt
    fstream fileEmployee;
    fileEmployee.open("employees.txt", ios::out);
    for (int i = 0; i < employee_count; i++)
        fileEmployee << employee_name[i] << ' ' << employee_id[i] << ' ' << employee_salary[i] << endl;
    fileEmployee.close();
    cout << "Employee removed." << endl;
}

void viewAllEmployees()
{
    if (employee_count == 0)
    {
        cout << "No employees." << endl;
        return;
    }
    cout << "Name\tID\tSalary" << endl;
    for (int i = 0; i < employee_count; i++)
        cout << employee_name[i] << '\t' << employee_id[i] << '\t' << employee_salary[i] << endl;
}

// ======================  PRODUCT operations  =======================
void addProducts()
{
    if (product_count >= MAX_RECORDS)
    {
        cout << "Product list full." << endl;
        return;
    }
    string name;
    int price;
    cout << "Product name : ";
    cin >> name;
    cout << "Price        : ";
    cin >> price;

    addProductIntoArray(name, price);

    fstream fileproduct;
    fileproduct.open("products.txt", ios::app);

    fileproduct << name << ' ' << price << endl;
    fileproduct.close();

    cout << "Product added." << endl;
}
void addProductIntoArray(string name, int price)
{
    product_name[product_count] = name;
    product_price[product_count] = price;
    product_count++;
}

void removeProducts()
{
    if (product_count == 0)
    {
        cout << "No products." << endl;
        return;
    }
    string name;
    cout << "Product to remove: ";
    cin >> name;
    removeProductFromArray(name);
}
void removeProductFromArray(string name)
{
    int idx = -1;
    for (int i = 0; i < product_count; i++)
        if (product_name[i] == name)
        {
            idx = i;
            break;
        }
    if (idx == -1)
    {
        cout << "Not found." << endl;
        return;
    }

    for (int j = idx; j < product_count - 1; j++)
    {
        product_name[j] = product_name[j + 1];
        product_price[j] = product_price[j + 1];
    }
    product_count--;

    fstream fileproduct;
    fileproduct.open("products.txt", ios::out | ios::trunc);
    for (int i = 0; i < product_count; i++)
        fileproduct << product_name[i] << ' ' << product_price[i] << endl;
    fileproduct.close();
    cout << "Product removed." << endl;
}

void viewAllProducts()
{
    if (product_count == 0)
    {
        cout << "No products." << endl;
        return;
    }
    cout << "Name\tPrice" << endl;
    for (int i = 0; i < product_count; i++)
        cout << product_name[i] << '\t' << product_price[i] << endl;
}

// Sorting
void productInOrder()
{
    for (int i = 0; i < product_count - 1; i++)
        for (int j = 0; j < product_count - i - 1; j++)
            if (product_price[j] < product_price[j + 1])
            // sort High -> Low
            {
                // sort price
                int tmpPrice = product_price[j];
                product_price[j] = product_price[j + 1];
                product_price[j + 1] = tmpPrice;

                // sort name
                string tmpName = product_name[j];
                product_name[j] = product_name[j + 1];
                product_name[j + 1] = tmpName;
            }
}

// ==================  EMPLOYEE FEATURES  ======================
void employeeSalary()
{
    if (employee_count == 0)
    {
        cout << "No employees." << endl;
        return;
    }
    cout << "Name\tSalary" << endl;
    for (int i = 0; i < employee_count; i++)
        cout << employee_name[i] << '\t' << employee_salary[i] << endl;
}
void sellProducts()
{
    string name;
    cout << "Product sold: ";
    cin >> name;
    for (int i = 0; i < product_count; i++)
        if (product_name[i] == name)
        {
            cout << "Sold " << name << " for " << product_price[i] << endl;
            employeeSales++;
            return;
        }
    cout << "Product not found." << endl;
}

void employeeSell()
{
    cout << "You sold " << employeeSales << " product(s)." << endl;
}

void productStocks()
{
    cout << "Products in stock: " << product_count << endl;
}

int employeeInfo()
{
    for (int i = 0; i < employee_count; i++)
        if (employee_name[i] == loggedInUsername)
        {
            return i;
        }
    return -1;
}
void searchProducts()
{
    string name;
    cout << "Search product: ";
    cin >> name;
    for (int i = 0; i < product_count; i++)
        if (product_name[i] == name)
        {
            cout << "Found " << name << " (price " << product_price[i] << ")" << endl;
            return;
        }
    cout << "Not found." << endl;
}

void updatePass()
{
    string newPass;
    cout << "New password: ";
    cin >> newPass;

    // load user data stored in array
    loadUsers();

    int idx = -1;
    for (int i = 0; i < userCount; i++)
        if (usernameA[i] == loggedInUsername)
        {
            idx = i;
            break;
        }
    if (idx == -1)
    {
        cout << "User missing." << endl;
        return;
    }

    passwordsA[idx] = newPass;

    fstream file;
    file.open("users.txt", ios::out);
    for (int i = 0; i < userCount; i++)
        file << usernameA[i] << ' ' << passwordsA[i] << ' ' << rolesA[i] << endl;
    file.close();
    cout << "Password changed & saved." << endl;
}

// send Notification

void sendNotificationToEmployee()
{
    string name;
    cout << "Enter employee name: ";
    cin.ignore();
    getline(cin, name);

    // Check if employee exists
    bool found = false;
    for (int i = 0; i < employee_count; i++)
    {
        if (employee_name[i] == name)
        {
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Employee not found." << endl;
        return;
    }

    string message;
    cout << "Enter message to send: ";
    getline(cin, message);

    string filename = "notifications_";
    filename += name;
    filename += ".txt";

    fstream file;
    file.open(filename, ios::app);
    if (file.is_open())
    {
        file << message << endl;
        file.close();
        cout << "Notification sent successfully." << endl;
    }
    else
    {
        cout << "Failed to write notification." << endl;
    }
}

// view notification

void showEmployeeNotifications(string loggedInUsername)
{
    string filename = "notifications_";
    filename += loggedInUsername;
    filename += ".txt";

    fstream file;
    file.open(filename, ios::in);
    if (!file.is_open())
    {
        cout << "No notifications found." << endl;
        return;
    }

    cout << "Notification For You" << endl;
    string line;
    while (getline(file, line))
    {
        cout << "- " << line << endl;
    }
    file.close();
}
