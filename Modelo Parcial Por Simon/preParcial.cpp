#include <iostream>
#include <cstring>
using namespace std;
#include "parcialPre2.h"


class Punto1{
private:
    char codCliente[5];
    char nombre[30];
    Fecha fechaTour;
public:
    void setCodCliente(const char *c){strcpy(codCliente,c);}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setFechaTour(Fecha f){fechaTour=f;}

    void Mostrar(){
        cout<<codCliente<<endl;
        cout<<nombre<<endl;
        fechaTour.Mostrar();
    }
    /*Hacer una sobrecarga de operador para clase nueva del punto 1
    que sea util para la resolucion de alguno de los puntos.
    */
    bool operator=(Cliente reg){
        if(strcpy(codCliente,reg.getCodigoCliente()))return true;
        return false;
    }
};

class ArchivoPunto1{
private:
    char nombre[30];
public:
    ArchivoPunto1(char *n){
        strcpy(nombre,n);
    }
    bool grabarRegistro(Punto1 reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
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
        reg.setNombre("-1");
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return reg;
        fseek(p, sizeof reg*pos,0);
        fread(&reg, sizeof reg,1, p);
        fclose(p);
        return reg;
    }
};


/*Generar un archivo con los clientes que hayan realizado una compra por un importe
 inferior a 15000. Cada registro debe tener el
-código de cliente,
-nombre del cliente
-fecha del tour.
 En caso de que haya más de una compra de esas características
 se debe registrar la fecha de la primera. */

void solucionEj1(){
    ArchivoClientes archiClientes("Clientes.dat");
    int contArchiCl=archiClientes.contarRegistros();
    ArchivoVentas archiVentas("Ventas.dat");
    int contArchiVe=archiVentas.contarRegistros();
    Cliente cli;
    Venta ven;

    Punto1 p1;
    ArchivoPunto1 archiP1("solucionP1.dat");

    for(int i=0;i<contArchiCl;i++){
        cli=archiClientes.leerRegistro(i);

        bool esPrimero=false;
        for(int j=0;j<contArchiVe;j++){
            ven=archiVentas.leerRegistro(j);

            if(strcmp(cli.getCodigoCliente(),ven.getNumeroDeCliente())==0 && ven.getImporte()<15000 && esPrimero==false){
                //p1.setCodCliente(cli.getCodigoCliente());
                p1=cli;
                p1.setFechaTour(ven.getFechaVenta());
                p1.setNombre(cli.getNombre());
                archiP1.grabarRegistro(p1);
                /// aca me aseguro que si entra una vez, ya no entra más.
                esPrimero=true;
            }

        }
    }
}

/*
Hacer una funcion que CREE un vector dinamico
para CARGAR los registros del archivo generado en el punto 1.
MOSTRAR los registros del vector.
*/

void solucionEj2(){
    // tengo que contar los registros para hacer dinamico el vector.
    ArchivoPunto1 archiSol2("solucionesP1.dat");
    int tam=archiSol2.contarRegistros();
    // si fuera -1 rompe todo asi que hacemos esta validacion.
    if(tam>0){
        /// CREO EL VECTOR DINAMICO
        Punto1 *vec=NULL;
        vec=new Punto1[tam];
        if(vec==NULL)exit(1);

        /// CARGO LOS REGISTRO DEL ARCHIVO GENERADO EN PUNTO 1
        for(int i=0;i<tam;i++){
            vec[i]=archiSol2.leerRegistro(i);
        }

        /// MUESTRO
        for(int i=0;i<tam;i++){
            vec[i].Mostrar();
        }
    }
    else{
        cout<<"El archivo NO se pudo leer"<<endl;
    }
}



int main(){
    solucionEj1();
    solucionEj2();

return 0;
}
