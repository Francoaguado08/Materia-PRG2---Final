
# include<iostream>
# include<cstdlib>
using namespace std;


class Cola{
private:
  int *p;
  int tam;
  int pcio, fin;
public:
  Cola(int t=2){
    tam=t;
    p=new int[tam];
    if(p==NULL)exit(1);
    pcio=fin=0;
  }
  ~Cola(){
    delete p;
  }
  bool Agregar(int in){
       if(pcio==tam)return false;
       p[pcio]=in;
       pcio++;
       return true;
  }

  bool Sacar(int &out){
       if(pcio==fin)return false;
       out=p[fin];
       fin++;
       return true;
  }
};

class Pila{
private:
  int *p;
  int tam;
  int tope;
public:
  Pila(int t=2){
    tam=t;
    p=new int[tam];
    if(p==NULL)exit(1);
    tope=0;
  }
  ~Pila(){
    delete p;
  }
  bool Agregar(int in){
       if(tope==tam)return false;
       p[tope]=in;
       tope++;
       return true;
  }

  bool Sacar(int &out){
       if(tope==0)return false;
       tope--;
       out=p[tope];
       return true;
  }
};


int main(){
    Cola a(5);

    Cola b(5);

    int x, val;

    x=1;

    while(a.Agregar(x))x++;

    while(a.Sacar(val)){

        b.Agregar(val*2);

    }

    while(b.Sacar(x))cout<<x-2;



	cout<<endl;

	system("pause");
    return 0;
}
