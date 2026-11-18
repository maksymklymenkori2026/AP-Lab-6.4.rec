// Lab 6.4.rec
// Variant 13

#include <iostream>
#include <time.h>
#include <iomanip>
#include <cmath>

using namespace std;

void Create(double* a, const int n, const double Low, const double High, int i = 0) {
    if (i >= n)
        return;
    a[i] = Low + (High - Low) * rand() / RAND_MAX;
    Create(a, n, Low, High, i + 1);
}

void Print(const double* a, const int n, int i = 0)
{
    if (i >= n) {
        cout << endl;
        return;
    }
    cout << setw(8) << a[i];
    Print(a, n, i + 1);
}

// 1.1. Кількість елементів зі значеннями в діапазоні [A; B]
int CountInRange(const double* a, const int n, const double A, const double B, int i = 0) {
    if (i >= n)
        return 0;
    return (a[i] >= A && a[i] <= B ? 1 : 0) + CountInRange(a, n, A, B, i + 1);
}

// Індекс першого максимального елемента серед a[i..n-1]
int IndexOfMax(const double* a, const int n, int i = 0) {
    if (i == n - 1)
        return i;
    int iMax = IndexOfMax(a, n, i + 1);
    return a[i] >= a[iMax] ? i : iMax;
}

// Сума елементів a[i..n-1]
double SumFrom(const double* a, const int n, int i) {
    if (i >= n)
        return 0;
    return a[i] + SumFrom(a, n, i + 1);
}

// 1.2. Сума елементів, розташованих після максимального
double SumAfterMax(const double* a, const int n) {
    return SumFrom(a, n, IndexOfMax(a, n) + 1);
}

// Індекс елемента з парним індексом (починаючи зі start) з найбільшим модулем
int IndexOfMaxAbsEven(const double* a, const int n, const int start) {
    if (start + 2 >= n)
        return start;
    int iMax = IndexOfMaxAbsEven(a, n, start + 2);
    return fabs(a[start]) >= fabs(a[iMax]) ? start : iMax;
}

void Swap(double& x, double& y) {
    double t = x;
    x = y;
    y = t;
}

// 2. Впорядкування елементів з парними індексами за спаданням модулів,
// інші елементи залишаються на своїх місцях
void SortEvenByAbsDesc(double* a, const int n, int i = 0) {
    if (i >= n)
        return;
    Swap(a[i], a[IndexOfMaxAbsEven(a, n, i)]);
    SortEvenByAbsDesc(a, n, i + 2);
}

int main() {

    srand((unsigned)time(NULL));

    int n;
    double A, B;
    cout << "n = "; cin >> n;
    cout << "A = "; cin >> A;
    cout << "B = "; cin >> B;
    if (n <= 0) {
        cout << "n must be positive" << endl;
        return 1;
    }

    double* a = new double[n];

    Create(a, n, -50, 50);
    cout << fixed << setprecision(2);
    cout << "Original array: " << endl;
    Print(a, n);
    cout << endl;

    cout << "Count of the elements in [A; B]: " << CountInRange(a, n, A, B) << endl;
    cout << "Sum of the elements after max: " << SumAfterMax(a, n) << endl;

    SortEvenByAbsDesc(a, n);
    cout << endl;
    cout << "Modified array: " << endl;
    Print(a, n);

    delete[] a;
    return 0;
}