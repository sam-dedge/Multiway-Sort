#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>
#include <cstdio>

using namespace std;

const int M = 22;
int passNum = 0;

typedef struct tuple
{
    string ename;
    double salary;
    int eid, age;
} Block;

bool eidSort(Block a, Block b) {
    return a.eid < b.eid;
}

bool minRecord(Block a, Block b) {
    return a.eid < b.eid;
}

void deleteRuns(int numberOfRuns, int delPassNum) {
    // Delete Code
    //cout << "In Delete - delPassNum = " << delPassNum << endl;
    for(int k=0; k<numberOfRuns; k++) {
        string toDel = to_string(delPassNum) + "run" + to_string(k+1) + ".txt";
        std::remove(toDel.c_str());
    }
}

int read() {
    std::array<Block, 22> record;
    //Block temp;

    // Read File
    fstream fin;
    fin.open("Emp.csv");

    string line, word;
    std::vector<string> tuple;

    int runNum = 1;
    int i=0;

    // PASS 0
    while (getline(fin, line, '\n') && passNum == 0) {
        stringstream ss(line);

        tuple.clear();
        while(getline(ss, word, ',')) {
            tuple.push_back(word);
        }

        // Weird representation of double? Why? Affects anything?
        /*if(stoi(tuple[0]) == 253754){
            cout << "HERE - " << tuple[3] << "   " << stoi(tuple[3]);
            int x = stoi(tuple[3]);
            double d = (double) x;
            double db = 999999+1;
            cout << "Double Check d - " << d << endl;
            cout << "Double Check db - " << db << endl;
        }*/

        // Fill block with record in tuple
        record[i].eid = stoi(tuple[0]);
        record[i].ename = tuple[1];
        record[i].age = stoi(tuple[2]);
        record[i].salary = stod(tuple[3]);

        //cout << record[i].ename << endl;
        i++;

        //Writes after Memory is full as Memory available = M (global)
        if(i>=M || fin.eof()) {
            //cout << "Here" << endl;

            sort(record.begin(), record.end(), eidSort);

            // Writing sorted record[1..M] into run file
            string filename = to_string(passNum) + "run" + to_string(runNum) + ".txt";
            std::ofstream outFile(filename);
            for (const auto &r : record){
                if(r.eid == 0)
                    continue;
                outFile << r.eid << "," << r.ename << "," << r.age << "," << r.salary << "\n";
            }
            runNum++;
            i = 0;
            //cout << "After Sorting... 2nd Rec: " << record[1].ename << "   " << record[1].eid << endl;

            // Resets record by putting NULL or 0 in record[1..M]
            memset(&record, '\0', sizeof(record));
        }

    }

    passNum++;
    fin.close();
    return runNum-1;

}

int passIth(int numOfRuns, int maxPasses) {
    cout << "-------Ongoing-------" << endl;
    cout << "Pass Number: " << passNum << "\t" << "Runs to Merge: " << numOfRuns << endl;
    cout << "...\n" << ".....\n" << "........." << endl;
    int runsLeftToMerge = numOfRuns;

    int mergePointers;
    if(numOfRuns>=M)
        mergePointers = M-1;
    else
        mergePointers = runsLeftToMerge;

    fstream fin[mergePointers];

    //cout << "Here2";
    std::array<Block, 21> record;
    Block outBuf;
    std::vector<string> tuple;
    string line, word;

    //cout << record[1].ename;
    //cout << "\n\nMerge Pointers = " << mergePointers << endl;

    int j=0; // J = New number of Runs of Pass i+1
    // When i = mergePointers, Values are initialized again and
    for(int i=0, runNum=1; i<=mergePointers && mergePointers >= 1; i++, runNum++) {

        if(i != mergePointers) {

            string filename;
            filename = to_string(passNum-1) + "run" + to_string(runNum) + ".txt";
            fin[i].open(filename);

            //cout << "Here3" << "  " << runNum << "   " << i << "  " << mergePointers << endl;
            //cout << &fin[i] << endl;

            getline(fin[i], line, '\n');
            stringstream ss(line);
            //cout << "Here4" << "   " << line;
            tuple.clear();
            while(getline(ss, word, ',')) {
                tuple.push_back(word);
            }

            record[i].eid = stoi(tuple[0]);
            record[i].ename = tuple[1];
            record[i].age = stoi(tuple[2]);
            record[i].salary = stod(tuple[3]);
            //cout << "Here" << i << "  " << record[i].eid << "   " << record[i].ename << endl;
        }
        else {
            //cout << "-----------------Sorted Run----------------" << j << "  " << mergePointers << endl;

            string outFilename;
            if(maxPasses == passNum)
                outFilename = "EmpSorted.csv";
            else
                outFilename = to_string(passNum) + "run" + to_string(j+1) + ".txt";
            //cout << outFilename << endl;

            ofstream outFile;
            outFile.open(outFilename, ios::app);

            while(true) {
                Block *ptr = std::min_element(record.begin(), record.end(), minRecord);
                // Block outBuf contains smallest tuple
                outBuf = *ptr;

                if(outBuf.eid == 999999999) {
                    //cout << "Break Reason - minEid = " << outBuf.eid << endl;
                    break;
                }


                int index = ptr - record.begin();

                if(fin[index].eof()) {
                    memset(&record[index], '\0', sizeof(Block));
                    // Arbitrarily long number to avoid collision with minRecord.
                    record[index].eid = 999999999;
                    continue;
                }
                else
                    getline(fin[index], line, '\n');

                //cout << line << endl;
                stringstream ss(line);
                tuple.clear();
                while(getline(ss, word, ',')) {
                    tuple.push_back(word);
                }
                record[index].eid = stoi(tuple[0]);
                record[index].ename = tuple[1];
                record[index].age = stoi(tuple[2]);
                record[index].salary = stod(tuple[3]);

                //  ---------TURN to OutputFile---------
                // Appends to EOF
                outFile << outBuf.eid << "," << outBuf.ename << "," << outBuf.age << "," << outBuf.salary << "\n";

                // cout << "outBuf: " << outBuf.eid << "   " << outBuf.ename << endl;
                //cout << "Record at 8: " << record[8].ename << "  " << index;
            }

            //cout << "Here2   " << mergePointers << endl;

            // New Initialising
            outFile.close();

            // i will be initialized to 0 after getting incremented after this iteration of loop
            i = -1;
            j++;

            for(int k=0; k<mergePointers; k++)
                fin[k].close();
            runsLeftToMerge = runsLeftToMerge - mergePointers;
            if(runsLeftToMerge>=M)
                mergePointers = M-1;
            else
                mergePointers = runsLeftToMerge;

            memset(&record, '\0', sizeof(record));
            for(int k=0; k<22; k++)
                record[k].eid = 999999999;

            runNum = runNum - 1; //The next continue statement skips one run file
        }

    }

    cout << "\nEnd of Pass Num " << passNum << " with # of Runs Created = " << j << endl << endl;
    deleteRuns(numOfRuns , passNum-1);
    passNum++;
    return j;

}

int main() {
    int numOfRuns = read();

    double x, base;
    x = (float)numOfRuns/M;
    base = M-1;
    int maxPasses = ceil(log(x)/log(base)) + 1;
    for(int i=1; i<=maxPasses; i++) {
        numOfRuns = passIth(numOfRuns, maxPasses);
    }

}
