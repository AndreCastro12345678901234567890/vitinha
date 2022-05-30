/*****************************************************************//**
 * @file: FuncoesOperações.c
 * @author: André Filipe da Silva Castro
 * @e-mail: andrefilipedasilvacastro123@gmail.com
 * @e-mail: a22768@alunos.ipca.pt
 * @date:  16 May 2022
 *********************************************************************/

#include "Funcoes.h"


 /**
  * .
  * @brief Cria nova Operacao
  * Aloca memória necessária para armazenar uma Operação em memória
  * @param novoCod Código da Operacao
  * @param nome Nome da Operacao
  * @return
  */

Operacao* CriaOperacao(int novoCod, char nome[N]) {
	Operacao* nova = (Operacao*)malloc(sizeof(Operacao));
	nova->codigoOperacao = novoCod;
	strcpy(nova->nome, nome);
	return nova;
}


/**
 * .
 * @brief Cria novo nodo para a Lista de Operações
 * Copia para o nodo da lista a informação de uma Operação
 * @param o operacao criada
 * @return
 */
ListaOperacoes* CriaNodoListaOperacoes(Operacao* o) {
	ListaOperacoes* nova = (ListaOperacoes*)calloc(sizeof(ListaOperacoes));
	nova->operacao.codigoOperacao = o->codigoOperacao;
	strcpy(nova->operacao.nome, o->nome);
	nova->listaMaquinas = NULL;
	nova->next = NULL;
	return nova;
}

/**
 * .
 * @brief Insere Operação na Lista de Operações
 * @param [in] o Nova Operação
 * @param [in] Apontador para o inicio da lista
 * @return
 */
ListaOperacoes* InsereOperacaoListaOperacao(ListaOperacoes* h, Operacao* o) {
	if (o == NULL) return h;	//se nova não tem dados
	//Cria novo nodo da lista de pessoas
	ListaOperacoes* nova = CriaNodoListaOperacoes(o);
	if (h == NULL) h = nova;	//se lista é vazia
	else {					//	insere ordenado pelo nc
		nova->next = h;
		h = nova;
	}
	return h;
}

/**
 * .
 * @brief Procura Operação
 * @param [in] Apontador para o inicio da lista
 * @param cod codigo da operação a procurar
 * @return
 */

ListaOperacoes* ProcuraOperacao(ListaOperacoes* inicio, int cod) {
	ListaOperacoes* aux = inicio;
	while (aux) {
		if (aux->operacao.codigoOperacao == cod) return aux;	//se encontrou
		aux = aux->next;
	}
	return NULL;			//se não encontrou
}


/**
 * .
 * @brief Insere Maquina numa Operação
 * @param [in] Apontador para o inicio da lista
 * @param m maquina a inserir
 * @param codOperacao
 * @param [out] Apontador para o inicio da lista
 */

ListaOperacoes* InsereMaquinaOperacao(ListaOperacoes* h, Maquina* m, int codOperacao) {
	if (h == NULL) return NULL;	// se lista vazia
	if (codOperacao == NULL) return h;	//se contacto não tem informação

	ListaOperacoes* aux = ProcuraOperacao(h, codOperacao);
	if (aux) {		//se existe essa operação
		aux->listaMaquinas = InsereMaquinaListaMaquina(aux->listaMaquinas, m);
	}
	return h;
}


/**
 * .
 * @brief Remover Opercação
 * @param [in] Apontador para o inicio da lista
 * @param cod codigo da operação a remover
 * @param [out] Apontador para o inicio da lista
 */
ListaOperacoes* RemoveOperacao(ListaOperacoes* h, int cod) {

	if (h == NULL) return NULL;            //Lista vazia

	else
	{
		ListaOperacoes* aux = h;
		ListaOperacoes* auxAnt = NULL;

		//caso seja a primeira operacao a ser removida
		if (aux && aux->operacao.codigoOperacao != cod) {

			ListaMaquinas* aux2 = aux->listaMaquinas;
			ListaMaquinas* aux3 = NULL;

			if (aux2 != NULL) {

				while (aux2 != NULL) {  //apaga as maquinas dentro de uma operacao
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

		while (aux && aux->operacao.codigoOperacao != cod) {    //procura para remover
			auxAnt = aux;
			aux = aux->next;
		}

		if (aux != NULL) {//se encontrou, remove

			ListaMaquinas* aux2 = aux->listaMaquinas;
			ListaMaquinas* aux3 = NULL;

			if (aux2 != NULL) {

				while (aux2 != NULL) {  //apaga as maquinas dentro de uma operacao
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

ListaOperacoes* RemoveOperacao2(ListaOperacoes* h, int cod) {

	if (h == NULL) return NULL;            //Lista vazia

	else
	{
		ListaOperacoes* aux = h;
		ListaOperacoes* auxAnt = NULL;

		//caso seja a primeira operacao a ser removida
		if (aux && aux->operacao.codigoOperacao != cod) {

			ListaMaquinas* aux2 = aux->listaMaquinas;
			ListaMaquinas* aux3 = NULL;

			if (aux2 != NULL) {

				RemoveTodasMaquinas(aux2);

				h = aux->next;
				free(aux);
				return h;
			}
			else //avança para a proxima maquina
			{
				auxAnt = aux;
				aux = aux->next;
			}

			while (aux && aux->operacao.codigoOperacao != cod) {    //procura para remover caso não seja a primeira
				auxAnt = aux;
				aux = aux->next;
			}

			if (aux != NULL) {//se encontrou, remove

				ListaMaquinas* aux2 = aux->listaMaquinas;
				ListaMaquinas* aux3 = NULL;

				if (aux2 != NULL) {

					RemoveTodasMaquinas(aux2);

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
 * @brief Remove todas as oprações
 * @param [in] Apontador para o inicio da lista
 * @param [out] Apontador para o inicio da lista
 */

ListaOperacoes* RemoveTodasOperacoes(ListaOperacoes* h) {

	if (h == NULL) return NULL;            //Lista vazia

	else {

		ListaOperacoes* aux = h;

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
 * @brief
 * @param [in] Apontador para o inicio da lista
 * @param cod codigo da operação a alterar
 * @param novoCod novo codigo da operação
 * @param novoNome novo nome
 * @param [out] Apontador para o inicio da lista
 */

ListaOperacoes* AlteraOperacao(ListaOperacoes* h, int cod, int novoCod, char* novoNome) {
	ListaOperacoes* aux = ProcuraOperacao(h, cod);
	if (aux != NULL)        //se encontrou a operacao
	{
		aux->operacao.codigoOperacao = novoCod;
		strcpy(aux->operacao.nome, novoNome);
	}
	return h;
}


/**
 * .
 * @brief Mostra todas as operações existentea
 * @param [in] Apontador para o inicio da lista
 */

void MostraTodasOperacoes(ListaOperacoes* h) {
	ListaOperacoes* aux = h;
	if (h != NULL) {
		if (aux) {

			while (aux) {
				printf("\n Operacao numero: %d", aux->operacao.codigoOperacao);
				printf("\n O nome desta operacao é: %s", aux->operacao.nome);
				printf("\n-----------------------------------------------");
				aux = aux->next;
			}
		}
		else
		{
			printf("Não existem operações!");
		}
	}
	else
	{
		printf("\n Lista vazia");
	}
}


/**
 * .
 * @brief Mostra uma das operações existentes(caaso exista)
 * @param [in] Apontador para o inicio da lista
 * @param cod codigo da operação a mostrar
 */

void MostraUmaOperacao(ListaOperacoes* inicio, int cod) {
	ListaOperacoes* aux = inicio;
	if (inicio != NULL) {
		aux = ProcuraOperacao(inicio, cod);

		if (aux) {
			ListaOperacoes* inicioOperacoes = aux;
			printf("\n Operacão numero: %d", aux->operacao.codigoOperacao);
			printf("\n O nome desta operacão é: %s", aux->operacao.nome);
			printf("\n-----------------------------------------------");
			aux = aux->next;
		}
		else
		{
			printf("Não existe nenhuma operação com este codigo!");
		}
	}
	else
	{
		printf("\n Lista vazia");
	}
}

/**
 * .
 * @brief Mostra as maquinas da operação
 * @param [in] Apontador para o inicio da lista
 * @param codOperacao
 */

void MostraMaquinasOperacao(ListaOperacoes* inicio, int codOperacao) {
	ListaOperacoes* aux = inicio;
	if (inicio != NULL) {
		aux = ProcuraOperacao(inicio, codOperacao);
		if (aux) {
			ListaMaquinas* inicioMaquinas = aux->listaMaquinas;
			MostraUmaOperacao(inicio, aux->operacao.codigoOperacao);
			MostraTodasMaquinas(inicioMaquinas);
		}
		else
		{
			printf("Não existe uma operação com este codigo,logo não temos maquinas associadas!");
		}
	}
	else
	{
		printf("\n Lista vazia");
	}
}

/**
 * .
 * @brief Mostra as maquinas de todas a operaçoes
 * @param [in] Apontador para o inicio da lista
 */

void MostraMaquinasOperacoes(ListaOperacoes* inicio) {
	ListaOperacoes* aux = inicio;
	if (inicio != NULL) {
		if (aux) {
			while (aux)
			{
				MostraUmaOperacao(inicio, aux->operacao.codigoOperacao);
				ListaMaquinas* inicioMaquinas = aux->listaMaquinas;
				MostraTodasMaquinas(inicioMaquinas);
				aux = aux->next;
			}

		}
		else
		{
			printf("Não existem operações,logo não temos maquinas associadas!");
		}
	}
	else
	{
		printf("\n Lista vazia");
	}
}
