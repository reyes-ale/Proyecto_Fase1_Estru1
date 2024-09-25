#include "Lista.h"


Lista::Lista(Nodo* cabeza) {
	this->cabeza = cabeza;
}

Lista::~Lista() {


}

Nodo* Lista::getCabeza() {
	return this->cabeza;
}

int Lista::agregar(Persona* persona) {
	Nodo* current = this->cabeza;
	Nodo* nuevo = new Nodo(persona);

	if (cabeza == nullptr) {
		cabeza = nuevo; 
		return 1;
	}
	else {
		while (current->getNext() != nullptr) {
			current = current->getNext();
		}
		current->setNext(nuevo);
		nuevo->setPrev(current);  
		return 1; 
	}
}

int Lista::tamanio_lista() {
	int tamanio = 0;
	Nodo* current = this->getCabeza();

	if (cabeza == NULL) {
		return tamanio;
	}
	else {
		while (current != NULL) {
			current = current->getNext();
			tamanio++;
		}
		return tamanio;
	}
}

int Lista ::extraer_anio(string cadena) {
	string cad = cadena.substr(4, 4);
	int anio = stoi(cad);

	return anio;
}

void Lista::ordenamiento_identidad() {
	bool intercambiado = true;

	if (this->cabeza == nullptr) {
		cout << "Muy pocos elementos, no se puede ordenar" << endl; 
	}
	
	while (intercambiado) {
		intercambiado = false;
		Nodo* current = this->cabeza;

		while (current->getNext() != nullptr) {
			if (extraer_anio(current->getPersona()->getIdentidad()) > extraer_anio(current->getNext()->getPersona()->getIdentidad())) {
				Persona* temp = current->getPersona();
				current->setPersona(current->getNext()->getPersona());
				current->getNext()->setPersona(temp);
				intercambiado = true;
			}
			current = current->getNext();
		}
	}
}

void Lista::imprimir() {
	Nodo* current = this->getCabeza();

	
	while (current != nullptr) {
		cout << "Nombres: " << current->getPersona()->getNombre() << endl;
		cout << "Apellidos: " << current->getPersona()->getApellido() << endl;
		cout << "Num.Identidad: " << current->getPersona()->getIdentidad() << endl;
		cout << "Direccion: " << current->getPersona()->getDireccion() << endl;
		cout << "Tel.Movil: " << current->getPersona()->getMovil() << endl;
		cout << "Tel.Fijo: " << current->getPersona()->getFijo() << endl;
		cout << "\n\n";
		current = current->getNext(); 
	}
}

Nodo*  Lista ::unir(Nodo* izquierda, Nodo* derecha, int tipo) {
	Nodo* cabeza = nullptr;
	Nodo* current = nullptr;

	if (tipo == 3) { 
		if (izquierda->getPersona()->getApellido() <= derecha->getPersona()->getApellido()) {
			cabeza = izquierda;
			izquierda = izquierda->getNext();
		}
		else {
			cabeza = derecha;
			derecha = derecha->getNext();
		}
	}
	else { 
		if (stoi(izquierda->getPersona()->getMovil()) <= stoi(derecha->getPersona()->getFijo())) {
			cabeza = izquierda;
			izquierda = izquierda->getNext();
		}
		else {
			cabeza = derecha;
			derecha = derecha->getNext();
		}
	}
	current = cabeza;

	while (izquierda != nullptr && derecha != nullptr) {
		if (tipo == 3) { 
			if (izquierda->getPersona()->getApellido() <= derecha->getPersona()->getApellido()) {
				current->setNext(izquierda);
				izquierda = izquierda->getNext();
			}
			else {
				current->setNext(derecha);
				derecha = derecha->getNext();
			}
		}
		else {
			if (stoi(izquierda->getPersona()->getMovil()) <= stoi(derecha->getPersona()->getFijo())) {
				current->setNext(izquierda);
				izquierda = izquierda->getNext();
			}
			else {
				current->setNext(derecha);
				derecha = derecha->getNext();
			}
		}
		current = current->getNext();
	}

	if (izquierda != nullptr) {
		current->setNext(izquierda);
	}
	else {
		current->setNext(derecha);
	}

	return cabeza; 
}

Nodo* Lista:: dividir(Nodo* cabeza) {
	if (cabeza == nullptr || cabeza->getNext() == nullptr) {
		return nullptr;
	}

	Nodo* lento = cabeza;
	Nodo* rapido = cabeza->getNext();

	while (rapido != nullptr && rapido->getNext() != nullptr) {
		lento = lento->getNext();
		rapido = rapido->getNext()->getNext();
	}

	Nodo* mitad = lento->getNext();
	lento->setNext(nullptr);
	return mitad;
}

Nodo* Lista::mergeSort(Nodo* cabeza, int tipo) {

	if (cabeza == nullptr || cabeza->getNext() == nullptr) {
		return cabeza;
	}

	Nodo* mitad = dividir(cabeza);
	Nodo* izquierda = mergeSort(cabeza, tipo);
	Nodo* derecha = mergeSort(mitad,tipo);

	return unir(izquierda, derecha, tipo);
}


void Lista::agregar_porcampos(Persona *temp, int campo) {
	Nodo* nuevo_nodo = new Nodo(temp); 
	Nodo* current = this->cabeza;

	switch (campo) {
		case 1://tel
			if (cabeza == NULL) {
				cabeza = nuevo_nodo;
			}
			else if (stoi(temp->getMovil()) <= stoi(current->getPersona()->getMovil())) {
				nuevo_nodo->setNext(cabeza);
				cabeza = nuevo_nodo;
			}
			else {
				while (current->getNext() != NULL && stoi(current->getNext()->getPersona()->getMovil()) < stoi(temp->getMovil())) {
					current = current->getNext();
				}

				nuevo_nodo->setPrev(current);

				if (current->getNext() == NULL) {//fin
					current->setNext(nuevo_nodo);
				}
				else {
					nuevo_nodo->setNext(current->getNext());
					current->getNext()->setPrev(nuevo_nodo);
					current->setNext(nuevo_nodo);
				}
			}
		
			break;

		case 2://iden
			if (cabeza == NULL) {
				cabeza = nuevo_nodo;
			}
			else if (extraer_anio(temp->getIdentidad()) <= extraer_anio(current->getPersona()->getIdentidad())) {
				nuevo_nodo->setNext(cabeza);
				cabeza = nuevo_nodo;
			}
			else {
				while (current->getNext() != NULL && extraer_anio(current->getNext()->getPersona()->getIdentidad()) < extraer_anio(temp->getIdentidad())) {
					current = current->getNext();
				}

				nuevo_nodo->setPrev(current);

				if (current->getNext() == NULL) {//fin
					current->setNext(nuevo_nodo);
				}
				else {
					nuevo_nodo->setNext(current->getNext());
					current->getNext()->setPrev(nuevo_nodo);
					current->setNext(nuevo_nodo);
				}
			}
			break;

		case 3://apellifo
			if (cabeza == NULL) {
				cabeza = nuevo_nodo;
			}
			else if (temp->getApellido() <= current->getPersona()->getApellido()) {
				nuevo_nodo->setNext(cabeza);
				cabeza = nuevo_nodo;
			}
			else {
				while (current->getNext() != NULL && current->getNext()->getPersona()->getApellido() < temp->getApellido()) {
					current = current->getNext();
				}

				nuevo_nodo->setPrev(current);

				if (current->getNext() == NULL) {//fin
					current->setNext(nuevo_nodo);
				}
				else {
					nuevo_nodo->setNext(current->getNext());
					current->getNext()->setPrev(nuevo_nodo);
					current->setNext(nuevo_nodo);
				}
			}
			break;

	}
}

int Lista::eliminar_porcampos(int campo,string atributo) {
	Nodo* current = this->cabeza;

	switch (campo) {
		case 1://tel
			while (current != nullptr && stoi(current->getPersona()->getMovil()) != stoi(atributo)) {
				current = current->getNext();
			}

			if (current == cabeza) {
				cabeza = current->getNext();
				if (cabeza != nullptr) {
					cabeza->setPrev(nullptr);
				}
			}
			else {
				current->getPrev()->setNext(current->getNext());
				if (current->getNext() != nullptr) {
					current->getNext()->setPrev(current->getPrev());
				}
			}
			delete current;
			return 1;

			break;

		case 2://iden

			while (current != nullptr && current->getPersona()->getIdentidad() != atributo) {
				current = current->getNext();
			}

			if (current == cabeza) {
				cabeza = current->getNext();
				if (cabeza != nullptr) {
					cabeza->setPrev(nullptr);
				}
			}
			else {
				current->getPrev()->setNext(current->getNext());
				if (current->getNext() != nullptr) {
					current->getNext()->setPrev(current->getPrev());
				}
			}
			delete current;
			return 1;

			break;

		case 3://apellido
			while (current != nullptr && current->getPersona()->getApellido() != atributo) {
				current = current->getNext();
			}

			if (current == cabeza) {
				cabeza = current->getNext();
				if (cabeza != nullptr) {
					cabeza->setPrev(nullptr);
				}
			}
			else {
				current->getPrev()->setNext(current->getNext());
				if (current->getNext() != nullptr) {
					current->getNext()->setPrev(current->getPrev());
				}
			}
			delete current;
			return 1;

			break;

	}

}

void Lista::ordenamiento_telefono() {
	this->cabeza = mergeSort(this->cabeza, 1);
}

void Lista::ordenamiento_apellido() {
	this->cabeza = mergeSort(this->cabeza,3);
}

bool Lista::lista_vacia() {
	return this->cabeza == nullptr;
}
