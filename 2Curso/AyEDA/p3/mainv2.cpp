#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stack>
#include "BigNumber.hpp"
#include "BigUnsignedPlantilla.hpp"
#include "BigIntegerPlantilla.hpp"
#include "BigRationalPlantilla.hpp"

using namespace std;

// Función para evaluar una expresión en notación polaca inversa
template<unsigned char Base>
BigNumber<Base>* evaluateRPN(const string& expression, const map<string, BigNumber<Base>*>& board) {
    stack<BigNumber<Base>*> stack;
    istringstream iss(expression);
    string token;

    while (iss >> token) {
        if (board.find(token) != board.end()) {
            // Si el token es un operando, lo pusheamos a la pila
            stack.push(board.at(token));
        } else {
            // Si el token es un operador, realizamos la operación
            BigNumber<Base>* right = stack.top();
            stack.pop();
            BigNumber<Base>* left = stack.top();
            stack.pop();

            if (token == "+") {
                stack.push(&(left->add(*right)));
            } else if (token == "-") {
                stack.push(&(left->subtract(*right)));
            } else if (token == "*") {
                stack.push(&(left->multiply(*right)));
            } else if (token == "/") {
                stack.push(&(left->divide(*right)));
            } else {
                throw invalid_argument("Operador no válido: " + token);
            }
        }
    }

    if (stack.size() != 1) {
        throw invalid_argument("Expresión RPN no válida");
    }

    return stack.top();
}

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    map<string, BigNumber<Base>*> board;
    unsigned char base = 10;

    if (!inputFile.is_open()) {
        cerr << "Error al abrir el archivo de entrada." << endl;
        return 1;
    }

    string line;
    getline(inputFile, line);
    if (line.find("Base = ") == 0) {
        base = stoi(line.substr(7));
    } else {
        cerr << "Formato de archivo incorrecto. La primera línea debe especificar la base." << endl;
        return 1;
    }

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string label, symbol, value;
        iss >> label >> symbol;

        if (symbol == "=") {
            // Es una asignación de un nuevo número
            iss >> value;
            try {
                BigNumber<Base>* number = BigNumber<Base>::create(value.c_str());
                board[label] = number;
            } catch (const exception& e) {
                cerr << "Error al crear el número: " << e.what() << endl;
                board[label] = new BigUnsigned<Base>(0); // Almacenar un cero en caso de error
            }
        } else if (symbol == "?") {
            // Es una expresión RPN
            string expression;
            getline(iss, expression);
            try {
                BigNumber<Base>* result = evaluateRPN<Base>(expression, board);
                board[label] = result;
            } catch (const exception& e) {
                cerr << "Error al evaluar la expresión: " << e.what() << endl;
                board[label] = new BigUnsigned<Base>(0); // Almacenar un cero en caso de error
            }
        } else {
            cerr << "Formato de línea no válido: " << line << endl;
        }
    }

    // Escribir los resultados en el archivo de salida
    outputFile << "Base = " << static_cast<int>(base) << endl;
    for (const auto& entry : board) {
        outputFile << entry.first << " = " << *entry.second << endl;
    }

    // Liberar la memoria
    for (const auto& entry : board) {
        delete entry.second;
    }

    inputFile.close();
    outputFile.close();
    return 0;
}