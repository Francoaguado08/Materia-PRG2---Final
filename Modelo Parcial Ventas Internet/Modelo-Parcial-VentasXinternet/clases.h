#ifndef CLASES_H_INCLUDED
#define CLASES_H_INCLUDED

class Fecha{
private:
	int dia, mes, anio;
public:
	int getDia(){return dia;}
	int getMes(){return mes;}
	int getAnio(){return anio;}
};

class Vendedor{
	private:
		char codigoVendedor[5];
		char nombre[30];
		int provincia,calificacion;
	public:
		const char *getCodigoVendedor(){return codigoVendedor;}
		const char *getNombreVendedor(){return nombre;}
		int getProvincia(){return provincia;}
		bool leerRegistro(int);
};

voi Vendedor::leerRegistro(int pos){
	FILE *p;
	p=fopen("vendedores.dat", "rb");
	if(p==NULL)exit(1);
	fseek(p, sizeof(Vendedor)*pos,0);
	bool leyo=fread(this, sizeof *this,1,p);
	fclose(p);
	return leyo;
}


class Usuario{
private:
	char codigoUsuario[5];
	char nombre[30];
	int DNI;
	Fecha registro;
public:
	bool leerRegistro(int);
	Fecha getFechaRegistro(){return registro;}
};

bool Usuario::leerRegistro(int pos){
	FILE *p;
	p=fopen("usuarios.dat", "rb");
	if(p==NULL)exit(1);
	fseek(p, sizeof *this*pos,0);
	bool leyo=fread(this, sizeof *this,1,p);
	fclose(p);
	return leyo;
}

class Venta{
private:
	int numeroCompra;
	char codigoVendedor[5];
	char codigoUsuario[5];
	float importe;
	Fecha fechaVenta;
	int tipoPago;
public:
	const char *getCodigoVendedor(){return codigoVendedor;}
	Fecha getFechaVenta(){return fechaVenta;}
	bool leerRegistro(int);
};

bool Venta::leerRegistro(int pos){
	FILE *p;
	p=fopen("ventas.dat", "rb");
	if(p==NULL)exit(1);
	fseek(p, sizeof *this*pos,0);
	bool leyo=fread(this, sizeof *this,1,p);
	fclose(p);
	return leyo;
}

class Inactivo{
private:
	char codigoVendedor[5];
	char nombre[30];
public:
	void setCodigoVendedor(const char *cv){strcpy(codigoVendedor,cv);}
	void setNombreVendedor(const char *n){strcpy(nombre,n);}
	bool escribirRegistro();
};

bool Inactivo::escribirRegistro(){
	FILE *p;
	p=fopen("inactivos.dat", "ab");
	if(p==NULL)exit(1);
	bool grabo=fread(this, sizeof *this,1,p);
	fclose(p);
	return grabo;
}

#endif // CLASES_H_INCLUDED
