#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class Pila{
private:
    int *p;
    int tam;
    int tope;

public:
    Pila(int t=2){
        tam=t;
        p=new int[tam];
        if(p==NULL) exit(1);
        tope=0;
    }
    ~Pila(){
        delete p;
    }
    bool Agregar(int in){
        if(tope==tam) return false;
        p[tope]=in;
        tope++;
        return true;
    }

    bool Sacar(int &out){
        if(tope==0) return false;
        tope--;
        out=p[tope];
        return true;


    }

};



class Cola{
private:
    int *p;
    int tam;
    int ppio, fin;

public:
    Cola(int t=2){
        tam=t;
        p=new int[tam];
        if(p==NULL) exit(1);
        ppio=fin=0;
    }
    ~Cola(){
        delete p;
    }
    bool Agregar(int in){
        if(ppio==tam) return false;
        p[ppio]=in;
        ppio++;
        return true;
    }

    bool Sacar(int &out){
        if(ppio==fin) return false;
        out=p[fin];
        fin++;
        return true;
    }

};



int main()
{
    ///PUNTO 4 PARCIAL DEL LUNES
    Pila a(5);
    Pila b(5);
    Cola c(5);
    int x,val;
    x=1;
    while(a.Agregar(x))x++;
    while(a.Sacar(val)){
        b.Agregar(val);
    }
    while(b.Sacar(x))c.Agregar(x);
    while(c.Sacar(x))cout<<x;
    cout<<endl;
    system("pause");
    return 0;
}
