 /*****************************************************************//**
  * @file: FuncoesMaquinas.c
  * @author: André Filipe da Silva Castro
  * @e-mail: andrefilipedasilvacastro123@gmail.com
  * @e-mail: a22768@alunos.ipca.pt
  * @date:  16 May 2022
  *********************************************************************/

#include "Funcoes.h"


 /**
  * .
  * @brief Cria nova Maquina
  * @param novoCod codigo da maquina
  * @param novoTempo tempo da maquina
  * @return
  */
Maquina* CriaMaquina(int novoCod, int novoTempo) {
	Maquina* nova = (Maquina*)malloc(sizeof(Maquina)); //Aloca memória necessária para armazenar uma Maquina em memória
	nova->codigoMaquina = novoCod;
	nova->tempo = novoTempo;
	return nova;
}


/**
 * .
 * @brief Cria novo nodo para a Lista de Maquinas
 * Copia para o nodo da lista a informação de uma Maquina
 * @param c nova maquina
 * @return
 */
ListaMaquinas* CriaNodoListaMaquinas(Maquina* c) {
	ListaMaquinas* nova = (ListaMaquinas*)calloc(sizeof(ListaMaquinas));
	nova->maquina.codigoMaquina = c->codigoMaquina;
	nova->maquina.tempo = c->tempo;
	nova->next = NULL;
	return nova;
}


/**
 * .
 * @brief Insere Maquina na Lista de Maquinas
 * @param [in] Apontador para o inicio da lista de maquinas
 * @param m maquina criada
 * @return
 */
ListaMaquinas* InsereMaquinaListaMaquina(ListaMaquinas* h, Maquina* m) {
	if (m == NULL) return h;	//se nova não tem dados
	//Cria novo nodo da lista de pessoas
	ListaMaquinas* nova = CriaNodoListaMaquinas(m);
	if (h == NULL) h = nova; //se lista é vazia
	else {					//insere ordenado pelo m
		nova->next = h;
		h = nova;
	}
	return h;
}


/**
 * .
 * @brief Procura Maquina
 * @param [in] Apontador para o inicio da lista de maquinas
 * @param cod codigo da maquina a procurar
 * @return
 */
ListaMaquinas* ProcuraMaquina(ListaMaquinas* inicio, int cod) {
	ListaMaquinas* aux = inicio;
	while (aux) {
		if (aux->maquina.codigoMaquina == cod) return aux; //se encontrou
		aux = aux->next;
	}
	return NULL;			//se não encontrou
}


/**
 * .
 * @brief Remove maquina
 * @param [in] Apontador para inicio da Lista
 * @param cod codigo da maquina a remover
 * @param [out] Apontador para inicio da Lista
 */

ListaMaquinas* RemoveMaquina(ListaMaquinas* h, int cod) {

	if (h == NULL) return NULL;    //Lista vazia
	else
	{
		ListaMaquinas* aux = h;
		ListaMaquinas* auxAnt = NULL;

		//caso seja a primeira maquina a ser removida
		if (aux && aux->maquina.codigoMaquina != cod) {
			h = aux->next;
			free(aux);
			return h;
		}
		else
		{
			auxAnt = aux;
			aux = aux->next;
		}

		while (aux && aux->maquina.codigoMaquina != cod) {   //procura para remover
			auxAnt = aux;
			aux = aux->next;
		}
		if (aux != NULL) {        //se encontrou, remove
			auxAnt->next = aux->next;
			free(aux); //limpar o espaco do armazenamento da maquina removida
		}
	}
	return h;
}


/**
 * .
 * @brief Remove todas as maquinas
 * @param [in] Apontador para inicio da Lista
 * @param [out] Apontador para inicio da Lista
 */

ListaMaquinas* RemoveTodasMaquinas(ListaMaquinas* h) {

	if (h == NULL) return NULL;    //Lista vazia

	else {

		ListaMaquinas* aux = h;

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
 * @brief Alterar tempo e codigo da Maquina
 * @param [in] Apontador para inicio da Lista
 * @param cod Codigo da maquina a alterar
 * @param novoTempo novo tempo da maquina
 * @param novoCod novo codigo da maquina
 * @param [out] Apontador para inicio da Lista
 */
ListaMaquinas* AlteraMaquina(ListaMaquinas* h, int cod, int novoTempo, int novoCod) {
	ListaMaquinas* aux = ProcuraMaquina(h, cod);
	if (aux != NULL)        //se encontrou a maquina, returnou o aux
	{
		aux->maquina.tempo = novoTempo;
		aux->maquina.codigoMaquina = novoCod;
	}
	return h;
}


/**
 * .
 * @brief Mostra todas as maquinas existentes
 * @param [in]  Apontador para inicio da Lista
 */

void MostraTodasMaquinas(ListaMaquinas* h) {
	ListaMaquinas* aux = h;
	if (h != NULL) {

		if (aux) {
			while (aux) {
				printf("\n Maquina numero: %d", aux->maquina.codigoMaquina);
				printf("\n Demora %d para realizar a operacao", aux->maquina.tempo);
				printf("\n-----------------------------------------------");
				aux = aux->next;
			}

		}
		else
		{
			printf("\n Não existem maquinas");
		}
	}
	else
	{
		printf("\n Lista vazia");
	}
}



/**
 * .
 * @brief Mostra uma das maquinas existentes (caso exista)
 * @param [in] Apontador para inicio da Lista
 * @param cod codigo da maquina a mostrar
 */

void MostraUmaMaquina(ListaMaquinas* inicio, int cod) {
	ListaMaquinas* aux = inicio;
	if (inicio != NULL) {
		aux = ProcuraMaquina(inicio, cod);
		if (aux) {
			ListaMaquinas* inicioOperacoes = aux;
			printf("\n Maquina numero: %d", aux->maquina.codigoMaquina);
			printf("\n Demora %d para realizar a operacao", aux->maquina.tempo);
			printf("\n-----------------------------------------------");
		}
		else
		{
			printf("Não existe nenhuma maquina com este codigo!");
		}
	}
	else
	{
		printf("\n Lista vazia");
	}
}
