/***
 Name: Alexander Zhang
 IDE: Xcode
 
 This assignment required me to read data from file "students.txt" into parallel arrays,
 display the major and GPA, and then output the data to file "out.txt" with the number
 of times each ID was searched for.
 Loops until the user is finished using the program.
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

// Function prototypes
void readData(string idArray[], double gpaArray[], string majorArray[], const int maxSize, int &sizeRef);
string getId(void);
int binarySearch(const string idArray[], int size, string value);
void displayInfo(const double gpaArray[], const string majorArray[], int location);
void outData(const int searchesArray[], const string idArray[], const string majorArray[], const double gpaArray[], int size);

int main()
{
    const int maxSize = 5000;    // maximum size of the arrays
    string idArray[maxSize];
    double gpaArray[maxSize];
    string majorArray[maxSize];
    int searchesArray[maxSize];
    int size; //actual size of arrays
    
    string id;
    char repeat;
    int position;
    
    readData(idArray, gpaArray, majorArray, maxSize, size);
    
    do
    {
        id = getId(); //ask user for a student id
        position = binarySearch(idArray, size, id); //searching for the id
        
        if (position != -1)
        {
            searchesArray[position]++; //adds one to amount of times the id is looked for
            displayInfo(gpaArray, majorArray, position);
        }
        else
        {
            cout << "Student ID not found." << endl;
        }
        
        cout << endl;
        cout << "Search another student ID?(y/n) ";
        cin >> repeat;
        cout << endl;
    } while (repeat == 'y' || repeat == 'Y');
    
    outData(searchesArray, idArray, majorArray, gpaArray, size); //outputs the info to a text file
    
    return 0;
}


//********************************************************************
// Function readData reads in the student ID, GPA, and major into
// three parallel arrays. If the input files have over 5000 lines,
// the program is terminated. Function returns nothing.
//********************************************************************
void readData(string idArray[], double gpaArray[], string majorArray[], const int maxSize, int &sizeRef)
{
    ifstream infile;
    string fileName = "students.txt";
    
    infile.open(fileName.c_str());
    
    if (infile.fail()) //test file opening.
    {
        cout << "The input file has failed to open." << endl;
        exit(EXIT_FAILURE);
    }
    
    //reading data in
    sizeRef = 0;
    while (infile >> idArray[sizeRef] >> gpaArray[sizeRef])
    {
        infile.ignore(); //ignores the first space that getline will read
        getline(infile, majorArray[sizeRef]); //using getline since some majors have spaces
        sizeRef++;
        
        if (sizeRef == maxSize && !infile.eof())
        {
            cout << "The file is too big. It has more than " << maxSize << " items.";
            exit(EXIT_FAILURE);
        }
    }
    infile.close();
}


//********************************************************************
// Function getId asks the user for an ID to search for.
// It returns the id.
//********************************************************************
string getId(void)
{
    string idNum;
    cout << "Enter a student ID: ";
    cin >> idNum;
    
    return idNum;
}

//********************************************************************
//Function binarySearch searches the idArray array for the id which
//the user inputs.
//The program returns the integer position of the id.
//********************************************************************
int binarySearch(const string idArray[], int size, string value)
{
    int position = -1;
    bool found = false;
    int min = 0;
    int max = (size - 1);
    int mid;
    
    while (!found && min <= max)
    {
        mid = (min + max) / 2;
        if (idArray[mid] == value)
        {
            found = true;
            position = mid;
        }
        else if (idArray[mid] > value)
        {
            max = mid - 1;
        }
        else
        {
            min = mid + 1;
        }
    }
    
    return position;
}


//********************************************************************
//Function displayInfo displays the GPA and the Major
//Function returns nothing.
//********************************************************************
void displayInfo(const double gpaArray[], const string majorArray[], int location)
{
    cout << "GPA: " << gpaArray[location] << endl;
    cout << "Major: " << majorArray[location] << endl;
}


//********************************************************************
//Function outData writes the contents of the arrays to a text file,
//and how many times each id was searched for.
//********************************************************************
void outData(const int searchesArray[], const string idArray[], const string majorArray[], const double gpaArray[], int size)
{
    ofstream outfile;
    string filename = "out.txt";
    
    outfile.open(filename.c_str());
    
    if (outfile.fail()) //test file opening
    {
        cout << "The output file has failed to open." << endl;
        exit(EXIT_FAILURE);
    }
    
    //writing data out
    for (int i = 0; i < size; i++)
    {
        outfile << searchesArray[i] << " " << idArray[i] << " " << majorArray[i] << " (" << gpaArray[i]
        << ")" << endl;
    }
    outfile.close();
}
//********************************************************************



/****************** OUTPUT ******************
 Enter a student ID: JP200
 GPA: 3.8
 Major: Nursing
 
 Search another student ID?(y/n) y
 
 Enter a student ID: abc123
 Student ID not found.
 
 Search another student ID?(y/n) y
 
 Enter a student ID: 333XY
 GPA: 3.9
 Major: Computer Science
 
 Search another student ID?(y/n) y
 
 Enter a student ID: AC234
 GPA: 3.9
 Major: Marketing
 
 Search another student ID?(y/n) y
 
 Enter a student ID: 333XY
 GPA: 3.9
 Major: Computer Science
 
 Search another student ID?(y/n) y
 
 Enter a student ID: 333XY
 GPA: 3.9
 Major: Computer Science
 
 Search another student ID?(y/n) y
 
 Enter a student ID: 9QWE9
 GPA: 3.4
 Major: Psychology
 
 Search another student ID?(y/n) y
 
 Enter a student ID: DR123
 GPA: 2.7
 Major: Criminal Justice
 
 Search another student ID?(y/n) y
 
 Enter a student ID: 9QWE9
 GPA: 3.4
 Major: Psychology
 
 Search another student ID?(y/n) n
 
 Program ended with exit code: 0
 */
