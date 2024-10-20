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

    // Pruebas para EditAttribute

    // Agregar un atributo
    char attributeKey[] = "class";
    char attributeValue[] = "button";
    if (xmlDoc.EditAttribute(attributeKey, attributeValue, xmlDoc.getAddMode())) {
        std::cout << "Atributo 'class=button' agregado correctamente." << std::endl;
    } else {
        std::cout << "Error al agregar el atributo 'class=button'." << std::endl;
    }

    // Sobrescribir el atributo
    char newValue[] = "button-primary";
    if (xmlDoc.EditAttribute(attributeKey, newValue, xmlDoc.getOvrMode())) {
        std::cout << "Atributo 'class' sobrescrito a 'button-primary' correctamente." << std::endl;
    } else {
        std::cout << "Error al sobrescribir el atributo 'class'." << std::endl;
    }

    // Agregar al final del valor del atributo
    char appendedValue[] = "-large";
    if (xmlDoc.EditAttribute(attributeKey, appendedValue, xmlDoc.getApdMode())) {
        std::cout << "Atributo 'class' actualizado con 'button-primary-large' correctamente." << std::endl;
    } else {
        std::cout << "Error al actualizar el atributo 'class'." << std::endl;
    }

    // Eliminar el atributo
    if (xmlDoc.EditAttribute(attributeKey, attributeValue, xmlDoc.getDelMode())) {
        std::cout << "Atributo 'class' eliminado correctamente." << std::endl;
    } else {
        std::cout << "Error al eliminar el atributo 'class'." << std::endl;
    }

    if (xmlDoc.SwitchContentPosition()) {
        std::cout << "Posición del contenido cambiada correctamente." << std::endl;
    } else {
        std::cout << "Error al cambiar la posición del contenido." << std::endl;
    }

    std::cout << "Contenido del nodo después de cambiar la posición:" << std::endl;
    std::cout << xmlDoc.ViewNode() << std::endl;

    // Prueba de DefineTemplate
    char templateName[] = "Plantilla1";
    char templateContent[] = "<tag>Contenido de la plantilla</tag>";

    int templateId = xmlDoc.DefineTemplate(templateName, templateContent);

    if (templateId != -1) {
        std::cout << "Plantilla '" << templateName << "' definida correctamente con ID: " << templateId << std::endl;
    } else {
        std::cout << "Error al definir la plantilla." << std::endl;
    }

    // Prueba de EditTemplate
    char newTemplateContent[] = "<tag>Contenido editado de la plantilla</tag>";

    if (xmlDoc.EditTemplate(templateId, newTemplateContent)) {
        std::cout << "Contenido de la plantilla con ID " << templateId << " editado correctamente." << std::endl;
    } else {
        std::cout << "Error al editar el contenido de la plantilla." << std::endl;
    }



    // Eliminar el nodo seleccionado
    if (xmlDoc.Delete()) {
        std::cout << "Nodo eliminado correctamente." << std::endl;
    } else {
        std::cout << "Error al eliminar el nodo." << std::endl;
    }


    //Mostrar XML y guardarlo

    std::cout<<"XML creado:"<<std::endl;
    std::cout<<xmlDoc.ViewXML()<<std::endl;

    if(xmlDoc.Save("Primer XML")){
        std::cout<<"XML guardado con exito."<<std::endl;
    } else {
        std::cout<<"Hubo un error al guardar el XML."<<std::endl;
    }

    return 0;
}
  
  

/*
Para compilar y ejecutar:
g++ -c main.cpp
g++ main.o -o miPrograma
./miPrograma.exe
*/
