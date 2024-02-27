#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
#include "clases.h"


void puntoA();
void puntoB();
void puntoC();

int main() {
	puntoA();///ver como evitar duplicaci�n registros
	puntoB();
	puntoC();
	return 0;
}


//CONSIGNA------->
/* a) Generar un archivo con el código y el nombre de los vendedores inactivos (se
consideran inactivos los vendedores que no hicieron ventas este año).*/

bool buscarVentas(const char *cv, int anio){
	Venta reg;
	int pos=0;
	while(reg.leerRegistro(pos++)){
		if(reg.getFechaVenta().getAnio()==anio)
			if(strcmp(reg.getCodigoVendedor(),cv)==0)
				return true;
 	}
	return false;
}

void puntoA(){
	Inactivo aux;
	Vendedor reg;
	int pos=0;
	/**while(reg.leerDeDisco(pos++)){
		if(buscarVentas(reg.getCodigoVendedor(),2020)==false){
			aux.setCodigoVendedor(reg.getCodigoVendedor());
			aux.setNombreVendedor(reg.getNombreVendedor());
			aux.grabarEnDisco();
		}
	}*/
	FILE *p;
	p=fopen("ventas.dat", "rb");
	if(p==NULL)exit(1);
	while(fread(reg, sizeof reg,1,p)==1){
     	if(buscarVentas(reg.getCodigoVendedor(),2020)==false){
			aux.setCodigoVendedor(reg.getCodigoVendedor());
			aux.setNombreVendedor(reg.getNombreVendedor());
			aux.escribirRegistro();
     }

   }
	fclose(p);
}

void mostrarVector(int v[], int tam){
    int i;
    for(i=0;i<tam;i++){
        cout<<v[i]<<"\t";
    }
}




//CONSIGNA------->
/// b) Informar la cantidad de usuarios registrados por cada mes del año 2015.
void puntoB(){
	Usuario reg;
	int pos=0;
	int v2015[12]={0};
	while(reg.leerDeDisco(pos++)){
		if(reg.getFechaRegistro().getAnio()==2015)
			v2015[reg.getFechaRegistro().getMes()-1]++;

        /**if(reg.getAnio()==2015) si se decide usar 3 propiedades para la fecha
			v2015[reg.getMes()-1]++;*/
	}
	mostrarVector(v2015);
}


///           CONSIGNA--->
/*c) La cantidad de ventas realizadas por los vendedores de las provincias del Litoral
(números de provincia 8, 9, y 10), el primer semestre de este año.*/
int buscarProvincia(const char *cv){
    Vendedor reg;
    int pos = 0;

    while (reg.leerDeDisco(pos++)) {
        if (strcmp(reg.getCodigoVendedor(), cv) == 0) {
            return reg.getNumeroProvincia();
        }
    }

    // Retornar -1 en caso de que no se encuentre el vendedor (código de provincia nunca será -1)
    return -1;

}

void puntoC(){
	Venta reg;
	int pos=0, cant=0, prov;


 	while(reg.leerDeDisco(pos++)){
		if(reg.getFechaVenta().getAnio()==2020 &&
           reg.getFechaVenta().getMes()<7 ){
                prov=buscarProvincia(reg.getCodigoVendedor());
                if(prov>=7 &&prov<=9)
                    cant++;
           }
	}
	cout<<"LA CANTIDAD DE VENTAS DE LOS VENDEDORES DE LITORAL FUE: "<<cant<<endl;
}
