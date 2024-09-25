#include "Nodo.h"

Nodo::Nodo(Persona* persona) {
	this->persona = persona;
	this->next = nullptr;
	this->previo = nullptr;
}

Nodo::~Nodo() {

}

Nodo* Nodo :: getNext() {
    return this->next;
}

Nodo* Nodo ::getPrev() {
    return this->previo;
}

Persona* Nodo::getPersona() {
    return this->persona;
}


void Nodo::setNext(Nodo* next) {
    this->next = next;
}

void Nodo:: setPrev(Nodo* previo) {
    this->previo = previo;
}

void Nodo::setPersona(Persona* persona) {
    this->persona = persona;
}
