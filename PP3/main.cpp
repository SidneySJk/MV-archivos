#include <iostream>
#include "XMLDocument.hpp"

int main() {
    XMLDocument xmlDoc;
    std::cout << "El programa ha comenzado correctamente." << std::endl;

    char rootName[] = "raiz";
    char rootName1[] = "Hola";

    // Crear el nodo raíz
    int rootId = xmlDoc.Root(rootName);
    std::cout << "ID del primer nodo raiz: " << rootId << std::endl;

    int rootId1 = xmlDoc.Root(rootName1);
    std::cout << "ID del segundo nodo raiz: " << rootId1 << std::endl;

    // Seleccionar el segundo nodo raíz
    if (xmlDoc.Select(rootId1)) {
        std::cout << "El nodo con ID " << rootId1 << " ha sido seleccionado." << std::endl;
    } else {
        std::cout << "No se pudo seleccionar el nodo con ID " << rootId1 << "." << std::endl;
    }

    // Agregar un hijo solo con nombre
    char childName[] = "hijo1";
    int childId1 = xmlDoc.Child(childName);
    std::cout << "ID del hijo 1: " << childId1 << std::endl;

    // Agregar un hijo con nombre y contenido
    char childName2[] = "hijo2";
    char childContent[] = "Este es el contenido del hijo 2";
    int childId2 = xmlDoc.Child(childName2, childContent);
    std::cout << "ID del hijo 2: " << childId2 << std::endl;

    // Editar el contenido del nodo seleccionado
    char newContent[] = "Contenido editado";
    if (xmlDoc.EditContent(newContent, xmlDoc.getOvrMode())) {
        std::cout << "Contenido editado correctamente." << std::endl;
    } else {
        std::cout << "Error al editar el contenido." << std::endl;
    }

    // Eliminar el nodo seleccionado
    if (xmlDoc.Delete()) {
        std::cout << "Nodo eliminado correctamente." << std::endl;
    } else {
        std::cout << "Error al eliminar el nodo." << std::endl;
    }

    return 0;
}


/*
Para compilar y ejecutar:
g++ -c main.cpp
g++ main.o -o miPrograma
./miPrograma.exe
*/
