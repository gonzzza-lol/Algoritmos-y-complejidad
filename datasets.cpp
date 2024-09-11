#include <vector>
#include <algorithm>
#include <random>

#define SEED 2050

using namespace std;

// Crea vectores con elementos desde
// el 0 hasta size-1

vector<int> createVector(int size)
{
    vector<int> vec(size);
    for (int i = 0; i < size; ++i)
    {
        vec[i] = i + 1;
    }
    return vec;
}

// Mueve los elementos k posiciones
// para generar listas semi-ordenadas

void kOrderVector(vector<int> &vec, int k)
{
    mt19937 g(SEED);
    int size = vec.size();
    for (int i = 0; i < size; ++i)
    {
        int j = i + (uniform_int_distribution<>(0, k)(g) % (size - i));
        if (j < size)
        {
            std::swap(vec[i], vec[j]);
        }
    }
}

// Desordena la lista

void randomizeVector(vector<int> &vec)
{
    mt19937 g(SEED);
    shuffle(vec.begin(), vec.end(), g);
}

// Generador de matrcies

vector<vector<int>> generateRandomMatrix(int n)
{
    vector<vector<int>> matrix(n, vector<int>(n));
    mt19937 gen(SEED);
    uniform_int_distribution<> distrib(0, 10000);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            matrix[i][j] = distrib(gen);
        }
    }

    return matrix;
}