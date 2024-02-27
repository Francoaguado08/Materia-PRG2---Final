
#include<iostream>
#include <cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>
using namespace std;
#include "parcial2.h"


/*

Punto (1)
/ *Generar un archivo con la cantidad de ventas que cada restaurante de la categoría 2 tuvo
este año.
Cada registro debe tener el siguiente formato:
---->  Código de restaurante,
---->  nombre de restaurante,
-----> cantidad de ventas

Listar el archivo generado.*/


/// CLASE PARA LOS ATRIBUTOS QUE TE PIDE TENER EL NUEVO ARCHIVO.
class SolucionPunto{
private:
        int codRestaurante;
        char nombreRestaurante[50];
        int cantVentas;
        bool estado ;



    public:
        /// CONSTRUCTORES



        /// CONSTRUCTOR CON VALORES DE OMISION.
        SolucionPunto(int codigo=0, const char *nom = "-", int cantV = 0){
                     codRestaurante = codigo;
                     strcpy(nombreRestaurante, nom);
                     cantVentas = cantV;
                     estado =true;
                     }


        //SETS
        void setCodRestaurante(int i){ codRestaurante = i; }
        void setNombreRestaurante(const char* n){ strcpy(nombreRestaurante,n); }
        void setCantVentas(int i){ cantVentas = i; }


        //GETS
        int getCodRestaurante(){ return codRestaurante; }
        const char* getNombreRestaurante(){ return nombreRestaurante; }
        int getCantVentas(){ return cantVentas;}
        bool getEstado(){return estado;}

        //OTROS
        void Mostrar(){
            if( estado ){
                cout << codRestaurante<< endl;
                cout << nombreRestaurante << endl;
                cout << cantVentas << endl;

            }
        }

        /*void operator=(Tecnico &obj){
            DNI = obj.getDNI();
        }


        bool operator=(Tecnico &obj){
        if(strcpy(nombre,obj.getNombre()))return true;
        return false;*/



        ///  PUNTO 3:
        //  Agregar una sobrecarga para el operador == de la clase nueva del punto 1, que reciba
        //  como parámetro un objeto de la misma clase*/

        bool operator==(SolucionPunto obj){
        if(codRestaurante == obj.getCodRestaurante())return true;
        return false;}


    };

/// ClASE PARA GENERAR LAS FUNCIONES DEL NUEVO ARCHIVO: CONTAR,ESCRIBIR,LISTAR,LEER.
class ArchivoSolucionPunto{
    private:
        char nombre[30];
    public:
        ArchivoSolucionPunto(const char* n){
            strcpy(nombre,n);
        }

        SolucionPunto leerRegistro(int pos){
            SolucionPunto reg;
            FILE *p=fopen(nombre, "rb");
            if(p==NULL) return reg;
            fseek(p, sizeof reg*pos,0);
            fread(&reg, sizeof reg,1, p);
            fclose(p);
            return reg;
        }
        int contarRegistros(){
            FILE *p=fopen(nombre, "rb");
            if(p==NULL) return -1;
            fseek(p, 0,2);
            int tam=ftell(p);
            fclose(p);
            return tam/sizeof(SolucionPunto);
        }


        bool Escribir(SolucionPunto reg){
            FILE *p=fopen(nombre, "ab");
            if(p==NULL) return false;
            bool escribio = fwrite(&reg, sizeof reg, 1, p);
            fclose(p);
            return escribio;
        }

       bool listarArchivo(){
       SolucionPunto reg;
       FILE *p;
       p= fopen(nombre, "rb");
       if(p == NULL){
        cout << "NO SE PUDO ABRIR EL ARCHIVO." << endl;
        return false;
        }
       while(fread(&reg, sizeof reg, 1, p)== 1){
        reg.Mostrar();
        cout << endl;
        }
       fclose(p);
      return true;
      }
};

/// SE RECORRE DOS ARCHIVOS. SE VERIFICA LA CONDICION Y LUEGO SE ESCRIBE EN EL NUEVO ARCHIVO.
void solucionPunto1(){

    ///  1)
    ArchivoRestaurantes archiRest("restaurantes.dat");
    int cantRegRest = archiRest.contarRegistros();
    Restaurante regRest;
    ///  2)
    ArchivoVentas archiVentas("ventas.dat");
    int cantRegVentas = archiVentas.contarRegistros();
    Venta regVenta;
    ///  3)
    ArchivoSolucionPunto archi("Soluciones.dat");
    SolucionPunto obj;
    /// Inicializo el contador para contar Las Ventas.
    int contador=0;

    for(int i=0; i<cantRegRest;i++){
        regRest=archiRest.leerRegistro(i);

        for(int j=0; i<cantRegVentas;j++){
            regVenta=archiVentas.leerRegistro(j);

            if( (regRest.getCodigoRestaurante() == regVenta.getCodigoRestaurante()) &&
                (regRest.getCategoria()== 2) && (regVenta.getFechaReserva().getAnio() == 2023) )
                {
                 contador++; // CANT DE VENTAS CON LAS CONDICIONES ESPECIFICADAS.
                }


        }

         //cuando salgo de la iteracion chica, tengo los valores sin haberlo perdido antes de que itere.
        // por lo tanto guarda los valores para cada tipo de restaurante.
        obj.setCodRestaurante(regRest.getCodigoRestaurante());
        obj.setNombreRestaurante(regRest.getNombre());
        obj.setCantVentas(contador);

        archi.Escribir(obj);


    }

    archi.listarArchivo();

 }

/*Punto 2
Informar la provincia con menor cantidad de restaurantes de la categoría 1.*/
void solucionPunto2(){

    //Instancio el archivo y el Objeto.
    ArchivoRestaurantes archiRest("restaurantes.dat");
    int cantRegRest = archiRest.contarRegistros();
    Restaurante regRest;

    int vProvincia[24]={0};// Vector para contar cuantos restaurantes.

    for(int i=0; i< cantRegRest; i++){
        regRest=archiRest.leerRegistro(i);

        //Categoria (1)
        if(regRest.getCategoria()==1){
        vProvincia[regRest.getProvincia()-1]++; //Lo guardo aca.
        }
    }

      //Declaro mi Menor para luego comparar.
     int menor = vProvincia[0];

     //Ignorando los que tienen 0 en el acumulador.
     for(int i=0; i<24; i++){
        if( (vProvincia[i] < menor) && (vProvincia[i]!=0) )
        menor = vProvincia[i];
     }



    cout << "La Provincia con menor cantidad de restaurantes de la categoria 1 es: " << menor + 1 << endl;

}



/* Punto 3
Agregar una sobrecarga para el operador == de la clase nueva del punto 1, que reciba
como parámetro un objeto de la misma clase*/

/*
   //si yo quisiera agregar mas propiedades  tendria que agregar mas gets.
    bool operator ==(Punto1 obj){
     if(codigoRestaurante == obj.getCodigoRestaurante()) return true;
     return false;
    }
*/

/// EJEMPLO PARA PROBAR LA SOBRECARGA EN EL MAIN.
 /* Punto1 obj(10,"FRANCO", 5), obj2(12,"Otro nombre", 25);
  if(obj == obj2){
    cout << "IGUALES." << endl;
  }else{
   cout << "DISTINTOS." << endl;
  }*/



/*Punto 4
Crear un vector dinámico para copiar y mostrar el archivo creado en el punto 1*/
void solucionPunto4(){
 ArchivoSolucionPunto archiP4 ("Solluciones.dat");
 int cant = archiP4.contarRegistros();

 SolucionPunto *vec = nullptr;
 vec = new SolucionPunto[cant];
 if(vec == nullptr)return;

 for(int i=0; i<cant; i++){
    vec[i] = archiP4.leerRegistro(i);
    vec[i].Mostrar();
 }



 delete vec;
}






int main()
{

 solucionPunto1();
 system("pause");
 system("cls");

 solucionPunto2();
 system("pause");
 system("cls");


 solucionPunto4();
 system("pause");
 system("cls");





    return 0;
}
