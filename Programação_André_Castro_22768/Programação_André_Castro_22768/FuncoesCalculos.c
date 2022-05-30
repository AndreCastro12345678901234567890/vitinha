/*****************************************************************//**
 * @file: FuncoesCalculos.c
 * @author: Andr� Filipe da Silva Castro
 * @e-mail: andrefilipedasilvacastro123@gmail.com
 * @e-mail: a22768@alunos.ipca.pt
 * @date:  16 May 2022
 *********************************************************************/

#include "Funcoes.h"



	/**
	 *
	 * @brief Calcula o minimo de tempo requirido para completar um Job
	 *Avalia o numero de opera��es que o job tem de realizar
	 *Compara em cada opera��o do job qual a maquina que demora menos tempo
	 *Soma os menores tempos que a maquina com o tempo minimo realiza cada opera��o e retorna esse valor

	 * @param [in] Apontador para o incio da lista de opera��es
	 * @return
	 */

	int TempoMinimo(ListaOperacoes * InicioOperacao)
{
	ListaOperacoes* aux = InicioOperacao;
	ListaMaquinas* aux2 = aux->listaMaquinas;
	int minimo = 0;
	int soma = 0;

	while (aux != NULL)
	{

		if (aux2->maquina.tempo != NULL) {
			minimo = aux2->maquina.tempo;
		}

		while (aux2->next != NULL)
		{
			aux2 = aux2->next;
			if (minimo > aux2->maquina.tempo)
			{
				minimo = aux2->maquina.tempo;
			}

			aux2 = aux2->next;
		}

		soma = soma + minimo;

		aux = aux->next;
		aux2 = aux->listaMaquinas;
	}

	return soma;
}

/**
 *
 * @brief Calcula o tempo m�ximo requirido para completar um Job
 * @param [in] Apontador para o incio da lista
 */
int TempoMaximo(ListaOperacoes* InicioOperacao)
{
	ListaOperacoes* aux = InicioOperacao;
	ListaMaquinas* aux2 = aux->listaMaquinas;
	int maximo = 0;
	int soma = 0;

	while (aux != NULL)
	{

		if (aux2->maquina.tempo != NULL) {
			maximo = aux2->maquina.tempo;
		}

		while (aux2->next != NULL)
		{
			aux2 = aux2->next;
			if (maximo < aux2->maquina.tempo)
			{
				maximo = aux2->maquina.tempo;
			}

			aux2 = aux2->next;
		}

		soma = soma + maximo;

		aux = aux->next;
		aux2 = aux->listaMaquinas;
	}

	return soma;
}

/**
 * .
 * @brief Calcula o tempo m�dio requirido para completar uma opera��o
 * @param [in] Apontador para o incio da lista  de opera�oes
 * @param Cod � o codigo de uma opera��o
 * @return
 */

float TempoMedioDeUmaOperacao(ListaOperacoes* InicioOperacao, int Cod) {

	ListaMaquinas* aux = ProcuraOperacao(InicioOperacao, Cod)->listaMaquinas;
	int SomaMaquinas = 0;
	int SomaTempo = 0;
	float media;

	while (aux != NULL)
	{
		SomaMaquinas++;
		SomaTempo += aux->maquina.tempo;
		aux = aux->next;
	}
	media = SomaTempo / SomaMaquinas;

	return (media);

}

/**
 * .
 * @brief Calcula o tempo m�dio requirido para completar um Job
 * @param [in] Apontador para o incio da lista de opera�o�es
 * @return
 */

float TempoMedioDeUmJob(ListaOperacoes* InicioOperacao)
{

	ListaOperacoes* aux = InicioOperacao;
	ListaMaquinas* aux2 = aux->listaMaquinas;
	int nMaquinas = 0;
	int x = 0;
	int mediaDeUmaOperacao = 0;
	float media = 0;

	while (aux != NULL)
	{

		while (aux2->next != NULL)
		{

			x = x + aux2->maquina.tempo;
			nMaquinas++;
			aux2 = aux2->next;
		}

		mediaDeUmaOperacao = x / nMaquinas;
		media = media + mediaDeUmaOperacao;

		aux = aux->next;
		aux2 = aux->listaMaquinas;
	}

	return media;
}
