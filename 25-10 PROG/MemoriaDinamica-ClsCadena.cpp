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
    Cadena(const char *inicio){
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






    int getTam(){return tam;}
    ~Cadena(){delete puntero;}

 };










int main()
{

   Cadena palabra("HOLA COMO TE VA?");
   palabra.Mostrar();
   cout << palabra.getTam() << endl;
   palabra.agregarCaracter('f');
   palabra.Mostrar();
   return 0;


}
/* EJERCICIOS: agregarCaracter--> recibe un caracter y lo agrega a la cadena existente.
               concatenar --> recibe una cadena y la agrega a la cadena existentes.
