/*
1) El área de desarrollo de una empresa de software tiene, entre otros, los siguientes archivos en su sistema:

programadores.dat: DNI (int), nombre y apellido (char[50]), número de oficina (entero entre 1 y 30), categoría (1 a 5) y especialidad(1 a 10).

Asignaciones.dat: DNI del programador (int), fecha (día, mes y año), tipo de tarea (1 a 5), número de proyecto.

El archivo tiene las asignaciones de los investigadores a los proyectos desde el año 2018 a la fecha.

Se pide:

a) Generar un archivo nuevo con las asignaciones de los programadores de categoría 5. Cada registro del archivo debe tener el siguiente formato:

- DNI, el nombre y apellido del programador, y la cantidad de asignaciones. (3 puntos)


b)  Informar la especialidad con más programadores (3 puntos).

Desarrollar la clase necesaria para el nuevo archivo. Suponer que el resto de las clases necesarias para la resolución del ejercicio exiten.


2) Agregar una sobrecarga de un operador para alguna de las clases del ejercicio 1. La sobrecarga debe recibir como parámetro un objeto Fecha.


3) Suponiendo que existe una clase de nombre Animal, crear una clase de nombre Reptil utilizando el mecanismo de la herencia. Reptil tiene que tener como propiedades, además de las definidas en Animal, las siguientes:

Color (char[30]) y ambiente (‘t’: terrestre; ‘m’: marino).

Cómo métodos agregar los sets() y gets() de las propiedades de la línea anterior.
*/
#include <iostream>
#include <cstring>
using namespace std;

void cargarCadena(char *pal, int tam)
{
    int i;
    fflush(stdin);
    for(i=0; i<tam; i++)
    {
        pal[i]=cin.get();
        if(pal[i]=='\n') break;
    }
    pal[i]='\0';
    fflush(stdin);
}


class Punto1
{
private:

    int dni;
    char nombreyApellido[50];
    int asignaciones;
public:
    void setDni(int d)
    {
        dni=d;
    }
    void setNombreyApellido(const char *n)
    {
        strcpy(nombreyApellido,n);
    }
    void setAsignaciones(int a)
    {
        asignaciones=a;
    }

    int getDni()
    {
        return dni;
    }
    const char *getNombreyApellido()
    {
        return nombreyApellido;
    }
    int getAsignaciones()
    {
        return asignaciones;
    }
};

class ArchivoPunto1
{
private:
    char nombre[30];
public:
    ArchivoPunto1(const char *n)
    {
        strcpy(nombre, n);
    }
    Punto1 leerRegistro(int pos)
    {
        Punto1 reg;
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return reg;
        fseek(p, sizeof reg*pos,0);
        fread(&reg, sizeof reg,1, p);
        fclose(p);
        return reg;
    }
    int contarRegistros()
    {
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return -1;
        fseek(p, 0,2);
        int tam=ftell(p);
        fclose(p);
        return tam/sizeof(Punto1);
    }
    bool grabarRegistro(Punto1 reg)
    {
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
    }
};



void SolucionP1()
{

    ArchivoProgramadores ArchPro("programadores.dat");
    int cantRegPro = ArchPro.contarRegistros();
    Programadores RegPro;

    ArchivoAsignaciones ArchAsig("asignaciones.dat");
    int cantRegAsig = ArchAsig.contarRegistros();
    Asignaciones RegAsig;

    ArchivoPunto1 ArchP1("punto1.dat");
    Punto1 p1;


    for(int i=0; i<cantRegPro; i++)
    {
        int asignaciones=0;

        RegPro=ArchPro.leerRegistro(i);

        for(int j=0; j<cantRegAsig; j++)
        {

            RegAsig= ArchAsig.leerRegistro(j);

            if( RegPro.getDni() == RegAsig.getDni() && RegPro.getCategoria() == 5)
            {

                asignaciones++;

            }
        }
        p1.setDni(RegPro.getDni());
        p1.setNombreyApellido(RegPro.getNombreyApellido());
        p1.setAsignaciones(asignaciones);
        ArchP1.grabarRegistro(p1);

    }

}

void SolucionP1B()
{

    int especialidades[10]= {0};

    ArchivoProgramadores ArchPro("programadores.dat");
    int cantRegPro = ArchPro.contarRegistros();
    Programadores RegPro;

    for(int i=0; i<cantRegPro; i++)
    {

        RegPro=ArchPro.leerRegistro(i);

        especialidades[RegPro.getEspecialidad()-1]++;

    }
    int Mayor = especialidades[0];
    int EspMayor = 0;
    for(int j=1; j<10; j++)
    {

        if(especialidades[j]>Mayor)
        {

            mayor=especialidades[j];
            EspMayor=j;

        }


    }

    cout << "especialidad con más programadores: " << EspMayor+1 << endl;

}

void SolucionP2()
{
///clase asignaciones
    bool operator == (Fecha &reg)
    {
        if( reg.getDia()==dia && reg.getMes() == mes && reg.getAnio() == anio)
        {
            return true;
        }
        return false;
    }



}



void SolucionP3()
{

    class Reptil : public Animal
    {
    private:
        char color[30];
        char ambiente;
    public:


        void setColor(const char* c)
        {
            strcpy(color,c);
        }


        void setAmbiente(char a)
        {
            ambiente = a;
        }

        const char* getColor()
        {
            return color;
        }

        char getAmbiente()
        {
            return ambiente;
        }

    };

}

int main()
{
    SolucionP1();
    SolucionP1B();
    return 0;
}
