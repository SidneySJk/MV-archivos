#include "Nodo.hpp"
#include "String.hpp"

class XMLDocument {

private:
    const int ADD = 100;    // Mode addition, adds the value to the beginning of the set
                            // as allowed by the specific function (with or without repetition)
    const int OVR = 200;    // Mode overwrite, if it already exists, replaces the value, if not, just add it.
    const int APD = 300;    // Mode append, appends the value to the end of the set as
                            // allowed by the specific function (with or without repetition)
    const int DEL = 400;    // Mode delete, if the value exists, it is deleted instead
    
    // Node content location type
    const int BEG = 10;     // Content is displayed before children of node, just after the opening tag.
    const int END = 20;     // Content is displayed after children of node, just before the closing tag.



    Nodo* apNodoRaiz;
    Nodo* apNodoSeleccionado;
    int aId;

    bool buscarNodo(Nodo* pNodo, int id) {
        if (pNodo == nullptr) {
            return false;
        }
        if (pNodo->getId() == id) {
            apNodoSeleccionado = pNodo; 
            return true; 
        }
        for (int i = 0; i < pNodo->getNumHijos(); i++) {
            if (buscarNodo(pNodo->getHijo(i), id)) {
                return true;
            }
        }

        return false;
    }

    Nodo* buscarPadre(Nodo* pNodo, Nodo* pHijo) {
        if (pNodo == nullptr) {
            return nullptr; 
        }
        for (int i = 0; i < pNodo->getNumHijos(); i++) {
            if (pNodo->getHijo(i) == pHijo) {
                return pNodo; 
            }
            
            Nodo* resultado = buscarPadre(pNodo->getHijo(i), pHijo);
            if (resultado != nullptr) {
                return resultado; 
            }
        }

        return nullptr; 
    }

        

public:

    int getAddMode() const { return ADD; }
    int getOvrMode() const { return OVR; }
    int getApdMode() const { return APD; }
    int getDelMode() const { return DEL; }
    int getBegLocation() const { return BEG; }
    int getEndLocation() const { return END; }




    XMLDocument() {
        apNodoRaiz = nullptr;
        apNodoSeleccionado = nullptr;
        aId = 0;
    }

    ~XMLDocument() {
        delete apNodoRaiz;
    }


    int Root (char *pNombre) {
        if (pNombre ==nullptr) {
            return -1;
        }
        Nodo* nuevoNodo = new Nodo(aId,pNombre);
        if (apNodoRaiz == nullptr) {
            apNodoRaiz = nuevoNodo;
            apNodoSeleccionado = nuevoNodo;
        } else {
            nuevoNodo->agregarHijo(apNodoRaiz);
            apNodoRaiz = nuevoNodo;
        }
        aId++;
        return nuevoNodo->getId();
    }   

    bool Select (int id) {
        return buscarNodo(apNodoRaiz, id);
    }

    int Child (char *pNombre) {
        if (apNodoSeleccionado == nullptr || pNombre == nullptr) {
            return -1; 
        }
        Nodo* nuevoHijo = new Nodo(aId, pNombre);
        apNodoSeleccionado->agregarHijo(nuevoHijo); 
        aId++;
        return nuevoHijo->getId();
    }

    int   Child (char *pNombre, char *pContenido){
        if (apNodoSeleccionado == nullptr || pNombre == nullptr || pContenido == nullptr) {
            return -1; 
        }
        Nodo* nuevoHijo = new Nodo(aId, pNombre, pContenido);
        apNodoSeleccionado->agregarHijo(nuevoHijo); 
        aId++;
        return nuevoHijo->getId(); 
    }

    /*bool  EditAttribute (char *key, char *value, int mode) {
        Editar atributos o contenido de un nodo actual: los atributos se agregan como pares llave-valor, por lo que se reciben estos parámetros mientras que el contenido es únicamente el valor de lo que se agrega. Estos se pueden ejecutar en modo de agregado, adjunto, sobre escritura o borrado. No puede existir atributos con llaves repetidas y cada nodo tiene únicamente un contenido.
    }
    */


    bool  EditContent (char *pContenido, int modo) {
        String contenidoDelNodo(apNodoSeleccionado->getContenido());
        String vacio("");
        if (modo == OVR) {
            apNodoSeleccionado->setContenido(pContenido);
            return true;
        }

        if (modo == DEL) {
            contenidoDelNodo.reemplazarOcurrencias(pContenido,vacio.mostrarCadena());
            apNodoSeleccionado->setContenido(contenidoDelNodo.mostrarCadena());
            return true;
        }
        if (modo == ADD) {
           contenidoDelNodo.concatenarEn(pContenido,0);
            apNodoSeleccionado->setContenido(contenidoDelNodo.mostrarCadena());
            return true;
        }
        if (modo == APD){
           contenidoDelNodo.concatenar(pContenido);
            apNodoSeleccionado->setContenido(contenidoDelNodo.mostrarCadena());
            return true;

        } else {
            return false;
        }
    }

    /*
    bool  SwitchContentPosition ();
    int   DefineTemplate (char *name, char *xmlContent);
    bool  EditTemplate (int templateId, char *xmlContent);
    int   InstantiateTemplate (int templateId, char **placeholders, char **values, int placeholderCount);
    bool  DeleteTemplate (int templateId);
    char* TemplatesToString();
    */



    bool Delete() {
        if (apNodoSeleccionado == nullptr) {
            return false; 
        }
        if (apNodoSeleccionado == apNodoRaiz) {
            Nodo* nodoARemover = apNodoRaiz;
            apNodoRaiz = nullptr; 
            delete nodoARemover; 
            apNodoSeleccionado = nullptr; 
            return true; 
        }
        Nodo* padre = buscarPadre(apNodoRaiz, apNodoSeleccionado);
        if (padre != nullptr) {
            padre->eliminarHijo(apNodoSeleccionado); 
            delete apNodoSeleccionado; 
            apNodoSeleccionado = nullptr; 
            return true; 
        }

        return false; 
    }

    /*
    char* ViewTree ();
    */
    char* ViewNode () {
        String nombre("Nombre Etiqueta: ");
        String atributos("Atributos: ");
        String contenido("Contenido: ");
        String salto_linea("\n");
        String temporal(nombre);
        temporal.concatenar(apNodoSeleccionado->getNombre());
        temporal.concatenar(salto_linea.mostrarCadena());
        temporal.concatenar(atributos.mostrarCadena());
        temporal.concatenar(apNodoSeleccionado->getAtributos());
        temporal.concatenar(salto_linea.mostrarCadena());
        temporal.concatenar(contenido.mostrarCadena());
        temporal.concatenar(apNodoSeleccionado->getContenido());
        temporal.concatenar(salto_linea.mostrarCadena());
        return temporal.mostrarCadena();
    }

    /*
    char* ViewXML ();
    bool  Save (char *filename);
    */


};