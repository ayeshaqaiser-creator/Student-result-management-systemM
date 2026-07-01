#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX = 100;

int rollNo[MAX];
string name[MAX];
string section[MAX];
int marks[MAX][5];
int total[MAX];
float percentage[MAX];
char grade[MAX];
string status[MAX];

int countStudents = 0;

// Function Prototypes
void loadFromFile();
void saveToFile();
void addStudent();
void displayStudents();
void searchStudent();
void calculateResult(int index);

// Main Function
int main()
{
    loadFromFile();

    int choice;

    do
    {
        cout << "\n=====================================\n";
        cout << " Student Result Management System\n";
        cout << "=====================================\n";
        cout << "1. Add Student Record\n";
        cout << "2. Display All Student Records\n";
        cout << "3. Search Student by Roll Number\n";
        cout << "4. Save Records to File\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            saveToFile();
            cout << "Records saved successfully.\n";
            break;

        case 5:
            saveToFile();
            cout << "Program closed successfully.\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 5);

    return 0;
}

// Load Records From File
void loadFromFile()
{
    ifstream file("students.txt");

    if (!file)
        return;

    while (file >> rollNo[countStudents]
                >> name[countStudents]
                >> section[countStudents])
    {
        for (int i = 0; i < 5; i++)
        {
            file >> marks[countStudents][i];
        }

        calculateResult(countStudents);
        countStudents++;
    }

    file.close();
}

// Save Records To File
void saveToFile()
{
    ofstream file("students.txt");

    for (int i = 0; i < countStudents; i++)
    {
        file << rollNo[i] << " "
             << name[i] << " "
             << section[i] << " ";

        for (int j = 0; j < 5; j++)
        {
            file << marks[i][j] << " ";
        }

        file << endl;
    }

    file.close();
}

// Calculate Result
void calculateResult(int index)
{
    total[index] = 0;

    for (int i = 0; i < 5; i++)
    {
        total[index] += marks[index][i];
    }

    percentage[index] = total[index] / 5.0;

    if (percentage[index] >= 85)
        grade[index] = 'A';
    else if (percentage[index] >= 75)
        grade[index] = 'B';
    else if (percentage[index] >= 65)
        grade[index] = 'C';
    else if (percentage[index] >= 50)
        grade[index] = 'D';
    else
        grade[index] = 'F';

    if (percentage[index] >= 50)
        status[index] = "Pass";
    else
        status[index] = "Fail";
}

// Add Student
void addStudent()
{
    if (countStudents >= MAX)
    {
        cout << "Maximum limit reached.\n";
        return;
    }

    int roll;

    cout << "Enter Roll Number: ";
    cin >> roll;

    // Check duplicate roll number
    for (int i = 0; i < countStudents; i++)
    {
        if (rollNo[i] == roll)
        {
            cout << "Roll Number already exists!\n";
            return;
        }
    }

    rollNo[countStudents] = roll;

    cout << "Enter Name: ";
    cin >> name[countStudents];

    cout << "Enter Section: ";
    cin >> section[countStudents];

    for (int i = 0; i < 5; i++)
    {
        do
        {
            cout << "Enter Marks of Subject "
                 << i + 1 << " (0-100): ";
            cin >> marks[countStudents][i];

            if (marks[countStudents][i] < 0 ||
                marks[countStudents][i] > 100)
            {
                cout << "Invalid marks! Enter again.\n";
            }

        } while (marks[countStudents][i] < 0 ||
                 marks[countStudents][i] > 100);
    }

    calculateResult(countStudents);

    countStudents++;

    cout << "Student record added successfully.\n";
}

// Display All Records
void displayStudents()
{
    if (countStudents == 0)
    {
        cout << "No student record available.\n";
        return;
    }

    for (int i = 0; i < countStudents; i++)
    {
        cout << "\n----------------------------------\n";
        cout << "Roll Number : " << rollNo[i] << endl;
        cout << "Name        : " << name[i] << endl;
        cout << "Section     : " << section[i] << endl;

        cout << "Marks: ";
        for (int j = 0; j < 5; j++)
        {
            cout << marks[i][j] << " ";
        }

        cout << "\nTotal Marks : " << total[i];
        cout << "\nPercentage  : " << percentage[i] << "%";
        cout << "\nGrade       : " << grade[i];
        cout << "\nStatus      : " << status[i] << endl;
    }
}

// Search Student
void searchStudent()
{
    int roll;
    bool found = false;

    cout << "Enter Roll Number to Search: ";
    cin >> roll;

    for (int i = 0; i < countStudents; i++)
    {
        if (rollNo[i] == roll)
        {
            cout << "\nStudent Found\n";
            cout << "Roll Number : " << rollNo[i] << endl;
            cout << "Name        : " << name[i] << endl;
            cout << "Section     : " << section[i] << endl;

            cout << "Marks: ";
            for (int j = 0; j < 5; j++)
            {
                cout << marks[i][j] << " ";
            }

            cout << "\nTotal Marks : " << total[i];
            cout << "\nPercentage  : " << percentage[i] << "%";
            cout << "\nGrade       : " << grade[i];
            cout << "\nStatus      : " << status[i] << endl;

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Student record not found.\n";
    }
}
