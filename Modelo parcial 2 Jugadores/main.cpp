#include <iostream>
#include <cstring>

using namespace std;

#include "parcialm2.h"

class EquiposMas10{
    private:
        int idEquipo;
        char nombre[30];
        int categoriaDeporte;
        bool estado;
    public:
        void setIdEquipo(int i){idEquipo=i;}
        void setNombre(const char *n){strcpy(nombre,n);}
        void setCategoriaDeporte(int c){categoriaDeporte=c;}
        void setEstado(bool e){estado=e;}
};

class ArchivoEquipoMas10{
private:
    char nombre[30];
public:
    ArchivoEquipoMas10(const char *n){
        strcpy(nombre, n);
    }
    EquipoMas10 leerRegistro(int pos){
        EquipoMas10 reg;
        reg.setEstado(false);
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return reg;
        fseek(p, sizeof reg*pos,0);
        fread(&reg, sizeof reg,1, p);
        fclose(p);
        return reg;
    }
    int contarRegistros(){
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return -1;
        fseek(p, 0,2);
        int tam=ftell(p);
        fclose(p);
        return tam/sizeof(EquipoMas10);
    }
    bool grabarRegistro(EquipoMas10 reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        int escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
    }
};

void puntoA();

int main()
{
    puntoA();
    return 0;
}
/***
Generar un archivo con los equipos que tengan al
menos 10 jugadores inscriptos.
Cada registro debe tener el ID de equipo,
el nombre del equipo, y la categoría del deporte al que
pertenece el equipo.

Voy a necesitar leer los archivos de jugadores, equipos y
deportes

*/

int buscarCategoria(int idDeporte){
    ArchivoDeportes arcD("deportes.dat");
    Deporte objD;
    int cant=arcD.contarRegistros();
    for(int i=0; i<cant; i++){
        objD=arcD.leerRegistro(i);
        if(objD.getIdDeporte()==idDeporte){
            return objD.getIdCtegoria();
        }
    }
    return -1;
}

void puntoA(){
    ArchivoEquipos arcE("equipos.dat");
    Equipo objE;
    ArchivoJugadores arcJ("jugadores.dat");
    Jugador objJ;
    ArchivoEquipoMas10 arcN("equipoMas10.dat");
    EquiposMas10 objN;
    int cont, idDeporte;
    int cantEq=arcE.contarRegistros();
    int cantJug=arcJ.contarRegistros();
    for(int i=0; i<cantEq; i++){
        objE=arcE.leerRegistro(i);
        cont=0;
        if(objE.getEstado()){
            for(int j=0; j<cantJug; j++){
                objJ=arcJ.leerRegistro(j);
                if(objJ.getEstado()){
                    if(objE.getIdEquipo()==objJ.getIdEquipo()){
                        cont++;
                        idDeporte=objJ.getIdDeporte();
                    }
                }
            }
            if(cont>=10){
                objN.setIdEquipo(objE.getIdEquipo());
                objN.setNombre(objE.getNombre());
                objN.setCategoriaDeporte(buscarCategoria(idDeporte));
                objN.setEstado(true);
                arcN.grabarRegistro(objN);
            }
        }
    }
}
