#include <functional>
#include <cmath>
#include <iomanip>
#include<iostream>

double function2(double x) {
    return cos(x) / (1 + x * x);
}


double CalcIntegral(double a, double h, int n) {
    int i;
    double result;

    result = 0;

    for (i = 0; i < n; i++) {
        result += function2(a + h * (i + 0.5));
    }

    result *= h;

    std::cout << "integral is: \n" << std::setprecision(15);
    return result;
}

double SIM(double a, double b, double h, int n) {
    int i;
    double result;

    result = 0;


    for (i = 1; i < n; i++) {

        result += 2 * function2(a + h * (i)) +
                  4 * function2(a + h * (i) - h / 2); //Вычисляем в средней точке и добавляем в сумму
    }
    result += function2(a) + function2(b) + 4 * function2(a + h * (i) - h / 2);
    result *= h / 6;

    std::cout << "integral sim is: \n" << std::setprecision(15) << result;
    return result;
}

void task2() {
    double a = 0, b = 2, n1 = 500, n2 = 1000, r1, r2, rS1, rS2;

    double h1 = (b - a) / n1;
    double h2 = (b - a) / n2;
    double i1 = CalcIntegral(0, h1, 500);
    std::cout << "with h=" << h1 << "\n";
    double i2 = CalcIntegral(0, h2, 1000);
    std::cout << "with h=" << h2 << "\n";
    double C1 = ((i2 - i1) / (h1 * h1 - h2 * h2));
    r1 = C1 * h1;
    r2 = C1 * h2;
    std::cout << "C1 " << C1 << "\n" << "r1=" << r1 << "\n" << "r2=" << r2 << "\n";
    double iS1 = SIM(a, b, h1, 500);
    std::cout << "with h=" << h1 << "\n";
    double iS2 = SIM(a, b, h2, 1000);
    std::cout << "with h=" << h1 << "\n";
    double C2 = ((iS2 - iS1) / (h1 * h1 - h2 * h2));
    rS1 = C2 * h1;
    rS2 = C2 * h2;
    std::cout << "C2 " << C2 << "\n" << "rS1=" << rS1 << "\n" << "rS2=" << rS2 << "\n";
    std::cout << "h1 :r1-rS1\n " << std::setprecision(15) << r1 - rS1 << "\n" << "h2 :r2-rS2\n" << r2 - rS2 << "\n";

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

auto f3(double t) {
    return std::exp(3 * t) * (std::pow(cos(std::sqrt(t * t + 1)), 2) + 2);

};

double MRT(std::pair<double, double> interval,
           double step) {

    double x = interval.first;
    double result = 0.0;

    while (x+step < interval.second) {

        result += (f3(x + step/2));
        x += step;

    }

    return step * result;
}

auto integral(double x, double step) {
    return MRT({1, x}, step) - 2;
}

auto newthon(std::pair<double, double> interval, double step, double eps = 1e-6) {

    auto left = interval.first;
    auto right = interval.second;

    if (integral(left, step) * integral(right, step) >= 0) {
        throw;
    }
    double xn_1 = (right + left) / 2;
    double xn = left;
    while (fabs(xn - xn_1) > eps) {
        xn = xn_1;
        xn_1 = xn - integral(xn, step) / (f3(xn));

    }

    return xn_1;
}


void task3() {

    double step = 0.0000001;

    auto x = newthon({1, 2}, step);

    std::cout << std::setprecision(9) <<"x = "<<x << "\n" <<"func = "<< integral(x, step) << "\n";
}

int main() {
    task3();
    return 0;
}