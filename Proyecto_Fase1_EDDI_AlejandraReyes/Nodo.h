#pragma once
#include "Persona.h"

class Nodo {
private:
    Persona* persona;
    Nodo* next;
    Nodo* previo;

public:
    Nodo(Persona* persona);
    ~Nodo();
    Nodo* getNext();
    Nodo* getPrev();
    Persona* getPersona(); 
    void setNext(Nodo* next);
    void setPrev(Nodo* previo);
    void setPersona(Persona *);
};