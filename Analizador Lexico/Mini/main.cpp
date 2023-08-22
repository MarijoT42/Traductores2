#include <iostream>
#include <string>

using namespace std;

int main() {
	string text;
	cout << "Introduce el texto a analizar:\n";
	getline(cin, text);
	
	text += " ";  // Agregar un espacio extra al final para facilitar el análisis
	
	int estado = 0;
	string cadena;
	
	for (char c : text) {
		switch (estado) {
		case 0:
			if (isdigit(c)) {
				estado = 1;
			} else if (isalpha(c) || c == '_') {
				estado = 2;
			} else if (c == ' ') {
				cout << cadena << "\t\t\t" << "No válido" << "\n";
				cadena = "";
				estado = 0;
			} else {
				estado = -1;
			}
			break;
		case 1:
			if (isdigit(c)) {
				estado = 1;
			} else if (c == '.') {
				estado = 3;
			} else if (c == ' ') {
				cout << cadena << "\t\t\t" << "Entero" << "\n";
				cadena = "";
				estado = 0;
			} else {
				estado = -1;
			}
			break;
		case 2:
			if (isdigit(c) || isalpha(c) || c == '_') {
				estado = 2;
			} else if (c == ' ') {
				cout << cadena << "\t\t\t" << "Identificador" << "\n";
				cadena = "";
				estado = 0;
			} else {
				estado = -1;
			}
			break;
		case 3:
			if (isdigit(c)) {
				estado = 4;
			} else if (c == ' ') {
				cout << cadena << "\t\t\t" << "No válido" << "\n";
				cadena = "";
				estado = 0;
			} else {
				estado = -1;
			}
			break;
		case 4:
			if (isdigit(c)) {
				estado = 4;
			} else if (c == ' ') {
				cout << cadena << "\t\t\t" << "Real" << "\n";
				cadena = "";
				estado = 0;
			} else {
				estado = -1;
			}
			break;
		case -1:
			if (c == ' ') {
				cout << cadena << "\t\t\t" << "No válido" << "\n";
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
