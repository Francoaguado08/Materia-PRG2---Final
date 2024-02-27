#include<iostream>
#include <cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>

using namespace std;
#include "clases.h"

/// 1) Generar un  archivo con:
/// A) CODIGO Y NOMBRE DEL JUGADOR.
/// B)NOMBRE DE PAIS QUE PERTENECE
/// C) CANTIDAD DE GOLES CONVERTIDOS.
/// SOLO DE LOS JUGADORES QUE HICIERON GOLES, SIN CONTAR GOLES EN CONTRA.

 /*bool operator>(const GolesJugador &aux){
 if(this->cantidadGoles>aux.cantidadGoles) return true;
 return false;
 }*/




class Punto1{
private:
    char codigoJugador[5];
    char nombreJugador[30];
    char nombrePais[30];
    int cantidadGoles;
public:
  void setCodigoJugador(const char *cod){strcpy(codigoJugador, cod);}
  void setNombreJugador(const char *nom){strcpy(nombreJugador, nom);}
  void setNombrePais(const char *n){strcpy(nombrePais, n);}
  void setCantidadGoles(int g){cantidadGoles = g;}

  const char *getCodigoJugador(){return codigoJugador;}
  const char *getNombreJugador(){return nombreJugador;}
  const int getCantidadGoles(){return cantidadGoles;}

  void Mostrar(){
  cout<<"CODIGO DE JUGADOR: ";
  cout<<codigoJugador<<endl;
  cout<<"NOMBRE DE JUGADOR: ";
  cout<<nombreJugador<<endl;
  cout<<"PAIS: ";
  cout<<nombrePais<<endl;
  cout<<"CANTIDAD DE GOLES: ";
  cout<<cantidadGoles<<endl;
   }
  /// SOBRECARGA DE OPERADOR.
 bool operator>(const Punto1 &reg){
 if(this->cantidadGoles>reg.cantidadGoles) return true;
 return false;
 }
};


class ArchivoPunto1{
 private:
     char nombre[30];
 public:
    ArchivoPunto1(){
    strcpy(nombre,"Punto1.dat");
    }

    bool escribirRegistro(Punto1 reg){
     FILE *p;
     p = fopen(nombre, "ab");
     if(p==NULL) return false;
     bool escribio = fwrite(&reg, sizeof(reg), 1,p);
     fclose(p);
     return escribio;
    }

    void vaciar(){
    FILE *p=fopen(nombre, "wb");
    if (p==NULL){return;}
    fclose(p);
    }

    bool listarArchivo(){
    Punto1 reg;
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

    int contarRegistros(){
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return -1;
        fseek(p, 0,2);
        int tam=ftell(p);
        fclose(p);
        return tam/sizeof(Punto1);
    }

    Punto1 leerRegistro(int pos){
        Punto1 reg;
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return reg;
        fseek(p, sizeof(Punto1)*pos,0);
        fread(&reg, sizeof reg,1, p);
        fclose(p);
        return reg;
    }
};

// Función para buscar el nombre de un país dado su código
const char *buscarNombrePais(int codPais){
 Pais obj; // creo mi intancia de objeto pais.

 int pos=0;
 while(obj.leerRegistro(pos++)){
     if(codPais==obj.getCodigoPais())
     return obj.getNombrePais();
  }

 }


// Función para contar la cantidad de goles de un jugador
int contarGoles(const char *codigoJugador){
 Gol obj;// Creo mi instancia de la clase de goles.
 int pos=0, cant=0;
 while(obj.leerRegistro(pos++)){ //recorro mientras me de true.
 if(strcmp(codigoJugador, obj.getCodigoJugador())==0) // si Hacen MATCH :
 if(obj.getTipo()!=2) //chequeo que los goles no sean en contra.
    cant++;
  }
  return cant;
 }


void punto1(){
 Jugador regJug;
 Punto1 p1;
 ArchivoPunto1 archiP1;
 archiP1.vaciar();


 int pos=0;
 int cantGoles;

 while(regJug.leerRegistro(pos++)){
   // Contar la cantidad de goles del jugador actual
   cantGoles=contarGoles(regJug.getCodigoJugador());
   if(cantGoles>0){
          p1.setCantidadGoles(cantGoles);
          p1.setCodigoJugador(regJug.getCodigoJugador());
          p1.setNombreJugador(regJug.getNombreJugador());

          p1.setNombrePais(buscarNombrePais(regJug.getCodigoPais()));
          // GRABO TODO.
          archiP1.escribirRegistro(p1);
         }
    }
}


//sin sobrecarga de operador >


/// 2) Informar los datos del jugador que más cantidad de goles a favor convirtió.
void punto2(){
 Punto1 obj, aux;
    ArchivoPunto1 archi;

    int pos = 0, maxGoles = 0;
    // Leer registros de Punto1 hasta encontrar uno que no exista
     while (true) {
        obj = archi.leerRegistro(pos++);

        // Verificar si se llegó al final del archivo
        if (obj.getCantidadGoles() == 0) {
            break;
        }

        if (obj.getCantidadGoles() > maxGoles) {
            maxGoles = obj.getCantidadGoles();
            aux = obj;
        }
    }

  }




//sobrecargando el operador > para la clase GolesJugador
/*void punto2(){
GolesJugador obj, aux;
aux.setCantidadGoles(0);
int pos=0;
while(obj.leerDeDisco(pos++)){
if(obj>aux){
aux=obj;
}
}
cout<<"GOLEADOR: ";
aux.Mostrar();
}
*/



int main(){
punto1();
punto2();
system("pause");
return 0;
}























