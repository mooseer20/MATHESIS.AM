
// test_parser.cpp
//
// Ձեռքով գրված test-եր, framework-ի կարիք չկա (Catch2 կգա ավելի ուշ):
// Կանչել. make test

#include "../include/parser.h"
#include <iostream>
#include <cmath>

int tests_run = 0;
int tests_failed = 0;

void check(const std::string& expr, double expected) {
    ++tests_run;
    std::vector<Token> tokens = tokenize(expr);
    Parser parser(std::move(tokens));
    double actual = parser.parseExpression();

    if (std::fabs(actual - expected) > 1e-9) {
        ++tests_failed;
        std::cout << "FAIL: \"" << expr << "\" -- ակնկալվում էր " << expected
                  << ", ստացվեց " << actual << std::endl;
    } else {
        std::cout << "PASS: \"" << expr << "\" = " << actual << std::endl;
    }
}

void check_error(const std::string& expr) {
    ++tests_run;
    try {
        Parser parser(tokenize(expr));
        parser.parse();
        ++tests_failed;
        std::cout << "FAIL: \"" << expr << "\" -- error էր սպասվում" << std::endl;
    } catch (const std::exception&) {
        std::cout << "PASS: \"" << expr << "\" -> error" << std::endl;
    }
}

void check_derivative(const std::string& expr, double x, double expected) {
    ++tests_run;
    const double actual = derivative_at(expr, "x", x);

    if (std::fabs(actual - expected) > 1e-4) {
        ++tests_failed;
        std::cout << "FAIL: d/dx " << expr << " at " << x << " -- ակնկալվում էր "
                  << expected << ", ստացվեց " << actual << std::endl;
    } else {
        std::cout << "PASS: d/dx " << expr << " at " << x << " = " << actual << std::endl;
    }
}

int main() {
    check("2 + 3", 5);
    check("2 + 3 * (4 - 1)", 11);
    check("10 / 2 - 3", 2);
    check("-5 + 3", -2);
    check("2 + 9", 11);
    check("9 /11", 9.0 / 11.0);

    // TODO (եթե parsePower()-ը արդեն գրած ես) -- ապակոմենտար արա.
     check("2 ^ 3", 8);
    check("2 ^ 3 ^ 2", 512);

    std::cout << "\n" << (tests_run - tests_failed) << "/" << tests_run << " passed" << std::endl;
    check_error("2 3");
check_error("2)");
check_error("1 / 0");

check_derivative("x^2", 1, 2);
check_derivative("x^2", 10, 20);
check_derivative("x^2", 1000, 2000);
    return tests_failed == 0 ? 0 : 1;
}