/**
*
* UNIVERSIDADE DO ESTADO DO AMAZONAS
* Adriano Freitas - adrianofreitas.me
*
*/
#include <stdio.h>
#include <stdlib.h>

/**
* Struct com os atributos do processo
* pid, duracao, prioridade, tempo de execucao, tempo de espera
*/
typedef struct processos{
    int pid;
    int duracao;
    int prioridade;
    int execucao;
    int espera;
    struct processos *prox;
}Processo;

/**
* Funcao do tipo Processo
* que inicia um processo, recebe os parametros pid, prioridade, duracao
*/
Processo *init_process (int pid, int duracao, int prioridade) {
    Processo *processo;
    //aloca dinamicamento o processo na memoria
    processo = (Processo*)malloc(sizeof(Processo));
    //caso a alocacao falhe o programa e encerrado
    if (processo == NULL) exit(1);

    processo->pid = pid;
    processo->duracao = duracao;
    processo->prioridade = prioridade;
    processo->execucao = 0;
    processo->espera = 0;
    processo->prox = NULL;
    return(processo);
};

void listarProcessos (Processo *processo) {
  Processo *tmp = processo;
  printf("PROCESSOS\n\n");
  printf("PID\tUSER    \tTIME\tPRI\n");
  while (tmp != NULL) {
    printf("%d\tafreitas\t%d\t%d\n", tmp->pid, tmp->duracao, tmp->prioridade);
    tmp = tmp->prox;
  };
  printf("\n\n");
 }


/**
* Funcao de escalonamento Round-Robin
*/
void round_robin (Processo *processo, int quantum) {
  int jobsremain, passes;

  Processo *copia, *tmpsrc, *tmp, *slot;
  printf("Escalonamento Round-Robin\tQuantum: %d\n", quantum);
  printf("\n");
  tmpsrc = processo;
  copia = tmp = NULL;

  while (tmpsrc != NULL) {
    if (copia == NULL) {
    copia = init_process(tmpsrc->pid, tmpsrc->duracao, tmpsrc->prioridade);
    tmp = copia;
    } else {
    tmp->prox = init_process(tmpsrc->pid, tmpsrc->duracao, tmpsrc->prioridade);
    tmp = tmp->prox;
    };
    tmpsrc = tmpsrc->prox;
  };

  /* Programa rotina de an�lise de prioridade  */
  jobsremain = 2;
  slot = NULL;
  //int x=0;
  while (jobsremain) {
    //x++;
    jobsremain = 0;
    /* Seleciona o pr�ximo processo efetuando sua aloca��o */
    if (slot == NULL) {
    slot = copia;
    jobsremain = 2;
    } else {
      passes = 0;
      do {
        if (slot->prox == NULL) {
          passes++;
          slot = copia;
        } else {
          slot = slot->prox;
        };
      } while (passes <= 3 && slot->duracao == slot->execucao);

      if (passes <= 3) {
        jobsremain = 2;
      }
    }
    /* Executa um ciclo */
    tmp = copia;
    while (tmp != NULL) {
    if (tmp->duracao > tmp->execucao) {
      if (tmp == slot) {
        tmp->execucao += quantum;
      } else {
        tmp->espera += quantum;
      };
    };
    tmp = tmp->prox;
    };
  };
  /* Exibe os resultados e elimina as replica��es */
  tmp = copia;

  printf("PID\tUSER    \tTIME\tWAIT\tRETURN\n");
  while (tmp != NULL) {
    printf("%d\tafreitas\t%d\t%d\t%d\n", tmp->pid, tmp->duracao, tmp->espera, tmp->execucao + tmp->espera  );
    tmpsrc = tmp;
    tmp = tmp->prox;
    free(tmpsrc);
  };

  printf("\n");
};

/**
* Funcao Principal
*/
int main (void)
{
    Processo *plist, *ptmp;
    plist       = init_process(100, 3, 1);
    plist->prox = init_process(101, 2, 2); ptmp = plist->prox;
    ptmp->prox  = init_process(102, 1, 3); ptmp = ptmp->prox;
    ptmp->prox  = init_process(103, 2, 2); ptmp = ptmp->prox;
    ptmp->prox  = init_process(104, 3, 1);

    listarProcessos(plist);
    round_robin(plist,2);

    while (plist != NULL) {
        ptmp = plist;
        plist = plist->prox;
        free(ptmp);
    };
    return(0);
}
