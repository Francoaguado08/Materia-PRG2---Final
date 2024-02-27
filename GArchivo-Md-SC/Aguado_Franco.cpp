#include<iostream>
#include <cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>

using namespace std;
#include "parcial2.h"

/*
class Medico{
private:
    int IDpersonal;
    char nombre[30];
    char telefono[30];
    char email[30];
    char direccion[30];
    bool estado;

class Socio{
private:
    char codigoSocio[5];
    int categoria;
    char nombre[30];
    char direccion[30];
    char telefono[30];
    char email[30];
    Fecha inscripcion;
    bool estado;

class Especialidad{
private:
    int codigoEspecialidad, tipo;
    char nombre[30];
    bool estado;

class Turno{
private:
    int numeroTurno;
    char codigoSocio[5];
    int codigoEspecialidad;
    int IDpersonal;
    float importe;
    Fecha fechaTurno;
    bool estado;

*/




///  PUNTO 1 : Generar un archivo con los socios que hayan tenido un turno para la especialidad con código 11.
///  Cada registro debe tener el
///  + código de socio,
///  + el nombre del socio
///  + la fecha del turno.


/// CLASE PARA LOS ATRIBUTOS QUE TE PIDE TENER EL NUEVO ARCHIVO.
class SolucionPunto{
private:
        char codSocio[5];
        char nombreSocio[50];
        Fecha fechaTurno;
        bool estado;

    public:

        /// CONSTRUCTOR CON VALORES DE OMISION.
        /// Verificar bien mi constructor.
        SolucionPunto(const char *_codSocio= "-", const char *_nombreSocio = "-", Fecha _fechaTurno=Fecha(), bool _estado=true)
        {
         strcpy(codSocio, _codSocio);
         strcpy(nombreSocio, _nombreSocio);
         fechaTurno = _fechaTurno;
         estado =true;
        }



        //SETS
        void setCodSocio(const char  *i){ strcpy(codSocio , i); }
        void setNombreSocio(const char* n){ strcpy(nombreSocio,n); }
        void setFechaTurno(Fecha _fechaTurno){ fechaTurno = _fechaTurno;}


        //GETS
        const char *getCodSocio()const{ return codSocio; }
        const char* getNombreSocio()const{ return nombreSocio; }
        Fecha getFechaTurno(){ return fechaTurno;}
        bool getEstado(){return estado;}

        //OTROS
        void Mostrar(){

                cout << "CODIGO DE SOCIO:";
                cout << codSocio<< endl;
                cout << "NOMBRE DEL SOCIO:";
                cout << nombreSocio << endl;

                fechaTurno.Mostrar();


        }



        ///  PUNTO 3:
        //// Hacer una sobrecarga de operador para la clase nueva del punto 1 que sea útil para la resolución de alguno de los puntos.

        /// SI ES INT
        /* bool operator==(SolucionPunto obj){
        if(codSocio == obj.getCodSocio())return true;
        return false;}*/

        ///SI ES CHAR

       // PUNTO 3: Sobrecarga de operador ==
        bool operator==(const SolucionPunto &obj) const {
        return (strcmp(codSocio, obj.getCodSocio()) == 0);
       }

    };




/// ClASE PARA GENERAR LAS FUNCIONES DEL NUEVO ARCHIVO: CONTAR,ESCRIBIR,LISTAR,LEER.
class ArchivoSolucionPunto{
    private:
        char nombre[30];
    public:
        ArchivoSolucionPunto(const char* n){
            strcpy(nombre,n);
        }

        ArchivoSolucionPunto(){
        strcpy(nombre,"Soluciones.dat");
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


    bool Escribir(SolucionPunto reg) {
    FILE *p = fopen(nombre, "ab");
    if (p == NULL) return false;

    // Mostramos la información antes de escribirla
    reg.Mostrar();

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



        void vaciar(){
        FILE *p = fopen(nombre, "wb");
        if (p == NULL){return ;}
        fclose(p);
        }
};


/// RECORRO TURNOS, RECORRO SOCIOS, COMPARO QUE TENGAN EL MISMO CODIGO, CONDICION DE ESPECIALIDAD 11 Y LUEGO ESCRIBO EN EL NUEVO ARCHIVO CADA SOCIO.
void solucionPunto1() {
    ArchivoSocios archiSocios("socios.dat");
    int cantRegSoc = archiSocios.contarRegistros();
    Socio regSocio;

    ArchivoTurnos archiTurnos("turnos.dat");
    int cantRegTur = archiTurnos.contarRegistros();
    Turno regTurno;


    ArchivoSolucionPunto archi;
    SolucionPunto obj;
    archi.vaciar();

    for (int i = 0; i < cantRegTur; i++) {
        bool socioEncontrado = false;
        regTurno = archiTurnos.leerRegistro(i);


        for (int j = 0; j < cantRegSoc; j++) {
            regSocio = archiSocios.leerRegistro(j);


            if (strcmp(regSocio.getCodigoSocio(), regTurno.getCodigoSocio()) == 0) {
                if (regTurno.getCodigoEspecialidad() == 11) {

                    //  Esto verifica En caso
                    // de que si hay más de un turno para esa especialidad se debe registrar la fecha del primero.
                    if(!socioEncontrado){
                    socioEncontrado = true;

                    obj.setCodSocio(regSocio.getCodigoSocio());
                    obj.setNombreSocio(regSocio.getNombre());
                    obj.setFechaTurno(regTurno.getFechaTurno());


                    archi.Escribir(obj);
                    }


                   break;// Sale del bucle interno desp de ecnontrar el primer turno para este socio.

                }

            }
        }


    }

    archi.listarArchivo();
}




///     PUNTO 2:

/*Hacer una función (llamarla desde el mismo main() que llama a la función que resuelve el punto 1) para
generar de manera dinámica un vector
que contenga los socios que se hayan inscripto en un año que se ingresa por teclado. Listar el vector creado*/


void solucionPunto2(){

  int year;
  cout << "INGRESE EL AÑO:";
  cin >> year;

  ArchivoSocios archiSoc ("socios.dat");
  int tamSoc = archiSoc.contarRegistros();
  Socio regSoc;


 /*Se recorre el archivo de socios y se cuenta cuántos de ellos se inscribieron
 en el año proporcionado por el usuario. Para darle un tamaño al vector Dinamico.*/

 int contador=0;
 for(int i=0;i<tamSoc;i++){
    regSoc=archiSoc.leerRegistro(i);

    if(regSoc.getInscripcion().getAnio()==year){
    contador++;
     cout << "Socio encontrado para el anio " << year << ": " << regSoc.getNombre() << endl;
    }

 }

 /*Se crea un vector dinámico vec de tipo Socio con el tamaño igual al contador obtenido anteriormente.*/
 Socio *vec= nullptr;
 vec= new Socio[contador];
 if(vec == nullptr) return;

 //Llenamos el vector dinamico con los socios inscritos en el año dado.
 /*Se recorre nuevamente el archivo de socios y se llenan los elementos
 del vector (((vec)))) con los socios que se inscribieron en el año proporcionado.*/
 int pos =0;
 for(int i=0;i<tamSoc;i++){
    regSoc=archiSoc.leerRegistro(i);
    if(regSoc.getInscripcion().getAnio()==year){
        vec[pos]=regSoc;
        pos++;
        cout << "Añadiendo socio al vector: " << regSoc.getNombre() << endl;
    }
 }


 /// Muestro el vector de socios filtrados.
 /// LISTAR EL VECTOR CREADO.
 for (int i = 0; i < contador; i++) {
    vec[i].Mostrar();
   }



 delete vec;
 }



///    PUNTO 3:
/*Hacer una sobrecarga de operador para la clase nueva del punto 1 que sea útil para la resolución de alguno de los puntos.*/

/*


     bool operator == (Punto1 obj){
        if(codigoSocio == obj.getCodSocio()) return true;
        return false;
    }


*/








int main() {


    solucionPunto1();
    system("pause");

    solucionPunto2();
    system("pause");


}
