/***
 Name: Alexander Zhang
 IDE: Xcode
 
 This assignment had me make a program which reads in a table from a file and determine if the table
 is a perfect square. The first number in the file is the size of one side.
 If the table has a side of 8 or less, the table is outputted. If larger, it is not outputted.
 The file name, whether it is a perfect square, and the constant are all outputted.
 */

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAXTBLSIZE = 100;  // the maximum table size is 100


bool readTable(string filename, int table[][MAXTBLSIZE], int &size);
int testTable(const int table[][MAXTBLSIZE], int size);
void printTable(const int table[][MAXTBLSIZE], int size, string filename);
void printResults(int constant, string filename, int size);


int main( void )
{
    string fileName[] = {"t0.txt", "t1.txt", "t2.txt", "tA.txt", "t3.txt", "t4.txt", "t5.txt", "t6.txt", "t7.txt", ""};
    int table[MAXTBLSIZE][MAXTBLSIZE] = {0};
    int tblSize;     // the number of rows and columns
    int tblConstant; // -1 if it is not a perfect table or the table's constant otherwise
    int choice = 1;  // to stop the program to allow the user to see the results one table at a time
    int fileIndex;
    string sentinel = ""; // template had "" as a 'sentinel' so I will use it in this program
    
    // test loop: takes the names of 7 input files from an array
    for (fileIndex = 0; choice == 1 && fileName[fileIndex] != sentinel; fileIndex++)
    {
        if (readTable(fileName[fileIndex], table, tblSize))
        {
            tblConstant = testTable(table, tblSize);
            
            if (tblSize <= 8) // display table only if there are 8 or less rows
            {
                printTable(table, tblSize, fileName[fileIndex]); // pass filename for consistency in output
            }
            printResults(tblConstant, fileName[fileIndex], tblSize);
        }
        else
        {
            cout << "Error: Input file \"" << fileName[fileIndex] << "\" not found!" << endl;
        }
        
        if (fileName[fileIndex + 1] == sentinel.c_str()) // detects if the next element is the sentinel
        {             // I did this so the user is not asked to continue when the program will end anyways.
            cout << "All done!" << endl;
            return 0;
        }
        
        cout << "Please enter 1 to continue or 0 to stop: ";
        cin >> choice;
        cout << endl;
    }
    
    cout << "All done!" << endl; // shows up when the user chooses 0 to stop.
    return 0;
}


//***********************************************************************
// Function readTable passes the filename, and references the table and size
// It reads in the table from the text file
// The functions has a reference for tblSize so we know
// how large the actual table is.
// returns true if the file can be read, false if otherwise
//***********************************************************************
bool readTable(string filename, int table[][MAXTBLSIZE], int &size)
{
    ifstream infile;
    infile.open(filename.c_str());
    
    if (infile.fail())
    {
        return false;
    }
    else
    {
        infile >> size;
        
        if (size > MAXTBLSIZE) // makes sure file table fits into 2D array
        {
            cout << "File table too large" << endl;
            infile.close();
            return false;
        }
        for (int r = 0; r < size; r++)
        {
            for (int c = 0; c < size; c++)
                infile >> table[r][c];
        }
        infile.close();
        
        return true;
    }
    
}


//***********************************************************************
// Function testTable references the table and passes the size.
// It tests if the table is a perfect square table
// it first finds the sum of the first row. If any other row, column,
// or diagonal does not match the sum, the function returns -1.
// If the table is a perfect square, the function returns the constant.
//***********************************************************************
int testTable(const int table[][MAXTBLSIZE], int size)
{
    int constant = 0;
    
    for (int r = 0; r < size; r++) // checks sum of each row
    {
        int sum = 0; // resets sum after each row
        for (int c = 0; c < size; c++)
        {
            if (r == 0) // only assigns to variable constant the sum of the first row. Uses this to compare others to.
            {
                constant += table[r][c];
                sum += table[r][c]; // this only happens once to bypass the sum != constant comparison later
            }
            else        // other rows' sum gets assigned to sum. This way, the variable constant is unchanged
                sum += table[r][c];
        }
        if (sum != constant) // bypassed the first time due to the comment on line 128.
            return -1;
    }
    
    for (int c = 0; c < size; c++)
    {
        int sum = 0; // resets sum after each column
        for (int r = 0; r < size; r++)
        {
            sum += table[r][c];
        }
        if (sum != constant)
            return -1;
    }
    
    int LRdiagSum = 0;
    int RLdiagSum = 0;
    for (int i = 0; i < size; i++) // finds sum of LR and RL diagonal
    {
        LRdiagSum += table[i][i];
        RLdiagSum += table[i][size - 1 - i];
    }
    if (LRdiagSum != constant || RLdiagSum != constant)
        return -1;

    return constant;
}


//***********************************************************************
// Function printTable references the table and passes the size and filename
// It prints the table to output.
// There is an if statement which only lets this function execute if the
// size is less than or equal to 8.
// returns nothing.
//***********************************************************************
void printTable(const int table[][MAXTBLSIZE], int size, string filename)
{
    cout << "File name: " << filename << endl; // consistent to output this every time. clear to user.
    cout << "Square Table Size: " << size << endl;
    
    cout << "-"; // leading em-dash to match length of table
    for (int i = 0; i < size; i++) // leading ceiling
        cout << "----"; // 4 dashes per number in row
    cout << endl;
    
    for (int r = 0; r < size; r++)
    {
        cout << "|"; // leading wall
        for (int c = 0; c < size; c++)
        {

                cout << setw(3) << table[r][c] << "|";
        }
        cout << endl;
        
        cout << "-"; // used to match length of table
        for (int i = 0; i < size; i++)
            cout << "----"; // 4 dashes per number in row
        cout << endl;
    }
}


//***********************************************************************
// Function printResults passes the table constant, filename, and the size
// It outputs a message either saying that the table
// is a perfect square with the constant, or a message saying that the
// table is not a perfect square.
// returns nothing.
//***********************************************************************
void printResults(int constant, string filename, int size) // pass filename to give info to user
{
    if (size <= 8) // only does this if the table is outputted
    {
        if (constant == -1)
        {
            cout << "This is not a Perfect Square Table" << endl << endl;
        }
        else
        {
            cout << "This is a Perfect Square Table with a constant of " << constant << "!" << endl << endl;
        }
    }
    else // does this whenever the user can not see the table. Reveals information to give clarity
    {
        if (constant == -1)
        {
            cout << "File " << filename << " does not contain a Perfect Square Table" << endl << endl;
        }
        else
        {
            cout << "File " << filename << " contains a Perfect Square Table" << endl //clarity to user
                 << "with a constant of " << constant << "!" << endl << endl;
        }
    }
    
}

/** Save the output below
 File name: t0.txt
 Square Table Size: 4
 -----------------
 | 16|  3|  2| 13|
 -----------------
 |  5| 10| 11|  8|
 -----------------
 |  9|  6|  7| 12|
 -----------------
 |  4| 15| 14|  1|
 -----------------
 This is a Perfect Square Table with a constant of 34!
 
 Please enter 1 to continue or 0 to stop: 1
 
 File name: t1.txt
 Square Table Size: 4
 -----------------
 | 16|  3|  2| 13|
 -----------------
 |  5| 10| 11|  8|
 -----------------
 |  9|  6|  7| 12|
 -----------------
 |  4| 15|  1| 14|
 -----------------
 This is not a Perfect Square Table
 
 Please enter 1 to continue or 0 to stop: 1
 
 File name: t2.txt
 Square Table Size: 5
 ---------------------
 |  3| 16|  9| 22| 15|
 ---------------------
 | 20|  8| 21| 14|  2|
 ---------------------
 |  7| 25| 13|  1| 19|
 ---------------------
 | 24| 12|  5| 18|  6|
 ---------------------
 | 11|  4| 17| 10| 23|
 ---------------------
 This is a Perfect Square Table with a constant of 65!
 
 Please enter 1 to continue or 0 to stop: 1
 
 Error: Input file "tA.txt" not found!
 Please enter 1 to continue or 0 to stop: 1
 
 File name: t3.txt
 Square Table Size: 6
 -------------------------
 | 35|  1|  6| 26| 19| 24|
 -------------------------
 |  3| 32|  7| 21| 23| 25|
 -------------------------
 | 31|  9|  2| 22| 27| 20|
 -------------------------
 |  8| 28| 33| 17| 10| 15|
 -------------------------
 | 30|  5| 34| 12| 14| 16|
 -------------------------
 |  4| 36| 29| 13| 11| 18|
 -------------------------
 This is not a Perfect Square Table
 
 Please enter 1 to continue or 0 to stop: 1
 
 File t4.txt contains a Perfect Square Table
 with a constant of 369!
 
 Please enter 1 to continue or 0 to stop: 1
 
 File t5.txt does not contain a Perfect Square Table
 
 Please enter 1 to continue or 0 to stop: 1
 
 File t6.txt does not contain a Perfect Square Table
 
 Please enter 1 to continue or 0 to stop: 1
 
 Error: Input file "t7.txt" not found!
 All done!
 Program ended with exit code: 0
 */
