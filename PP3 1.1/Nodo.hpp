#include "String.hpp"

class Nodo {
private:
    int aId;
    Nodo** apHijos;
    String aNombre;
    String aContenido;
    String aAtributos;
    Nodo* apSiguienteNodo;
    int aNumHijos;
    int aCapacidadHijos;
    int aPosicionContenido;

public:
    // Constructores
    Nodo() : aId(-1), apHijos(new Nodo*[2]()), aNombre(""), aContenido(""), aAtributos(""), apSiguienteNodo(nullptr), aNumHijos(0), aCapacidadHijos(2), aPosicionContenido(10) {}

    Nodo(int id, char* pNombre) : aId(id), apHijos(new Nodo*[2]()), aNombre(pNombre), aContenido(""), aAtributos(""), apSiguienteNodo(nullptr), aNumHijos(0), aCapacidadHijos(2), aPosicionContenido(10) {}

    Nodo(int id, char* pNombre, char* pContenido) : aId(id), apHijos(new Nodo*[2]()), aNombre(pNombre), aContenido(pContenido), aAtributos(""), apSiguienteNodo(nullptr), aNumHijos(0), aCapacidadHijos(2), aPosicionContenido(10) {}

    // Destructor
    ~Nodo() {
        for (int i = 0; i < aNumHijos; ++i) {
            delete apHijos[i]; 
        }
        delete[] apHijos; 
    }

    // Métodos de acceso (getters)
    int getId() const {
        return aId;
    }

    char* getNombre() {
        return aNombre.mostrarCadena();
    }

    char* getContenido() {
        return aContenido.mostrarCadena();
    }

    char* getAtributos() {
        return aAtributos.mostrarCadena();
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

    int getPosicionContenido() const {
        return aPosicionContenido;
    }

    // Métodos de modificación (setters)
    void setId(int id) {
        aId = id;
    }

    void setNext(Nodo* pNextNode) {
        apSiguienteNodo = pNextNode;
    }

    void setAtributo(char* pAtributo) {
        aAtributos.cambiarCadena(pAtributo);
    }

    void setContenido(char* pContenido) {
        aContenido.cambiarCadena(pContenido);
    }

    void setPosicionContenido(int posicion) {
        aPosicionContenido = posicion;
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

    void alternarPosicionContenido(int BEG, int END) {
        aPosicionContenido = (aPosicionContenido == BEG) ? END : BEG;
    }
};
