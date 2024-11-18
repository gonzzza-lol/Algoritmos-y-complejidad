#include "costos.hpp"

vector<int> insertArr(26);
vector<int> deleteArr(26);
vector<vector<int>> replaceMatrix(26, vector<int>(26));
vector<vector<int>> transposeMatrix(26, vector<int>(26));

void fillArray(vector<int>& v, string file) {
    ifstream f;
    f.open(file);
    for (int i = 0;i < 26;++i) {
        f >> v[i];
    }
    f.close();
}

void fillMatrix(vector<vector<int>>& m, string file) {
    ifstream f;
    int input;
    f.open(file);
    for (int i = 0;i < 26;++i) {
        for (int j = 0;j < 26;++j) {
            f >> m[j][i];
        }
    }
    f.close();
}

int costo_sub(char a, char b) {
    return replaceMatrix[a - 97][b - 97];
}

int costo_ins(char a) {
    return insertArr[a - 97];
}

int costo_del(char a) {
    return deleteArr[a - 97];
}

int costo_trans(char a, char b) {
    return transposeMatrix[a - 97][b - 97];
}

void testTime(const string& doc) {
    ifstream archivo(doc);
    long long dpTime = 0;
    long long bfTime = 0;

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << doc << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        string s1, s2;
        iss >> s1 >> s2;

        if (s1 == "-") s1 = "";
        if (s2 == "-") s2 = "";

        auto start1 = high_resolution_clock::now();
        editDistDP(s1, s2);
        auto end1 = high_resolution_clock::now();
        dpTime += duration_cast<microseconds>(end1 - start1).count();

        auto start2 = high_resolution_clock::now();
        editDistBF(s1, s2);
        auto end2 = high_resolution_clock::now();
        bfTime += duration_cast<microseconds>(end2 - start2).count();
    }
    archivo.close();

    cout << "Tiempo usando DP: " << dpTime << " microsegundos\n";
    cout << "Tiempo usando BF: " << bfTime << " microsegundos\n";
}
