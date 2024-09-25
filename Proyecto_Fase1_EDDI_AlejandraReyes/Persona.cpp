#include "Persona.h"

Persona::Persona(string nombre, string apellido, string tel_movil, string tel_fijo, string direccion, string num_identidad) {
	this->nombre = nombre;
	this->apellido = apellido;
	this->tel_movil = tel_movil;
	this->tel_fijo = tel_fijo; 
	this->num_identidad = num_identidad; 
	this->direccion = direccion; 
}

Persona :: ~Persona() {

}

Persona :: Persona() {

}

string Persona::getNombre() {
	return this->nombre;
}

string Persona::getApellido() {
	return this->apellido;
}

string Persona::getIdentidad() {
	return this->num_identidad;
}

string Persona::getDireccion() {
	return this->direccion;
}

string Persona::getMovil() {
	return this->tel_movil;
}

string Persona::getFijo() {
	return this->tel_fijo;
}

void Persona::setNombre(string nombre) {
	this->nombre = nombre;
}

void Persona::setDireccion(string direccion) {
	this->direccion = direccion;
}

void Persona::setTelFijo(string tel_fijo) {
	this->tel_fijo = tel_fijo;
}
