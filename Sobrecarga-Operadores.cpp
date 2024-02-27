#include<iostream>
#include <cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>
using namespace std;

class Cadena{
private:
    char *puntero;
    int tam;
public:
    Cadena(const char *inicio="nada"){
     tam = strlen(inicio)+1;
     puntero=new char[tam];
     if(puntero==NULL){
        cout << "ERROR DE ASIGNACION DE MEMORIA.";
     }
     strcpy(puntero, inicio);
     puntero[tam-1]='\0';
    }


    void Mostrar(){
    cout << puntero << endl;
    }

    void agregarCaracter(char letra){
    char *punteroAux;
    tam++;
    punteroAux = new char[tam];
    if(punteroAux == NULL){
        exit(1);
    }
    strcpy(punteroAux, puntero);
    punteroAux[tam-2]= letra;
    punteroAux[tam-1]='\0';
    delete puntero;
    puntero = new char[tam];
    strcpy(puntero, punteroAux);
    delete punteroAux;
    }

    /*
    void concatenar(const char *cadena){
    for(int i=0; i<strlen(cadena); i++)
    {
     agregarCaracter(cadena[i]);
    }
    }
    */

    void concatenar(const char *cadena)
    {
     char *punteroAux;

     punteroAux=new char[tam];
     if(punteroAux==NULL){
        exit(1);
     }
     strcpy(punteroAux, puntero);
     delete puntero;
     tam = tam + strlen(cadena);
     puntero=new char[tam];
     if(puntero==NULL){
        exit(1);
     }
      strcpy(puntero, punteroAux);
      delete punteroAux;
      strcat(puntero, cadena); //función  para concatenar.
      puntero[tam-1]='\0';
    }

    const char *getPuntero(){return puntero;}
    int getTam(){return tam;}
    ~Cadena(){delete puntero;}

    /// SobreCarga:
    // En general si yo voy a sobrecargar un operador relacional " == " estoy esperando un valor booleano.

    /// (&obj) si yo le pongo el "(Cadena &obj)" estamos haciendo el paso de parametros por referencia.
    /// Cadena obj --> si yo hago esto se copia el objeto completo.
    /// si yo no quiero que ese parametro sea cambiado le agrego un const.(const Cadena &obj)
    bool operator == (const Cadena &obj){
     if(strcmp(this->puntero, obj.puntero)==0) return true;
     return false;
    }

    bool operator == (const char *obj){
     if(strcmp(this->puntero, obj)==0) return true;
     return false;
    }


    // orden del psicográfico, si puntero esta mas cerca del final del diccionario,
    // que obj.puntero significa que es mayor. y va a ser mayor a 0 el resultado.
    bool operator > (const Cadena &obj){
    if(strcmp(this->puntero, obj.puntero)>0) return true;
     return false;
    }

    bool operator > (int tamanio){
     if(tam > tamanio)return true;
     return false;
    }



    void operator = (const Cadena &obj){
     delete puntero;
     tam = obj.tam;
     puntero=new char[tam];
     if(puntero==NULL) exit(1);
     strcpy(puntero, obj.puntero);
    }

    void operator = (const char *obj){
     delete puntero;
     tam = strlen(obj)+1;
     puntero=new char[tam];
     if(puntero==NULL) exit(1);
     strcpy(puntero, obj);
     puntero[tam-1]= '\0';
    }

    Cadena & operator = (const Cadena &obj){
     delete puntero;
     tam = obj.tam;
     puntero=new char[tam];
     if(puntero==NULL) exit(1);
     strcpy(puntero, obj.puntero);
     return *this;
    }

     Cadena & operator = (const char *obj){
     delete puntero;
     tam = strlen(obj)+1;
     puntero=new char[tam];
     if(puntero==NULL) exit(1);
     strcpy(puntero, obj);
     puntero[tam-1]= '\0';
     return *this;
    }
 };









/// SOBRECARGA DE OPERADORES: MECANISMO QUE NOS PERMITE AGREGAR FUNCIONALIDAD A LOS OPERADORES EXISTENTES.
/// SE CONSIGUE ESCRIBIENDO UN CÓDIGO SUJETO A CIERTAS REGLAS DENTRO DE LA CLASE.
int main()
{

   Cadena palabra("zorro"),aux("zorrino");

   palabra=aux;
   palabra="UNA ASIGNACION NUEVA.";
   palabra.Mostrar();



   /*if(palabra=="zorro")cout << "Son iguales.";
   else cout << "Son distintos.";*/






   /*palabra.Mostrar();
   cout << palabra.getTam() << endl;
   palabra.agregarCaracter('f');
   palabra.Mostrar();
   */

   //if(strcmp(palabra.getPuntero(), aux.getPuntero())==0){

   /// Generalmente el que se recibe como parametro es el de la derecha.
   /*if(palabra.operator==(aux)){
    cout << "SON IGUALES.";
   }
   else{
    cout << "SON DISTINTAS.";
   }*/


   /*if(aux > palabra){
    cout << "Mayor la primera.";
   }
   else{
    cout << "No es mayor la primera.";
   }*/


   /*if(aux > palabra.getTam()){
    cout << "La primera tiene mas caracteres.";
   }
   else{
    cout << "La primera no tiene mas caracteres.";
   }
   */

   return 0;


}
/* EJERCICIOS: agregarCaracter--> recibe un caracter y lo agrega a la cadena existente.
               concatenar --> recibe una cadena y la agrega a la cadena existentes.*/

/// sobrecargar el operador  != de manera tal que sea verdadero cuando los dos objetos a comparar sean
/// distintos.
/// SOBRECARGAR EL OPERA <= PARA DOS CASOS: PARA COMPARAR LAS CADENAS DE CARACTERES Y PARA COMPARAR EL LARGO DE LA CADENA.
/// SOBRECARGAR EL OPERA += DE MANERA TAL QUE SE CONCATENEN LAS DOS CADENAS.
