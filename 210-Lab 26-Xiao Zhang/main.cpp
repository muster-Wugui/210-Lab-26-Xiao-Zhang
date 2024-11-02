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

int durations[4][3][15] = {0};

void read(string name, int turn);
void sorting(int turn);
void insert(int turn);
void del(int turn);
void printavg();

int main() {
    string name = "codes.txt";
    
    for (int i = 0; i < 15; i++) {
        read(name, i);
        sorting(i);
        insert(i);
        del(i);

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
    
    durations[0][0][turn] = duration_cast<milliseconds>(end_ve - start_ve).count();
    
    file.close();
    
    file.open(name);
    auto start_li = high_resolution_clock::now();
    
    while (file >> temp) {
        li.push_back(temp);
    }
    
    auto end_li = high_resolution_clock::now();
    
    durations[0][1][turn] = duration_cast<milliseconds>(end_li - start_li).count();
    
    file.close();
    
    file.open(name);
    auto start_se = high_resolution_clock::now();
    
    while (file >> temp) {
        se.insert(temp);
    }
    
    auto end_se = high_resolution_clock::now();
    
    durations[0][2][turn] = duration_cast<milliseconds>(end_se - start_se).count();
    file.close();
}

void sorting() {
    auto start_ve = high_resolution_clock::now();
    sort(ve.begin(), ve.end());
    auto end_ve = high_resolution_clock::now();
    auto duration_ve = duration_cast<milliseconds>(end_ve - start_ve);
    
    auto start_li = high_resolution_clock::now();
    li.sort();
    auto end_li = high_resolution_clock::now();
    auto duration_li = duration_cast<milliseconds>(end_li - start_li);
    
    int duration_se = -1;
    
    cout << "Sort\t" << duration_ve.count() << "\t" << duration_li.count() << "\t" << duration_se << endl;
}

void insert() {
    string code = "TESTCODE";
    
    auto start_ve = high_resolution_clock::now();
    long middle = ve.size() / 2;
    ve.insert(ve.begin() + middle, code);
    auto end_ve = high_resolution_clock::now();
    auto duration_ve = duration_cast<milliseconds>(end_ve - start_ve);
    
    auto start_li = high_resolution_clock::now();
    auto it = li.begin();
    advance(it, li.size() / 2);
    li.insert(it, code);
    auto end_li = high_resolution_clock::now();
    auto duration_li = duration_cast<milliseconds>(end_li - start_li);
    
    auto start_se = high_resolution_clock::now();
    se.insert(code);
    auto end_se = high_resolution_clock::now();
    auto duration_se = duration_cast<milliseconds>(end_se - start_se);
    
    cout << "Insert\t" << duration_ve.count() << "\t" << duration_li.count() << "\t" << duration_se.count() << endl;
}

void del() {
    auto start_ve = high_resolution_clock::now();
    long middle = ve.size() / 2;
    ve.erase(ve.begin() + middle);
    auto end_ve = high_resolution_clock::now();
    auto duration_ve = duration_cast<milliseconds>(end_ve - start_ve);
    
    auto start_li = high_resolution_clock::now();
    auto it = li.begin();
    advance(it, li.size() / 2);
    li.erase(it);
    auto end_li = high_resolution_clock::now();
    auto duration_li = duration_cast<milliseconds>(end_li - start_li);
    
    auto start_se = high_resolution_clock::now();
    auto it_se = se.begin();
    advance(it_se, se.size() / 2);
    se.erase(it_se);
    auto end_se = high_resolution_clock::now();
    auto duration_se = duration_cast<milliseconds>(end_se - start_se);
    
    cout << "Delete\t" << duration_ve.count() << "\t" << duration_li.count() << "\t" << duration_se.count() << endl;
}
