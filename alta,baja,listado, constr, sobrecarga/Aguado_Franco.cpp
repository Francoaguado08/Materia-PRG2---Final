#include<iostream>
#include <cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>

using namespace std;

///   EXAMEN FINAL ------> 29/11

///   PUNTO 1: 1) Desarrollar un programa con un menú para dar el alta, baja lógica y listado del
///   siguiente archivo. (6 PUNTOS).

///   PUNTO 2: 2) Agregar un constructor para la clase que da formato a los registros del archivo con valores por omisión que deben usarse en caso que el constructor sea llamado sin valores.
///   Si recibe valores debe usarlos ignorando los que tiene por omisión (2 puntos)

///   PUNTO 3: Agregar una sobrecarga para alguna de las clases del programa (2 puntos.



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

///  TENGO LA CLASE CON SUS PROP, SU METODO CARGAR Y MOSTRAR. UTILIZO EL OBJETO FECHA, MUESTRO COMO SON LOS SET Y GET.
///  contiene un constructor onstructor para la clase que da formato a los registros del archivo con valores por omisión
///  que deben usarse en caso que
///  el constructor sea llamado sin valores. Si recibe valores debe usarlos ignorando los que tiene por omisión

class Asignacion {
private:
    int numeroAsignacion;
    int legajoProgramador;
    int codigoProyecto;
    int localidadProyecto; //1a30
    char comentario[100];
    Fecha fechaAsignacion;
    bool estado;

public:

    /// CONSTRUCTOR X OMISION, EN CASO DE QUE EL CONSTRUCTOR SEA LLAMADO SIN VALORES.
    Asignacion(int _numeroAsignacion = -1, int _legajoProgramador = -1, int _codigoProyecto = -1,
               int _localidadProyecto=-1, const char *_comentario=" ", Fecha _fechaAsignacion=Fecha(),
               bool _estado = true){
               numeroAsignacion = _numeroAsignacion;
               legajoProgramador = _legajoProgramador;
               codigoProyecto = _codigoProyecto;
               localidadProyecto = _localidadProyecto;
               strcpy(comentario, _comentario);
               fechaAsignacion = _fechaAsignacion;
               estado = _estado;
               }







    /// GETTERS
    int getNumeroAsigancion() const { return numeroAsignacion; }
    int getLegajoProgramador() const { return legajoProgramador; }
    int getCodigoProyecto() const { return codigoProyecto; }
    int getLocalidadProyecto() const { return localidadProyecto; }
    const char *getComentario() const { return comentario; }
    Fecha getFechaAsignacion(){ return fechaAsignacion; }
    bool getEstado() const { return estado; }

    ///SETTERS
    void setNumeroAsignacion(int numero) { numeroAsignacion = numero; }
    void setLegajoProgramador(int legajo) { legajoProgramador = legajo; }
    void setCodigoProyecto(int codigo) { codigoProyecto = codigo; }

    bool setLocalidadProyecto(int localidad){
        if((localidad>=1) && (localidad<=30)) return true;
        else return false;
         }

    void setComentario(const char *_comentario) { strcpy(comentario, _comentario); }
    /// OBJETO SET.
    void setFechaAsignacion(Fecha _fechaAsignacion);
    void setEstado(bool estado) { this->estado = estado; }

    /// METODOS -->
    void Cargar() {
        cout << "INGRESE NRO DE ASIGNACION:" ;
        cin >> numeroAsignacion;
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

    void Mostrar(){
        cout << "NRO ASIGANCION: " << numeroAsignacion << endl;
        cout << "Legajo del programador: " << legajoProgramador << endl;
        cout << "Codigo de proyecto: " << codigoProyecto << endl;
        cout << "Localidad del proyecto: " << localidadProyecto << endl;
        cout << "Comentario: " << comentario << endl;
        cout << "Fecha de la asignacion: ";
        fechaAsignacion.Mostrar();
    }


    /// SOBRECARGA DE OPERADORES :
    void operator=(const Asignacion &obj){
            numeroAsignacion = obj.getNumeroAsigancion();
        }







};

/// MANIPULACION DEL ARCHIVO: METODO LISTAR, AGREGAR, BUSCAR, LEER, MODIFICAR, CONTAR REGISTROS.
class ArchivoAsignacion {
private:
    char nombre[30];

public:
    ArchivoAsignacion(const char *nombreArchivo) {
        strcpy(nombre, nombreArchivo);
    }

    const char *getNombre() {
        return nombre;
    }


    //bool copiaSeguridad(const char *nombreCopia);

    /// LISTADO:
    /// esta funcion desp la utilizo para listar.
    bool listarRegistros(){
    Asignacion reg;
    FILE *p = fopen(nombre, "rb");

    if (p == NULL) {
        cout << "ERROR DE ARCHIVO" << endl;
        return false;
    }
    while (fread(&reg, sizeof reg, 1, p) == 1) {
        reg.Mostrar();
        cout << endl;
    }
    fclose(p);
    return true;
    }


    /// AGREGAR REGISTRO.
    // esta funcion desp iria dentro de la alta logica.
    bool agregarRegistro(Asignacion reg) {
    FILE *p = fopen(nombre, "ab");

    if (p == NULL) {
        cout << "ERROR DE ARCHIVO" << endl;
        return false;
    }

    bool escribio = fwrite(&reg, sizeof reg, 1, p);
    fclose(p);
    return escribio;
    }

    ///BUSCAR REGISTRO.
    int buscarRegistro(int numero) {
    Asignacion reg;
    FILE *p = fopen(nombre, "rb");

    if (p == NULL) {
        cout << "ERROR DE ARCHIVO" << endl;
        return -2;
    }
    int cont = 0;
    while (fread(&reg, sizeof reg, 1, p) == 1) {
        if (reg.getNumeroAsigancion() == numero) {
            fclose(p);
            return cont;
        }
        cont++;
    }
    fclose(p);
    return -1;
   }

    /// Leer registro.
    Asignacion leerRegistro(int pos) {
    Asignacion reg;
    reg.setEstado(false);
    FILE *p = fopen(nombre, "rb");

    if (p == NULL) {
        cout << "ERROR DE ARCHIVO" << endl;
        return reg;
    }

    fseek(p, sizeof(Asignacion) * pos, 0);
    fread(&reg, sizeof reg, 1, p);
    fclose(p);

    reg.setEstado(false);

    return reg;
    }


    /// MODIFICAR UN REGISTRO.
    bool modificarRegistro(int pos, Asignacion reg) {
    FILE *p = fopen(nombre, "rb+");

    if (p == NULL) {
        cout << "ERROR DE ARCHIVO" << endl;
        return false;
    }

    fseek(p, sizeof(Asignacion) * pos, 0);
    bool escribio = fwrite(&reg, sizeof reg, 1, p);
    fclose(p);

    return escribio;
    }

    int contarRegistros(){
    FILE *p;
    p = fopen(nombre, "rb");
    if (p == NULL) return -1;
    fseek(p, 0, 2);
    int tam = ftell(p);
    fclose(p);

    return tam / sizeof(Asignacion);
    }

    /// ME FALTA LA FUNCION ELIMINAR REGISTRO.



};


/// FUNCION QUE UTILIZA AGREGAR REGISTRO DE ARCHIVO-ASIGNACIONESY EL METODO CARGAR DE LA CLASE ASIG.
void altaLogica(){
    Asignacion reg;
    ArchivoAsignacion archi("Asiganciones.dat");
    reg.Cargar();
    bool agregar=archi.agregarRegistro(reg);
    if(agregar==true){
        cout<<"REGISTRO AGREGADO.";
    }
    else{
        cout<<"NO SE PUDO AGREGAR EL REGISTRO."<<endl;
    }
}

/// FUNCION PARA LISTAR EL ARCHIVO. UTILIZA LISTAR REGISTROS DE ARCHIVO-ASIGANCIONES.
void listadoDelArchivo() {
    ArchivoAsignacion archi("Asignaciones.dat");
    archi.listarRegistros();
}

/// FUNCION PARA BORRAR EL REGISTRO(LOGICAMENTE). UTILIZA BUSCAR REGISTRO, LEER Y MODIFICAR DE
/// LA CLASE ARCHIVO ASIGNACIONES.
bool bajaLogica(){
    ArchivoAsignacion archi("Asignaciones.dat");
    int numero;
    cout<<"INGRESE EL NUMERO DE ASIGNACION A BORRAR: ";
    cin >>numero;

    int pos;
    pos=archi.buscarRegistro(numero); //buscarRegistro(int ) devuelve la pos del registro en el archivo.

    if(pos==-1){
        cout<<"NO EXISTE EL REGISTRO CON ESE CODIGO"<<endl;
        return false;
    }
    else{
        if(pos==-2){
            cout<<"NO SE PUDO ABRIR EL ARCHIVO"<<endl;
            return false;
        }
    }
    Asignacion reg=archi.leerRegistro(pos);
        reg.Mostrar();
        reg.setEstado(false);
        bool quePaso=archi.modificarRegistro(pos,reg);
        if(quePaso==true){
            cout<<"REGISTRO BORRADO"<<endl;
        }
        else{
            cout<<"NO SE PUDO BORRAR EL REGISTRO"<<endl;
        }
    cout<<endl;
    return true;
}


int main(){


    int opc;
    while(true){
        system("cls");
        cout<<"-------------------------"<<endl;
        cout<<"--------- MENU --------- "<<endl;
        cout<<"-------------------------"<<endl;
        cout<<"1) ALTA LOGICA"<<endl;
        cout<<"2) BAJA LOGICA" <<endl;
        cout<<"3) LISTADO DEL ARCHIVO"<<endl;
        cout<<"0) FIN DEL PROGRAMA "<<endl;
        cout<<"OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1:altaLogica();
                   break;
            case 2:bajaLogica();
                   break;
            case 3:listadoDelArchivo();
                   break;
            case 0:return 0;
                   break;
            default:cout<<"OPCION INCORRECTA"<<endl;
                   break;
        }
        cout<<endl;
        system("pause");
    }

    return 0;
}




    /*
    ejemplo de la sobrecarga...



    Asignacion asignacion1;
    asignacion1.setNumero(1);
    // ... (asigna otras propiedades)

    Asignacion asignacion2;

    // Usando la sobrecarga del operador de asignación
    asignacion2 = asignacion1;

    // Verificar que los valores se hayan copiado correctamente
    cout << "Asignacion1: ";
    asignacion1.Mostrar();
    cout << "Asignacion2 (después de la asignación): ";
    asignacion2.Mostrar();

    */




