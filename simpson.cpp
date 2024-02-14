#include <iostream>
#include <cmath>

double f(double x) {
    return exp(x); 
}

double simpsons_rule(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = f(a) + f(b); 

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += i % 2 == 0 ? 2 * f(x) : 4 * f(x); 
    }

    return (h / 3) * sum;
}

int main() {
    double lb = 0;    
    double ub = 10;    
    int n = 100000;     

    double integral = simpsons_rule(lb, ub, n);
    
    std::cout << "Result of the integral using Simpson's Rule: " << integral << std::endl;
    
    return 0;
}
