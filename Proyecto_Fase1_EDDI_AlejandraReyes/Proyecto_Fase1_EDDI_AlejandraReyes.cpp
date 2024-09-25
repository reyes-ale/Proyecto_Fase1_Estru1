#include <iostream>
#include <string>
#include <fstream>
#include "Persona.h"
#include "Lista.h"

void escribir(string ruta, Lista *&lista, int flag) {
	ofstream archivo(ruta, ios::out | ios::binary | ios::trunc);
	if (!archivo) {
		cerr << "No se pudo abrir el archivo para escribir" << endl;
		exit(EXIT_FAILURE);
	}
	
	Nodo* current = lista->getCabeza(); 
	
	archivo.write(reinterpret_cast<char*>(&flag), sizeof(flag));

	while (current != nullptr) {
		archivo.write(reinterpret_cast<char*>(current->getPersona()), sizeof(Persona));
		current = current->getNext(); 
	}

	archivo.close();
}

Lista* leer(const std::string& ruta, Lista *lista, int& flag) {

	ifstream archivo(ruta, ios::in | ios::binary);
	if (!archivo) {
		std::cerr << "No se pudo abrir el archivo" << std::endl;
		exit(EXIT_FAILURE);
	}

	archivo.read(reinterpret_cast<char*>(&flag), sizeof(int));

	while (archivo.peek() != EOF) { 
		Persona* temp = new Persona();
		archivo.read(reinterpret_cast<char*>(temp), sizeof(Persona));
		lista->agregar(temp);
	}

	archivo.close();
	return lista;
}

Nodo* obtener_nodo(Lista* lista, int pos) {
	Nodo* current = lista->getCabeza();
	int cont = 0;

	if (lista->getCabeza() == NULL) {
		return nullptr;
	}
	else {
		while (current != NULL && cont < pos) {
			current = current->getNext();
			cont++;
		}
		return current;
	}
}

Nodo* busqueda(string atributo, Lista* lista, int flag) {
	int tamanio = lista->tamanio_lista();
	int left = 0;
	int right = tamanio - 1;

	while (left <= right) {
		int mitad = (left + right) / 2;
		Nodo* nodo_mitad = obtener_nodo(lista, mitad);

		switch (flag) {
			case 1:
				lista->ordenamiento_telefono();
				if (stoi(nodo_mitad->getPersona()->getMovil()) == stoi(atributo)) {
					return nodo_mitad;
				}
				else if (stoi(nodo_mitad->getPersona()->getMovil()) > stoi(atributo)) {
					right = mitad - 1;

				}
				else if (stoi(nodo_mitad->getPersona()->getMovil()) < stoi(atributo)) {
					left = mitad + 1;
				}
				break;

			case 2:
				lista->ordenamiento_identidad();
				if (lista->extraer_anio(nodo_mitad->getPersona()->getIdentidad()) == lista->extraer_anio(atributo)) {
					return nodo_mitad;
				}
				else if (lista->extraer_anio(nodo_mitad->getPersona()->getIdentidad()) > lista->extraer_anio(atributo)) {
					right = mitad - 1;

				}
				else if (lista->extraer_anio(nodo_mitad->getPersona()->getIdentidad()) < lista->extraer_anio(atributo)) {
					left = mitad + 1;
				}
				break;

			case 3:
				lista->ordenamiento_apellido();
				if (nodo_mitad->getPersona()->getApellido() == atributo) {
					return nodo_mitad;
				}
				else if (nodo_mitad->getPersona()->getApellido() > atributo) {
					right = mitad - 1;

				}
				else if (nodo_mitad->getPersona()->getApellido() < atributo) {
					left = mitad + 1;
				}
				break;
		}
	}

	return nullptr;
}

int tiene_letras(string& cadena) {
	for (int i = 0; i < cadena.size(); i++) {
		if (!isdigit(cadena[i])) {
			return 1;
		}
	}
	return 0;
}

void validacion_letras(string& cadena) {
	while (tiene_letras(cadena)) {
		cout << "El numero que ingreso contiene letras. Ingrese nuevamente: ";
		cin >> cadena;
	}
}

int tiene_numeros(string& cadena) {
	for (int i = 0; i < cadena.size(); i++) {
		if (isdigit(cadena[i])) {
			return 1;
		}
	}
	return 0;
}

void validacion_numeros(string& cadena) {
	while (tiene_numeros(cadena)) {
		cout << "El texto que ingreso contiene numeros. Ingrese nuevamente: ";
		getline(cin, cadena);
	}
}

bool validacion_telefonos(string& cadena) {
	if (cadena.size() != 8) {
		return false;
	}

	for (int i = 0; i < cadena.size(); i++) {
		if (!isdigit(cadena[i]) || cadena[i] == ' ') {
			return false;
		}
	}
	return true;
}

void telefono_valido(string& cadena) {
	while (!(validacion_telefonos(cadena))) {
		cout << "El numero debe tener exactamente 8 digitos sin letras ni espacios. Ingrese nuevamente (********): ";
		getline(cin, cadena);

	}
}

bool existe_contacto(string& atributo, Lista* lista, int campo) {
	return busqueda(atributo, lista, campo) != nullptr;
}

bool validacion_identidad(string& cadena) {
	if (cadena.size() != 13) {
		return false;
	}

	for (int i = 0; i < cadena.size(); i++) {
		if (!isdigit(cadena[i]) || cadena[i] == ' ') {
			return false;
		}
	}

	return true;
}

void identidad_valida(string& cadena) {
	while (!(validacion_identidad(cadena))) {
		cout << "La identidad debe tener exactamente 13 digitos sin letras ni espacios. Ingrese nuevamente (*************) ";
		getline(cin, cadena);
	}
}

Persona* pedir_datos(string& nombre, string& apellido, string& tel_movil, string& tel_fijo, string& direccion, string& num_identidad,Lista *lista, int campo) {
	cout << "Ingrese nombres: ";
	cin.ignore();
	getline(cin, nombre);
	validacion_numeros(nombre);


	switch (campo) {
		case 1:
			cout << "Ingrese apellidos: ";
			getline(cin, apellido);
			validacion_numeros(apellido);

			cout << "Ingrese numero de identidad (*************): ";
			getline(cin, num_identidad);
			identidad_valida(num_identidad);


			while (true) {
				cout << "Ingrese telefono movil (********): ";
				getline(cin, tel_movil);
				telefono_valido(tel_movil);

				if (existe_contacto(tel_movil, lista, 1)) {
					cout << "Ese numero movil ya existe. Ingrese otro numero." << endl;
				}
				else {
					break;
				}
			}
		
			break;

		case 2:
			cout << "Ingrese apellidos: ";
			getline(cin, apellido);
			validacion_numeros(apellido);

			while (true) {
				cout << "Ingrese numero de identidad (*************): ";
				getline(cin, num_identidad);
				identidad_valida(num_identidad);

				if (existe_contacto(num_identidad, lista, 2)) {
					cout << "Ese numero de identidad ya existe. Ingrese otro numero." << endl;
				}
				else {
					break;
				}
			}

			cout << "Ingrese telefono movil (********): ";
			getline(cin, tel_movil);
			telefono_valido(tel_movil);
			break;

		case 3:

			while (true) {
				cout << "Ingrese apellidos: ";
				getline(cin, apellido);
				validacion_numeros(apellido);

				if (existe_contacto(num_identidad, lista, 3)) {
					cout << "Un contacto con esos apellidos ya existe. Ingrese otro apellido." << endl;
				}
				else {
					break;
				}
			}

			cout << "Ingrese numero de identidad (*************): ";
			getline(cin, num_identidad);
			identidad_valida(num_identidad);

			cout << "Ingrese telefono movil (********): ";
			getline(cin, tel_movil);
			telefono_valido(tel_movil);
		
			break;

	}

	cout << "Ingrese telefono fijo (********): ";
	getline(cin, tel_fijo);
	telefono_valido(tel_fijo);

	cout << "Ingrese direccion: ";
	getline(cin, direccion);

	Persona* persona = new Persona(nombre, apellido, tel_movil, tel_fijo, direccion, num_identidad);
	return persona;
}


void agregar(Lista *&lista) {
	int opcion;
	string nombre, apellido, tel_movil, tel_fijo, direccion, num_identidad;

	do {
		system("cls");
		cout << "----------\n Agregar | \n----------  \n1. Por telefono movil \n2. Por numero de identidad \n3. Por apellido \n4. Salir\nIngrese la opcion: ";
		cin >> opcion;

		switch (opcion) {
			case 1://telefono
				lista->ordenamiento_telefono();
				lista->agregar_porcampos(pedir_datos(nombre, apellido, tel_movil, tel_fijo, direccion, num_identidad, lista,1), 1);
				escribir("Contactos.bin",lista,1);

				break;

			case 2:
				lista->ordenamiento_identidad();
				lista->agregar_porcampos(pedir_datos(nombre, apellido, tel_movil, tel_fijo, direccion, num_identidad,lista,2),2);
				escribir("Contactos.bin",lista,2);
				break;

			case 3://apellido
				lista->ordenamiento_apellido();
				lista->agregar_porcampos(pedir_datos(nombre, apellido, tel_movil, tel_fijo, direccion, num_identidad, lista,3), 3);
				escribir("Contactos.bin",lista,3);
				break;

			default:
				if (opcion != 4) {
					cout << endl;
					cout << "Ingrese la opción nuevamente: " << endl;
				}
				break;
		}

	} while (opcion != 4);
}


void eliminar(Lista* lista,int &flag) {
	int opcion;
	string  apellido, tel_movil, num_identidad;


	if (lista->lista_vacia()) {
		cout << "No se pueden eliminar contactos. La lista esta vacia." << endl;
	}
	else {
		do {
			system("cls");
			cout << "-----------\n Eliminar | \n-----------  \n1. Por telefono movil \n2. Por numero de identidad \n3. Por apellido \n4. Salir\nIngrese la opcion: ";
			cin >> opcion;

			switch (opcion) {
				case 1:
					lista->ordenamiento_telefono();
					cin.ignore();

					while (true) {
						cout << "Ingrese el telefono movil del contacto a eliminar: ";
						getline(cin, tel_movil);
						telefono_valido(tel_movil);

						if (existe_contacto(tel_movil, lista, 1)==false) {
							cout << "Ese numero movil no existe." << endl;
						}
						else {
							lista->eliminar_porcampos(1, tel_movil);
							escribir("Contactos.bin", lista, 1);
							break;
						}
					}
					flag = 1;
					break;

				case 2://num identidad
					lista->ordenamiento_identidad();
					cin.ignore();

					while (true) {
						cout << "Ingrese el numero de identidad del contacto a eliminar: ";
						getline(cin, num_identidad);
						identidad_valida(num_identidad);

						if (existe_contacto(num_identidad, lista, 2) == false) {
							cout << "Ese numero de identidad no existe." << endl;
						}
						else {
							lista->eliminar_porcampos(2, num_identidad);
							escribir("Contactos.bin", lista, 2);
							break;
						}
					}
					flag = 2;
					break;

				case 3://apellido
					lista->ordenamiento_identidad();
					cin.ignore();

					while (true) {
						cout << "Ingrese los apellidos del contacto a eliminar: ";
						getline(cin, apellido);
						tiene_numeros(apellido);

						if (existe_contacto(apellido, lista, 3) == false) {
							cout << "Esos apellidos no existen." << endl;
						}
						else {
							lista->eliminar_porcampos(3, apellido);
							escribir("Contactos.bin", lista, 3);
							break;
						}
					}
					flag = 3;
					break;

				default:
					if (opcion != 4) {
						cout << endl;
						cout << "Ingrese la opción nuevamente: " << endl;
					}
					break;
			}


		} while (opcion != 4);
	}
}


void imprimir_nodo(Nodo *nodo) {
	cout << "\n"; 
	cout << "Nombres: " << nodo->getPersona()->getNombre() << endl;
	cout << "Apellidos: " << nodo->getPersona()->getApellido() << endl;
	cout << "Num.Identidad: " << nodo->getPersona()->getIdentidad() << endl;
	cout << "Direccion: " << nodo->getPersona()->getDireccion() << endl;
	cout << "Tel.Movil: " << nodo->getPersona()->getMovil() << endl;
	cout << "Tel.Fijo: " << nodo->getPersona()->getFijo() << endl;
	cout << "\n";
}

void buscar(Lista *lista, int &flag) {
	int opcion;
	string apellido, tel_movil, num_identidad;
	Nodo* encontrado; 

	if (lista->lista_vacia()) {
		cout << "No se pueden buscar contactos. La lista esta vacia." << endl;
	}
	else {
		do {
			system("cls");
			cout << "---------\n Buscar | \n--------- \n1. Por telefono movil \n2. Por numero de identidad \n3. Por Apellido \n4. Salir\nIngrese la opcion: ";
			cin >> opcion;

			switch (opcion) {
				case 1://telefono
					lista->ordenamiento_telefono();
					cin.ignore();
					while (true) {
						cout << "Ingrese el telefono movil del contacto a buscar: ";
						getline(cin, tel_movil);
						telefono_valido(tel_movil);

						encontrado = busqueda(tel_movil, lista, 1);
						if (encontrado == nullptr) {
							cout << "Ese numero movil no existe." << endl;
						}
						else {
							imprimir_nodo(encontrado);
							cout << "Presione ENTER para volver al menu...";
							cin.get();
							system("cls");
							break;
						}
					}
					flag = 1; 
					
					break;

				case 2:
					lista->ordenamiento_identidad();
					cin.ignore();
					while (true) {
						cout << "Ingrese el numero de identidad del contacto a buscar: ";
						getline(cin, num_identidad);
						identidad_valida(num_identidad);

						encontrado = busqueda(num_identidad, lista, 2);
						if (encontrado == nullptr) {
							cout << "Ese numero de identidad no existe." << endl;
						}
						else {
							imprimir_nodo(encontrado);
							cout << "Presione ENTER para volver al menu...";
							cin.get();
							system("cls");
							break;
						}
					}
					flag = 2;
					break;

				case 3://apellido
					lista->ordenamiento_apellido();
					cin.ignore();
					while (true) {
						cout << "Ingrese el apellido del contacto a buscar: ";
						getline(cin, apellido);
						tiene_numeros(apellido);

						encontrado = busqueda(apellido, lista, 3);
						if (encontrado == nullptr) {
							cout << "Ese apellido no existe." << endl;
						}
						else {
							
							imprimir_nodo(encontrado);
							cout << "Presione ENTER para volver al menu...";
							cin.get();
							system("cls");
							break;
						}
					}
					flag = 3;
					break;

				default:
					if (opcion != 4) {
						cout << endl;
						cout << "Ingrese la opción nuevamente: " << endl;
					}
					break;
			}


		} while (opcion != 4);
	}
	
}



void editar(Lista *lista,int flag) {
	int opcion;

	string nombre, apellido, tel_movil, tel_fijo, direccion, num_identidad;
	Nodo* encontrado; 

	if (lista->lista_vacia()) {
		cout << "No se pueden editar contactos. La lista esta vacia." << endl;
	}
	else {
		do {
			system("cls");
			cout << "---------\n Editar | \n--------- \n1. Nombre  \n2. Direccion \n3. Num.Fijo \n4. Salir  \n\nIngrese la opcion : ";
			cin >> opcion;

			switch (opcion) {
			case 1:
				switch (flag) {
				case 1:
					lista->ordenamiento_telefono();
					cin.ignore();
					while (true) {
						cout << "Ingrese el telefono movil del contacto a editar: ";
						getline(cin, tel_movil);
						telefono_valido(tel_movil);

						encontrado = busqueda(tel_movil, lista, 1);
						if (encontrado == nullptr) {
							cout << "Ese numero movil no existe." << endl;
						}
						else {
							cout << "Ingrese nuevos nombres: ";
							getline(cin, nombre);
							validacion_numeros(nombre);

							encontrado->getPersona()->setNombre(nombre);
							escribir("Contactos.bin", lista, 1);
							break;
						}
					}
					break;

				case 2:
					lista->ordenamiento_identidad();
					cin.ignore();
					while (true) {
						cout << "Ingrese el numero de identidad del contacto a editar: ";
						getline(cin, num_identidad);
						identidad_valida(num_identidad);

						encontrado = busqueda(num_identidad, lista, 2);
						if (encontrado == nullptr) {
							cout << "Ese numero de identidad no existe." << endl;
						}
						else {
							cout << "Ingrese nuevos nombres: ";
							getline(cin, nombre);
							validacion_numeros(nombre);

							encontrado->getPersona()->setNombre(nombre);
							escribir("Contactos.bin", lista, 2);
							break;
						}
					}

					break;

				case 3:
					lista->ordenamiento_apellido();
					cin.ignore();
					while (true) {
						cout << "Ingrese el apellido del contacto a editar: ";
						getline(cin, apellido);
						tiene_numeros(apellido);

						encontrado = busqueda(apellido, lista, 3);
						if (encontrado == nullptr) {
							cout << "Ese apellido no existe." << endl;
						}
						else {
							cout << "Ingrese nuevos nombres: ";
							getline(cin, nombre);
							validacion_numeros(nombre);

							encontrado->getPersona()->setNombre(nombre);
							escribir("Contactos.bin", lista, 3);
							break;
						}
					}
					break;
				}
				break;

			case 2:
				switch (flag) {
				case 1:
					lista->ordenamiento_telefono();
					cin.ignore();
					while (true) {
						cout << "Ingrese el telefono movil del contacto a editar: ";
						getline(cin, tel_movil);
						telefono_valido(tel_movil);

						encontrado = busqueda(tel_movil, lista, 1);
						if (encontrado == nullptr) {
							cout << "Ese numero movil no existe." << endl;
						}
						else {
							cout << "Ingrese nueva direccion: ";
							getline(cin, direccion);

							encontrado->getPersona()->setDireccion(direccion);
							escribir("Contactos.bin", lista, 1);
							break;
						}
					}
					break;

				case 2:
					lista->ordenamiento_identidad();
					cin.ignore();
					while (true) {
						cout << "Ingrese el numero de identidad del contacto a editar: ";
						getline(cin, num_identidad);
						identidad_valida(num_identidad);

						encontrado = busqueda(num_identidad, lista, 2);
						if (encontrado == nullptr) {
							cout << "Ese numero de identidad no existe." << endl;
						}
						else {
							cout << "Ingrese nueva direccion: ";
							getline(cin, direccion);

							encontrado->getPersona()->setDireccion(direccion);
							escribir("Contactos.bin", lista, 2);
							break;
						}
					}

					break;

				case 3:
					lista->ordenamiento_apellido();
					cin.ignore();
					while (true) {
						cout << "Ingrese el apellido del contacto a editar: ";
						getline(cin, apellido);
						tiene_numeros(apellido);

						encontrado = busqueda(apellido, lista, 3);
						if (encontrado == nullptr) {
							cout << "Ese apellido no existe." << endl;
						}
						else {
							cout << "Ingrese nueva direccion: ";
							getline(cin, direccion);

							encontrado->getPersona()->setDireccion(direccion);
							escribir("Contactos.bin", lista, 3);
							break;
						}
					}
					break;
				}
				break;

			case 3:
				switch (flag) {
				case 1:
					lista->ordenamiento_telefono();
					cin.ignore();
					while (true) {
						cout << "Ingrese el telefono movil del contacto a editar: ";
						getline(cin, tel_movil);
						telefono_valido(tel_movil);

						encontrado = busqueda(tel_movil, lista, 1);
						if (encontrado == nullptr) {
							cout << "Ese numero movil no existe." << endl;
						}
						else {
							cout << "Ingrese nuevo telefono fijo: ";
							getline(cin, tel_fijo);
							telefono_valido(tel_fijo);

							encontrado->getPersona()->setTelFijo(tel_fijo);
							escribir("Contactos.bin", lista, 1);
							break;
						}
					}
					break;

				case 2:
					lista->ordenamiento_identidad();
					cin.ignore();
					while (true) {
						cout << "Ingrese el numero de identidad del contacto a editar: ";
						getline(cin, num_identidad);
						identidad_valida(num_identidad);

						encontrado = busqueda(num_identidad, lista, 2);
						if (encontrado == nullptr) {
							cout << "Ese numero de identidad no existe." << endl;
						}
						else {
							cout << "Ingrese nuevo telefono fijo: ";
							getline(cin, tel_fijo);
							telefono_valido(tel_fijo);

							encontrado->getPersona()->setTelFijo(tel_fijo);
							escribir("Contactos.bin", lista, 2);
							break;
							break;
						}
					}

					break;

				case 3:
					lista->ordenamiento_apellido();
					cin.ignore();
					while (true) {
						cout << "Ingrese el apellido del contacto a editar: ";
						getline(cin, apellido);
						tiene_numeros(apellido);

						encontrado = busqueda(apellido, lista, 3);
						if (encontrado == nullptr) {
							cout << "Ese apellido no existe." << endl;
						}
						else {
							cout << "Ingrese nuevo telefono fijo: ";
							getline(cin, tel_fijo);
							telefono_valido(tel_fijo);

							encontrado->getPersona()->setTelFijo(tel_fijo);
							escribir("Contactos.bin", lista, 3);
							break;
						}
					}
					break;
				}
				break;

			default:
				if (opcion != 4) {
					cout << endl;
					cout << "Ingrese la opcion nuevamente: " << endl;
				}
				break;

			}

		} while (opcion != 4);
	}
}


void menu(Lista* lista, int flag) {

	int opcion;
	do {
		system("cls");
		cout << "------------\n Contactos | \n------------ \n1. Agregar  \n2. Eliminar \n3. Editar \n4. Buscar \n5. Mostrar \n6. Salir \n\nIngrese la opcion: ";
		cin >> opcion;

		switch (opcion) {
		case 1:
			agregar(lista);
			break;

		case 2:
			eliminar(lista, flag);
			break;

		case 3:
			editar(lista, flag);
			break;

		case 4:
			buscar(lista, flag);
			break;

		case 5:
			if (lista->lista_vacia()) {
				cout << "No se pueden mostrar contactos. La lista esta vacia." << endl;
			}
			else {
				lista->imprimir();
				cout << "Presione ENTER para volver al menu...";
				cin.ignore();
				cin.get();
				system("cls");
			}
			break;

		default:
			if (opcion != 6) {
				cout << endl;
				cout << "Ingrese la opcion nuevamente: " << endl;
			}
			break;
		}


	} while (opcion != 6);
}

int main() {
	int flag;
	Nodo* cabeza = nullptr;
	Lista* lista = new Lista(cabeza);

	ifstream file("Contactos.bin", ios::binary);

	if (file) {
		leer("Contactos.bin", lista, flag);
	}
	else {
		cout << "No existe un archivo para cargar. Agregue contactos. " << endl;
	}
	menu(lista,flag); 
}
