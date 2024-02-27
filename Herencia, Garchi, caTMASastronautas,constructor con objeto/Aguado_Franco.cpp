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


class Astronautas{
private:
    int DNI;
    char nombre[50];
    char apellido[50];
    int pais;
    int categoria;
public:
    /// CONSTRUCTOR:
    Astronautas(int _DNI=0, const char *_nombre="-", const char *_apellido="-", int _pais=0,int _categoria=0){
     DNI=_DNI;
     strcpy(nombre,_nombre);
     strcpy(apellido,_apellido);
     pais=_pais;
     categoria = _categoria;
    }

    /// SETTERS
    void setDNI(int d){DNI = d;}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setApellido(const char *a) {strcpy(apellido,a);}
    bool setPais(int _pais){
      if(_pais>=1 && _pais <=50)return true;
      else return false;
      }
    bool setCategoria(int _categoria){
     if(_categoria>=1 && _categoria<=15)return true;
     else return false;

    }


    /// GETTERS.
    int getDNI(){return DNI;}
    const char *getNombre(){return nombre;}
    const char *getApellido(){return apellido;}
    int getPais(){return pais;}
    int getCategoria(){return categoria;}

    void Mostrar(){
    cout << "DNI:";
    cin >> DNI;
    cout << "NOMBRE:";
    cargarCadena(nombre,50);
    cout << endl;
    cout << "APELLIDO:";
    cargarCadena(apellido,50);
    cout << endl;
    cout << "PAIS:";
    cin >> pais;
    cout << "CATEGORIA:";
    cin >> categoria;
    }






};

/// Clase Con objeto Fecha. Contiene Constructor que recibe como parametro un obj de una clase distina e inicializa
/// las prop que son comunes entre ambos objetos.
/// TIENEN EN COMUN EL DNI EL ARCHI DE ASTRO CON EL DE MISIONES, POR LO TANTO RECIBE ASTRONAUTA COMO PARAMETRO.

class Misiones{
 private:
 int numeroDeMision;
 int DNIastronauta;
 Fecha fechaDeInicio;
 int cargo;
 bool estado;

 public:
 /// CONSTRUCTOR:
 Misiones(int _numeroDeMision=0,int _DNIastronauta=0, Fecha _fechaDeInicio=Fecha(), int _cargo = 0)
 {
 numeroDeMision = _numeroDeMision;
 DNIastronauta  = _DNIastronauta;
 fechaDeInicio  = _fechaDeInicio;
 cargo = _cargo;
 estado = true;
 }



  /*
   PUNTO 2 :AGREGAR UN CONSTRUCTOR PARA ALGUNA DE LAS CLASES DEL EJERCICIO 1, QUE RECIBA COMO PARAMETRO
    UN OBJETO DE UNA CLASE DISTINTA, Y QUE INICIALICE LAS PROPIEDADES QUE SON COMUNES ENTRE AMBOS OBJETOS.
    NUEVO CONSTRUCTOR QUE RECIBE UN OBJETO DE OTRA CLASE (Astronautas en este caso)



   Este constructor adicional de Misiones recibe un objeto Astronautas como parámetro y utiliza su función
   getDNI() para inicializar la propiedad DNIastronauta.


    */


  Misiones(Astronautas &astro, int _numeroDeMision=0, int _cargo = 0 ){
  numeroDeMision = _numeroDeMision;
  DNIastronauta = astro.getDNI();
  cargo = _cargo;
  estado = true;
  }









 /// SETTERS.
 void setnumeroDeMision(int _numeroDeMision){ numeroDeMision = _numeroDeMision;}
 void setDNIastronauta(int _DNIastronauta){DNIastronauta = _DNIastronauta;}
 // SET DE OBJETO.
 void setFechaDeInicio(Fecha f){fechaDeInicio=f;}
 bool setCargo(int _cargo){
  if(_cargo>=1 && _cargo <=10)return true;
  else return false;
 }
 bool setEstado(bool _estado){estado = _estado;}


    /// GETTERS.
    int getNumeroDeMision(){return numeroDeMision;}
    int getDNI(){return DNIastronauta;}
    //GET DE OBJETO
    Fecha getFechaDeInicio() {return fechaDeInicio;}
    int getCargo(){return cargo;}
    bool getEstado(){return estado;}


 void Mostrar(){
 cout << numeroDeMision << endl;
 cout << DNIastronauta << endl;
 fechaDeInicio.Mostrar();
 cout << cargo << endl;
 cout << endl;
 }

 };

class ArchivoAstronautas{
 private:
        char nombre[30];
  public:
        ArchivoAstronautas(const char *n){
            strcpy(nombre,n);
        }

        Astronautas leerRegistro(int pos){
            Astronautas reg;
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
            return tam/sizeof(Astronautas);
        }


        bool Escribir(Astronautas reg){
            FILE *p=fopen(nombre, "ab");
            if(p==NULL) return false;
            bool escribio = fwrite(&reg, sizeof reg, 1, p);
            fclose(p);
            return escribio;
        }

       bool listarArchivo(){
       Astronautas reg;
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


class ArchivoMisiones{
private:
    char nombre[40];

    public:
        ArchivoMisiones(const char* n){
            strcpy(nombre,n);
        }

         Misiones leerRegistro(int pos){
            Misiones reg;
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
            return tam/sizeof(Misiones);
        }


        bool Escribir(Misiones reg){
            FILE *p=fopen(nombre, "ab");
            if(p==NULL) return false;
            bool escribio = fwrite(&reg, sizeof reg, 1, p);
            fclose(p);
            return escribio;
        }

       bool listarArchivo(){
       Misiones reg;
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


class SolucionPunto{
private:
        int DNI;
        char nombre[50];
        char apellido[50];
        int cantMisiones;
        bool estado ;



    public:

        /// CONSTRUCTOR CON VALORES DE OMISION.
        SolucionPunto(int _DNI=0, const char *nom = "-",const char *ape = "-", int cantM = 0, bool _estado=true){
                     DNI = _DNI;
                     strcpy(nombre, nom);
                     strcpy(apellido, ape);
                     cantMisiones = cantM;
                     estado =true;
                     }


        //SETS
        void setDNI(int i){ DNI = i; }
        void setNombre(const char* n){ strcpy(nombre,n); }
        void setApellido(const char* a){ strcpy(nombre,a); }
        void setCantMisiones(int i){ cantMisiones = i; }
        void setEstado(bool s){estado = s; }

        //GETS
        int getDNI(){ return DNI; }
        const char* getNombre(){ return nombre; }
        const char* getApellido(){ return apellido; }
        int getCantMisiones(){ return cantMisiones;}
        bool getEstado(){return estado;}

        //OTROS
        void Mostrar(){
            if( estado ){
                cout << DNI<< endl;
                cout << nombre << endl;
                cout << apellido << endl;
                cout << cantMisiones << endl;

            }
        }

        /*void operator=(Tecnico &obj){
            DNI = obj.getDNI();
        }


        bool operator=(Tecnico &obj){
        if(strcpy(nombre,obj.getNombre()))return true;
        return false;*/



        ///  PUNTO 3:
        //  Agregar una sobrecarga para el operador == de la clase nueva del punto 1, que reciba
        //  como parámetro un objeto de la misma clase*/

        bool operator==(SolucionPunto obj){
        if(DNI == obj.getDNI())return true;
        return false;}


    };

/// ClASE PARA GENERAR LAS FUNCIONES DEL NUEVO ARCHIVO: CONTAR,ESCRIBIR,LISTAR,LEER.

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



/// ARCHIVO GENERADO CON SUS CONDICIONES.
void solucionPunto1(){

    ///  1)
    ArchivoAstronautas archiAstro("Astronautas.dat");
    int cantRegAstro = archiAstro.contarRegistros();
    Astronautas regAstro;
    ///  2)
    ArchivoMisiones archiMisio("Misiones.dat");
    int cantRegMisio = archiMisio.contarRegistros();
    Misiones regMisio;
    ///  3)
    ArchivoSolucionPunto archi("Soluciones.dat");
    SolucionPunto obj;
    archi.vaciar();




    /// Inicializo el contador para contar Las Misiones.
    int contador=0;

    for(int i=0; i<cantRegAstro;i++){
        regAstro=archiAstro.leerRegistro(i);

        for(int j=0; j<cantRegMisio;j++){
            regMisio=archiMisio.leerRegistro(j);

            if( (regAstro.getDNI() == regMisio.getDNI() ) && (regAstro.getPais()>=1&&regAstro.getPais()<=10)  )
                {
                 contador++; // CANT DE MISIONES.
                }


        }

         //cuando salgo de la iteracion chica, tengo los valores sin haberlo perdido antes de que itere.
        // por lo tanto guarda los valores para cada tipo de Astronauta.
        obj.setDNI(regAstro.getDNI());

        obj.setNombre(regAstro.getNombre());
        obj.setApellido(regAstro.getApellido());
        obj.setCantMisiones(contador);


        archi.Escribir(obj);


    }

    archi.listarArchivo();

 }


/// B ) CATEGORIA CON MAS ASTRONAUTAS
void puntoB(){
ArchivoAstronautas archiAstronautas("Astronautas.dat");
Astronautas objAstronauta;
int cantAstronautas = archiAstronautas.contarRegistros();

const int categorias = 15;
int vCategorias[categorias]={0};

for(int i=0;i<cantAstronautas;i++){

 objAstronauta=archiAstronautas.leerRegistro(i);

 vCategorias[objAstronauta.getCategoria()-1] ++ ;

 }

int mayor= vCategorias[0];

for(int i=0; i<categorias;i++){

    if(vCategorias[i] > mayor){
        mayor = vCategorias[i];
    }
}

cout << "CATEGORIA CON MAS ASTRONAUTAS:" << mayor+1 << endl;
 }







// PUNTO 3: DEFINIR HERENCIA Y SI SE APLICA EN ALGUNAS DE LAS CLASES DEL EJERCICIO (1).

/*
HERENCIA DEFINIENDOLO CON MIS PROPIAS PALABRAS, ES CUANDO UN OBJETO ADQUIERE LAS PROPIEDADES Y COMPORTAMIENTO
 DE OTRO OBJETO, MEDIANTE ESTE MECANISMO.
 Hay un caso que podría considerarse "herencia por composición".
La clase Misiones tiene un constructor que recibe un objeto de la clase Astronautas
como parámetro y utiliza propiedades de ese objeto para inicializar sus propias propiedades.





*/







int main()
{


 solucionPunto1();

 puntoB();








    return 0;
}
