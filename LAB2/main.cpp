#include <bits/stdc++.h>
#include "costos.hpp"
using namespace std;

int editDistRecAux(string s1, string s2, int i, int j) {
    int ins, del, sub, trans = INT_MAX / 2;
    int res = 0;

    if (i == 0) {
        for (int n = j; n > 0; --n) {
            res += costo_ins(s2[n - 1]);
        }
        return res;
    }

    else if (j == 0) {
        for (int n = i; n > 0; --n) {
            res += costo_del(s1[n - 1]);
        }
        return res;
    }

    else if (s1[i - 1] == s2[j - 1]) {
        return editDistRecAux(s1, s2, i - 1, j - 1);
    }

    ins = editDistRecAux(s1, s2, i, j - 1) + costo_ins(s2[j - 1]);
    del = editDistRecAux(s1, s2, i - 1, j) + costo_del(s1[i - 1]);
    sub = editDistRecAux(s1, s2, i - 1, j - 1) + costo_sub(s1[i - 1], s2[j - 1]);
    if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
        trans = editDistRecAux(s1, s2, i - 2, j - 2) + costo_trans(s1[i - 2], s1[i - 1]);
    }
    res = min({ ins,del,sub,trans });

    return res;
}

int editDistDPAux(string s1, string s2, int i, int j, vector<vector<int>>& dp) {
    if (dp[i][j] != -1) return dp[i][j];

    int ins, del, sub, trans = INT_MAX / 2;
    int res = 0;

    if (i == 0) {
        for (int n = j; n > 0; --n) {
            res += costo_ins(s2[n - 1]);
        }
        return res;
    }

    else if (j == 0) {
        for (int n = i; n > 0; --n) {
            res += costo_del(s1[n - 1]);
        }
        return res;
    }

    else if (s1[i - 1] == s2[j - 1]) {
        return editDistDPAux(s1, s2, i - 1, j - 1, dp);
    }

    ins = editDistDPAux(s1, s2, i, j - 1, dp) + costo_ins(s2[j - 1]);
    del = editDistDPAux(s1, s2, i - 1, j, dp) + costo_del(s1[i - 1]);
    sub = editDistDPAux(s1, s2, i - 1, j - 1, dp) + costo_sub(s1[i - 1], s2[j - 1]);
    if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
        trans = editDistDPAux(s1, s2, i - 2, j - 2, dp) + costo_trans(s1[i - 2], s1[i - 1]);
    }
    dp[i][j] = min({ ins,del,sub,trans });

    return dp[i][j];
}

int editDistBF(string& s1, string& s2) {
    int res = editDistRecAux(s1, s2, s1.length(), s2.length());
    //cout << "Distancia de edicion" << res << '\n';
    return res;
}

int editDistDP(string& s1, string& s2) {
    int l1 = s1.length();
    int l2 = s2.length();
    vector<vector<int>> dp(l1 + 1, vector<int>(l2 + 1, -1));
    int res = editDistDPAux(s1, s2, l1, l2, dp);
    //cout << "Distancia de edicion" << res << '\n';
    return res;
}

int main() {
    fillArray(insertArr, "./dataSets/cost_insert.txt");
    fillArray(deleteArr, "./dataSets/cost_delete.txt");
    fillMatrix(replaceMatrix, "./dataSets/cost_replace.txt");
    fillMatrix(transposeMatrix, "./dataSets/cost_transpose.txt");
    testTime("./dataSets/dataset.txt");
    return 0;
}