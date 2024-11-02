// COMSC-210 | Lab 26 | Xiao Zhang
#include <iostream>
#include <chrono>
#include <fstream>
#include <list>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
using namespace std::chrono;

const int MAX_SZ = 20000;

vector<string> ve;
list<string> li;
set<string> se;

int durations[4][3][15] = {0}; //This is a array for storing the time of each race

void read(string name, int turn); //Read the data from file
void sorting(int turn); //Sort the data in the container
void insert(int turn); //insert an element
void del(int turn); //delete an element
void printavg(); //print out the average time for each container

int main() {
    string name = "codes.txt";
    
    for (int i = 0; i < 15; i++) { //run 15 simulations as required
        read(name, i);
        sorting(i);
        insert(i);
        del(i);

        //we have to clear the container for the next round
        ve.clear();
        li.clear();
        se.clear();
    }
    

    printavg();
    
    return 0;
}

void read(string name, int turn) {
    string temp;
    ifstream file(name);
    auto start_ve = high_resolution_clock::now();
    
    while (file >> temp) {
        ve.push_back(temp);
    }
    
    auto end_ve = high_resolution_clock::now();
    
    durations[0][0][turn] = duration_cast<milliseconds>(end_ve - start_ve).count(); //put the time in the first column for the container vector
    
    file.close();
    
    file.open(name);
    auto start_li = high_resolution_clock::now();
    
    while (file >> temp) {
        li.push_back(temp);
    }
    
    auto end_li = high_resolution_clock::now();
    
    durations[0][1][turn] = duration_cast<milliseconds>(end_li - start_li).count(); //put the time in the second column for the container list
    
    file.close();
    
    file.open(name);
    auto start_se = high_resolution_clock::now();
    
    while (file >> temp) {
        se.insert(temp);
    }
    
    auto end_se = high_resolution_clock::now();
    
    durations[0][2][turn] = duration_cast<milliseconds>(end_se - start_se).count(); //put the time in the third column for the container set
    file.close();
}

void sorting(int turn) {
    auto start_ve = high_resolution_clock::now();
    
    sort(ve.begin(), ve.end());
    
    auto end_ve = high_resolution_clock::now();
    
    durations[1][0][turn] = duration_cast<milliseconds>(end_ve - start_ve).count();
    
    auto start_li = high_resolution_clock::now();
    li.sort();
    auto end_li = high_resolution_clock::now();
    durations[1][1][turn] = duration_cast<milliseconds>(end_li - start_li).count();
    
    durations[1][2][turn] = -1; // there's no sorting needed for set, so set the value to -1
}

void insert(int turn) {
    string code = "TESTCODE";
    
    auto start_ve = high_resolution_clock::now();
    
    ve.insert(ve.begin() + ve.size() / 2, code); //insert in the middle, same for the list as shown in line 119
    
    auto end_ve = high_resolution_clock::now();
    
    durations[2][0][turn] = duration_cast<milliseconds>(end_ve - start_ve).count();
    
    auto start_li = high_resolution_clock::now();
    
    auto it = li.begin();
    advance(it, li.size() / 2);
    li.insert(it, code);
    auto end_li = high_resolution_clock::now();
    
    durations[2][1][turn] = duration_cast<milliseconds>(end_li - start_li).count();
    
    auto start_se = high_resolution_clock::now();
    se.insert(code); //insert into set with no specific position
    auto end_se = high_resolution_clock::now();
    
    durations[2][2][turn] = duration_cast<milliseconds>(end_se - start_se).count();
}

void del(int turn) {
    auto start_ve = high_resolution_clock::now();
    ve.erase(ve.begin() + ve.size() / 2);  //delete the element in the middle, same for the list as shown in line 141
    auto end_ve = high_resolution_clock::now();
    
    durations[3][0][turn] = duration_cast<milliseconds>(end_ve - start_ve).count();
    
    auto start_li = high_resolution_clock::now();
    auto it = li.begin();
    advance(it, li.size() / 2);
    li.erase(it);
    auto end_li = high_resolution_clock::now();
    
    durations[3][1][turn] = duration_cast<milliseconds>(end_li - start_li).count();
    
    auto start_se = high_resolution_clock::now();
    auto it_se = se.begin();
    
    advance(it_se, se.size() / 2);
    se.erase(it_se); //delete the element in set with no specific position
    auto end_se = high_resolution_clock::now();
    
    durations[3][2][turn] = duration_cast<milliseconds>(end_se - start_se).count();
}

void printavg() { // Calculate and print average times for each operation and container
    cout << "Number of simulations: 15"<< endl;
    cout << "Operation\tVector\tList\tSet" << endl;

    string operations[4] = {"Read", "Sort", "Insert", "Delete"};
    
    for (int i = 0; i < 4; i++) {
        cout << operations[i] << "\t";
        
        for (int type = 0; type < 3; type++) {
            int total = 0;
            for (int turn = 0; turn < 15; turn++) {
                total += durations[i][type][turn];
            }
            int average;
            // Set average time (0 for sorting in set)
            if (type == 2 && i == 1) {
                average = 0;
            }
            else {
                average = total / 15;
            }

            cout << average << "\t";
        }
        cout << endl;
    }
}
