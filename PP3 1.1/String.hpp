#include <fstream>
#ifndef STRING_HPP
#define STRING_HPP

class String {
private:
	char* paCadena = nullptr;
	
	void copiarCadena(const char *pFuente) {
            	if (pFuente != nullptr) {
                		int largo = 0;
                		while (pFuente[largo] != '\0') {
    				++largo;
    			}
                		paCadena = new char[largo + 1];

                		for (int i = 0; i <= largo; ++i) {
                    		paCadena[i] = pFuente[i];
                		}
            	} else {
                		paCadena = nullptr;
            	}
    	}

public:
	String(const char *pCadena) : paCadena(nullptr) {
    		copiarCadena(pCadena);
    	}

	~String() {
    		delete[] paCadena;
    	}

	char* mostrarCadena() {
    		return paCadena;
    	}

	int len() const{
    		int largo = 0;
    		while (paCadena[largo] != '\0') {
    			++largo;
    		}
    		return largo;

    	}

	int leng(char* cadena) {
    		int largo = 0;
    		while (cadena[largo] != '\0') {
    			++largo;
    		}
    		return largo;
    	}

	void cambiarCadena(const char *pCadenaNueva) {
    		delete[] this->paCadena;
    		copiarCadena(pCadenaNueva);
    	}

	char caracterEn(int pos){
    	       if (pos > len()){
    		 return '\0';
    	       }
    	       return paCadena[pos];
    	}

        bool operator==(const String& otro) const {
        	if (paCadena == nullptr && otro.paCadena == nullptr) {
            		return true;
        	} else if (paCadena != nullptr && otro.paCadena != nullptr) {
            		int i = 0;
            		while (paCadena[i] != '\0' && otro.paCadena[i] != '\0') {
                		if (paCadena[i] != otro.paCadena[i]) {
                    			return false;
                		}
                    	i++;
            		}
            		return paCadena[i] == '\0' && otro.paCadena[i] == '\0';
        	} else {
            		return false;
         	}
    	}

	String** split(char separador){
    		 int ind = 0;
    		 int indR = 0;
    		 String **pRes = new String*[len()];
    		 char *pTempList = new char[len()];
    		 for(int i = 0; i < len(); i++){
    	            if(paCadena[i] == separador){
    		    	pTempList[ind] = '\0';
    			pRes[indR] = new String(pTempList);
    			indR ++;
    			ind = 0; 
    		    } else {
    			pTempList[ind] = paCadena[i];
    			ind++;
    		    }		
    		}
    		pTempList[ind] = '\0';
            	pRes[indR] = new String(pTempList);
    		indR++;
            	return pRes;
    	}

	String* reemplazarOcurrencias(char* anterior, char* nuevo) {
        		int largo = len();
        		int largo_Anterior = leng(anterior);
        		int largo_Nuevo = leng(nuevo);	
        		char *pResultado = new char[largo * largo_Nuevo]; 
        		int indice2 = 0;
        		int i = 0;

        		while (i < largo - largo_Anterior + 1) {
            		bool iguales = true;
            		for (int j = 0; j < largo_Anterior; j++) {
                			if (paCadena[i + j] != anterior[j]) {
                    			iguales = false;
                    			break;
                			}
            		}
            		if (iguales) {
                	    	    for (int j = 0; j < largo_Nuevo; j++) {
                           	         pResultado[indice2] = nuevo[j];
    		                 indice2++;
                	     	    }
                	    	    i += largo_Anterior;
            		} else {
                	     	    pResultado[indice2] = paCadena[i];
    	    	     	    indice2++;
    	    	            i++;
            		}
        		}

    		for (; i < largo; ++i) {
            	    pResultado[indice2++] = paCadena[i];
        		}

        		pResultado[indice2] = '\0'; 

        		cambiarCadena(pResultado);

        		return this;
    	}

    	String* concatenarCadenas(char** cadenas) {
        		int i = 0;
        		while (cadenas[i] != nullptr) {
            		concatenar(cadenas[i]);
            		++i;
        		}
        		return this;
    	}

    	void concatenarEn(char *pCadena, int indice) {
    		if(pCadena == nullptr) return;

    		int largo_cadena_original = len();
    		int largo_cadena_nueva = leng(pCadena);
    		int indice_nuevo;

    	    	if (indice < 0) {
            		indice_nuevo = ((indice % largo_cadena_original) + largo_cadena_original) % largo_cadena_original;
        		} else {
        	   		indice_nuevo = indice % largo_cadena_original;
        		}

    	    	char *pCadena_nueva = new char[largo_cadena_original + largo_cadena_nueva + 1];

            	for (int i = 0; i < indice_nuevo; ++i) {
            		pCadena_nueva[i] = paCadena[i];
        		}

        		for (int i = 0; i < largo_cadena_nueva; ++i) {
            		pCadena_nueva[indice_nuevo + i] = pCadena[i];
        		}

        		for (int i = indice_nuevo; i < largo_cadena_original; ++i) {
        	    		pCadena_nueva[largo_cadena_nueva + i] = paCadena[i];
        		}

        		pCadena_nueva[largo_cadena_original + largo_cadena_nueva] = '\0';

    		cambiarCadena(pCadena_nueva);
    	}

    	void reemplazarEn(char *pCadenaNueva, int indice) {
            	if (paCadena == nullptr || pCadenaNueva == nullptr) {
                		return;
            	}

            	int largo_cadena_original = len();
            	int largo_cadena_nueva = leng(pCadenaNueva);
            	int indice_nuevo;

            	if (indice < 0) {
                		indice_nuevo = ((indice % largo_cadena_original) + largo_cadena_original) % largo_cadena_original;
            	} else {
                		indice_nuevo = indice % largo_cadena_original;
            	}

            	char *pCadena_nueva = new char[largo_cadena_original + largo_cadena_nueva + 1];

            	for (int i = 0; i < indice_nuevo; ++i) {
                		pCadena_nueva[i] = paCadena[i];
            	}

            	for (int i = 0; i < largo_cadena_nueva; ++i) {
                		pCadena_nueva[indice_nuevo + i] = pCadenaNueva[i];
            	}

            	for (int i = indice_nuevo + largo_cadena_nueva; i < largo_cadena_original; ++i) {
                		pCadena_nueva[i] = paCadena[i - largo_cadena_nueva];
            	}

            	pCadena_nueva[largo_cadena_original + largo_cadena_nueva] = '\0';

            	cambiarCadena(pCadena_nueva);
    	}

    	void concatenar(char *pCadena) {
    		if(pCadena == nullptr) return;
    		int largo_cadena_original = len();
    		int largo_cadena_nueva = leng(pCadena);
    		int indice_nuevo = largo_cadena_original + largo_cadena_nueva + 1;
    		
    		char *pCadena_concatenada = new char[indice_nuevo];

    		for (int i = 0; i < largo_cadena_original; i++) {
    			pCadena_concatenada[i]=paCadena[i];
    		}
    		int contador_interno=0;
    		for (int i = largo_cadena_original;i< indice_nuevo;i++) {
    			pCadena_concatenada[i]=pCadena[contador_interno];
    			contador_interno++;
    		}

    		pCadena_concatenada[indice_nuevo-1]='\0';

    		cambiarCadena(pCadena_concatenada);

    	}

    	int contarCaracter(char caracter) {
    		int largo_cadena = len();
    		int contador = 0;
    		for (int i = 0; i < largo_cadena; i++) {
    			if (paCadena[i]==caracter) contador++;
    		}
    		return contador;
    	}

    	int ultimoIndice(char caracter) {
    		int largo_cadena = len();
    		int contador = 0;
    		for (int i = 0; i < largo_cadena; i++) {
    			if (paCadena[i]==caracter) contador=i;
    		}
    		return contador;
    	}
    
    	void guardarEnArchivo(char *pRuta,char *pModo) {

    		if(pRuta == nullptr || pModo == nullptr)return;
    		if(leng(pModo)!=1)return;
    		if(pModo[0] != 'w' && pModo[0] != 'a') return;
    		
    		if(pModo[0] == 'w') {
    			std::ofstream archivo(pRuta,std::ios::out);
    			if(!archivo.is_open())return;

    			archivo << paCadena << std::endl;
    			archivo.close();

    		} else {
    			std::ofstream archivo(pRuta,std::ios::app);
    			if(!archivo.is_open())return;

    			archivo << paCadena << std::endl;
    			archivo.close();
    		}

    	}

    	void leerArchivo(char *pRuta) {
    		if(pRuta==nullptr)return;

    		std::ifstream archivo(pRuta);
    		if(!archivo.is_open())return;

    		archivo.seekg(0, std::ios::end);
    		int tamano_archivo= archivo.tellg();
    		archivo.seekg(0, std::ios::beg);

    		char *pTexto=new char[tamano_archivo +1];

    		archivo.read(pTexto, tamano_archivo);
    		pTexto[tamano_archivo]= '\0';

    		archivo.close();

    		cambiarCadena(pTexto);

    		delete[] pTexto;
    	}
};
#endif
