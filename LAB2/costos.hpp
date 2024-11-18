#ifndef COSTOS_HPP
#define COSTOS_HPP

#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

extern vector<int> insertArr;
extern vector<int> deleteArr;
extern vector<vector<int>> replaceMatrix;
extern vector<vector<int>> transposeMatrix;

void fillArray(vector<int>& v, string file);
void fillMatrix(vector<vector<int>>& m, string file);
int costo_sub(char a, char b);
int costo_ins(char a);
int costo_del(char a);
int costo_trans(char a, char b);
int editDistRecAux(string s1, string s2, int i, int j);
int editDistDPAux(string s1, string s2, int i, int j, vector<vector<int>>& dp);
int editDistBF(string& s1, string& s2);
int editDistDP(string& s1, string& s2);
void testTime(const string& doc);
#endif
