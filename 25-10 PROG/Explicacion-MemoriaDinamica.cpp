
#include<iostream>
#include <cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>

using namespace std;


void cargarVector(int *v, int tam){
    int i;
    for(i=0;i<tam;i++){
        v[i]=i+1;
    }
}

void mostrarVector(int *v, int tam){
    int i;
    for(i=0;i<tam;i++){
        cout<<v[i]<<endl;
    }
}


void copiarVector(int *destino,int *origen,int tam){
    int i;
    for(i=0;i<tam;i++){
        destino[i]=origen[i];
    }
}


void agregarValores(int *v,int ini,int fin){
    int i;
    for(i=ini;i<fin;i++){
        v[i]=i+1;
    }

}



int main(){


   int tamLista;
   cout << "INGRESE LA CANTIDAD DE NUMEROS DE LA LISTA ";
   cin >> tamLista;

   int *vec;
   vec=new int[tamLista];
   if(vec==NULL){
    cout << "NO SE PUDO ASIGNAR LA MEMORIA." << endl;
   }

   cargarVector(vec, tamLista);
   mostrarVector(vec, tamLista);
   cout << endl;

   int agregar;
   int *nuevoVector;
   cout << "INGRESE LA CANTIDAD DE COMPONENTES A AGREGARLE AL VECTOR:";
   cin >> agregar;
   /// Lo que tenga el vector que lo mantenga, pero ahora quiero agregarle mas cosas.
   nuevoVector = new int[tamLista+agregar];
   if(nuevoVector == nullptr){
    cout << "ERROR DE MEMORIA.";
   }
   copiarVector(nuevoVector, vec, tamLista);
   agregarValores(nuevoVector, tamLista, tamLista+agregar);
   mostrarVector(nuevoVector, tamLista+agregar);

   delete vec;
   delete nuevoVector;




    system("pause") ;
    return 0;
}
