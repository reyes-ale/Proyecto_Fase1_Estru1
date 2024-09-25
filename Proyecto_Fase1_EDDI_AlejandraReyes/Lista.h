#pragma once
#include "Nodo.h"


class Lista {
private:
	Nodo* cabeza;

public:

	Lista(Nodo* cabeza);
	~Lista();
	Nodo* getCabeza();
	int agregar(Persona* persona);
	int tamanio_lista();
	int extraer_anio(string); 
	void ordenamiento_telefono();
	void ordenamiento_apellido();
	bool lista_vacia();
	void ordenamiento_identidad();
	void imprimir();
	Nodo* dividir(Nodo* cabeza);
	Nodo* unir(Nodo* izquierda, Nodo* derecha,int tipo);
	Nodo* mergeSort(Nodo* cabeza,int tipo);
	void agregar_porcampos(Persona* temp, int campo);
	int eliminar_porcampos(int campo, string atributo);
	
};
