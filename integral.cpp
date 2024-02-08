#include <iostream>
#include <stdio.h>
double f(double x){
    return exp(x);                  // Put mathematical expression to integrate here
}
int main(){
    double ub = 10;                 // Upper Bound
    double lb = 0;                  // Lower Bound
    double inf = 999999999;         // Psuedo Infinity
    double h = (ub-lb)/inf;         // Infitessimal Increment
    double sum = 0;                 // Reimann Sum
    for(int i=0; i<=inf; i++){
        sum = sum + (f(lb+(i*h)))*h ;  // Area calculation
    }
    std::cout << "Result of the integral is " << sum << std::endl; //display result
    return 0;
}

