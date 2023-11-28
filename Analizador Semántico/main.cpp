#include <iostream>
#include <fstream>

#include <string>
#include "lexico.h"
#include "sintactico.h"

using namespace std;
int main() {
	Lexico lexico;
	Sintactico sintactico;
	Semantico semantico;
	
	char cadena[400];
	cout << "Compilador" << endl;
	string line;
	bool flag = false;
	ifstream codigo("codigo.txt");
	if (codigo.is_open())
	{
		while (getline(codigo, line))
		{
			char cadena2[400];
			strcpy_s(cadena2, line.c_str());
			if (flag){
				strcat_s(cadena, cadena2);
			}
			else {
				strcpy_s(cadena, cadena2);
				flag = true;
			}
		}
		codigo.close();
	}
	
	else {
		cout << "Unable to open file";
		return 0;
	}
	//cout << cadena;
	lexico.entrada(cadena);
	sintactico.empezar();
	//sintactico.printLR();
	cout << "Estado en pila\t\tEntrada\t\tSalida" << endl;
	bool lexicoFlag = true;
	bool sintaticoFlag = true;
	string entradaSint = lexico.getCadenaFromInd();
	string back = sintactico.pilaTop()->getToken();
	lexico.sigSimbolo();
	
	string salida = sintactico.salida(lexico.token, lexico.tipo);
	while (salida.compare("r0") != 0) {
		entradaSint = lexico.getCadenaFromInd();
		string pilaString = sintactico.pilaToString();
		if (lexico.tipo < 0) {
			lexicoFlag = false;
		}
		if (salida.empty()) {
			cout << pilaString << "\t\t\t" << entradaSint << "$\t\t" << "Error" << endl;
			
			cout << "Resultado del analisis sintactico: Error" << endl;
			sintaticoFlag = false;
			break;
		}
		else {
			cout << pilaString << "\t\t\t"<< entradaSint  << "$\t\t" << salida << endl;
		}
		back = sintactico.pilaTop()->getToken();
		if (salida.find("-e") == string::npos)
			lexico.sigSimbolo();
		salida = sintactico.salida(lexico.token, lexico.tipo);
	}
	if (salida.compare("r0") == 0) {
		cout << sintactico.pilaToString() << "\t\t\t" << entradaSint << "$\t\t" << "r0 (acept)" << endl;
		cout << "Resultado del analisis sintactico: Correcto" << endl;
		
	}
	
	//RESULTADO DE ANALISIS LEXICO
	cout << "Resultado del analisis lexico: ";
	if (lexicoFlag) {
		cout << "Correcto" << endl;
	}
	else {
		cout << "Error" << endl;
	}
	
	if (lexicoFlag && sintaticoFlag) {
		Sintactico copiaSint = sintactico;
		cout << endl << "ANALISIS SEMANTICO" << endl;
		if (semantico.start(sintactico)) {
			semantico.printFunciones();
			semantico.printVariables();
			cout << "Generando codigo... " << endl;
			GenCodigo genCodigo;
			if (genCodigo.crearASM(copiaSint,semantico)) {
				cout << "Codigo generado con exito " << endl;
			}
			else {
				cout << "Error generando codigo" << endl;
			}
		}
		else {
			cout << "Hubo un error: " << endl;
			cout << semantico.getError()<< endl;
		}
	}
	
	
	
	cout << "Programa terminado, presiona enter para terminar" << endl;
	cin.get();
	
	return 0;
}
