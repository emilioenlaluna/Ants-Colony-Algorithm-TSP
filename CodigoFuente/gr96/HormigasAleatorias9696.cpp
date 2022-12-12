//Libreria que incluye librerias de C++
#include<bits/stdc++.h>

//Libreria auxiliar para entrada y salida de datos
using namespace std;


//Clase con la solucion de hormigas
class ColoniaHormigas {

	public:

		//Constructor de la clase, se ejecutara al instanciar un nuevo objeto
		ColoniaHormigas() {
			//Establecemos la cantidad de decimales
			cout.precision(4);
			std::cout << std::fixed << std::showpoint;

			cout<<endl<<"------------Algoritmo de Colonia de Hormigas-------------"<<endl;
			//Pedimos los parametros iniciales
			ParametrosIniciales();
			//Leemos el archivo
			LeerGR96();
			//Funcion de solucion
			Solucion();
		}


		//Variables
		//tinicial- feromona inicial
		// Q constante parametro para la feromona
		// a alpha
		// B bheta
		// p parametro de reduccion de feromona
		float tinicial=0.1,Q=1,a=1,B=1,p=0.01;
		//Numero de iteraciones maximas y la cantidad de hormigas por iteracion
		int cantidadHormigasIteracion=1,maximoteraciones=1;
		//Variable para guardar el punto inicial
		int puntoInicial=0;
		//Variable para guardar si el punto inicial es aleatorio o en algun punto
		bool puntoInicialtipo=false;

		//Matriz que contiene las distencias de los caminos
		float matrizDistancias[96][96];

		// Matriz que contiene las cantidad de feromina de un camino
		float matrizFeromonas[96][96];

		//Matriz de visibilidad se obtinne con el inverso de la distencia
		float matrizVisibiliadad[96][96];

		//Lista tabu auxiliar para saber que ciudad ya fue visitada
		int listaTabu[96];


		//Funcion para guardar los parametros del usuario
		void ParametrosIniciales() {
			cout<<"Ingrese el valor de Tinicial"<<endl;
			do {
				cout<<":";
				cin>>tinicial;
			} while(tinicial<=0);

			cout<<"Ingrese el valor de Q"<<endl;
			do {
				cout<<":";
				cin>>Q;
			} while(Q<=0);

			cout<<"Ingrese el valor de a (alpha)"<<endl;
			do {
				cout<<":";
				cin>>a;
			} while(a<=0);

			cout<<"Ingrese el valor de B"<<endl;

			do {
				cout<<":";
				cin>>B;
			} while(B<=0);

			cout<<"Ingrese el valor de p"<<endl;
			do {
				cout<<":";
				cin>>p;
			} while(p>1||p<0);


			cout<<"Ingrese la cantidad de hormigas por iteracion"<<endl;
			do {
				cout<<":";
				cin>>cantidadHormigasIteracion;
			} while(cantidadHormigasIteracion<=0||cantidadHormigasIteracion>=100);

			cout<<"Ingrese la cantidad de iteraciones"<<endl;


			do {
				cout<<":";
				cin>>maximoteraciones;
			} while(maximoteraciones<=0||maximoteraciones>=100);

			
		}

		//
		void Solucion() {
			//Generacion de la semilla para aleatorios
			srand(time(NULL));

			//Varible para guardar el numero de ciudades
			int ciudades=96;

			//Variable para encontrar este objetivo
			//int comidaPosicion=3;

			//Variable para saber la posicion actual de la hormiga
			puntoInicial=rand()%95;
			int posicionActual=puntoInicial;

			//Variable para almacenar el aletorio para continuar a la siguiente ciudad
			int posicionAleatorio=0;

			//Variable para guardar las probabilidades de una ciudad tao i j
			float tn=1;

			//Arreglo para guardar la probabilidad de cada camino por una hormiga
			float hormigaProbabilidad[ciudades];

			//Arreglo para guardar el camino que sigue una hormiga
			int solucionHormiga[(ciudades+1)];

			//Variable para guardar la suma de la probabilidad
			float sumaProbability=0;

			//Variable para guardar la nueva cantidad de feromona de la siguiente iteracion
			float h=0;

			//Auxiliar de probabilidad de un camino
			int auxiliarProbabilidad=0;

			//Variable para guardar los aletorios
			float aleatorio=0;

			//Auxiliar de probabilidad para cuando se encuentran caminos no validos
			float auxiliarSumaProbabilidad=0.0;

			//Auxiliar para contar posiciones
			int contador=1;

			//Variable auxiliar para cuando no existen caminos validos
			int contaNullos=0;

			//Inicializamos los arreglos como no visitados y vacios
			for(int i=0; i<ciudades; i++) {
				hormigaProbabilidad[i]=0;
				solucionHormiga[i]=-1;
			}

			//Inicializamos el punto de inicio
			solucionHormiga[0]=puntoInicial;

			//llllllllllllllllllll
			solucionHormiga[ciudades]=puntoInicial;

			listaTabu[puntoInicial]=1;



			/*
						for(int i=0; i<ciudades; i++) {
							for(int j=0; j<ciudades; j++) {
								matrizVisibiliadad[i][j]=tinicial;
							}
						}
						*/

		
			//Obteniendo la matriz de visibilidad
			for(int i=0; i<ciudades; i++) {
				for(int j=0; j<ciudades; j++) {
					if(i!=j) {
						matrizVisibiliadad[i][j]=(1/matrizDistancias[i][j]);
					}

				}
			}

		

			//Obteniendo la matriz de feromonas
			for(int i=0; i<ciudades; i++) {
				for(int j=0; j<ciudades; j++) {
					matrizFeromonas[i][j]=tinicial;
				}
			}

			



			//Variable para guardar el costo de la solucion de la hormiga actual
			float acumula=0;
			//Variables auxiliares
			int x,y;

			//Arreglo para guardar el costo de cada camino de las hormigas
			int sumaCostoCaminos[cantidadHormigasIteracion];


			cout<<endl<<"------------------------INICIA SOLUCION------------------------------"<<endl;

			//Ciclo para iteraciones
			for(int iterador=0; iterador<maximoteraciones; iterador++) {
				cout<<"-----------------Iteracion:"<<(iterador+1)<<"-----------------------"<<endl;

				//Reiniciamos el lugar para guardar el costo de los caminos
				for(int b=0; b<cantidadHormigasIteracion; b++) {
					sumaCostoCaminos[b]=0;
				}

				//Ciclo para las hormigas por cada iteracion
				for(int hormiga=0; hormiga<cantidadHormigasIteracion; hormiga++) {
					cout<<"-----------------------Hormiga--------------------------"<<(hormiga+1)<<endl;
					acumula=0;
					puntoInicial=rand()%95;
					posicionActual=puntoInicial;
					//hormigaPosicion=0;
					sumaProbability=0;
					tn=0;
					for(int i=0; i<ciudades; i++) {
						hormigaProbabilidad[i]=0;
						solucionHormiga[i]=-1;
						listaTabu[i]=0;
					}
					listaTabu[puntoInicial]=1;
					solucionHormiga[0]=puntoInicial;
					auxiliarSumaProbabilidad=0.0;
					contador=0;
					posicionAleatorio=puntoInicial;
					contaNullos=0;

					//Metodo para busqueda de soluciones
					do {
					
						//cout<<"Ubicacion Alimento"<<comidaPosicion<<endl;
						for(int i=0; i<ciudades; i++) {
						
							if(matrizDistancias[posicionActual][i]!=0&&listaTabu[i]!=1) {
							tn=(pow(matrizFeromonas[posicionActual][i],a))*(pow(matrizVisibiliadad[posicionActual][i],B));
									hormigaProbabilidad[i]=tn;
								
								sumaProbability+=tn;
								
							}
						}

						for(int i=0; i<ciudades; i++) {
							if(sumaProbability!=0) {
								hormigaProbabilidad[i]=(hormigaProbabilidad[i]*100)/sumaProbability;
							
							} else {
								hormigaProbabilidad[i]=0;
								contaNullos++;
							}

						}
						aleatorio = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100));
						for(int i=0; i<ciudades; i++) {

							
							auxiliarSumaProbabilidad+=hormigaProbabilidad[i];
							
							if(auxiliarSumaProbabilidad>=aleatorio) {
								posicionAleatorio=i;
								break;
							}
							if(contaNullos>=95|(auxiliarSumaProbabilidad==0&&i==95)) {
								
								posicionActual=puntoInicial;
								//hormigaPosicion=0;
								sumaProbability=0;
								tn=0;
								for(int i=0; i<ciudades; i++) {
									hormigaProbabilidad[i]=0;
									solucionHormiga[i]=-1;
									listaTabu[i]=0;
								}
								puntoInicial=rand()%95;
								listaTabu[puntoInicial]=1;
								solucionHormiga[0]=puntoInicial;
								auxiliarSumaProbabilidad=0.0;
								contador=0;
								posicionAleatorio=puntoInicial;
								contaNullos=0;
								break;
							}
						}




						solucionHormiga[contador]=posicionAleatorio;
					
						listaTabu[posicionAleatorio]=1;

						posicionActual=posicionAleatorio;
						//hormigaPosicion=posicionAleatorio;
						sumaProbability=0;
						contaNullos=0;
						tn=0;
						for(int i=0; i<ciudades; i++) {
							hormigaProbabilidad[i]=0;
						}
						auxiliarSumaProbabilidad=0.0;
						contador++;
					} while(contador<ciudades);
					//Fin busqueda de solucion

					cout<<"La solucion es"<<endl;
					for(int i=0; i<ciudades; i++) {
						cout<<" "<<(solucionHormiga[i]+1)<<" ";
					}
					

					for(int cont=0; cont<ciudades; cont++) {
						if(solucionHormiga[cont]!=-1) {
							x = solucionHormiga[cont];
							y = solucionHormiga[cont+1];
							
							acumula += matrizDistancias[x][y];
							
						}
					}
					cout<<"El valor de la solucion es = " << acumula<<endl;
					sumaCostoCaminos[hormiga]=acumula;

				}

				for(int u=0; u<cantidadHormigasIteracion; u++) {
					h+=(Q/sumaCostoCaminos[u]);
				}
				cout<<"El valor de H es "<<h<<endl;

				for(int i=0; i<ciudades; i++) {
					for(int j=0; j<ciudades; j++) {
						matrizFeromonas[i][j]=matrizFeromonas[i][j]*(1-p);
					}
				}

				for(int cont=0; cont<ciudades; cont++) {
					if(solucionHormiga[cont]!=-1) {
						x = solucionHormiga[cont];
						y = solucionHormiga[cont+1];

						matrizFeromonas[x][y]=matrizFeromonas[x][y]+h;
						matrizFeromonas[y][x]=matrizFeromonas[y][x]+h;
					}

				}

				//Imprimimos la matriz de feromonas con los cambios de la iteracion
				


				cout<<"Fin iteracion..."<<endl;
			}//Fin iteraciones
			cout<<"Programa terminado..."<<endl;
		}//Fin funcion Solucion


		void LeerGR96() {

			fstream my_file;
			float aux1,aux2,aux3;
			int contador=0;
			int tam=96;
			float x [tam];
			float y [tam];
			for(int i=0; i<tam; i++) {
				x[i]=0;
				y[i]=0;
			}

			my_file.open("gr96.tsp", ios::in);
			if (!my_file) {
				cout << "Archivo no encontrado";
				exit(0);
			} else {
				string ch,ch2,ch3;

				while (1) {
					my_file >> ch>>ch2>>ch3;
					if (my_file.eof())
						break;

					cout << ch <<" "<<ch2<<" "<<ch3<<endl;
					aux1=atof(ch.c_str());
			aux2=atof(ch2.c_str());
			aux3=atof(ch3.c_str());
					x[contador]=aux2;
					y[contador]=aux3;
					contador++;
				}

			}
			my_file.close();

			

			float matrix [tam][tam];

			float PI=3.141596;

			float degi=0;
			float degj=0;
			float mini=0;
			float minj=0;
			//latitud y longitud
			float latitudei=0;
			float latitudej=0;
			float longitudei=0;;
			float longitudej=0;;

			float RRR=6378.388;

			float q1=0,q2=0,q3=0;
			float dij=0;

			for(int i=0; i<tam; i++) {
				for(int j=0; j<tam; j++) {
					// i
					////latitude
					degi=round(x[i]);
					mini=x[i]-degi;
					latitudei=PI*(degi+5.0*mini/3.0)/180.0;
					////longitude
					degi=round(y[i]);
					mini=y[i]-degi;
					longitudei=PI*(degi+5.0*mini/3.0)/180.0;

					// j

					////latitude
					degj=round(x[j]);
					minj=x[j]-degj;
					latitudej=PI*(degj+5.0*minj/3.0)/180.0;
					////longitude
					degj=round(y[j]);
					minj=y[j]-degj;
					longitudej=PI*(degj+5.0*minj/3.0)/180.0;

					q1=cos(longitudei-longitudej);
					q2=cos(latitudei-latitudej);
					q3=cos(latitudei+latitudej);
					dij=round(RRR*acos(0.5*((1.0+q1)*q2-(1.0-q1)*q3))+1.0);
					matrizDistancias[i][j]=dij;
				}
			}

		
		}






};//Fin clase


//Funcion inicial
int main() {
	ColoniaHormigas solucion;//Genereamos un objeto de la clase Colonia de Hormigas
	return 0;
}//Fin funcion