//---------------------------------------------------------------------
// Arquivo      : geracarga.c
// Conteudo     : gerador de carga para o ordenador de URLs 
// Autor        : Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico    : 2021-12-23 - arquivo criado
//---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <unistd.h>
#include <getopt.h>
#include "msgassert.h"

const double DBL_EPS_COMP = 1 - DBL_EPSILON; 

double RandU() 
// Descricao: gera um numero aleatorio (distribuicao uniforme) entre 0 e 1
// Entrada: nenhuma
// Saida: numero aleatorio
{
    return DBL_EPSILON + ((double) rand()/RAND_MAX);
}

double RandN2(double mu, double sigma) 
// Descricao: gera um numero aleatorio 
//            (distribuicao normal, media mu e variancia sigma)
// Entrada: mu e sigma
// Saida: numero aleatorio
{
  return mu+(rand()%2?-1.0:1.0)*sigma*pow(-log(DBL_EPS_COMP*RandU()),0.5);
}

double RandN() 
// Descricao: gera um numero aleatorio 
//            (distribuicao normal, media 0 e variancia 1)
// Entrada: nenhuma
// Saida: numero aleatorio
{
    return RandN2(0, 1.0);
}

// estrutura de dados que contem os parametros
typedef struct prm{
  char nomesaida[1000];
  double urls, prof, varprof, pop, varpop;
} prmGeracao;

void uso()
// Descricao: imprime as instrucoes de uso do programa
// Entrada:  N/A
// Saida: instrucoes
{
  fprintf(stderr,"geracarga\n");
  fprintf(stderr,"\t-o <arq>\t(arquivo de saida) \n");
  fprintf(stderr,"\t-u <num>\t(URLs)\n");
  fprintf(stderr,"\t-p <num>\t(profundidade URL)\n");
  fprintf(stderr,"\t-q <num>\t(variancia profundidade URL)\n");
  fprintf(stderr,"\t-r <num>\t(popularidade URL)\n");
  fprintf(stderr,"\t-s <num>\t(variancia popularidade URL)\n");
  fprintf(stderr,"\t-h\t(opcoes de uso)\n");
}

void parse_args(int argc,char ** argv, prmGeracao * prm)
// Descricao: analisa a linha de comando a inicializa variaveis
// Entrada: argc e argv
// Saida: prm
{
     extern char * optarg;
     extern int optind;
     int c ;
     // valores padrao
     prm->nomesaida[0] = 0;
     prm->urls = 10;
     prm->prof = 3;
     prm->varprof = 1;
     prm->pop = 100;
     prm->varpop = 30;
     // percorre a linha de comando buscando identificadores
     while ((c = getopt(argc, argv, "o:u:p:q:r:s:h")) != EOF)
       switch(c) {
         case 'o':
	          // arquivo de saida
	          strcpy(prm->nomesaida,optarg);
                  break;
         case 'u':
	          // numero medio de urls
	          prm->urls = atof(optarg);
		  break;
         case 'p':
	          // profundidade media 
	          prm->prof = atof(optarg);
		  break;
         case 'q':
	          // variancia da profundidade media
	          prm->varprof = atof(optarg);
		  break;
         case 'r':
	          // popularidade media 
	          prm->pop = atof(optarg);
		  break;
         case 's':
	          // variancia da popularidade
	          prm->varpop = atof(optarg);
		  break;
         case 'h':
         default:
                  uso();
                  exit(1);

       }
       // verifica apenas o nome do arquivo de saida
       erroAssert(prm->nomesaida[0],"Arquivo de saida nao definido.");
}

void gerapalavra(int tam, char * ret)
// Descricao: gera uma palavra aleatoria 
// Entrada: tam
// Saida: ret
{
  int i;
  for (i=0; i<tam; i++){
    ret[i] = (char)(rand()%26)+'a';
  }
  ret[tam] =0;
}


int main(int argc, char ** argv){
  int pop,i,j,k,szserv,tampal,auxprof,retclose;
  prmGeracao prm;
  char auxstr[1000],auxurl[1000];
  FILE * out;

  parse_args(argc,argv,&prm);

  out = fopen(prm.nomesaida,"wt");
  erroAssert(out!=NULL,"Erro no fopen");

  // gera carga de trabalho
  for (i=0; i<prm.urls; i++){
    strcpy(auxurl,"http://");
    szserv = (int) RandN2(3.0,1.0);
    szserv=(szserv==0?1:szserv);
    for (j=0; j<szserv; j++){
      tampal = (int) RandN2(6.0,2.0);
      tampal=(tampal<3?3:tampal);
      gerapalavra(tampal,auxstr); 
      strcat(auxurl,auxstr);
      strcat(auxurl,".");
    }
    strcat(auxurl,"com/");
    // sorteia a profundidade
    auxprof = (int) RandN2(prm.prof,prm.varprof);
    // gera a URL
    for (k=0;k<auxprof;k++){
      tampal = (int) RandN2(6.0,2.0);
      gerapalavra(tampal,auxstr); 
      strcat(auxurl,auxstr);
      strcat(auxurl,"/");
    }
    // sempre termina com um arquivo html
    tampal = (int) RandN2(6.0,2.0);
    gerapalavra(tampal,auxstr); 
    strcat(auxurl,auxstr);
    strcat(auxurl,".html");
    pop = -1;
    while (pop<0){
      pop = (int) RandN2(prm.pop, prm.varpop);
    }
    fprintf(out,"%s %d\n",auxurl,pop);
  }
  // gera as demais tarefas
  retclose = fclose(out);
  erroAssert(retclose==0,"Erro no fclose");
  return 0;
}
