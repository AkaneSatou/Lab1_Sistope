Lab1_Sistope
============
#include <iostream>
#include <fstream> //stream de ficheros
#include <string.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unistd.h>
#include <exception>
#include <stdio.h>
using namespace std;
//Claudia Bustamante Arce
/*Función recibe un fichero, y lo pasa a un vector de vectores*/
vector<vector<string> > lecturaA(string& fichero){

	vector<vector<string> > estrdato; 	//almacenamiento de ficheros
	ifstream ficheroA; 	//vector<string> vprincipal;
	string word;  //linea almacenada

	ficheroA.open(fichero.c_str()); 
	if(ficheroA.fail()){ //si la lectura es erronea
		cout << "Alguno de los archivos no se abrió correctamente." <<  endl; 
		exit(0);
	} //si es correcta, se recorre hasta eof el fichero
	while(!ficheroA.eof()){
		string ok;
		vector<string> captura;
		getline(ficheroA,word);
		istringstream line(word);
		while(getline(line, ok,' ')) //se obtiene la linea hasta el espacio
			captura.push_back(ok);
		estrdato.push_back(captura); //se almacena la palabra en el vector de vectores
	}
	ficheroA.close(); //se cierra el fichero
	return estrdato;//se retorna el vector bidimensional con los datos del fichero
}

/*Función que imprime un vector bidimensional*/
void imprimir2(vector<vector<string> > estrdato){
	for(int i=0;i<estrdato.size();i++){
		for(int j=0;j<estrdato[i].size(); j++){
			cout <<  estrdato.at(i).at(j)+" ";
		}
		cout << " " << endl;
	} 
}

/*Funión que imprime un vector unidimensional*/
void imprimir1(vector<string> arreglo){
	for(int i=0;i<arreglo.size();i++){
		cout <<  arreglo.at(i)+"\n";
	} 
}

/*Función que recibe dos vectores bidimensionales, y busca las palabras contenidas en ambos*/
vector<string> RepeatWord(vector<vector<string> > estrd1, vector<vector<string> > estrd2){
	string word1,word2;
	vector<string> repeat;
	repeat.clear();
	int cont=0;
	int yaesta=0;
	
	for(int i=0;i<estrd1.size();i++){
			for(int j=0;j<estrd1[i].size(); j++){
				word1=estrd1.at(i).at(j);
				for(vector<string>::iterator G = repeat.begin();G!=repeat.end(); G++){
					if(word1.compare(*G)==0){
						yaesta=1;
						break;
					}
				}
				if(yaesta==0){
					for(int k=0;k<estrd2.size();k++){
						for (int l=0;l<estrd2[k].size();l++){
							word2=estrd2.at(k).at(l);
							if(word1.compare(word2)==0){
								repeat.push_back(word2);
								cont++;
								break;
							}	
						}
						if (cont > 0) break;
					}
				}
				cont = 0;
				yaesta=0;
			}
	}
	return repeat;
}

/*Función que recibe un vector bidimensional, y busca las palabras repetidas*/
vector<string> Repetidas(vector<vector<string> > estrd1){
	string word1,word2;
	vector<string> repeat;
	repeat.clear();
	int cont=0;
	int yaesta=0;
	
	for(int i=0;i<estrd1.size();i++){
			for(int j=0;j<estrd1[i].size(); j++){
				word1=estrd1.at(i).at(j);
				for(vector<string>::iterator G = repeat.begin();G!=repeat.end(); G++){
					if(word1.compare(*G)==0){
						yaesta=1;
						break;
					}
				}
				if(yaesta==0){
					for(int k=0;k<estrd1.size();k++){
						for (int l=0;l<estrd1[k].size();l++){
							word2=estrd1.at(k).at(l);
							if(word1.compare(word2)==0){
								cont++;
							}	
							if (cont > 1){
							repeat.push_back(word2);
							break;
							}
						}
						if (cont > 1){
						break;
						}
					}
				}
				cont = 0;
				yaesta=0;
			}
	}
	return repeat;
}


/*Función que escribe en un archivo el vector resultado*/
void EscrituraVector(string& SVal, vector<string> repetidas, string& pVal, string& hVal){
	int i=0;
	ofstream FICHERO(SVal.c_str());
	if(FICHERO.fail()){
		cout<< "El archivo no se creó correctamente\n"<<endl;
		exit(0);
	}
	int tam= repetidas.size();
	FICHERO<<"nHebras: "<< hVal <<endl;
	FICHERO<<"nProceso: "<< pVal <<endl;
	FICHERO << "\n" << endl;
	while(i<tam){
		FICHERO << repetidas.at(i)+" "<< endl;
		i++;
	}
	FICHERO.close();
}

void Escritura2Vector(string& SVal, vector<vector<string> > estrdato, string& pVal, string& hVal){
	int i=0;
	ofstream FICH(SVal.c_str());
	if(FICH.fail()){
		cout<< "El archivo no se creó correctamente\n"<<endl;
		exit(0);
	}
	FICH<<"nHebras: "<< hVal <<endl;
	FICH<<"nProceso: "<< pVal <<endl;
	FICH << "\n" << endl;
	for(int i=0;i<estrdato.size();i++){
		for(int j=0;j<estrdato[i].size();j++){
			FICH << estrdato.at(i).at(j)+" " << endl;
		}
		FICH << "\n" << endl;
	}
	FICH.close();
}

/*Función que retorna el tipo de archivo que se ingresa.*/
void bandera_o(string& oVal){ 
	stringstream s;
	s << "file -i " <<oVal;
	system(s.str().c_str());
}

void escribir_o(string& SVal, string& oVal,string& pVal, string& hVal){
	stringstream linea;
	FILE* lect;
	char temp[100];
	ofstream sale(SVal.c_str());
	if(sale.fail()){
		cout<< "El archivo no se creó correctamente\n"<<endl;
		exit(0);
	}
	sale<<"nHebras: "<< hVal <<endl;
	sale<<"nProceso: "<< pVal <<endl;
	sale << "\n" << endl;
	linea << "file -i " << oVal;
	lect = popen(linea.str().c_str(),"r");
	while(fgets(temp,sizeof(temp),lect)!=NULL){
		sale << temp;
	}
}

/*Función que, si retorna que el tipo de archivo es texto plano, entonces lo imprime.*/
int bandera_O(string& OVal){

	FILE *fichero;
	char palabras[512];
	int id=0;
	
	stringstream consola;
	consola << "file -i " << OVal;
	fichero = popen(consola.str().c_str(), "r");
	while(fgets(palabras,sizeof(palabras),fichero)!=NULL){
		for(int i=0;i<sizeof(palabras)-4;i++){
			if(palabras[i]=='t' && palabras[i+1]=='e' && palabras[i+2]=='x' && palabras[i+3]=='t'){
				id=1;
				break;
			}else{
				id=0;
			//si está contenida la palabra text, entonces es texto plano y puede imprimirse 
			}
		}
	}
	return id;
}

void mask_bandera_O(string& OVal, int id){
	vector<vector<string> > mat;
	if(id==0){
		cout<< "El parámetro no corresponde a texto plano, no puede imprimirse." << endl;

	}
	if(id==1){
		cout<< "Es texto plano\n " << endl;
		mat=lecturaA(OVal);
		imprimir2(mat);
	}

}

/*Función principal*/		
int main(int argc, char **argv){
	int columna1=0, columna2=0;
	int fila1=0, fila2=0;
	vector<string> repetidas;
	vector<vector<string> > estr1;
	vector<vector<string> > estr2;

	string oVal = ""; // debe indicar tipo de archivo
	int oflag=0;
	string OVal = ""; // abre el archivo, si es plano lo imprime
	int Oflag=0;
	string hVal = ""; // lee y muestra numero de hebras por pantalla
	int hflag=0;
	string pVal = ""; // lee y muestra numero de procesos por pantalla
	int pflag=0;
	string sVal = ""; // muestra el nombre de salida, y retorna un documento
	int sflag=0;
	string SVal = ""; // retorna resultado en un documento pero no muestra nada por pantalla
	int Sflag=0;
	string fVal = ""; // se abre el archivo y se muestran las palabras repetidas en el mismo
	int fflag=0;
	string gVal = ""; // se leen ambos archivos y se muestra las palabras qe estan en los dos textos
	int gflag=0;
	int c;
	opterr =0;
	while((c = getopt(argc,argv,"o:O:h:p:s:S:f:g:")) != -1)
		switch(c){
			case 'o':
					oflag = 1;
					oVal= optarg;
					break;
			case 'O':
					Oflag = 1;
					OVal = optarg;
					break;
			case 'h':
					hflag = 1;
					hVal = optarg;
					break;
			case 'p':
					pflag = 1;
					pVal = optarg;
					break;
			case 's':
					sflag = 1;
					sVal=optarg;
					break;
			case 'S':
					Sflag = 1;
					SVal=optarg;
					break;
			case 'f':
					fflag = 1;
					fVal=optarg;
					break;
			case 'g':
					gflag = 1;
					gVal = optarg;
					break;
			case '?':
				if (optopt=='f'||optopt == 'g'||optopt == 'o'||optopt == 'O'||optopt == 'h'||optopt == 'p'||optopt == 's'||optopt == 'S')
					fprintf (stderr, "Opcion -%c requiere un argumento.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Opcion incorrecta `-%c'.\n", optopt);
				else
					fprintf (stderr,"Opcion desconocida `\\x%x'.\n", optopt);
				return 1;
			default:
				abort();
		}

  		if(pflag==0 || hflag==0){
  			cout << "Faltan banderas\n";
  			exit(0);

  		}else{

        	if (Sflag==1) // retorna en documento
        	{
        		int id=0;
        		if(oflag==1){//debe imprimir el tipo de archivo en el txt
        			escribir_o(SVal, oVal, pVal, hVal);
        		}
        		if(Oflag==1){
        			id=	bandera_O(OVal); //busca la palabra text en fichero
        			if(id==1){ //imprime en texto
	        			estr1=lecturaA(OVal);
	        			Escritura2Vector(SVal,estr1, pVal, hVal);
        			}else{  //imprime que no se imprime xd 
	        			vector<string> buffer; 
						string frase;
						frase = "El archivo no es texto plano.";
						buffer.push_back(frase);
						EscrituraVector(SVal,buffer,pVal,hVal);
        			}
				}

				if(fflag==1 && gflag==1){ //acá retorna el vector de intersección en la salida 
					estr1 = lecturaA(gVal);
					estr2 = lecturaA(fVal);
					repetidas = RepeatWord(estr1,estr2);
					int tam = repetidas.size();
					//cout << "nPalabras: " << tam << endl;
					EscrituraVector(SVal,repetidas, pVal, hVal);
				}
				else if(fflag==1){ //acá retorna las palabras repetidas en un mismo texto
					estr1 = lecturaA(fVal);
					repetidas = Repetidas(estr1);
					int tam = repetidas.size();
					//cout << "nPalabras: " << tam << endl;
					EscrituraVector(SVal,repetidas, pVal, hVal);
				}
				else if(gflag==1){ //acá escribe mensaje de error por bandera g
					vector<string> buffer; 
					string frase;
					frase = "Error en ingreso de parámetros, verifique banderas.";
					buffer.push_back(frase);
					EscrituraVector(SVal,buffer,pVal,hVal);
				}

        	}
        	else if(sflag==1){ //imprime por pantalla y guarda en texto

				cout<<"nHebras: "<< hVal <<endl;
				cout<<"nProceso: "<< pVal <<endl;
				if(fflag==1 && gflag==1){
					estr1 = lecturaA(gVal);
					estr2 = lecturaA(fVal);
					repetidas = RepeatWord(estr1,estr2);
					int tam = repetidas.size();
					//cout << "nPalabras: " << tam << endl;
					EscrituraVector(SVal,repetidas, pVal, hVal);
					imprimir1(repetidas);

				}else if(fflag=1){
					estr1 = lecturaA(fVal);
					repetidas = Repetidas(estr1);
					int tam = repetidas.size();
					//cout << "nPalabras: " << tam << endl;
					EscrituraVector(SVal,repetidas, pVal, hVal);
					imprimir1(repetidas);

				}else if (gflag==1){
					vector<string> buffer; 
					string frase;
					frase = "Error en ingreso de parámetros, verifique banderas.";
					buffer.push_back(frase);
					EscrituraVector(SVal,buffer,pVal,hVal);
					cout << "Error en ingreso de parámetros, verifique banderas.\n";
					exit(0);
        		}
        	}
        	else{	//solo imprime por pantalla 
	        	cout<<"nHebras: "<< hVal <<endl;
				cout<<"nProceso: "<< pVal <<endl;
				
				if(oflag==1){
					bandera_o(oVal);
				}

				if(Oflag==1){
					int id;
					id=	bandera_O(OVal);//buscar la palabra text en fichero
					mask_bandera_O(OVal,id);
				}

				if(fflag==1 && gflag==1){
					estr1 = lecturaA(gVal);
					estr2 = lecturaA(fVal);
					repetidas = RepeatWord(estr1,estr2);
					imprimir1(repetidas);

				}else if(fflag==1){
					estr1 = lecturaA(fVal);
					repetidas=Repetidas(estr1);
					imprimir1(repetidas);
				}
				else if (gflag==1){
					cout << "error banderas\n";
					exit(0);
				}
        	}
  		}
	return 0;
}
