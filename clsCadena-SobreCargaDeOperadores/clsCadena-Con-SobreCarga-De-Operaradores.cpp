#include<iostream>
#include <cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>
using namespace std;

class Cadena{
private:
    char *puntero; // Puntero que apunta a la cadena de caracteres.
    int tam; // Tamaño de la cadena.
public:
    /// Constructor de la clase.
    Cadena(const char *inicio = "nada"){
     /*1)Se calcula el tam de la cadena +1 para el caracter nulo "\0".
     contamos cada caracter con strlen.*/
     tam = strlen(inicio)+1;
     // 2) Se asigna memoria dinamica y se copia el contenido.
     puntero = new char[tam];
     if(puntero == NULL){
        cout << "ERROR DE ASIG DE MEMORIA.";
     }
     strcpy(puntero, inicio);
     //3)Se asegura de que la cadena termine con  "\0".
     puntero[tam-1]='\0';
    }
    //Destructor de la clase.
    ~Cadena() {
        delete puntero;  // Se libera la memoria Dinamica.
    }


    /// Método para agregar un caracter a la cadena.
    void agregarCaracter(char letra){
     char *punteroAux;
     //Incrementamos el tam de la cadena.
     tam++;
     //Se crea un nuevo vector auxiliar con el nuevo tam.
     punteroAux = new char[tam];
     if(punteroAux == NULL){
        exit(1);
     }
     //Copiamos el contenido original al vector auxiliar.
     strcpy(punteroAux, puntero);
     //Agregamos el nuevo caracter al final del arreglo aux.
     punteroAux[tam-2]=letra;
     //Aseguramos que termine en "\0".
     punteroAux[tam-1]='\0';
     //Se libera la memoria de la cadena original.
     delete puntero;
     //Se crea un nuevo vector para la cadena con el nuevo tamaño.
     puntero = new char[tam];
     //Se copia el contenido del arreglo auxiliar a la cadena
     strcpy(puntero, punteroAux);
     // Se libera la memoria del vector auxiliar .
     delete punteroAux;
    }



    /// METODO PARA CONCATENAR OTRA CADENA A UNA EXISTENTE.
    void concatenarCadena(const char *cadena){
    //Se crea un nuevo vector AUX para almacenar la cadena original.
     char *punteroAux = new char[tam];
     if(punteroAux==NULL){
        exit(1);
     }

     //Copiamos el contenido de la cadena original al arreglo AUX.
     strcpy(punteroAux, puntero);
     //Liberamos la memoria de la cadena original.
     delete puntero;
     //Se actualiza el tamaño de la cadena.
     tam = tam + strlen(cadena);

     //Se crea un nuevo arreglo para la cadena con el nuevo tamaño.
     puntero = new char[tam];
     if(puntero ==NULL){
        exit(1);
     }
     //Se copia el contenido del arreglo AUX  a la nueva cadena.
     strcpy(puntero, punteroAux);
     //Se libera la memoria del arreglo AUX.
     delete punteroAux;
     //Se concatena la nueva cadena al final de la existente.
     strcat(puntero, cadena);
     //Aseguramos que termine con '\0'.
     puntero[tam-1]='\0';
    }


    ///METODO PARA OBTENER EL PUNTERO A LA CADENA
    const char *getPuntero(){
     return puntero;
    }

    /// SOBRECARGA DEL OPERADOR DE IGUALDAD PARA COMPARAR CON OTRA CADENA.
    //DEL LADO DERECHO ESTA LO QUE LE PASAMOS POR PARAMETRO ?
    bool operator == (const Cadena &obj){
     return (strcmp(this->puntero, obj.puntero) == 0);
    }













};

















int main()
{

   /// MAIN  PARA PROBAR TODAS LAS FUNCIONALIDADES:


   /*
   //PRUEBA 01:
   Cadena miCadena("Hola, Mundo!");
   //Obtener el puntero constante a la cadena.
   const char *punteroCadena = miCadena.getPuntero();
   //Imprimo la cadena desde fuera de la clase.
   cout << "Cadena desde fuera de la clase: " << punteroCadena << endl;
   return 0;
   */


   /*
   //Prueba 02:
   Cadena cad1("HOLA COMO TE VA.");
   Cadena cad2("HOLA COMO TE VA.");
   // Utilizar la sobrecarga del operador == para comparar las cadenas.
    if (cad1 == cad2) {
        cout << "Las cadenas son iguales." << endl;
    } else {
        cout << "Las cadenas son distintas." << endl;
    }
    */









    return 0;
}
