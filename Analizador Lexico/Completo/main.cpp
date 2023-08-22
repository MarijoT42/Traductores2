#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<char, string> operators = {
	{'+', "OpSuma"},
	{'-', "OpSuma"},
	{'*', "OpMul"},
	{'/', "OpMul"},
	{'=', "OpIgualdad"},
	{'<', "OpRelac"},
	{'>', "OpRelac"},
	{'&', "OpAnd"},
	{'|', "OpOr"},
	{'!', "OpNot"}
};

bool is_txt(char c) {
	return (isalpha(c) || c == '_');
}

bool is_number(char c) {
	return (isdigit(c));
}

bool is_space(char c) {
	return (c == ' ');
}

int main() {
	int estado = 0;
	string text;
	string cadena = "";
	
	cout << "Introduce el texto a analizar:\n";
	getline(std::cin, text);
	
	text += " ";
	
	for (char c : text) {
		switch (estado) {
		case 0:
			if (is_number(c)) {
				estado = 1;
			} else if (is_txt(c)) {
				estado = 2;
			} else if (is_space(c)) {
				cout << cadena << "\t\t\tNo válido\n";
				cadena = "";
				estado = 0;
			} else if (operators.find(c) != operators.end()) {
				estado = 5;
				cadena = cadena + c;
			} else {
				estado = -1;
			}
			break;
		case 1:
			if (is_number(c)) {
				estado = 1;
			} else if (c == '.') {
				estado = 3;
			} else if (is_space(c)) {
				cout << cadena << "\t\t\t1\tEntero\n";
				cadena = "";
				estado = 0;
			} else {
				estado = -1;
			}
			break;
		case 2:
			if (is_number(c) || is_txt(c) || c == '_') {
				estado = 2;
			} else if (is_space(c)) {
				if (cadena == "int" || cadena == "float") {
					cout << cadena << "\t\t\t4\tTipo\n";
				} else if (cadena == "if") {
					cout << cadena << "\t\t\t19\n";
				} else if (cadena == "while") {
					cout << cadena << "\t\t\t20\n";
				} else if (cadena == "return") {
					cout << cadena << "\t\t\t21\n";
				} else if (cadena == "else") {
					cout << cadena << "\t\t\t22\n";
				} else {
					cout << cadena << "\t\t\t0\tIdentificador\n";
				}
				cadena = "";
				estado = 0;
			} else {
				estado = -1;
			}
			break;
		case 3:
			if (is_number(c)) {
				estado = 4;
			} else if (is_space(c)) {
				cout << cadena << "\t\t\t2\tReal\n";
				cadena = "";
				estado = 0;
			} else {
				estado = -1;
			}
			break;
		case 4:
			if (is_number(c)) {
				estado = 4;
			} else if (is_space(c)) {
				cout << cadena << "\t\t\t2\tReal\n";
				cadena = "";
				estado = 0;
			} else {
				estado = -1;
			}
			break;
		case 5:
			if (is_space(c)) {
				cout << cadena << "\t\t\t" << operators[cadena[0]] << "\n";
				cadena = "";
				estado = 0;
			} else {
				estado = -1;
			}
			break;
		case -1:
			if (is_space(c)) {
				cout << cadena << "\t\t\tNo válido\n";
				cadena = "";
				estado = 0;
			}
			break;
		}
		
		if (estado >= 0) {
			cadena += c;
		}
	}
	
	return 0;
}
