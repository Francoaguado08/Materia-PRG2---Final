#include<iostream>
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


class Asignaciones{
 private:
     int nroAsignacion;
     int legajoProgramador;
     int codigoProyecto;
     int localidadProyecto;
     char comentario[30];
     Fecha fechaAsignacion;
     bool estado;
 public:
    Asignaciones(int _nroAsignacion=0,int _legajoProgramador=0,int _codigoProyecto=0,int _localidadProyecto=0, const char *_comentario = " ",
    Fecha _fechaAsignacion = Fecha(), bool _estado = true){

    nroAsignacion = _nroAsignacion;
    legajoProgramador = _legajoProgramador;
    codigoProyecto = _codigoProyecto;
    localidadProyecto = _localidadProyecto;
    strcpy(comentario, _comentario);
    fechaAsignacion = _fechaAsignacion;
    estado = _estado;

    }



    void setNroAsignacion(int _nroAsignacion){nroAsignacion = _nroAsignacion;}
    void setLegajoProgramador(int _legajoProgramador){legajoProgramador = _legajoProgramador;}
    void setCodigoProyecto(int _codigoProyecto){codigoProyecto = _codigoProyecto;}
    void setLocalidadProyecto(int _localidadProyecto){localidadProyecto = _localidadProyecto;}
    void setComentario(const char *_comentario){strcpy(comentario,_comentario);}
    void setFechaAsignacion(Fecha _fechaAsignacion){fechaAsignacion = _fechaAsignacion;}
    bool setEstado(bool _estado){ estado = _estado;}


    int getNroAsigancion(){return nroAsignacion;}
    int getLegajoProgramador(){return legajoProgramador;}
    int getCodigoProyecto(){return codigoProyecto;}
    int getLocalidadProyecto(){return localidadProyecto;}
    const char *getComentario() { return comentario;}
    Fecha getFechaAsignaciion(){return fechaAsignacion;}
    bool getEstado(){return estado;}

    void Mostrar(){
     cout <<"NRO ASIGNACION:";
     cout << nroAsignacion << endl;
     cout <<"LEGAJO PROGRAMADOR:";
     cout << legajoProgramador << endl;
     cout <<"CODIGO PROYECTO:";
     cout << codigoProyecto << endl;
     cout <<"LOCALIDAD PROYECTO:";
     cout << localidadProyecto << endl;
     cout <<"COMENTARIO:";
     cout << comentario << endl;
     cout <<"FECHA DE ASIGNACION:";
     fechaAsignacion.Mostrar();
    }

void Cargar() {
        cout << "INGRESE NRO DE ASIGNACION:" ;
        cin >> nroAsignacion;
        cout << endl;

        cout << "INGRESE EL LEGAJO DEL PROGRAMADOR: ";
        cin >> legajoProgramador;
        cout << endl;

        cout << "Ingrese el codigo de proyecto: ";
        cin >> codigoProyecto;
        cout << endl;

        cout << "Ingrese la localidad del proyecto (1 a 30): ";
        cin >> localidadProyecto;
        cout << endl;

        cout << "Ingrese el comentario (hasta 100 caracteres): ";
        cargarCadena(comentario,100);
        cout << endl;

        cout << "Ingrese la fecha de la asignación: ";
        fechaAsignacion.Cargar();

        estado = true;
        cout << endl;
    }





  };


class ArchivoAsignaciones{
private:
    char nombre[30];
public:
    ArchivoAsignaciones( const char *nombreArchivo){
     strcpy(nombre, nombreArchivo);
    }

    bool listarRegistros(){
    Asignaciones reg;
    FILE *p=fopen(nombre, "rb");
    if(p==NULL){
        cout << "ERROR DE ARCHIVO." << endl;
    }
    while(fread(&reg, sizeof reg, 1, p)==1){
        reg.Mostrar();
    }
    fclose(p);
    return true;
    }


    bool agregarRegistro(Asignaciones reg){
     FILE *p=fopen(nombre, "ab");
     if(p==NULL){
        cout << "ERROR DE ARCHIVO."<<endl;
        return false;
     }

     bool escribio = fwrite(&reg,sizeof reg, 1,p);
     fclose(p);
     return escribio;
    }

    int contarRegistros(){
    FILE *p=fopen(nombre,"rb");
    if(p==NULL){return -1;}
    fseek(p,0,2);
    int tam = ftell(p);
    fclose(p);
    return tam / sizeof(Asignaciones);
    }

    Asignaciones leerRegistro(int pos){
    Asignaciones reg;
    reg.setEstado(false);
    FILE *p = fopen(nombre, "rb");

    if (p == NULL) {
        cout << "ERROR DE ARCHIVO" << endl;
        return reg;
    }

    fseek(p, sizeof(Asignaciones) * pos, 0);
    fread(&reg, sizeof reg, 1, p);
    fclose(p);

    reg.setEstado(false);

    return reg;
    }


     /// MODIFICAR UN REGISTRO.
    bool modificarRegistro(int pos, Asignaciones reg) {
    FILE *p = fopen(nombre, "rb+");

    if (p == NULL) {
        cout << "ERROR DE ARCHIVO" << endl;
        return false;
    }

    fseek(p, sizeof(Asignaciones) * pos, 0);
    bool escribio = fwrite(&reg, sizeof reg, 1, p);
    fclose(p);

    return escribio;
    }


///BUSCAR REGISTRO. LO UTILIZO EN LA BAJA LOGICA.
    int buscarRegistro(int numero) {
    Asignaciones reg;
    FILE *p = fopen(nombre, "rb");

    if (p == NULL) {
        cout << "ERROR DE ARCHIVO" << endl;
        return -2;
    }
    int cont = 0;
    while (fread(&reg, sizeof reg, 1, p) == 1) {
        if (reg.getNroAsigancion() == numero) {
            fclose(p);
            return cont;
        }
        cont++;
    }
    fclose(p);
    return -1;
   }










 };


void altaLogica(){
Asignaciones regAsig;
ArchivoAsignaciones archiAsig("Asignaciones.dat");
regAsig.Cargar();
bool agregar=archiAsig.agregarRegistro(regAsig);
if(agregar == true){
    cout << "Registro Agregado." << endl;
}
else{
    cout << "No se pudo agregar correctamente." << endl;
}

}


bool bajaLogica(){
 ArchivoAsignaciones archi("Asignaciones.dat");
 int nro;
 cout << "INGRESE EL NRO DE ASIGNACION A BORRAR:";
 cin >> nro;

 int pos;
 pos=archi.buscarRegistro(nro); //devuelve la pos del registro en el archivo.

 if(pos==-1){
    cout <<"No existe el registro con ese codigo." << endl;
    return false;
 }
 else{
    if(pos==-2){
        cout << "No se pudo abrir el archivo."<<endl;
        return false;
    }
 }

 Asignaciones reg=archi.leerRegistro(pos);
 reg.Mostrar();
 reg.setEstado(false);
 bool quePaso=archi.modificarRegistro(pos, reg);
 if(quePaso==true){
    cout << "Registro borrado."<<endl;
 }
 else{
    cout << "No se pudo borrar el registro." << endl;
    }

 cout << endl;
 return true;



 }



void listarArchivo(){
ArchivoAsignaciones archi("Asignaciones.dat");
archi.listarRegistros();
}



int main()
{

   int opc;

  while(true)
  {

        system("cls");

        cout<<"MENU PRINCIPAL"<<endl;
        cout<<"--------------"<<endl;
        cout<<"1) ALTA LOGICA"<<endl;
        cout<<"2) BAJA LOGICA"<<endl;
        cout<<"3) LISTADO DEL ARCHIVO"<<endl;

        cout<<"--------------"<<endl;
        cout << "0) SALIR  " << endl;

        cout<<"OPCION: ";
        cin >> opc;

        system("cls");

    switch(opc)
    {

      case 1: altaLogica();
      break;

      case 2: bajaLogica();
      break;

      case 3: listarArchivo();
      break;

      case 0: return 0;
      break;

      default: cout<<"OPCION INCORRECTA. INGRESAR OPCION NUEVAMENTE ";
      break;

    }
       cout << endl;
       system("pause");

  }

    return 0;

 }











