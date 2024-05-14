#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void estratificacion(int columna, int fila, char arr[columna][fila][100]);

int main()
{
	FILE *archivo;
	int i=0,j=0,k=0;
	char nom_archivo[50];

	printf("\n\tEjecicio de Lab. 9");
	//printf("\n\n\tClasificador de petalos\n");
	printf("\n\tIntroduce el nombre del archivo: ");
	scanf("%s",nom_archivo);
	
	archivo = fopen(nom_archivo,"r");
	if(archivo == NULL)
		printf("\n\tError en la apertura del archivo");

	int c,fila=1,coma=0,columna;
	while ((c = fgetc(archivo)) != EOF) 
	{
		if(c == '\n')
		{
			fila++;
		}
		else if(c == ',')
		{	
			coma++;
		}
    	}
	//printf("\n\tFila : %d",fila);
	//printf("\n\tComas : %d",coma);
	columna = (coma/fila) + 1;
	//printf("\n\tColumnas : %d",columna);
	fseek(archivo,0,SEEK_SET);

	char line[1024];
	char arr[columna][fila][100];
	
	
    	while(fgets(line, sizeof(line), archivo) != NULL) 
	{
        	char *token = strtok(line, ",");
        	while (token != NULL) 
		{
			//printf("\t%s\n", token);
			if (strchr(token, '\n') != NULL) 
			{
            			token[strcspn(token, "\n")] = '\0';
        		}
			strcpy(arr[i][j], token);
           		token = strtok(NULL, ",");
			i++;
        	}
		j++;
		i=0;
	}	

	estratificacion(columna,fila,arr);
	fclose(archivo);
	return 0;
}

void estratificacion(int columna, int fila, char arr[columna][fila][100])
{
	int i,j,k;
	int num_clase=0;
    	char clases[100][100] = {0}; 
	int clase = columna - 1;
	int flag;
   	char elementos[100] = {0};

	float valor_f[columna][fila];
	float aux[columna][fila];

	//printf("\n\tClases:\n\t");
    	for(i=0;i<fila;i++) 
	{
        	if(strlen(arr[clase][i])>0) 
		{
            		flag = 1;
            		for(j=0;j<num_clase;j++) 
			{
                		if(strcmp(clases[j], arr[clase][i]) == 0) 
				{
                	 		flag = 0;
					elementos[j]++;
                    			break;
                		}
            		}
            		if(flag) 
			{
                		//printf("%s\n\t", arr[clase][i]);
                		strcpy(clases[num_clase], arr[clase][i]);
				elementos[num_clase]++;
                		num_clase++;
            		}
		}
    	}
	int l=0,r;
	int max;
	int min=0;
	int vf[fila];
	

	for(i=0;i<fila;i++)
	{
		vf[i] = -1;
	}
	srand(time(NULL));
	flag=0;
	for(k=0;k<num_clase;k++)
	{ 
		max = elementos[l]+min; 
		
		for(i=min;i<max;i++)
		{
			while(flag == 0)
			{
				r = min + rand() % (max - min);
    				//printf("\n\tNumero aleatorio entre %d y %d: %d\n", min, max, r);
				for(j=min;j<max;j++)
				{	
					//printf("\n\tR vale: %d",r);
					//printf("\n\tvf[%d] vale: %d",j,vf[j]);
					if(r == vf[j])
					{
						flag=0;
						break;
					}
					else
						flag=1;
				}
			}
			vf[i] = r;
			flag=0;
		}

		//printf("\n\n\tColumna %d:\n\t",k+1);
		//printf("\n\tMin vale: %d\n",min);
		//printf("\n\tMax vale: %d\n",max);
		for(i=min;i<max;i++) 
		{	
			//printf("[");	
      			for(j=0;j<clase;j++) 
			{
					//printf("%s,",arr[j][i-1]);
					valor_f[j][i] = atof(arr[j][i]);
					//printf("\n\tAtof vale: %.2f\n",atof(arr[j][i-1]));
        		}
			//printf("]\n\t");
			/*printf("\n\t[");	
			for(j=0;j<clase;j++)
			{
				printf("%.2f,",valor_f[j][i]);
			}
			printf("]\t");*/
    		}

		//Arreglo ordenado aleatoriamente
		//printf("\n\n\tColumna %d orden aleatorio:\n",k+1);
		for(i=min;i<max;i++) 
		{	
			//printf("\n\t[");
      			for(j=0;j<clase;j++) 
			{
				aux[j][i] = valor_f[j][vf[i]];
				//printf("%.2f,",aux[j][i]);
        		}
			//printf("]\t");
		}

		min = max;
		l++;
	}


	int k_partes=10;
	float fila_k[k_partes - 1];	
	float fila_1k[k_partes - (k_partes - 1)];
	int filaE=0,filaP=0;

	printf("\n\n\tNumero de valores para cada clase:\n");
   	for(i=0;i<num_clase;i++) 
	{
        	printf("\n\tClase %s: %d", clases[i], elementos[i]);
		fila_1k[i] = elementos[i] / (k_partes - 1);
		fila_1k[i] = round(fila_1k[i]);
		fila_k[i] = elementos[i] - fila_1k[i];

		//printf("\n\tFila k menos 1 vale: %.0f",fila_k[i]);
		//printf("\n\tFila k menos fila vale: %.0f\n",fila_1k[i]);
		filaE = fila_k[i] + filaE;
		filaP = fila_1k[i] + filaP;
    	}
	//printf("\n\tFilaE vale: %d",filaE);
	//printf("\n\tFilaP vale: %d",filaP);

	float auxE[columna][filaE];
	float auxP[columna][filaP];

	//printf("\n\n\n\tNuevo arreglo E:\n\t");
	min = 0;
	l = 0;
	for(k=0;k<num_clase;k++) 
	{
		max = fila_k[k] + min;
		//printf("\n\tMin vale: %d",min);
		//printf("\n\tMax vale: %d",max);

		for(i=min;i<max;i++) 
		{	
			//printf("\n\tValor float:\n\t[");	
      			for(j=0;j<clase;j++) 
			{
				auxE[j][l] = aux[j][i];
				//printf("%.2f,",aux70[j][l]);
        		}
			//printf("]\n\n\t");
			l++;	
    		}
		min = max + fila_1k[k];
	}

	printf("\n\n\tConjunto E:\n\t");
	printf("Total de elementos: %d\n",filaE);
	for(i=0;i<filaE;i++) 
	{	
		printf("\n\t[");
      		for(j=0;j<clase;j++) 
		{
			printf("%.2f,",auxE[j][i]);
        	}
		printf("]\t");
	}

	//printf("\n\n\n\tNuevo arreglo P:\n\t");
	min = fila_k[0];
	l = 0;
	for(k=0;k<num_clase;k++) 
	{
		max = fila_1k[k] + min;
		//printf("\n\tMin vale: %d",min);
		//printf("\n\tMax vale: %d",max);

		for(i=min;i<max;i++) 
		{	
			//printf("\n\tValor float:\n\t[");	
      			for(j=0;j<clase;j++) 
			{
				auxP[j][l] = aux[j][i];
				//printf("%.2f,",aux30[j][l]);
        		}
			//printf("]\n\n\t");
			l++;	
    		}
		min = max + fila_k[k+1];
	}

	printf("\n\n\tConjunto P:\n\t");
	printf("Total de elementos: %d\n",filaP);
	for(i=0;i<filaP;i++) 
	{	
		printf("\n\t[");
      		for(j=0;j<clase;j++) 
		{
			printf("%.2f,",auxP[j][i]);
        	}
		printf("]\t");
	}
	printf("\n");
}