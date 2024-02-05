
#include <iostream>
#include <cmath>
using namespace std;

int main()


{
    float a,b,c,discriminante, x1, x2, x;
    
    cout<<"Ingrese los valores de la ecuacion cuadratica"<<endl;
    
    cin>>a>>b>>c;
    
    if(a==0){
        cout<<"La ecuación no es de segundo grado"<<endl;
    }
    else{
        
        discriminante= b*b- 4*a*c;
        if(discriminante<0) {
            
            cout<<"La solución es imaginaria";
     
        }    
        else if(discriminante>0) {
         
        x1= (-b+sqrt(discriminante))/(2*a);
        x2= (-b-sqrt(discriminante))/(2*a);
        
        cout<<"La primera solución es "<<x1<< " y la segunda solución es "<<x2<<endl;
        }
        else if(discriminante==0)
        {
            x= -b/2*a;
        cout<<"La solución única de la ecuación es " <<x<<endl;    
        }
        
    } 

    return 0;
}
