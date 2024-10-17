#include "String.hpp"

struct Atributo {
    String clave;
    String valor;

    // Constructor por defecto
    // que acepta const char*
    Atributo(const char* pClave = "", const char* pValor = "") : clave(pClave), valor(pValor) {}

    // Constructor que acepta objetos String
    Atributo(const String& pClave, const String& pValor) : clave(pClave), valor(pValor) {}

};

class Nodo {
private:
    int aId;
    Nodo** apHijos;
    String aNombre;
    String aContenido;
    Atributo* aAtributos;  // Almacena los pares clave-valor
    Nodo* apSiguienteNodo;
    int aNumHijos;
    int aCapacidadHijos;
    int aNumAtributos;
    int aCapacidadAtributos;
    bool contenidoAntesDeHijos;  // Para controlar si el contenido se despliega antes o después de los hijos

public:
    // Constructores
    Nodo() : aId(-1), apHijos(new Nodo*[2]()), aNombre(""), aContenido(""), apSiguienteNodo(nullptr), aNumHijos(0), aCapacidadHijos(2), aNumAtributos(0), aCapacidadAtributos(2), contenidoAntesDeHijos(true) {
        aAtributos = new Atributo[aCapacidadAtributos];
    }

    Nodo(int id, char* pNombre) : aId(id), apHijos(new Nodo*[2]()), aNombre(pNombre), aContenido(""), apSiguienteNodo(nullptr), aNumHijos(0), aCapacidadHijos(2), aNumAtributos(0), aCapacidadAtributos(2), contenidoAntesDeHijos(true) {
        aAtributos = new Atributo[aCapacidadAtributos];
    }

    Nodo(int id, char* pNombre, char* pContenido) : aId(id), apHijos(new Nodo*[2]()), aNombre(pNombre), aContenido(pContenido), apSiguienteNodo(nullptr), aNumHijos(0), aCapacidadHijos(2), aNumAtributos(0), aCapacidadAtributos(2), contenidoAntesDeHijos(true) {
        aAtributos = new Atributo[aCapacidadAtributos];
    }

    // Destructor
    ~Nodo() {
        for (int i = 0; i < aNumHijos; ++i) {
            delete apHijos[i]; 
        }
        delete[] apHijos; 
        delete[] aAtributos;
    }

    // Métodos de acceso (getters)
    int getId() const {
        return aId;
    }

    int getNumAtributos(){
        return aNumAtributos;
    }

    char* getNombre() {
        return aNombre.mostrarCadena();
    }

    char* getContenido() {
        return aContenido.mostrarCadena();
    }

    Nodo* getNext() {
        return apSiguienteNodo;
    }

    Nodo* getHijo(int indice) {
        if (indice < 0 || indice >= aNumHijos) {
            return nullptr; 
        }
        return apHijos[indice];
    }

    int getNumHijos() {
        return aNumHijos; 
    }

    // Obtener el valor de un atributo
    char* getAtributos(const char* clave) {
        for (int i = 0; i < aNumAtributos; ++i) {
            if (aAtributos[i].clave == clave) {
                return aAtributos[i].valor.mostrarCadena();
            }
        }
        return nullptr; //no existe la clave
    }

    // Métodos de modificación (setters)
    void setId(int id) {
        aId = id;
    }

    void setNext(Nodo* pNextNode) {
        apSiguienteNodo = pNextNode;
    }

    void setContenido(char* pContenido) {
        aContenido.cambiarCadena(pContenido);
    }

    // Agregar o actualizar un atributo
    void setAtributo(const char* clave, const char* valor) {
        for (int i = 0; i < aNumAtributos; ++i) {
            if (aAtributos[i].clave == clave) {
                aAtributos[i].valor.cambiarCadena(valor);  // Actualizar si existe
                return;
            }
        }

        // Si no existe, agregar un nuevo atributo
        if (aNumAtributos >= aCapacidadAtributos) {
            aCapacidadAtributos *= 2;
            Atributo* nuevoArray = new Atributo[aCapacidadAtributos];
            for (int i = 0; i < aNumAtributos; ++i) {
                nuevoArray[i] = aAtributos[i];
            }
            delete[] aAtributos;
            aAtributos = nuevoArray;
        }

        aAtributos[aNumAtributos++] = {String(clave), String(valor)};
    }

    // Métodos de lógica
    void agregarHijo(Nodo* hijo) {
        if (hijo == nullptr) {
            return; 
        }

        if (aNumHijos >= aCapacidadHijos) {
            aCapacidadHijos *= 2; 
            Nodo** nuevoArray = new Nodo*[aCapacidadHijos];

            for (int i = 0; i < aNumHijos; ++i) {
                nuevoArray[i] = apHijos[i];
            }

            delete[] apHijos;
            apHijos = nuevoArray; 
        }

        apHijos[aNumHijos++] = hijo; 
    }

    void eliminarHijo(Nodo* pHijo) {
        if (pHijo == nullptr || aNumHijos == 0) {
            return; 
        }
        for (int i = 0; i < aNumHijos; ++i) {
            if (apHijos[i] == pHijo) {
                delete apHijos[i]; 
                for (int j = i; j < aNumHijos - 1; ++j) {
                    apHijos[j] = apHijos[j + 1];
                }
                apHijos[--aNumHijos] = nullptr; 
                return; 
            }
        }
    }

    // Cambiar el modo de visualización del contenido (antes o después de los hijos)
    void cambiarModoVisualizacionContenido() {
        contenidoAntesDeHijos = !contenidoAntesDeHijos;
    }

    void ViewTree(Nodo* nodo, int nivel = 0) {
    if (nodo == nullptr) {
        return; // Si el nodo es nulo, no hacemos nada
    }

    // Imprimir el nombre del nodo con indentación según su nivel
    for (int i = 0; i < nivel; ++i) {
        std::cout << "  "; // Indentación
    }
    std::cout << nodo->getNombre() << std::endl;

    // Imprimir atributos del nodo, si los hay
    for (int i = 0; i < nodo->getNumAtributos(); ++i) {
        // Suponiendo que hay un método para obtener todos los atributos
        std::cout << "  " << nodo->getAtributos(i).clave << ": " << nodo->getAtributos(i).valor << std::endl;
    }

    // Recorrer los hijos del nodo
    for (int i = 0; i < nodo->getNumHijos(); ++i) {
        ViewTree(nodo->getHijo(i), nivel + 1); // Llamada recursiva para cada hijo, aumentando el nivel
    }
}

};
