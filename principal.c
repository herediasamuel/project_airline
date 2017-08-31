///*****Declaracion de las Librerias a Utilizar**** ///
#include <stdio.h>
#include <string.h>
///*****Definicion de una Constante***** ///
#define max 20
///*****Declaracion del tipo Cadena***** ///
typedef char cadena[50];

///*****Declaracion de Estructuras a Utilizar***** ///
typedef struct
{
    cadena Ciu;			//se guardaran las Ciudades
	int num;			//numero de cada ciudad
}Ciudades;
typedef struct
{
	int dia;			//dia en el cual se obtubieron los valores
	float Retraso;		//valores del retraso por ruta
	float clima;		//valores de condicion climatica de cada ruta
}Promedios;
typedef struct
{
	cadena vuelo[2];	/*Vector que contendra el nombre de las Ciudades por Ruta*/
    int K_dias;			//Numero de dias de Retraso
    Promedios Prom[50]; //Promedios por dia de cada ruta
	float P_total;		//Promedio Total de los K_dias por cada Ruta
}Vuelos;
typedef struct
{
	int N_Ciu;			//Contendra el numero de las Ciudades por Mapa
	int N_Rvuelos;		//Numero de las Rutas de Vuelo por cada Mapa
	int V_retraso;		//Promedio Maximo de Retraso por Ruta
	int N_consul;		//Numero de Consultas por el Usuario
	int Sus;			//Numero de rutas Suspendidas
	float CT;			//Promedio total del Arbol Expandido Minimo
}Valores;
typedef struct
{
	cadena Salida;		//Ciudad Origen de la Consulta Solicitada
	cadena Destino;		//Ciudad Destino de la Consulta Solicitada
}Consulta;
typedef struct
{
	int v1[2];			//Contiene la Direccion Matricial del vertice origen de un Arco
	int v2[2];			//Contiene la Direccion Matricial del vertice Destino de un Arco
	float costo;		//Contiene el Peso del Arco
}Etiqueta;

///*****CABECERA DE FUNCIONES Y PROCEDIMIENTOS***** ///
void null(FILE *archi);
void lectura(int *n,FILE *e);
void cargarDatos(FILE *entrada ,Ciudades a[],Vuelos b[],Consulta c[],Valores v[]);
float promedio (Vuelos v);
void calcuP(Vuelos v[],Valores a);
void inicializar(float M[][max],Valores v);
void viasAereas(Valores v,float Matriz[][20],Vuelos a[],Ciudades c[],Etiqueta A[max]);
void suspendidos(Vuelos v[],Valores a,FILE *s);
void menorRiesgo(Vuelos v[],Valores a,FILE *s);
void matrizAux(float Matriz[][max], int Aux[][max],Valores v);
void g();
void asignaEtiquetas(int i, int c[][max], int n);
void llenar(int n,int c[][max]);
int existeArcos(int n,int A[][max],Etiqueta *arc,int *band);
int buscarComponente(int n, int a, int c[][max]);
int buscaC(int n,int c[][max],int a);
void unir(int n,int c[][max],int can,int a,int b);
void componenteConexa(int A[][20],Valores v,int c[max][max],int *p);
void extraerMin(Etiqueta *e,float M[][max],Etiqueta Aux[],Valores v,int O[][max]);
void construirM(Etiqueta e, int Amin[][max]);
void asignar(Etiqueta Aux[], Etiqueta A[],Valores v);
void auxiliar(int A[][max],int B[][max],Valores v);
void formaCircuito(Etiqueta e,int Amin[][max],int *band,Valores v,int *m);
int nArco(float M[][max],Valores v);
void Kruskal(float Matriz[][max],int O[][max],Etiqueta A[max],Valores v,int *m);
int consulta(cadena c,Ciudades ciu[],Valores v);
void vertM(int i,int vert[],int m,int *verif);
void busqueda(Etiqueta A[],int x,int m,Etiqueta v[],int *cont,int vert[]);
int Verif(Etiqueta O,int x);
void busquedaA(Etiqueta A[],int x,int y,int m,Etiqueta Ondas[max],int *band,int *num);
void rutaMasCorta(Etiqueta A[],Valores v,int x,int y,int m,Etiqueta via[],Ciudades c[],int f);
void Archivos(FILE *salida,FILE *entrada);
void interfaz();
void agradecimiento();
/// *****Funcion Principal***** ///
int main()
{
	Ciudades a[max];
	Vuelos b[100];
	Consulta c[10];
	Valores v[2];
	Etiqueta A[max],via[max];
	int opc;
	int h=1,map=1;
	int Aux[20][20]={{0}};
	int p[max][max];
	int i,o,m,y,q;//opc :opcion del menu, i: indice de ciclos, o: componente conexo
	FILE *entrada,*salida;
	float Matriz[20][20]={{0.0}};
	//interfaz();
	entrada=fopen("Vuelos.in","r");
							salida=fopen("vuelos.out","w");
							null(entrada);
							null(salida);
	do
	{
	
		system("clear");
		printf(" \E[1;33m _____________Menu__________________\E[00m\n");
		printf(" \E[1;33m|1. Ver las Rutas Suspendidas.      |\E[00m\n");
		printf(" \E[1;33m|2. Ver las Rutas de Menor Promedio.|\E[00m\n");
		printf(" \E[1;33m|3. Ver los Resultados de Consultas.|\E[00m\n");
		printf(" \E[1;33m|4. Ver todos los Resultados.       |\E[00m\n");
		printf(" \E[1;33m|5. Agradecimientos.                |\E[00m\n");
		printf(" \E[1;33m|6. Salir.                          |\E[00m\n");
		printf(" \E[1;33m|___________________________________|\E[00m\n");
		scanf("%i",&opc);

		switch(opc)
		{
			case 1:
							/*entrada=fopen("Vuelos.in","r");
							salida=fopen("vuelos.out","w");
							null(entrada);
							null(salida);*/
						lectura(&v[0].N_Ciu,entrada);
						while(h!=0)
						{
							cargarDatos(entrada,a,b,c,v);
							calcuP(b,v[0]);
							viasAereas(v[0],Matriz,b,a,A);
							printf("\n\tMapa %i de Rutas",map);
							fprintf(salida,"\n\tMapa %i de Rutas",map);
							suspendidos(b,v[0],salida);
							lectura(&v[0].N_Ciu,entrada);
							h=v[0].N_Ciu;
							map+=1;
						}
						system("sleep 3.0");
						//fclose(entrada);
						//fclose(salida);

			break;
			case 2:
							/*entrada=fopen("Vuelos.in","r");
							salida=fopen("vuelos.out","w");
							null(entrada);
							null(salida);*/
						lectura(&v[0].N_Ciu,entrada);
						while(h!=0)
						{
							cargarDatos(entrada,a,b,c,v);
							calcuP(b,v[0]);
							viasAereas(v[0],Matriz,b,a,A);
							printf("\n\tMapa %i de Rutas",map);
							fprintf(salida,"\n\tMapa %i de Rutas",map);
							menorRiesgo(b,v[0],salida);
							lectura(&v[0].N_Ciu,entrada);
							h=v[0].N_Ciu;
							map+=1;
						}
						system("sleep 5.0");
						//fclose(entrada);
						//fclose(salida);

			break;
			case 3:
						
						/*entrada=fopen("e1.in","r");
						salida=fopen("vuelos.out","w");
						null(entrada);
						null(salida);*/
						lectura(&v[0].N_Ciu,entrada);
						while(h!=0)
						{
							cargarDatos(entrada,a,b,c,v);
							calcuP(b,v[0]);
							viasAereas(v[0],Matriz,b,a,A);
							matrizAux(Matriz,Aux,v[0]);
							componenteConexa(Aux,v[0],p,&o);
							Kruskal(Matriz,Aux,A,v[0],&m);
							printf("\n\tMapa %i de Rutas",map);
							fprintf(salida,"\n\tMapa %i de Rutas",map);
							for(i=0;i<v[0].N_consul;i++)
							{
								y=consulta(c[i].Salida,a,v[0]);
								q=consulta(c[i].Destino,a,v[0]);
								rutaMasCorta(A,v[0],y,q,m,via,a,i);
							}
								h=v[0].N_Ciu;
								map+=1;
						}
						fclose(entrada);
						fclose(salida);
			break;
			case 4:
					    /*entrada=fopen("Vuelos.in","r");
						salida=fopen("vuelos.out","w");
						null(entrada);
						null(salida);*/
						lectura(&v[0].N_Ciu,entrada);
						while(h!=0)
						{
							printf("\n\tMapa %i de Rutas",map);
							fprintf(salida,"\n\tMapa %i de Rutas",map);
							cargarDatos(entrada,a,b,c,v);
							calcuP(b,v[0]);
							viasAereas(v[0],Matriz,b,a,A);
							suspendidos(b,v[0],salida);
							menorRiesgo(b,v[0],salida);
							matrizAux(Matriz,Aux,v[0]);
							componenteConexa(Aux,v[0],p,&o);
							Kruskal(Matriz,Aux,A,v[0],&m);
							for(i=0;i<v[0].N_consul;i++)
							{
								y=consulta(c[i].Salida,a,v[0]);
								q=consulta(c[i].Destino,a,v[0]);
								rutaMasCorta(A,v[0],y,q,m,via,a,i);
							}
								lectura(&v[0].N_Ciu,entrada);
								h=v[0].N_Ciu;
								map+=1;
						}
						//fclose(entrada);
						//fclose(salida);
			
			break;
			case 5:
			          agradecimiento();
			break;
			case 6:
					printf("\t\n\E[1;31mHasta Luego, DIOS LE BENDIGA\E[00m\n");
			break;
			default:
						printf("Opcion Incorrecta\n");
						system("sleep 2.0");
			break;
			
		}
	}while(opc!=6);

fclose(entrada);
						fclose(salida);
return 0;
}

void null(FILE *archi)
{
     if(archi)
             printf("La Ejecucion del Archivo ha sido Exitosa\n");
       else
            printf("No se ha Ejecutado el Archivo \n");
}
void lectura(int *n,FILE *e)
{
	fscanf(e,"%d\n",n);
}

void cargarDatos(FILE *entrada ,Ciudades a[],Vuelos b[],Consulta c[],Valores v[])
{
	int i,j;
		lectura(&v[0].N_Ciu,entrada);// v->N_Ciu:Esta Variable Representa el Numero de Ciudades
		for(i=0;i<v[0].N_Ciu;i++)
		{
		  fscanf(entrada,"%s",a[i].Ciu);
		  a[i].num=i;
		}
		lectura(&v[0].N_Rvuelos,entrada);
		for(i=0;i<v[0].N_Rvuelos;i++)
		{
			fscanf(entrada,"%s %s",b[i].vuelo[0],b[i].vuelo[1]);
			lectura(&b[i].K_dias,entrada);//Lectura del numero de k_Dias
			for(j=0;j<b[i].K_dias;j++)
			{
				//Lectura de los promedios por Ruta de Vuelo
				fscanf(entrada,"%d %f %f\n",&b[i].Prom[j].dia,&b[i].Prom[j].clima,&b[i].Prom[j].Retraso);
			}
		}
		lectura(&v[0].V_retraso,entrada);//v.V_retraso: Esta Variable Contiene el Valor Maximo de Retraso Escalado, del Archivo
		lectura(&v[0].N_consul,entrada);//C: Contiene el numero de Consultas Solicitadas por el Usuario
		//Se Realiza la Lectura de las consultas (Ciudadd: Salida, Ciudad: Destino);
		for(i=0;i<v[0].N_consul;i++)
		{
			fscanf(entrada,"%s %s",c[i].Salida,c[i].Destino);
	
		}
	
}
float promedio (Vuelos v)
{
	int i,n;
	float Suma;
	Suma=0;
	n=v.K_dias;
	for(i=0;i<n;i++)
	{
		Suma+=v.Prom[i].Retraso*v.Prom[i].clima;
	}
	Suma/=n;
	return (Suma*100);
}
void calcuP(Vuelos v[],Valores a)
{
	int i;

	for(i=0;i<a.N_Rvuelos;i++)
	{
		v[i].P_total=promedio(v[i]);
	}
}
void inicializar(float M[][max],Valores v)
{
	int i,j;
	for(i=0;(i<v.N_Ciu-1);i++)
	{
		for(j=i+1;j<v.N_Ciu;j++)
		{
			M[i][j]=0;
			M[j][i]=0;
		}
	}
}
void viasAereas(Valores v,float Matriz[][20],Vuelos a[],Ciudades c[],Etiqueta A[max])
{
	int i,j,n,x,x1,x2,x3,t;
	t=0;
	inicializar(Matriz,v);
	//printf("-----%i------",v.N_Ciu);
	for(i=0;(i<v.N_Ciu-1);i++)
	{
		for(j=i+1;j<v.N_Ciu;j++)
		{
			for(n=0;n<v.N_Rvuelos;n++)
			{
				x = strcmp(c[i].Ciu,a[n].vuelo[0] );
				x2 = strcmp(c[i].Ciu,a[n].vuelo[1] );
				//printf("\nComparo %s con %s",c[i].Ciu,a[n].vuelo[0]);
				x1 = strcmp( c[j].Ciu,a[n].vuelo[1] );
				x3 = strcmp( c[j].Ciu,a[n].vuelo[0] );
				//printf("\nComparo %s con %s",c[j].Ciu,a[n].vuelo[1]);
				if(((x==0)&&(x1==0))||((x2==0)&&(x3==0)))
				{
					if (a[n].P_total<=v.V_retraso)
					{
						Matriz[i][j]=a[n].P_total;
						Matriz[j][i]=a[n].P_total;
						A[t].v1[0]=i;
						A[t].v1[1]=j;
						A[t].v2[0]=j;
						A[t].v2[1]=i;
						A[t].costo=a[n].P_total;
						t++;
					}
				}
			}
		}
	}
}

void suspendidos(Vuelos v[],Valores a,FILE *s)
{
	int i,cont;
	cont=0;
	printf("\n\nRutas Suspendidas (por tolerancia t= %i ):\n",a.V_retraso);
	fprintf(s,"\n\nRutas Suspendidas (por tolerancia t= %i ):\n",a.V_retraso);
	for(i=0;i<a.N_Rvuelos;i++)
	{
		if (v[i].P_total>=a.V_retraso)
		{
			printf("\E[1;31m%s %s\E[00m\n",v[i].vuelo[0],v[i].vuelo[1]);
			fprintf(s,"%s %s\n",v[i].vuelo[0],v[i].vuelo[1]);
			cont+=1;
		}
	}
	if(cont==0)
	{
		printf("No se Suspendio Ninguna Ruta\n");
	}
}
void menorRiesgo(Vuelos v[],Valores a,FILE *s)
{
	int i;
	printf("\nRutas con menor riesgo de retraso:\n");
	fprintf(s,"\nRutas con menor riesgo de retraso:\n");
	for(i=0;i<a.N_Rvuelos;i++)
	{
		if (v[i].P_total<=a.V_retraso)
		{
			printf("\E[1;31m%s %s\E[00m\n",v[i].vuelo[0],v[i].vuelo[1]);
			fprintf(s,"%s %s\n",v[i].vuelo[0],v[i].vuelo[1]);
		}
	}
}

void matrizAux(float Matriz[][max], int Aux[][max],Valores v)
{
	int Dim,i,j;
	Dim=v.N_Ciu;

	for (i=0;i<Dim;i++)
	{
		for (j=i+1;j<Dim;j++)
		{
			if (Matriz[i][j]>0)
			{
				Aux[i][j]=1;
				Aux[j][i]=1;
			}
		}

	}
}

/// Implementacion de un Algoritmo Previamente Realizado por Otro Grupo ///
void g(){
getchar();
}

void asignaEtiquetas(int i, int c[][max], int n)
{
	int z=0;
  for(i=0;i<n;i++)
  {
      c[0][i]=z;
      z+=1;
   }
}

void llenar(int n,int c[][max])
{
	int i,j;
	for(i=1;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			c[i][j]=-1;
		}
   }
}

int existeArcos(int n,int A[][max],Etiqueta *arc,int *band)
{
   int i,j;
   *band=0;
   for(i=0;i<(n-1);i++)
   {
       for(j=i+1;j<n;j++)
	   {
	        if(A[i][j]==1)
			{
				arc->v1[0]=i;
				arc->v2[0]=j;
				A[i][j]=-1;
				return (*band=1);
			}
        }
   }
   return *band;

}

int buscarComponente(int n, int a, int c[][max])
{
	int i,j;
	//Recorre la Matriz
	for(i=0;i<n;i++)
	{
      for(j=0;j<n;j++)
	  {
		  //Condicion para determinar donde esta la componente (vertice de un arco)
	     if(c[i][j]==a)
		 {
	        return (j);
	     }
      }
   }
   return (j);
}

int buscaC(int n,int c[][max],int a)
{
   int j;
   int con=0;
      for(j=0;j<n;j++)
	  {
		  //Condicion que verifica el nuemro de Componentes
	     if(c[j][a]!=-1)
		 {
		    con=con+1;
	     }
      }
   return (con);
}

void unir(int n,int c[][max],int can,int a,int b)
{
   int i,j=0;
   //can representa el numero de las componentes
   for(i=can;i<n;i++)
   {
      c[i][a]=c[j][b];
	  j+=1;
   }
   for(i=0;i<n;i++)
   {
      c[i][b]=-1;
   }
}
void componenteConexa(int A[][20],Valores v,int c[max][max],int *p)
{
	Etiqueta arc;
	int n,i,band=0,a,b,can,u;
	n=v.N_Ciu;
	asignaEtiquetas(i,c,n);				   //asigna a cada vertice una componente conexa
	llenar(n,c);
	//getchar();
	*p=n;									//busca un arco distinto en la matriz de adyacencia y retorna a band (1 si hay arcos disponibles,0 en caso contrario)
	u = existeArcos(n,A,&arc,&band);
	while((u==1)){
       a=buscarComponente(n,arc.v1[0],c);	//cuando consiga un arco le asigna a "a" el valor de j del arco [i,j]
       b=buscarComponente(n,arc.v2[0],c);	//cuando consiga un arco le asigna a "b" el valor de j del arco [i,j]
	  if(a!=b){
		 can=buscaC(n,c,a);					//retorna la cantidad de elementos de conjunti c[0][a]
		 unir(n,c,can,a,b);					//une c[a] con c[b]
		 *p=*p-1;
	  }
	  u=existeArcos(n,A,&arc,&band);
	}
}
/// Finalizacion del Algoritmo Implementado ///
void extraerMin(Etiqueta *e,float M[][max],Etiqueta Aux[],Valores v,int O[][max])
{
		int i,j;
		float mayor;
		mayor=100;

		for(i=0;i<v.N_Ciu;i++)
		{
			for(j=i+1;j<v.N_Ciu;j++)
			{
				if ((M[i][j]!= 0)&&(M[i][j]<mayor))
				{
						mayor=M[i][j];
						e->v1[0]=i;
						e->v1[1]=j;
						e->v2[0]=j;
						e->v2[1]=i;
						e->costo=mayor;
				}

			}
		}
		i=e->v1[0];
		j=e->v1[1];
		M[i][j]=0;
		M[j][i]=0;
}
void construirM(Etiqueta e, int Amin[][max])
{
	int i,j;
	i=e.v1[0];
	j=e.v1[1];
	Amin[i][j]=1;
	Amin[j][i]=1;
}
void asignar(Etiqueta Aux[], Etiqueta A[],Valores v)
{
	int i;
	for(i=0;i<v.N_Rvuelos;i++)
	{
		Aux[i].v1[0]=A[i].v1[0];
		Aux[i].v1[1]=A[i].v1[1];
		Aux[i].v2[0]=A[i].v2[0];
		Aux[i].v2[1]=A[i].v2[1];
		Aux[i].costo=A[i].costo;
	}
}
void auxiliar(int A[][max],int B[][max],Valores v)
{
	int i,j,n;
	n=v.N_Ciu;

	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			B[i][j]=A[i][j];
			B[j][i]=A[j][i];

		}
	}
 }
void formaCircuito(Etiqueta e,int Amin[][max],int *band,Valores v,int *m)
{
	int p[max][max],au[max][max]={{0}};
	int c,y;
	y=v.N_Ciu;

	construirM(e,Amin);
	auxiliar(Amin,au,v);
	componenteConexa(au,v,p,&c);
	*band=(*m-y)+c;
}
int nArco(float M[][max],Valores v)
{
	int i,j,n,suma;
	suma=0;
	n=v.N_Ciu;

	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			suma+=M[i][j];
		}
	}
	return(suma);
 }

void Kruskal(float Matriz[][max],int O[][max],Etiqueta A[max],Valores v,int *m)
{
	Etiqueta e,C[max];
	int t,h,k,n,band,Amin[max][max]={{0}},u;
	float CT;
	CT=0;
	t=0;
	*m=0;
	u=1;
	n=v.N_Ciu;
	band=1;
	while((u!=0))
	{
		extraerMin(&e,Matriz,C,v,O);
		*m+=1;
		formaCircuito(e,Amin,&band,v,m);
		if(band==0)
		{
				C[t].v1[0]=e.v1[0];
				C[t].v1[1]=e.v1[1];
				C[t].v2[0]=e.v2[0];
				C[t].v2[1]=e.v2[1];
				C[t].costo=e.costo;
				t+=1;
				CT+=e.costo;
		}else
		{
			h=e.v1[0];
			k=e.v1[1];
			Amin[h][k]=0;
			Amin[k][h]=0;

		}
		u=nArco(Matriz,v);
	}
	asignar(A,C,v);
	v.CT=CT;
}
int consulta(cadena c,Ciudades ciu[],Valores v)
{
	int i,x1;
	
	for(i=0;i<v.N_Ciu;i++)
	{
				x1 = strcmp(ciu[i].Ciu,c);
				if(x1==0)
				{
					return(i);
				}
	}
}
void vertM(int i,int vert[],int m,int *verif)
{
	int j;
	
	for(j=0;j<m;j++)
	{
		if(i==vert[j])
		{
			*verif=1;
		}
	}
}
void busqueda(Etiqueta A[],int x,int m,Etiqueta v[],int *cont,int vert[])
{
	int i,j,verif;
	j=0;

		for(i=0;i<m;i++)
		{
			verif=0;
			vertM(i,vert,m,&verif);
				if(verif==0)
				{
					if ((A[i].v1[0]==x)||(A[i].v1[1]==x))
					{
						v[*cont].v1[0]=A[i].v1[0];
						v[*cont].v1[1]=A[i].v1[1];
						v[*cont].costo=A[i].costo;
						vert[*cont]=i;
						*cont+=1;
					}
				}
		}
}
int Verif(Etiqueta O,int x)
{
	if(O.v1[0]!=x)
	{
		return (O.v1[0]);
	}else{
		return (O.v1[1]);
	}
}
void busquedaA(Etiqueta A[],int x,int y,int m,Etiqueta Ondas[max],int *band,int *num)
{
	int cont,i,j,cancel,c,vert[max]={-1};
	cont=0;
	cancel=0;
	i=0;
	c=x;
	busqueda(A,x,m,Ondas,&cont,vert);
	if(cont>0)
	{
		while(cancel==0)
		{
			j=Verif(Ondas[i],c);
			if(j==y)
			{
				cancel+=1;
			}else{
			busqueda(A,j,m,Ondas,&cont,vert);
			c=j;
			i++;
			}
		}
		*num=cont;
	}else{
		*band=1;
	}
}
void rutaMasCorta(Etiqueta A[],Valores v,int x,int y,int m,Etiqueta via[],Ciudades c[],int f)
{
	int band,i,num,n,p;
	float CTT;
	band=0;
	p=x;
	busquedaA(A,x,y,m,via,&band,&num);
		if(band==0)
		{
			printf("\nRecorrido %i ( %s - %s)\n",f+1,c[x].Ciu,c[y].Ciu);
			for(i=1;i<=num;i++)
			{
				if(via[i].costo>0)
				{
					n=Verif(via[i],p);
					if(n==y)
					{
						n=Verif(via[i],y);
						printf("\E[1;31m%s\E[00m ",c[n].Ciu);
					}else{
						printf("\E[1;31m%s\E[00m ",c[n].Ciu);
						p=n;
					}
				}
			}
			
			
			for(i=0;i<num;i++)
			{
				if(via[i].costo>0)
				{
					CTT+=via[i].costo;
				}
			}
			printf("\n\E[1;31m%f\n\E[00m",CTT);
			
			
		}else{
			
			printf("\nRecorrido %i ( %s - %s)\n",f+1,c[x].Ciu,c[y].Ciu);
			printf("\E[1;31mNo es Posible Relizar el Recorrido\E[00m\n");
		}
		
		
}  
void interfaz()
{

	   system("clear");
	  printf("		CARGANDO......\n");
printf("	                              0%\n");
system("sleep 0.6");
system("clear");
printf("		CARGANDO......\n");
printf("	\E[46m ||||||||\E[00m                      30%\n");
system("sleep 1.3");
system("clear");
printf("		CARGANDO......\n");
printf("	\E[46m ||||||||||||| \E[00m                55%\n");
system("sleep 1.6");
system("clear");
printf("		CARGANDO......\n");
printf("	\E[46m |||||||||||||||||||\E[00m           80%\n");
system("sleep 1.8");
system("clear");
printf("		CARGANDO......\n");
printf("	\E[46m |||||||||||||||||||||||||||\E[00m   100%\n");
system("sleep 1.8");
system("clear");
	  
printf("\E[1;33m    AAA   EEEEEEE RRRRRR  EEEEEEE  OOOOO  LL      IIIII NN   NN EEEEEEE   AAA\E[00m  \n");
printf("\E[1;33m   AAAAA  EE      RR   RR EE      OO   OO LL       III  NNN  NN EE       AAAAA\E[00m  \n");
printf("\E[1;33m  AA   AA EEEEE   RRRRRR  EEEEE   OO   OO LL       III  NN N NN EEEEE   AA   AA\E[00m  \n");
printf("\E[1;33m  AAAAAAA EE      RR  RR  EE      OO   OO LL       III  NN  NNN EE      AAAAAAA\E[00m  \n");
printf("\E[1;33m  AA   AA EEEEEEE RR   RR EEEEEEE  OOOO0  LLLLLLL IIIII NN   NN EEEEEEE AA   AA\E[00m  \n");
system("sleep 0.6");
system("clear");
printf("\E[1;32m    AAA   EEEEEEE RRRRRR  EEEEEEE  OOOOO  LL      IIIII NN   NN EEEEEEE   AAA\E[00m  \n");
printf("\E[1;32m   AAAAA  EE      RR   RR EE      OO   OO LL       III  NNN  NN EE       AAAAA\E[00m  \n");
printf("\E[1;32m  AA   AA EEEEE   RRRRRR  EEEEE   OO   OO LL       III  NN N NN EEEEE   AA   AA\E[00m  \n");
printf("\E[1;32m  AAAAAAA EE      RR  RR  EE      OO   OO LL       III  NN  NNN EE      AAAAAAA\E[00m  \n");
printf("\E[1;32m  AA   AA EEEEEEE RR   RR EEEEEEE  OOOO0  LLLLLLL IIIII NN   NN EEEEEEE AA   AA\E[00m  \n");
system("sleep 0.6");
system("clear");
printf("\E[1;34m    AAA   EEEEEEE RRRRRR  EEEEEEE  OOOOO  LL      IIIII NN   NN EEEEEEE   AAA\E[00m  \n");
printf("\E[1;34m   AAAAA  EE      RR   RR EE      OO   OO LL       III  NNN  NN EE       AAAAA\E[00m  \n");
printf("\E[1;34m  AA   AA EEEEE   RRRRRR  EEEEE   OO   OO LL       III  NN N NN EEEEE   AA   AA\E[00m  \n");
printf("\E[1;34m  AAAAAAA EE      RR  RR  EE      OO   OO LL       III  NN  NNN EE      AAAAAAA\E[00m  \n");
printf("\E[1;34m  AA   AA EEEEEEE RR   RR EEEEEEE  OOOO0  LLLLLLL IIIII NN   NN EEEEEEE AA   AA\E[00m  \n");
system("sleep 0.6");
system("clear");

printf("\E[1;36m    AAA   EEEEEEE RRRRRR  EEEEEEE  OOOOO  LL      IIIII NN   NN EEEEEEE   AAA\E[00m  \n");
printf("\E[1;36m   AAAAA  EE      RR   RR EE      OO   OO LL       III  NNN  NN EE       AAAAA\E[00m  \n");
printf("\E[1;36m  AA   AA EEEEE   RRRRRR  EEEEE   OO   OO LL       III  NN N NN EEEEE   AA   AA\E[00m  \n");
printf("\E[1;36m  AAAAAAA EE      RR  RR  EE      OO   OO LL       III  NN  NNN EE      AAAAAAA\E[00m  \n");
printf("\E[1;36m  AA   AA EEEEEEE RR   RR EEEEEEE  OOOO0  LLLLLLL IIIII NN   NN EEEEEEE AA   AA\E[00m  \n");
system("sleep 0.6");
system("clear");

printf("\E[1;35m    AAA   EEEEEEE RRRRRR  EEEEEEE  OOOOO  LL      IIIII NN   NN EEEEEEE   AAA\E[00m  \n");
printf("\E[1;35m   AAAAA  EE      RR   RR EE      OO   OO LL       III  NNN  NN EE       AAAAA\E[00m  \n");
printf("\E[1;35m  AA   AA EEEEE   RRRRRR  EEEEE   OO   OO LL       III  NN N NN EEEEE   AA   AA\E[00m  \n");
printf("\E[1;35m  AAAAAAA EE      RR  RR  EE      OO   OO LL       III  NN  NNN EE      AAAAAAA\E[00m  \n");
printf("\E[1;35m  AA   AA EEEEEEE RR   RR EEEEEEE  OOOO0  LLLLLLL IIIII NN   NN EEEEEEE AA   AA\E[00m  \n");
system("sleep 0.6");
system("clear");

printf("\E[0;36m    AAA   EEEEEEE RRRRRR  EEEEEEE  OOOOO  LL      IIIII NN   NN EEEEEEE   AAA\E[00m \n");
printf("\E[0;36m   AAAAA  EE      RR   RR EE      OO   OO LL       III  NNN  NN EE       AAAAA\E[00m \n");
printf("\E[0;36m  AA   AA EEEEE   RRRRRR  EEEEE   OO   OO LL       III  NN N NN EEEEE   AA   AA\E[00m \n");
printf("\E[0;36m  AAAAAAA EE      RR  RR  EE      OO   OO LL       III  NN  NNN EE      AAAAAAA\E[00m \n");
printf("\E[0;36m  AA   AA EEEEEEE RR   RR EEEEEEE  OOOO0  LLLLLLL IIIII NN   NN EEEEEEE AA   AA\E[00m \n");
system("sleep 0.6");
system("clear");

printf("\E[1;34m    AAA   EEEEEEE RRRRRR  EEEEEEE  OOOOO  LL      IIIII NN   NN EEEEEEE   AAA\E[00m \n");
printf("\E[1;34m   AAAAA  EE      RR   RR EE      OO   OO LL       III  NNN  NN EE       AAAAA\E[00m \n");
printf("\E[1;34m  AA   AA EEEEE   RRRRRR  EEEEE   OO   OO LL       III  NN N NN EEEEE   AA   AA\E[00m \n");
printf("\E[1;34m  AAAAAAA EE      RR  RR  EE      OO   OO LL       III  NN  NNN EE      AAAAAAA\E[00m \n");
printf("\E[1;34m  AA   AA EEEEEEE RR   RR EEEEEEE  OOOO0  LLLLLLL IIIII NN   NN EEEEEEE AA   AA\E[00m \n");
system("sleep 0.6");
system("clear");

printf("\E[1;31m    AAA   EEEEEEE RRRRRR  EEEEEEE  OOOOO  LL      IIIII NN   NN EEEEEEE   AAA\E[00m \n");
printf("\E[1;31m   AAAAA  EE      RR   RR EE      OO   OO LL       III  NNN  NN EE       AAAAA\E[00m \n");
printf("\E[1;31m  AA   AA EEEEE   RRRRRR  EEEEE   OO   OO LL       III  NN N NN EEEEE   AA   AA\E[00m \n");
printf("\E[1;31m  AAAAAAA EE      RR  RR  EE      OO   OO LL       III  NN  NNN EE      AAAAAAA\E[00m \n");
printf("\E[1;31m  AA   AA EEEEEEE RR   RR EEEEEEE  OOOO0  LLLLLLL IIIII NN   NN EEEEEEE AA   AA\E[00m \n");
system("sleep 0.6");
system("clear");

printf("\E[5;32m    AAA   EEEEEEE RRRRRR  EEEEEEE  OOOOO  LL      IIIII NN   NN EEEEEEE   AAA\E[00m \n");
printf("\E[5;32m   AAAAA  EE      RR   RR EE      OO   OO LL       III  NNN  NN EE       AAAAA\E[00m \n");
printf("\E[5;32m  AA   AA EEEEE   RRRRRR  EEEEE   OO   OO LL       III  NN N NN EEEEE   AA   AA\E[00m \n");
printf("\E[5;32m  AAAAAAA EE      RR  RR  EE      OO   OO LL       III  NN  NNN EE      AAAAAAA\E[00m \n");
printf("\E[5;32m  AA   AA EEEEEEE RR   RR EEEEEEE  OOOO0  LLLLLLL IIIII NN   NN EEEEEEE AA   AA\E[00m \n");
system("sleep 0.6");
system("clear");

printf("\E[1;32m    AAA   EEEEEEE RRRRRR  EEEEEEE  OOOOO  LL      IIIII NN   NN EEEEEEE   AAA\E[00m  \n");
printf("\E[1;32m   AAAAA  EE      RR   RR EE      OO   OO LL       III  NNN  NN EE       AAAAA\E[00m  \n");
printf("\E[1;32m  AA   AA EEEEE   RRRRRR  EEEEE   OO   OO LL       III  NN N NN EEEEE   AA   AA\E[00m  \n");
printf("\E[1;32m  AAAAAAA EE      RR  RR  EE      OO   OO LL       III  NN  NNN EE      AAAAAAA\E[00m  \n");
printf("\E[1;32m  AA   AA EEEEEEE RR   RR EEEEEEE  OOOO0  LLLLLLL IIIII NN   NN EEEEEEE AA   AA\E[00m  \n");
system("sleep 0.6");
system("clear");

printf("\E[1;31m    AAA   EEEEEEE RRRRRR  EEEEEEE  OOOOO  LL      IIIII NN   NN EEEEEEE   AAA\E[00m  \n");
printf("\E[1;33m   AAAAA  EE      RR   RR EE      OO   OO LL       III  NNN  NN EE       AAAAA\E[00m  \n");
printf("\E[1;34m  AA   AA EEEEE   RRRRRR  EEEEE   OO   OO LL       III  NN N NN EEEEE   AA   AA\E[00m  \n");
printf("\E[1;35m  AAAAAAA EE      RR  RR  EE      OO   OO LL       III  NN  NNN EE      AAAAAAA\E[00m  \n");
printf("\E[1;36m  AA   AA EEEEEEE RR   RR EEEEEEE  OOOO0  LLLLLLL IIIII NN   NN EEEEEEE AA   AA\E[00m  \n");
system("sleep 0.6");
system("clear");
}
void agradecimiento()
{

	system("clear");
    printf("\E[0;34mA\E[00m\n");
    system("sleep 0.3");
    system("clear");
	 printf("\E[0;34mAG\E[00m\n");
    system("sleep 0.3");
    system("clear");
	 printf("\E[0;34mAGR\E[00m\n");
    system("sleep 0.2");
    system("clear");
	 printf("\E[0;34mAGRA\E[00m\n");
    system("sleep 0.2");
    system("clear");
	 printf("\E[0;34mAGRAD\E[00m\n");
    system("sleep 0.2");
    system("clear");
	 printf("\E[0;34mAGRADE\E[00m\n");
    system("sleep 0.2");
    system("clear");
	 printf("\E[0;34mAGRADEC\E[00m\n");
    system("sleep 0.2");
    system("clear");
	 printf("\E[0;34mAGRADECE\E[00m\n");
    system("sleep 0.2");
    system("clear");
	 printf("\E[0;34mAGRADECEM\E[00m\n");
    system("sleep 0.2");
    system("clear");
		 printf("\E[0;34mAGRADECEMO\E[00m\n");
    system("sleep 0.2");
    system("clear");
	printf("\E[0;34mAGRADECEMOS\E[00m\n");
    system("sleep 0.2");
    system("clear");
	printf("\E[0;34mAGRADECEMOS A\E[00m\n");
    system("sleep 0.2");
    system("clear");
	
    printf("       \E[0;35mDIOS\n     \E[00m");

	system("sleep 1.0");
    system("clear");
	printf("\E[0;37mPOR LA AYUDA EN LA REALIZACION DE ESTE PROYECTO....\E[00m\n");
	system("sleep 2.5");
}
