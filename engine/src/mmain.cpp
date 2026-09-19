#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

enum class
 TokenType { Number, 
    Plus, Minus, Star, Slash, LParen, RParen, End };

    struct Token {  TokenType type ; 
        double value ;
    };

    std::vector <Token> tokenize (const std::string & expr){\
        std::vector<Token> tokens;
        size_t i = 0 ; 
        while (i < expr.size()){
            char c  = expr[i];
            if (std::isspace(static_cast<unsigned char > (c))) {
                ++i ; continue; }


            
        if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
            size_t start = i;

            while (i < expr.size() &&
                   (std::isdigit(static_cast<unsigned char>(expr[i])) ||
                    expr[i] == '.')) {
                ++i;
            }

            double value = std::stod(expr.substr(start, i - start));
            tokens.push_back({TokenType::Number, value});
            continue;
        }

        switch (c) {
            case '+': tokens.push_back({TokenType::Plus, 0});   break;
            case '-': tokens.push_back({TokenType::Minus, 0});  break;
            case '*': tokens.push_back({TokenType::Star, 0});   break;
            case '/': tokens.push_back({TokenType::Slash, 0});  break;
            case '(': tokens.push_back({TokenType::LParen, 0}); break;
            case ')': tokens.push_back({TokenType::RParen, 0}); break;
            default:
                throw std::runtime_error(
                    std::string("անճանաչ նշան (unexpected character): ") + c);
        }

        ++i;
    }

    tokens.push_back({TokenType::End, 0});
    return tokens;
}

class Parser {
public:
    explicit Parser(std::vector<Token> tokens)
        : tokens_(std::move(tokens)), pos_(0) {}

    double parseExpression();
    double parseTerm();
    double parseFactor();

private:
    const Token& peek() const { return tokens_[pos_]; }
    Token advance() { return tokens_[pos_++]; }

    std::vector<Token> tokens_;
    size_t pos_;
};

// factor := number | '(' expr ')'
double Parser::parseFactor() {
    Token t = advance();

    if (t.type == TokenType::Number) {
        return t.value;
    }

    if (t.type == TokenType::LParen) {
        double result = parseExpression();

        if (peek().type != TokenType::RParen) {
            throw std::runtime_error("սպասվում էր ')' (expected closing paren)");
        }

        advance();
        return result;
    }

    throw std::runtime_error("սպասվում էր թիվ կամ '(' (expected number or '(')");
}

// term := factor (('*' | '/') factor)*
double Parser::parseTerm() {
    double result = parseFactor();

    while (peek().type == TokenType::Star ||
           peek().type == TokenType::Slash) {
        Token op = advance();
        double rhs = parseFactor();

        if (op.type == TokenType::Star) {
            result *= rhs;
        } else {
            if (rhs == 0) {
                throw std::runtime_error("զրոյի բաժանում (division by zero)");
            }
            result /= rhs;
        }
    }

    return result;
}

// expr := term (('+' | '-') term)*
double Parser::parseExpression() {
    double result = parseTerm();

    while (peek().type == TokenType::Plus ||
           peek().type == TokenType::Minus) {
        Token op = advance();
        double rhs = parseTerm();

        if (op.type == TokenType::Plus) {
            result += rhs;
        } else {
            result -= rhs;
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "{\"error\": \"no problem provided\"}" << std::endl;
        return 1;
    }

    std::string problem = argv[1];

    try {
        std::vector<Token> tokens = tokenize(problem);
        Parser parser(std::move(tokens));
        double result = parser.parseExpression();

        std::cout << "{"
                  << "\"input\": \"" << problem << "\", "
                  << "\"result\": " << result
                  << "}" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "{"
                  << "\"input\": \"" << problem << "\", "
                  << "\"error\": \"" << e.what() << "\""
                  << "}" << std::endl;
        return 1;
    }

    return 0;
}