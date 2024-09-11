#include <vector>
#include <random>
#include "datasets.cpp"

using namespace std;

// ALGORITMOS DE ORDENAMIENTO
void insertionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(vector<int> &arr, int left, int mid, int right)
{
    // Se calcula el tamano de los subarreglos
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    // Se copian los valores de arr en los
    // subarreglos auxiliares L y R
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Se mezclan L y R en el orden correcto
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int partition(vector<int> &arr, int low, int high)
{

    // Pivote random
    int pos = low + (rand() % (high - low + 1));
    int pivot = arr[pos];
    if (pos != high)
        swap(arr[pos], arr[high]);

    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int> &arr, int low, int high)
{

    if (low < high)
    {

        int pi = partition(arr, low, high);

        // Llamada recurisva para hacer quicksort
        // en la mitad de mayores y de menores
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// La siguiente funcion es sort() de la libreria estandar

// ALGORITMOS DE MULTIPLICACION DE MATRICES
void iterativoTrad(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C)
{
    int N = A.size();
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void iterativoOpt(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C, int N)
{
    // Transponer la vector<vector<int>> B
    vector<vector<int>> B_trans(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            B_trans[i][j] = B[j][i];
        }
    }

    // Multiplicación de matrices optimizada
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                C[i][j] += A[i][k] * B_trans[j][k];
            }
        }
    }
}

vector<vector<int>> add_m(vector<vector<int>> A, vector<vector<int>> B, int split, int m = 1)
{
    for (auto i = 0; i < split; i++)
    {
        for (auto j = 0; j < split; j++)
        {
            A[i][j] = A[i][j] + (m * B[i][j]);
        }
    }
    return A;
}

vector<vector<int>> strassen(vector<vector<int>> A, vector<vector<int>> B)
{
    int col_1 = A[0].size();
    int row_1 = A.size();
    int col_2 = B[0].size();
    int row_2 = B.size();

    vector<int> result_matrix_row(col_2, 0);
    vector<vector<int>> result_m(row_1, result_matrix_row);

    if (col_1 == 1)
        result_m[0][0] = A[0][0] * B[0][0];
    else
    {
        int split = col_1 / 2;

        vector<int> row_vector(split, 0);

        vector<vector<int>> a00(split, row_vector);
        vector<vector<int>> a01(split, row_vector);
        vector<vector<int>> a10(split, row_vector);
        vector<vector<int>> a11(split, row_vector);
        vector<vector<int>> b00(split, row_vector);
        vector<vector<int>> b01(split, row_vector);
        vector<vector<int>> b10(split, row_vector);
        vector<vector<int>> b11(split, row_vector);

        for (auto i = 0; i < split; i++)
            for (auto j = 0; j < split; j++)
            {
                a00[i][j] = A[i][j];
                a01[i][j] = A[i][j + split];
                a10[i][j] = A[split + i][j];
                a11[i][j] = A[i + split][j + split];
                b00[i][j] = B[i][j];
                b01[i][j] = B[i][j + split];
                b10[i][j] = B[split + i][j];
                b11[i][j] = B[i + split][j + split];
            }

        vector<vector<int>> p(strassen(a00, add_m(b01, b11, split, -1)));
        vector<vector<int>> q(strassen(add_m(a00, a01, split), b11));
        vector<vector<int>> r(strassen(add_m(a10, a11, split), b00));
        vector<vector<int>> s(strassen(a11, add_m(b10, b00, split, -1)));
        vector<vector<int>> t(strassen(add_m(a00, a11, split), add_m(b00, b11, split)));
        vector<vector<int>> u(strassen(add_m(a01, a11, split, -1), add_m(b10, b11, split)));
        vector<vector<int>> v(strassen(add_m(a00, a10, split, -1), add_m(b00, b01, split)));

        vector<vector<int>> result_matrix_00(
            add_m(add_m(add_m(t, s, split), u, split), q, split, -1));
        vector<vector<int>> result_matrix_01(add_m(p, q, split));
        vector<vector<int>> result_matrix_10(add_m(r, s, split));
        vector<vector<int>> result_matrix_11(
            add_m(add_m(add_m(t, p, split), r, split, -1), v, split, -1));

        for (auto i = 0; i < split; i++)
            for (auto j = 0; j < split; j++)
            {
                result_m[i][j] = result_matrix_00[i][j];
                result_m[i][j + split] = result_matrix_01[i][j];
                result_m[split + i][j] = result_matrix_10[i][j];
                result_m[i + split][j + split] = result_matrix_11[i][j];
            }

        a00.clear();
        a01.clear();
        a10.clear();
        a11.clear();
        b00.clear();
        b01.clear();
        b10.clear();
        b11.clear();
        p.clear();
        q.clear();
        r.clear();
        s.clear();
        t.clear();
        u.clear();
        v.clear();
        result_matrix_00.clear();
        result_matrix_01.clear();
        result_matrix_10.clear();
        result_matrix_11.clear();
    }
    return result_m;
}

int main()
{
    // int dimension = pow(2, *aqui va la potencia para darle dimension a la matriz*);
    // vector<vector<int>> A = generateRandomMatrix(dimension);
    // vector<vector<int>> B = generateRandomMatrix(dimension);
    // vector<vector<int>> C(dimension, vector<int>(dimension));

    // int largo = *aqui va el largo de la lista*
    // vector<int> vec = createVector(largo);
    // kOrderVector(vec, *aqui va el nivel de "desorden" del vector*);
    // randomizeVector(vec);

    return 0;
}