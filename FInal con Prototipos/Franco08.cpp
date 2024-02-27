##include<iostream>
#include <cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>
using namespace std;

/// METODO CARGAR CADENA, LA UTILIZO POR SI TENGO QUE CARGAR UNA CADENA DENTRO DE LA CLASE
void cargarCadena(char *palabra, int tamano){
    int i=0;
    fflush(stdin);
    for(i=0;i<tamano;i++)
    {
        palabra[i]=cin.get();
        if(palabra[i]=='\n')
        {
            break;
        }
    }

        palabra[i] = '\0'; // Marcar el final de la cadena correctamente
    fflush(stdin);

 }

/// CLASE FECHA SIMPLE, CON EL METODO CARGAR Y MOSTRAR Y CONSTRUCTOR.
class Fecha{
    private:
        int dia, mes, anio;
    public:
        Fecha(int d=0, int m=0, int a=0){
            dia=d;
            mes=m;
            anio=a;
        }

        ///sets
        void setDia(int x){if(x>0 && x<32) dia=x;}
        void setMes(int x){if(x>0 && x<13)mes=x;}
        void setAnio(int x){anio=x;}
        ///gets
        int getDia(){return dia;}
        int getMes(){return mes;}
        int getAnio(){return anio;}

    void Cargar(){
    cout<<"DIA: ";
    cin>>dia;
    cout<<"MES: ";
    cin>>mes;
    cout<<"ANIO: ";
    cin>>anio;
    }

    void Mostrar(){
    /*cout<<"DIA: "<<dia<<endl;
    cout<<"MES: "<<mes<<endl;
    cout<<"ANIO: "<<anio<<endl<<endl;*/
    cout<<dia<<"/"<<mes<<"/"<<anio<<endl;
    }

    };









int main()
{












    return 0;
}
