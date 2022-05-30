/*****************************************************************//**
 * @file: FuncoesJobs.c
 * @author: André Filipe da Silva Castro
 * @e-mail: andrefilipedasilvacastro123@gmail.com
 * @e-mail: a22768@alunos.ipca.pt
 * @date:  16 May 2022
 *********************************************************************/

#include "Funcoes.h"


 /**
  * @brief Criar novo Job
  * @param novoCod codigo do job
  * @param nome
  * @return
  */

Job* CriaJobs(int novoCod, char nome[N]) {
	Job* nova = (Job*)malloc(sizeof(Job)); //Aloca memória necessária para armazenar um Job em memória
	nova->codigoJob = novoCod;
	strcpy(nova->nome, nome);
	return nova;
}
/**
 * .
 * @brief Cria novo nodo para a Lista de Jobs
 * Copia para o nodo da lista a informação de um Job
 * @param [in] j novo job
 * @param [out] apontador para o nodo criado
 */
ListaJobs* CriaNodoListaJobs(Job* j) {
	ListaJobs* nova = (ListaJobs*)calloc(sizeof(ListaJobs));
	nova->job.codigoJob = j->codigoJob;
	strcpy(nova->job.nome, j->nome);
	nova->listaOperacoes = NULL;
	nova->next = NULL;
	return nova;
}

/**
 * @brief Insere Job na Lista de Jobs
 * @param [in] j Novo job
 * @param [in] Apontador para o inicio da lista
 * @param [out] Aapontador para o inicio da lista
 */

ListaJobs* InsereJobsListaJobs(ListaJobs* h, Job* j) {
	if (j == NULL) return h;	//se nova não tem dados

	 /*Cria novo nodo da lista de pessoas*/
	ListaJobs* nova = CriaNodoListaJobs(j);
	if (h == NULL) h = nova;	//se lista é vazia
	else {					//insere ordenado pelo
		nova->next = h;
		h = nova;
	}
	return h;
}

/**
 * .
 * @brief Procura um Job
 * @param inicio inicio da lista de jobs
 * @param cod Codigo do job
 * @return
 */

ListaJobs* ProcuraJob(ListaJobs* inicio, int cod) {
	ListaJobs* aux = inicio;
	while (aux) {
		if (aux->job.codigoJob == cod) return aux;	//se encontrou
		aux = aux->next;
	}
	return NULL; //se não encontrou
}

/**
 * .
 * @brief Insere uma Operacao num Job
 * @param [in] o operação
 * @param [in] codJob codigo do Job
 * @param [in] Apontador para o inicio da lista
 * @param [out] Apontador para o inicio da  lista
 */

ListaJobs* InsereOperacaoJobs(ListaJobs* h, Operacao* o, int codJob) {
	if (h == NULL) return NULL;	// se lista vazia
	if (codJob == NULL) return h;	//se operação não tem informação
	ListaJobs* aux = ProcuraJob(h, codJob);
	if (aux) {		//se existe esse job
		aux->listaOperacoes = InsereOperacaoListaOperacao(aux->listaOperacoes, o);
	}
	return h;
}


/**
 * @brief Remover Job
 * @param cod Codigo do Job a remover
 * @param [in] Apontador para inicio da Lista
 * @param [out] Apontador para inicio da Lista
 */


ListaJobs* RemoveJob(ListaJobs* h, int cod) {

	if (h == NULL) return NULL;  //Lista vazia
	else
	{
		ListaJobs* aux = h;
		ListaJobs* auxAnt = NULL;

		//caso seja a primeira operacao a ser removida
		if (aux && aux->job.codigoJob != cod) {

			ListaOperacoes* aux2 = aux->listaOperacoes;
			ListaOperacoes* aux3 = NULL;

			if (aux2 != NULL) {

				while (aux2 != NULL) { //apaga as operacoes dentro de um job

					ListaMaquinas* aux4 = aux2->listaMaquinas;
					ListaMaquinas* aux5 = NULL;

					if (aux4 != NULL) {

						while (aux4 != NULL) {  //apaga as maquinas dentro de uma operacao//
							aux5 = aux4->next;
							free(aux4);
							aux4 = aux5;

						}
					}

					aux3 = aux2->next;
					free(aux2);
					aux2 = aux3;

				}
			}

			h = aux->next;
			free(aux);
			return h;
		}
		else
		{
			auxAnt = aux;
			aux = aux->next;
		}

		while (aux && aux->job.codigoJob != cod) {  //procura para remover
			auxAnt = aux;
			aux = aux->next;
		}

		if (aux != NULL) { //se encontrou, remove

			ListaOperacoes* aux2 = aux->listaOperacoes;
			ListaOperacoes* aux3 = NULL;

			if (aux2 != NULL) {

				while (aux2 != NULL) { //apaga as operacoes dentro de um job

					ListaMaquinas* aux4 = aux2->listaMaquinas;
					ListaMaquinas* aux5 = NULL;

					if (aux4 != NULL) {

						while (aux4 != NULL) {  //apaga as maquinas dentro de uma operacao
							aux5 = aux4->next;
							free(aux4);
							aux4 = aux5;

						}
					}

					aux3 = aux2->next;
					free(aux2);
					aux2 = aux3;

				}
			}

			auxAnt->next = aux->next;
			free(aux);  //limpar o espaco do armazenamento da operacao removida
		}
	}
	return h;
}

ListaJobs* RemoveJob2(ListaJobs* h, int cod) {

	if (h == NULL) return NULL;     //Lista vazia

	else
	{
		ListaJobs* aux = h;
		ListaJobs* auxAnt = NULL;

		//caso seja a primeira operacao a ser removida
		if (aux && aux->job.codigoJob != cod) {

			ListaOperacoes* aux2 = aux->listaOperacoes;
			ListaOperacoes* aux3 = NULL;

			if (aux2 != NULL) {

				while (aux2 != NULL) { //apaga as operacoes dentro de um job

					ListaMaquinas* aux4 = aux2->listaMaquinas;
					ListaMaquinas* aux5 = NULL;

					if (aux4 != NULL) {

						RemoveTodasMaquinas(aux4);

					}

					RemoveTodasOperacoes(aux2);
				}
			}

			h = aux->next;
			free(aux);
			return h;
		}
		else
		{
			auxAnt = aux;
			aux = aux->next;
		}

		while (aux && aux->job.codigoJob != cod) {  //procura para remover
			auxAnt = aux;
			aux = aux->next;
		}

		if (aux != NULL) { //se encontrou, remove

			ListaOperacoes* aux2 = aux->listaOperacoes;
			ListaOperacoes* aux3 = NULL;

			if (aux2 != NULL) {

				while (aux2 != NULL) { //apaga as operacoes dentro de um job

					ListaMaquinas* aux4 = aux2->listaMaquinas;
					ListaMaquinas* aux5 = NULL;

					if (aux4 != NULL) {

						while (aux4 != NULL) {  //apaga as maquinas dentro de uma operacao
							aux5 = aux4->next;
							free(aux4);
							aux4 = aux5;

						}
					}

					aux3 = aux2->next;
					free(aux2);
					aux2 = aux3;

				}
			}

			auxAnt->next = aux->next;
			free(aux);  //limpar o espaco do armazenamento da operacao removida
		}
	}
	return h;
}


/**
 * .
 * @brief Remove Todos os Jobs
 * @param [in] Apontador para inicio da Lista
 * @param [out] Apontador para inicio da Lista
 */

ListaJobs* RemoveTodosJobs(ListaJobs* h) {

	if (h == NULL) return NULL;    //Lista vazia

	else {

		ListaJobs* aux = h;

		while (aux != NULL) {

			//caso seja a primeira maquina a ser removida
			if (aux) {
				h = aux->next;
				free(aux);
				aux = h;
			}
		}
	}
	return h;
}



/**
 * .
 * @brief Altera codigo e nome da Operacao
 * @param cod  Codigo da Operacao a alterar
 * @param novoCod novo codigo da Operacao
 * @param novoNome novo nome da Operacao
 * @param [in] Apontador para o incio da lista
 * @param [out] Apontador para o incio da lista
 */
ListaJobs* AlteraJob(ListaJobs* h, int cod, int novoCod, char* novoNome) {
	ListaJobs* aux = ProcuraJob(h, cod);
	if (aux != NULL)   //se encontrou a operacao
	{
		aux->job.codigoJob = novoCod;
		strcpy(aux->job.nome, novoNome);
	}
	return h;
}

/**
 * .
 * @brief Mostra todas os Jobs existentes
 * @param [in] Apontador para o incio da lista
 */
void MostraTodosJobs(ListaJobs* h) {
	ListaJobs* aux = h;
	if (h != NULL) {
		if (aux) {
			while (aux) {
				printf("\n Job numero: %d", aux->job.codigoJob);
				printf("\n O nome desta job é: %s", aux->job.nome);
				printf("\n-----------------------------------------------");
				aux = aux->next;
			}
		}
		else
		{
			printf("Não existem Jobs");
		}
	}
	else
	{
		printf("\n Lista vazia");
	}
}

/**
 * .
 * @brief Mostra um dos Jobs existentes(caso exista)
 * @param [in] Apontador para o incio da lista
 * @param cod codigo do job
 */
void MostraUmJob(ListaJobs* inicio, int cod) {
	ListaJobs* aux = inicio;
	if (inicio != NULL) {

		aux = ProcuraJob(inicio, cod);
		if (aux) {
			ListaJobs* inicioJobs = aux;
			printf("\n Job numero: %d", aux->job.codigoJob);
			printf("\n O nome deste job é: %s", aux->job.nome);
		}
		else
		{
			printf("Não existem Jobs com o codigo intruduzido");
		}
	}
	else
	{
		printf("\n Lista vazia");
	}
}

/**
 * .
 * @brief Mostra as operações e as maquinas de um job
 * @param [in] Apontador para o incio da lista
 * @param codJob codigo do job
 */

void MostraMaquinasOperacoesJob(ListaJobs* inicio, int codJob) {
	ListaJobs* aux = inicio;
	if (inicio != NULL) {
		if (aux) {
			aux = ProcuraJob(inicio, codJob);
			if (aux) {
				MostraUmJob(inicio, codJob);
				ListaOperacoes* inicioOperacao = aux->listaOperacoes;
				MostraMaquinasOperacoes(inicioOperacao);
			}
		}
		else
		{
			printf("Não existem Jobs,logo não temos operações e maquinas associadas!");
		}
	}
	else
	{
		printf("\n Lista vazia");
	}
}

/**
 * .
 * @brief Mostra as maquinas e operaçoes de todos os jobs
 * @param [in] Apontador para o incio da lista
 */

void MostraMaquinasOperacoesJobs(ListaJobs* inicio) {
	ListaJobs* aux = inicio;
	if (inicio != NULL) {
		if (aux) {
			while (aux)
			{
				MostraUmJob(inicio, aux->job.codigoJob);
				ListaOperacoes* inicioOperacao = aux->listaOperacoes;
				MostraMaquinasOperacoes(inicioOperacao);
			}
		}
		else
		{
			printf("Não existem Jobs,logo não temos operações e maquinas associadas!");
		}
	}
	else
	{
		printf("\n Lista vazia");
	}

}
