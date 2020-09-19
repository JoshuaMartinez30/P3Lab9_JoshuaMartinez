#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <vector>
using namespace std;

void read_and_write(){
    ifstream leer;
    string texto, texto2="";
    string nombrearchivo;

    leer.open("generator.txt",ios::in);
    if (leer.fail()){
        cout<<"no se pudo abrir el archivo";
        exit(1);
    }

    while (!leer.eof()){
        getline(leer,texto);
        texto2+=texto;
    }
    
    
    string nombre="", variable="", nombre_variable="";
    vector<string> variables;
    vector<string> nombre_variables;
    int auxiliar_name=0, cont1, cont3;
    for (int i = 0; i < texto2.size(); i++){
        if (texto2.at(i)==' '){
            continue;
        }
        
       if (auxiliar_name==0){
           if (texto2.at(i)==':'){
               cont3=1;
           }else if (texto2.at(i)=='A'){
               cont3=0;
               auxiliar_name++;
           }else if (cont3==1){
                nombre+=texto2.at(i);
           }
       }else if (texto2.at(i)==':'){
            cont1=1;
        }else if (texto2.at(i)=='|'){
            cont1=2;
        }else if (texto2.at(i)=='A'){
            cont1=3;
        }else if (texto2.at(i)==']'){
            cont1=3;
        }else if (cont1==1){
            variable+=texto2.at(i);
        }else if (cont1==2){
            nombre_variable+=texto2.at(i);
        }
        
        if (cont1==3){
            variables.push_back(variable);
            nombre_variables.push_back(nombre_variable);
            variable="";
            nombre_variable="";
            cont1=4;
        }

        if (texto2.at(i)==']'){
            variables.push_back(variable);
            nombre_variables.push_back(nombre_variable);
            string nombre_aux=nombre;
            nombre="";
            for (int i = 0; i < nombre_aux.size()-1; i++){
                nombre+=nombre_aux.at(i);
            }
            
            ofstream archivo;
            string nombre_archivo="", nombre_mayus;
            nombre_archivo+= nombre+".h";
            nombre_mayus = nombre;
            archivo.open("personaje.h",ios::out);
            for (int i = 0; i < nombre_mayus.length(); i++) {
                nombre_mayus[i] = toupper(nombre_mayus[i]);
            }

            archivo<<"#ifndef "<<nombre_mayus<<"_H"<<endl;
            archivo<<"#define "<<nombre_mayus<<"_H"<<endl;

            archivo<<"#include <string>"<<endl;
            archivo<<"using namespace std;"<<endl;
            archivo<<"class "<<nombre<<"{"<<endl;
            archivo<<"      private:"<<endl;
            int contador = 0;
            string todas_variables="";
            while(contador<variables.size()-1){
                archivo<<"            "<<variables[contador]<<" "<<nombre_variables[contador]<<";"<<endl;
                todas_variables+=variables[contador];
                if (contador<variables.size()-2){
                    todas_variables+=",";
                }
                contador++;
            }
            archivo<<"      public:"<<endl;
            archivo<<"            "<<nombre<<"();"<<endl;
            archivo<<"            "<<nombre<<"("<<todas_variables<<");"<<endl;
            contador=0;
            while(contador<variables.size()-1){
                archivo<<"            void set_"<<nombre_variables[contador]<<"("<<variables[contador]<<");"<<endl;
                contador++;
            }
            contador=0;
            while(contador<variables.size()-1){
                archivo<<"            "<<variables[contador]<<" get_"<<nombre_variables[contador]<<"();"<<endl;
                contador++;
            }
            archivo<<"            void toString();"<<endl;
            archivo<<"            ~"<<nombre<<"();"<<endl;
            archivo<<"};"<<endl;
            archivo<<"#endif"<<endl;

            ofstream archivo2;
            string nombre_archivo2="";
            nombre_archivo+= nombre+".cpp";
            nombre_mayus = nombre;
            archivo2.open("personaje.cpp",ios::out);
            string clase, killme="";
            clase = "\""+nombre+".h"+"\"";

            archivo2<<"#include "<<clase<<endl;
            archivo2<<"#include <string>"<<endl;
            archivo2<<nombre<<"::"<<nombre<<"(){"<<endl<<"}"<<endl;
            string aux2="";
            contador=0;
            string todas_variables2="";
            string todas_variables3="";
            while(contador<variables.size()-1){
                todas_variables2+=variables[contador]+" _"+nombre_variables[contador];
                todas_variables3+=nombre_variables[contador]+"= _"+nombre_variables[contador]+";\n";
                if (contador<variables.size()-2){
                    todas_variables2+=",";
                }
                contador++;
            }
            archivo2<<nombre<<"::"<<nombre<<"("<<todas_variables2<<"){"<<endl<<todas_variables3<<"}"<<endl;
            contador=0;
            while (contador<variables.size()-1){
                archivo2<<"void "<<nombre<<"::"<<"set_"<<nombre_variables[contador]<<"("<<variables[contador]<<" _"<<nombre_variables[contador]<<"){"<<endl;
                archivo2<<nombre_variables[contador]<<"= _"<<nombre_variables[contador]<<";"<<endl<<"}"<<endl;
                contador++; 
            }
            contador=0;
            while (contador<variables.size()-1){
                archivo2<<variables[contador]<<" "<<nombre<<"::"<<"get_"<<nombre_variables[contador]<<"(){"<<endl;
                archivo2<<"return "<<nombre_variables[contador]<<";"<<endl<<"}"<<endl;
                contador++; 
            }

            archivo2<<nombre<<"::"<<"~"<<nombre<<"(){"<<endl<<"}";
            //clase1(nombre,variables,nombre_variables);
            //clase2(nombre,variables,nombre_variables);
            nombre="";
            nombre_variables.clear();
            variables.clear();
            auxiliar_name=0;
            cont1=4;
            cont3=0;
        }
    }
    
    leer.close();
}

void clase1(string nombre, vector <string>variables, vector <string> nombre_variables){
   

}

void clase2(string nombre, vector <string>variables, vector <string> nombre_variables){
       
}

int main(){
    read_and_write();
    return 0;
}