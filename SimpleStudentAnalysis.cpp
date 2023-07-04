#include <iostream>
#include <algorithm>
using namespace std;

double calculateAverage(double* data, int dataSize)
{
    double sum = 0;
    for (int i = 0; i < dataSize; i++)
        sum += data[i];
    return sum / dataSize;
}

void SortujDane(int n, string*& tabNazw, double*& tabOc, int*& tabRok)
{
    string* tempNazw = new string[n];
    double* tempOc = new double[n];
    int* tempRok = new int[n];

    for (int i = 0; i < n; i++)
    {
        tempNazw[i] = tabNazw[i];
        tempOc[i] = tabOc[i];
        tempRok[i] = tabRok[i];
    }

    sort(tempNazw, tempNazw + n);

    cout << "\nPosortowane dane wedlug nazwisk:\n\n";
    for (int i = 0; i < n; i++)
    {
        int index = searchName(tabNazw, n, tempNazw[i]);
        cout << i + 1 << " --- " << tabNazw[index] << " --- " << tabOc[index] << " ---- " << tabRok[index] << endl;
    }

    delete[] tempNazw;
    delete[] tempOc;
    delete[] tempRok;
}

double ObliczMediane(int n, double* tabOc)
{
    double* tempOc = new double[n];
    for (int i = 0; i < n; i++)
    {
        tempOc[i] = tabOc[i];
    }

    sort(tempOc, tempOc + n);

    if (n % 2 == 0)
    {
        int index1 = n / 2 - 1;
        int index2 = n / 2;
        return (tempOc[index1] + tempOc[index2]) / 2;
    }
    else
    {
        int index = n / 2;
        return tempOc[index];
    }

    delete[] tempOc;
}

int menu()
{
    int option;
    system("cls");
    cout << "** GRADE STATISTICS **";
    cout << "\n--------------------------\n\n";
    cout << "\n** MENU **\n";
    cout << "\n  [1] Display data (sorted by last name)";
    cout << "\n  [2] Average grade";
    cout << "\n  [3] Minimum and maximum grade";
    cout << "\n  [4] Top-performing students";
    cout << "\n  [5] Weakest students";
    cout << "\n  [6] Grades of a specific student";
    cout << "\n--------------------------";
    cout << "\n  [0] EXIT PROGRAM";
    cout << "\n\n\n** Choose an option: ";

    cin >> option;
    if (option < 0 || option > 6)
        option = -1;
    return option;
}

int loadData(string*& names, double*& grades, int*& birthYears)
{
    int n = 10;
    grades = new double[n]{ 3, 3.5, 5, 4, 3.5, 3, 4, 2, 2, 5 };
    names = new string[n]{ "Adamski","Adamowski", "Kowal", "Kowalski", "Kowalkowski", "Nowak", "Nowacki", "Nowakowski", "Rak", "Ryba" };
    birthYears = new int[n]{ 1999, 1998, 2000, 2001, 1998, 1999, 2000, 2000, 2001, 1998 };
    return n;
}

void displayData(int dataSize, string*& names, double*& grades, int*& birthYears)
{
    for (int i = 1; i <= dataSize; i++)
    {
        cout << i << " --- " << names[i - 1] << " --- " << grades[i - 1] << " ---- " << birthYears[i - 1] << endl;
    }
}

void findMinMax(double* data, int dataSize)
{
    double maxGrade = data[0];
    double minGrade = maxGrade;
    for (int i = 1; i < dataSize; i++)
    {
        if (maxGrade < data[i])
        {
            maxGrade = data[i];
        }
        if (minGrade > data[i])
        {
            minGrade = data[i];
        }
    }
    cout << "Min: " << minGrade << "\nMax: " << maxGrade << endl;
}

bool compareGrades(double grade1, double grade2)
{
    return grade1 > grade2;
}

void topPerformingStudents(int dataSize, string*& names, double*& grades, int*& birthYears)
{
    double* tempGrades = new double[dataSize];
    for (int i = 0; i < dataSize; i++)
    {
        tempGrades[i] = grades[i];
    }

    sort(tempGrades, tempGrades + dataSize, compareGrades);

    cout << "\nTop-performing students:\n\n";
    for (int i = 0; i < dataSize; i++)
    {
        int index = searchName(names, dataSize, names[i]);
        cout << names[index] << " --- " << grades[index] << " --- " << birthYears[index] << endl;
    }

    delete[] tempGrades;
}

void weakestStudents(int dataSize, string*& names, double*& grades, int*& birthYears)
{
    double average = calculateAverage(grades, dataSize);
    cout << "\nWeakest students:\n\n";
    for (int i = 0; i < dataSize; i++)
    {
        if (grades[i] < average)
        {
            cout << names[i] << " --- " << grades[i] << " --- " << birthYears[i] << endl;
        }
    }
}

int searchName(string* names, int dataSize, string searchName)
{
    for (int i = 0; i < dataSize; i++)
    {
        if (names[i] == searchName)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    int dataSize, option;
    string* studentNames;
    double* studentGrades;
    int* studentBirthYears;
    string lastName;
    int studentIndex;
    dataSize = loadData(studentNames, studentGrades, studentBirthYears);
    do
    {
        option = menu();
        switch (option)
        {
        case 1:
            cout << "\nData List:\n\n";
            displayData(dataSize, studentNames, studentGrades, studentBirthYears);
            break;
        case 2:
            cout << "\nAverage grade: " << calculateAverage(studentGrades, dataSize) << "\n";
            break;
        case 3:
            cout << "\nMinimum and maximum grade:\n\n";
            findMinMax(studentGrades, dataSize);
            break;
        case 4:
            topPerformingStudents(dataSize, studentNames, studentGrades, studentBirthYears);
            break;
        case 5:
            weakestStudents(dataSize, studentNames, studentGrades, studentBirthYears);
            break;
        case 6:
            cout << "\nGrades of a specific student:\n\n";
            cout << "Enter last name: ";
            cin >> lastName;
            studentIndex = searchName(studentNames, dataSize, lastName);
            if (studentIndex == -1)
            {
                cout << "No such student." << endl;
            }
            else
            {
                cout << "\n" << studentNames[studentIndex] << " --- " << studentGrades[studentIndex] << " --- " << studentBirthYears[studentIndex] << endl;
            }
            break;
        case -1:
            cout << "\nInvalid option...";
            break;
        default:
            break;
        }
        cout << "\n--------------------------" << endl << endl;
        if (option != 0)
            system("pause");

    } while (option != 0);
}
