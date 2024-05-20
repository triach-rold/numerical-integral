#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <map>
class Parser {
public:
    Parser(const std::string& expression) : expr(expression), pos(0) {}

    double parse() {
        pos = 0;
        return parseExpression();
    }
private:
    std::string expr;
    size_t pos;

    double parseExpression() {
        double result = parseTerm();
        while (pos < expr.size()) {
            if (expr[pos] == '+') {
                pos++;
                result += parseTerm();
            } else if (expr[pos] == '-') {
                pos++;
                result -= parseTerm();
            } else {
                break;
            }
        }
        return result;
    }
    double parseTerm() {
        double result = parseFactor();
        while (pos < expr.size()) {
            if (expr[pos] == '*') {
                pos++;
                result *= parseFactor();
            } else if (expr[pos] == '/') {
                pos++;
                double divisor = parseFactor();
                if (divisor == 0) throw std::runtime_error("Division by zero");
                result /= divisor;
            } else {
                break;
            }
        }
        return result;
    }
    double parseFactor() {
        double result = parsePrimary();
        while (pos < expr.size()) {
            if (expr[pos] == '^') {
                pos++;
                result = pow(result, parsePrimary());
            } else {
                break;
            }
        }
        return result;
    }
    double parsePrimary() {
        if (expr[pos] == '(') {
            pos++;
            double result = parseExpression();
            if (pos < expr.size() && expr[pos] == ')') {
                pos++;
            } else {
                throw std::runtime_error("Mismatched parentheses");
            }
            return result;
        } else if (isalpha(expr[pos])) {
            return parseFunction();
        } else {
            return parseNumber();
        }
    }
    double parseNumber() {
        size_t startPos = pos;
        if (expr[pos] == '-') {
            pos++;
        }
        while (pos < expr.size() && (isdigit(expr[pos]) || expr[pos] == '.')) {
            pos++;
        }
        return std::stod(expr.substr(startPos, pos - startPos));
    }

    double parseFunction() {
        std::string func;
        while (pos < expr.size() && isalpha(expr[pos])) {
            func += expr[pos++];
        }

        if (func == "e") {
            return M_E;
        }

        if (pos < expr.size() && expr[pos] == '(') {
            pos++;
            double arg = parseExpression();
            if (pos < expr.size() && expr[pos] == ')') {
                pos++;
            } else {
                throw std::runtime_error("Mismatched parentheses");
            }
            if (func == "sin") return sin(arg);
            if (func == "cos") return cos(arg);
            if (func == "tan") return tan(arg);
            if (func == "cosec") return 1.0 / sin(arg);
            if (func == "sec") return 1.0 / cos(arg);
            if (func == "cot") return 1.0 / tan(arg);
            if (func == "sqrt") return sqrt(arg);
            if (func == "abs") return fabs(arg);
            if (func == "exp") return exp(arg);
            if (func == "sgn") return (arg > 0) - (arg < 0);

            throw std::runtime_error("Unknown function: " + func);
        }

        throw std::runtime_error("Unexpected identifier: " + func);
    }
};
double evaluate_function(const std::string& expression, double x) {
    std::string replacedExpression;
    for (size_t i = 0; i < expression.size(); ++i) {
        if (expression[i] == 'x') {
            replacedExpression += std::to_string(x);
        } else {
            replacedExpression += expression[i];
        }
    }
    Parser parser(replacedExpression);
    return parser.parse();
}
double simpsons_rule(const std::string& expression, double lower_bound, double upper_bound, int n) {
    if (n % 2 != 0) {
        throw std::invalid_argument("Simpson's rule requires an even number of intervals.");
    }
    double h = (upper_bound - lower_bound) / n;
    double sum = evaluate_function(expression, lower_bound) + evaluate_function(expression, upper_bound);

    for (int i = 1; i < n; i++) {
        double x = lower_bound + i * h;
        if (i % 2 == 0) {
            sum += 2 * evaluate_function(expression, x);
        } else {
            sum += 4 * evaluate_function(expression, x);
        }
    }
    return sum * h / 3;
}
int main(int argc, char* argv[]) {
    if (argc != 4 && argc != 6 && argc != 7) {
        std::cerr << "\033[1;31mUsage:\033[0m " << argv[0] << " \"function\" (lower_bound) (upper_bound) [--increment (increment_number)] [--simpson]" << std::endl;
        std::cout << "\033[1;36mNote: The increment flag is optional and set to 1000000 by default. Bigger numbers make the result more accurate, but evaluation time will also increase.\033[0m" << std::endl;
        return 1;
    }
    std::string function = argv[1];
    double lower_bound = std::stod(argv[2]);
    double upper_bound = std::stod(argv[3]);
    double increment = 1000000; // default increment value
    bool use_simpsons = false;

    for (int i = 4; i < argc; i++) {
        if (std::string(argv[i]) == "--increment" && i + 1 < argc) {
            increment = std::stod(argv[++i]);
        } else if (std::string(argv[i]) == "--simpson") {
            use_simpsons = true;
        }
    }
    try {
        if (use_simpsons) {
            double result = simpsons_rule(function, lower_bound, upper_bound, static_cast<int>(increment));
            std::cout << "Result by simpson's rule is " << result << std::endl;
        } else {
            double h = (upper_bound - lower_bound) / increment;
            double sum = 0;

            for (int i = 0; i <= increment; i++) {
                double x = lower_bound + (i * h);
                sum += evaluate_function(function, x) * h;
            }
            std::cout << "Result of the integral is " << sum << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mError:\033[0m " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
