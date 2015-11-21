#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define FALSO 0
#define VERDADE 1
#define P1_MAIS_INFINITO 2
#define INFINITO_MAIS_P2 3
#define NEGATIVO -1
typedef long long bigint;
bigint primo;

typedef struct Ponto {
	bigint x;
	bigint y;
} ponto;

int igualdade(ponto* P1, ponto *P2){
	if( ( P1->x==0 && P1->y==0 ) && (P2->x != 0 ||  P2->y!= 0)) return INFINITO_MAIS_P2;
	else if(P1->x == P2->x && P1->y == (primo - (P2->y)) % primo) return NEGATIVO;
	else if((P2->x==0 && P2->y==0 ) && (P1->x != 0 ||  P1->y!= 0)) return P1_MAIS_INFINITO;
	else if(P1->x == P2->x && P1->y == P2->y ) return VERDADE;
	return FALSO;
}

//usa o euclides extendido, retorna o inverso
bigint inverso(bigint num, bigint mod){
	bigint inv=1,inv_2=0,resto, div,tam = mod, true_num = num;
	while(mod){
		div = num / mod;
		resto = num % mod;
		
		bigint temp = inv_2;
		inv_2 = inv - div * inv_2;
		inv = temp;
		
		num = mod;
		mod= resto;
	}
	if(inv < 0) inv += tam;
	
	if( ((true_num * inv) % tam) == 1) return  inv;
	return 0;
}

ponto *dobro_ponto(ponto *G,bigint a){
	ponto* saida = (ponto *)malloc(sizeof(ponto));
	bigint equa_parte_cima, equa_parte_baixo,lambda;
	
	//descobre lambda
	equa_parte_cima = (3*(G->x*G->x)+a) % primo;
	
	equa_parte_baixo = (2*G->y) % primo;
	if(equa_parte_baixo<0)equa_parte_baixo+=primo;
	bigint inv_baixo = inverso(equa_parte_baixo, primo);
	lambda = (equa_parte_cima*inv_baixo) % primo;
	
	
	//calcula P(Xsaida, Ysaida)
	saida->x = ((lambda*lambda) - G->x - G->x) % primo;
	saida->y = (lambda*(G->x - saida->x) - G->y) % primo;
	//printf("saida-x : %lld saida-y %lld\n", saida->x,saida->y);
	if(saida->x < 0) saida->x+=primo;
	if(saida->y < 0) saida->y+=primo;
	return saida;
}

ponto *soma_pontos(ponto *G,ponto *Q){
	ponto *saida = (ponto*) malloc(sizeof(ponto));
	bigint lambda, equa_parte_cima, equa_parte_baixo,inv_baixo;
	//lambda
	equa_parte_cima = (G->y - Q->y) % primo;
	equa_parte_baixo = (G->x - Q->x) % primo;
	if(equa_parte_baixo<0)equa_parte_baixo+=primo;
	inv_baixo = inverso(equa_parte_baixo,primo);

	lambda = equa_parte_cima*inv_baixo % primo;
	//calcula P(Xsaida, Ysaida)
	saida->x = ((lambda*lambda) - Q->x - G->x) % primo;

	saida->y = ( lambda*(Q->x - saida->x) - Q->y) % primo;
	//printf("lambda: %lld\n", lambda);
	if(saida->x < 0) saida->x+=primo;
	if(saida->y < 0) saida->y+=primo;
	return saida;
}


ponto *soma(ponto* G, bigint n,bigint a) {
	bigint i;
	if(n==1) return G;
	ponto *R_temp=dobro_ponto(G,a), *G_temp=G;
	for(i=2;i<n;i++){
		//printf("i:%lld G(%lld,%lld) R(%lld,%lld)\n",i,G->x,G->y,R_temp->x,R_temp->y);
		int opcao = igualdade(G,R_temp);
		switch(opcao){
			case NEGATIVO:
				R_temp->x = 0;
				R_temp->y = 0;
				break;
			case FALSO:
				R_temp = soma_pontos(G,R_temp);
				break;
			case VERDADE:
				R_temp = dobro_ponto(G,a);
				break;
			case P1_MAIS_INFINITO:
				R_temp->x = G->x;
				R_temp->y = G->y;
				break;
		}
	}
	return R_temp;
}

int main (){
	bigint a,n;
	ponto G,*R,*Q;
	while(1){
		scanf("%lld", &n);
		if(n==0) break;
		scanf("%lld %lld %lld %lld", &a, &primo,&G.x,&G.y);

		R = soma(&G,n,a);

		printf("%lld %lld\n", R->x, R->y);
	}
}
