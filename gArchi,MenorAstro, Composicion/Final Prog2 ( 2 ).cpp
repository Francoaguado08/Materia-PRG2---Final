#include<iostream>
#include <cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>

using namespace std;

class Fecha{
private:
    int dia,mes, anio;
public:
    void Mostrar(){
        cout<<dia<<"/"<<mes<<"/"<<anio<<endl;
    }
    int getDia(){return dia;}
    int getMes(){return mes;}
    int getAnio(){return anio;}

    void setDia(int d){dia=d;}
    void setMes(int m){mes=m;}
    void setAnio(int a){anio=a;}
};



class Astronautas{
private:
    int DNI;
    char nombre[50];
    char apellido[50];
    int pais;
    int categoria;
    bool estado;
public:
    void setDNI(int i);
    void setNombre(const char*n);
    void setApellido(const char*n);
    void setPais(int i);
    void setCategoria(int i);


    int getDNI();
    const char* getNombre();
    const char* getApellido();
    int getPais();
    int getCategoria();




 Astronautas(int _DNI = 0,const char *_nombre="Nadie",const char *_apellido="Nadie",
 int _pais=0, int _categoria=0)
 {
 DNI = _DNI;
 strcpy(nombre, _nombre);
 strcpy(apellido, _apellido);
 pais = _pais;
 categoria = _categoria;
 estado = true;
 }


};


class ArchivoAstronautas{
private:
    char nombre[40];
public:
    ArchivoAstronautas(const char*n){strcpy(nombre, n);}
    int contarRegistros();
    Astronautas leerRegistro(int i);
};


class Misiones{
private:
    int numeroMision;
    int DNI;
    Fecha inicio;
    int cargo;
    bool activo;
public:
    void setDNI(int i);
    void setNumeroMision(int i);
    void setFechaInicio(Fecha i);
    void setCargo(int i);
    void setActivo(bool i);

    int getDNI();
    int getNumeroMision();
    Fecha getFecha();
    int getCargo();
    void getActivo();

};


class ArchivoMisiones{
private:
    char nombre[40];
public:
    ArchivoMisiones(const char*n){strcpy(nombre, n);}
    int contarRegistros();
    Misiones leerRegistro(int i);
};


class SolucionPunto{
private:
        int DNI;
        char nombre[50];
        char apellido[50];
        bool estado ;

    public:

        //SETS
        void setDNI(int i){ DNI = i; }
        void setNombre(const char* n){ strcpy(nombre,n); }
        void setApellido(const char* n){ strcpy(apellido,n); }
        void setEstado(bool n){estado = n;}

        //GETS
        int getDNI(){ return DNI; }
        const char* getNombre(){ return nombre; }
        const char* getApellido(){ return apellido; }
        bool getEstado(){return estado;}

        //OTROS
        void Mostrar(){
            if( estado ){
                cout << nombre << endl;
                cout << apellido << endl;
                cout << DNI << endl;

            }
        }

        /*void operator=(Tecnico &obj){
            DNI = obj.getDNI();
        }


        bool operator=(Tecnico &obj){
        if(strcpy(nombre,obj.getNombre()))return true;
        return false;*/
    };


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
};


void punto1();



int main()
{












    return 0;
}



/*
a) Generar un archivo con los astronautas del país 1
que hayan participado de misiones con
el siguiente formato de registro:
DNI, nombre y apellido del astronauta (3 puntos).
*/
void punto1(){
ArchivoAstronautas archiAstronautas("Astronautas.dat");
ArchivoMisiones archiMisiones("Misiones.dat");
Misiones objMisiones;
Astronautas objAstronautas;
int cantAstronautas = archiAstronautas.contarRegistros();
int cantMisiones = archiMisiones.contarRegistros();

SolucionPunto obj;
ArchivoSolucionPunto archi("SolucionPunto.dat");

for(int i=0; i<cantAstronautas;i++){
    objAstronautas = archiAstronautas.leerRegistro(i);

    for(int j=0; j<cantMisiones;j++){
     objMisiones = archiMisiones.leerRegistro(j);

     if( (objAstronautas.getDNI() == objMisiones.getDNI())&&(objAstronautas.getPais()==1) )
     {
     obj.setDNI(objAstronautas.getDNI());
     obj.setNombre(objAstronautas.getNombre());
     obj.setApellido(objAstronautas.getApellido());

     archi.Escribir(obj);
     }


    }




 }



 cout << "ARCHIVO GRABADO EXITOSAMENTE." << endl;

}


/// B ) CATEGORIA CON MENOS (-) ASTRONAUTAS.
void punto2(){
ArchivoAstronautas archiAstronautas("Astronautas.dat");
Astronautas objAstronauta;
int cantAstronautas = archiAstronautas.contarRegistros();
const int categorias = 15;
int vCategorias[categorias]={0};

for(int i=0;i<cantAstronautas;i++){

 objAstronauta=archiAstronautas.leerRegistro(i);

 vCategorias[objAstronauta.getCategoria()-1] ++ ;

 }

int menor = vCategorias[0];

for(int i=0; i<categorias;i++){

    if(vCategorias[i] < menor){
        menor= vCategorias[i];
    }
}

cout << "CATEGORIA CON MENOS ASTRONAUTAS:" << menor+1 << endl;
 }



///3) Defina qué es el mecanismo de la composición, y
///si se aplica en alguna de las clases del
  // ejercicio 1 (2 puntos).


/*
Composicion :  un objeto está compuesto por otros objetos.
Si el objeto principal se destruye, los objetos compuestos también se destruyen.

Hay una relación de "composición lógica" en el sentido de que tienes objetos de la clase
Fecha como miembros de la clase Misiones. En este caso, la clase Misiones está compuesta lógicamente por objetos de la clase Fecha.
Si eliminas una instancia de Misiones, su fecha asociada también dejará de existir.


*/





