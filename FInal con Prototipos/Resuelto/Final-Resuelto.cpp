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

class Tecnico{
private:
    char nombre[50];
    char apellido[50];
    int puesto;
    int DNI;
    float sueldo;
    Fecha ingreso;
    bool activo;
public:

    //Prototipos.
    void setDNI(int i);
    void setNombre(const char*n);
    void setApellido(const char*n);
    void setPuesto(int i);
    void setSueldo(float i);
    void setFecha(Fecha i);
    void setActivo(bool i);

    int getDNI();
    const char* getNombre();
    const char* getApellido();
    int getPuesto();
    float getSueldo();
    Fecha getFecha();
    void getActivo();
};

class ArchivoTecnico{
private:
    char nombre[40];
public:
    ArchivoTecnico(const char*n);
    int contarRegistros();
    Tecnico leerRegistro(int i);
};

class Tecnico_Obras{
private:
    int numero;
    int DNI;
    Fecha inicio;
    int tipo;
    bool activo;
public:
    void setDNI(int i);
    void setNumero(int i);
    void setFecha(Fecha i);
    void setTipo(int i);
    void setActivo(bool i);

    int getDNI();
    int getNumero();
    Fecha getFecha();
    int getTipo();
    void getActivo();

};


class ArchivoTecnicoObras{
private:
    char nombre[40];
public:
    ArchivoTecnicoObras(const char*n){strcpy(nombre, n);}
    int contarRegistros();
    Tecnico_Obras leerRegistro(int i);
};


class SolucionPunto{
    private:
        int DNI;
        char nombre[50];
        char apellido[50];
        bool estado;

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

        void operator=(Tecnico &obj){
            DNI = obj.getDNI();
        }


        bool operator=(Tecnico &obj){
        if(strcpy(nombre,obj.getNombre()))return true;
        return false;
    }


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

void punto2();


int main(){

    punto1();
    system("pause");
    system("cls");
    punto2();

    return 0;
}

/*
a) Generar un archivo nuevo con el siguiente formato de registro:
   --> DNI
 nombre y apellido de los técnicos que hayan participado de alguna obra este año
*/




void punto1(){
 // PASO 1:
 // Creo la instancia del Archivo y el Objeto.
 ArchivoTecnico archiTec("Tecnicos.dat");
 ArchivoTecnicoObras archiTecObras("Tecnicos_obras.dat");
 Tecnico objTec;
 Tecnico_Obras objTecObras;


 //PASO 2 :
 // GUARDO MI CANTIDAD DE REGISTROS.
 int cantTec = archiTec.contarRegistros();
 int cantTecObras = archiTecObras.contarRegistros();

 //PASO 3:
 // RECORRO  TECNICOS.DAT:
 for(int i=0; i<cantTec;i++){
     objTec = archiTec.leerRegistro(i);

 //PASO 4:
 // RECORRO TECNICOS_OBRAS.DAT
 for(int j=0; j<cantTecObras;j++){
    objTecObras = archiTecObras.leerRegistro(i);

 // PASO 5:
 // VERIFICO SI ES DE ESTE AÑO (2023) Y SI COINCIDE EL DNI DE UN ARCHIVO EN EL OTRO.
        if( (objTecObras.getFecha().getAnio() == 2023) && ( objTecObras.getDNI() == objTec.getDNI() )  ){

                //PASO 6 : SE CREA EL OBJETO.
                SolucionPunto obj;
                //seteamos
                obj.setApellido(objTec.getApellido());
                obj.setDNI( objTec.getDNI());
                obj.setNombre(objTec.getNombre());
                obj.setEstado(true);

                //CREAR ARCHIVO Y GUARDAR
                ArchivoSolucionPunto archiSolucionPunto("SolucionPunto.dat");
                archiSolucionPunto.Escribir(obj);

                //SALE DEL FOR OBRAS )?
                j = cantTecObras;


        }


    }

 }


 }//FIN






/*
b) El mes del 2022 en el que se registraron más ingresos de técnicos (3 puntos).
*/

void punto2(){
//PASO 1 : CREO EL ARCHIVO E INSTANCIO MI OBJ.
 ArchivoTecnico archiTec("Tecnico.dat");
 Tecnico objTec;
 //PASO 2: GUARDAR CANTIDADES E INICIALIZAR MI ACUMULADOR.
 int cantTec = archiTec.contarRegistros();
 const int meses = 12;
 nt vMeses[meses]={0};

 //PASO 3: RECORRER TECNICOS:
 for(int i=0; i<cantTec; i++){
    objTec = archiTec.leerRegistro(i);

    //PASO 4 : VERIFICO EL AÑO QUE SEA 2022.
    if(objTec.getFecha().getAnio()==2022){
        mes[ objTec.getFecha().getMes()-1 ] ++ ;
    }
 }

 //PASO 5: CONDICIONAMOS AL MAYOR.
 int mayor = vMeses[0];

 //PASO 6 : RECORRO EL VECTOR DE MESES Y COMPARO.
 for(int i=1; i<meses; i++){

    if(vMeses[i] > mayor){
        mayor = vMeses[i];

    }
 }

 //PASO 7: MUESTRO.
 cout << "El mes con mayor ingresos es " << mayor+1 << endl;
 }


/*Desarrollar todas las clases que se consideren necesarias para
la resolución del ejercicio. No es obligatorio codificar de manera completa los métodos;
se considera suficiente que se coloquen los prototipos dentro de las clases.*/

/*2) Agregar una sobrecarga para algún operador de alguna de las clases del ejercicio 1, que reciba como parámetro un objeto de una clase distinta.
     void operator=(Tecnico &obj){
            DNI = obj.getDNI();
        }


  SI ES CON CHARS ES ASI :
  bool operator=(Tecnico &obj){
        if(strcpy(nombre,reg.getNombre()))return true;
        return false;
    }

   */




  /* 3) ¿Es posible que una clase tenga varios constructores?. Justifique la respuesta
  Una clase puede tener más de un constructor,  debido a que en los parámetros
  del constructor se puede mandar varios parámetro, o ninguno, o uno solo.
  Dependiendo del caso en el que se quiera usar. */
