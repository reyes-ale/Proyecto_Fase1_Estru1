#pragma once
#include <string>
#include <iostream>
using namespace std; 

class Persona {
private:
	string nombre, apellido, num_identidad, direccion, tel_movil, tel_fijo;

public:
	Persona(string, string, string, string, string, string);
	Persona();
	~Persona();
	string getNombre();
	string getApellido();
	string getIdentidad();
	string getDireccion();
	string getMovil();
	string getFijo();
	void setNombre(string nombre);
	void setDireccion(string direccion);
	void setTelFijo(string tel_fijo);
};

