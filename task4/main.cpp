#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>

double h, a, b, lambda;
int n;

std::vector<double> fV, xV, Ak;
std::vector<std::vector<double>> AV;


std::vector<double> calculateSolutions(std::vector<std::vector<double>> matrix, std::vector<double> f, int n) {
    std::vector<double> x(n);
    double tmp;
    for (int i = 0; i < n; i++) {
        tmp = matrix[i][i];
        f[i] /= tmp;
        for (int j = n - 1; j >= i; j--) {
            matrix[i][j] /= tmp;
        }
        for (int j = i + 1; j < n; j++) {
            tmp = matrix[j][i];
            f[j] -= tmp * f[i];
            for (int k = n - 1; k >= i; k--) {
                matrix[j][k] -= tmp * matrix[i][k];
            }
        }
    }
    /*обратный ход*/
    x[n - 1] = f[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = f[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= matrix[i][j] * x[j];
        }
    }
    return x;
}

double K(double x, double s) {
    return tanh(sqrt(x*x+s*s+1));
}

double f(double x) {
    return 2*sin(x)+1;
}


void fillAV() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            if (i == j) {
                AV[i][j] = 1.0 - lambda * Ak[j] * K(a + i * h, a + j * h);
            } else {
                AV[i][j] = -lambda * Ak[j] * K(a + i * h, a + j * h);
            }
        }
    }
}

void fillF() {
    for (int i = 0; i <= n; i++) {
        fV[i] = f(a + i * h);
    }
}

void printX(std::vector<double> x) {
    for (double item : x) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

void calculateSolutions() {
    Ak.assign(n, h);
    Ak[n] = h/2;
    Ak[0]=h/2;
    fillAV();
    fillF();
    xV = calculateSolutions(AV, fV, n + 1);
    std::cout << "x For ex Fred ";
    printX(xV);
}

double lagranzh(double t) {
    double buffCh;
    double buffZn;
    double mnL = 0;
    for (int j = 0; j <= n; j++) {
        buffCh = 1;
        buffZn = 1;
        for (int i = 0; i <= n; i++) {
            if (i != j) {
                buffCh *= (t - (a + i * h));
                buffZn *= ((a + j * h) - (a + i * h));
            }
        }
        mnL += buffCh / buffZn * xV[j];
    }
    return mnL;
}

void calcInPointV() {
    double point = (a + b) / 2;
    std::cout<<"Fred at point ";
    double sol = f(point);
    for (int i = 0; i <= n; i++) {
        sol += lambda * xV[i] * K(point, a + i * h) * Ak[i];
    }

    std::cout<<sol;
}


int main() {

    std::cout << "\nSolution method mechanic sq\n";
    n = 100;
    a = 0;
    b = 0.5;
    h = (b - a) / n;
    lambda = 0.5;
    Ak.resize(n + 1);
    fV.resize(n + 1);

    AV.resize(n + 1, std::vector<double>(n + 1));
    std::cout << "nodes";
    for (int i = 0; i <= n; i++) {
        std::cout << (a + i * h) << " ";
    }
    std::cout << "\n";
    Ak.assign(n+1,h);
    Ak[0]=h/4;
    Ak[n] = h/4;
    std::cout << "Koef Ak:";
    printX(Ak);

    calculateSolutions();
    calcInPointV();

    return 0;
}

