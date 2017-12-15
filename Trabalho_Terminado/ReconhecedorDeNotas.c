#include <stdio.h>
#include <stdlib.h>


int Maior(float *arq, int tam, int offset){
	int i = 0, k = 0, indice = 0;
	float aux[tam];
	float aux2 = 0;

	for(i = 0; i < tam; i++){ //inicializando vetor auxiliar
		//printf("P0%d: %f\n",i, arq[i]);
		aux[i] = arq[i];
	}
		aux2 = arq[0];
		for(i = 0; i < tam; i++){
			if(aux2 < aux[i]){
				//printf("aux[i]: %f\n",aux[i] );
				k = i;
				aux2 = aux[i];
			}	
		}
		indice = k + offset;
		//printf("Posição: %d + %d = %d\n",k, offset, indice );
		return indice;
		
}


int reconhecerNota(float *realFreqNotas, float freq_aux){
		float sub1 = 0, sub2 = 0;
		int ref = 0, i = 0;
	
		
		sub1 = realFreqNotas[0] - freq_aux;
		sub2 = 0;
		ref = 0;
		if(sub1 < 0){
			sub1 *= -1;
		}

		for(i = 0; i < 8; i++ ){
			sub2 = realFreqNotas[i] - freq_aux;
			if(sub2 < 0){
				sub2 *= -1;
			}

			if(sub2 < sub1){
				sub1 = sub2;
				ref = i;
			}
		}

		return ref;
		
}

void main(){
	FILE *pks = fopen("pks.txt","r");
	FILE *idx = fopen("idx.txt","r");

	float sum = 0, aux = 0;
	int count  = 0, count2 = 0, i = 0, ref = 0, k = 0, j = 0;
	int posicoes = 0;
	float tres[3] = {0,0,0};
	

	fseek(pks, 0, SEEK_END);
	int tam  =  ftell(pks)/8;
//	fseek(pks, SEEK_END, SEEK_SET);
	rewind(pks);

	//printf("Tam: %d\n",tam );

	float picos[tam];
	float freq[tam];

	while(fscanf(pks, "%f",&picos[count]) != EOF){
		//printf("Pico0%d: %f\n", count,picos[count]);

		count++;
	}
	
	count = 0;
	while(fscanf(idx, "%f",&freq[count]) != EOF){
		//printf("Freq0%d: %f\n", count,freq[count]);
		count ++;
	
	}
	tam = count;
	count = 0;

	float picos_aux[tam];
	float freq_aux = 0;


	//printf("PS: %ld\n", sizeof(picos)/sizeof(float));
	//printf("FS: %ld\n", sizeof(freq)/sizeof(float));

	float realFreqNotas[8] = {523.25113, 587.32954, 659.25511, 698.45646, 783.99087, 880, 987.766, 1046.5023};
	//printf("tam: %d\n",tam );

	count2 = 0;
	int flag = 1;

	for(i = 0; i < tam; i++){

		if(picos[i] != 111){
			picos_aux[k] = picos[i];
			//printf("PA0%d: %f\n",k,picos_aux[k] );
			k++;
		}else{
			k= k+1;
			/*printf("\n\n");
			printf("Ops: %f\n", picos[i]);
			printf("K: %d\n",k );
			printf("Offset: %d\n",count2 );*/
			posicoes = Maior(picos_aux, k-1, count2);

			freq_aux = freq[posicoes];

			count2+=k;
			flag = 0;
			k = 0;

			printf("\n");
			if((freq_aux < 520) || (freq_aux > 1050)){
				printf("\t#########  RUIDO ########\n");
				continue;
			}
			//printf("F: %f\n", freq_aux );


			

			ref = reconhecerNota(realFreqNotas, freq_aux);
			printf("\t------------------------\n");
			switch(ref){
				case 0:
					printf("\t\tDÓ5\n");
				break;
				case 1:
					printf("\t\tRÉ5\n");
				break;
				case 2:
					printf("\t\tMI5\n");
				break;
				case 3:
					printf("\t\tFÁ5\n");
				break;
				case 4:
					printf("\t\tSOL5\n");
				break;
				case 5:
					printf("\t\tLÁ5\n");
				break;
				case 6:
					printf("\t\tSI5\n");
				break;
				case 7:
					printf("\t\tDÓ6\n");

			}
			printf("\t------------------------\n");
		}
	}
}