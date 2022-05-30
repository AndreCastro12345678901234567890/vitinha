/*****************************************************************//**
 * @file: Main.c
 * @author: André Filipe da Silva Castro
 * @e-mail: andrefilipedasilvacastro123@gmail.com
 * @e-mail: a22768@alunos.ipca.pt
 * @date:  16 May 2022
 *********************************************************************/

#include "Funcoes.h"

void main() {

	ListaJobs* inicio = NULL;

	GetAllMaquinas("dados.txt");
	GetAllOperacoes("dados.txt");
	GetAllJobs("dados.txt");
	GetAll("dados.txt", inicio);

	inicio = GetData("dados.txt");

	//Se não existem dados de entrada, insere manualmente(aqui coloquei a informaçao de um ramo de um job(1j, 1o, 2m)
	if (inicio == NULL) {

		Maquina* m1 = CriaMaquina("1", "4");
		ListaMaquinas* maquinas = NULL;
		maquinas = InsereMaquinaListaMaquina(maquinas, m1);

		Maquina* m2 = CriaMaquina("2", "4");
		maquinas = InsereMaquinaListaMaquina(maquinas, m2);

		Maquina* m3 = CriaMaquina("3", "5");
		maquinas = InsereMaquinaListaMaquina(maquinas, m3);

		Maquina* m4 = CriaMaquina("4", "5");
		maquinas = InsereMaquinaListaMaquina(maquinas, m4);

		Maquina* m5_1 = CriaMaquina("5", "6");
		maquinas = InsereMaquinaListaMaquina(maquinas, m5_1);

		Maquina* m5_2 = CriaMaquina("5", "5");
		maquinas = InsereMaquinaListaMaquina(maquinas, m5_2);

		Maquina* m6 = CriaMaquina("6", "4");
		maquinas = InsereMaquinaListaMaquina(maquinas, m6);

		Maquina* m7 = CriaMaquina("7", "5");
		maquinas = InsereMaquinaListaMaquina(maquinas, m7);

		Maquina* m8 = CriaMaquina("8", "9");
		maquinas = InsereMaquinaListaMaquina(maquinas, m8);



		Operacao* o1 = CriaOperacao(1, "cortar");
		ListaOperacoes* operacoes = NULL;
		operacoes = InsereOperacaoListaOperacao(operacoes, o1);

		Operacao* o2 = CriaOperacao(2, "colar");
		operacoes = InsereOperacaoListaOperacao(operacoes, o2);

		Operacao* o3 = CriaOperacao(3, "pintar");
		operacoes = InsereOperacaoListaOperacao(operacoes, o2);

		Operacao* o4 = CriaOperacao(4, "secar");
		operacoes = InsereOperacaoListaOperacao(operacoes, o2);



		Job* j1 = CriaJobs(1, "construir um carrinho");
		inicio = InsereJobsListaJobs(inicio, j1);

		/*incere maquinas na operação com o codigo respetivo codigo*/
		inicio = InsereMaquinaOperacao(operacoes, m1, 1);
		inicio = InsereMaquinaOperacao(operacoes, m3, 1);
		inicio = InsereMaquinaOperacao(operacoes, m2, 2);
		inicio = InsereMaquinaOperacao(operacoes, m4, 2);
		inicio = InsereMaquinaOperacao(operacoes, m3, 3);
		inicio = InsereMaquinaOperacao(operacoes, m5_1, 3);
		inicio = InsereMaquinaOperacao(operacoes, m4, 4);
		inicio = InsereMaquinaOperacao(operacoes, m5_2, 4);
		inicio = InsereMaquinaOperacao(operacoes, m6, 4);
		inicio = InsereMaquinaOperacao(operacoes, m7, 4);
		inicio = InsereMaquinaOperacao(operacoes, m8, 4);

		//incere operacao no job com o codigo respetivo codigo
		inicio = InsereOperacaoJobs(inicio, o1, 1);
		inicio = InsereOperacaoJobs(inicio, o2, 1);
		inicio = InsereOperacaoJobs(inicio, o3, 1);
		inicio = InsereOperacaoJobs(inicio, o4, 1);

		MostraMaquinasOperacoesJob(inicio, 1);

		int minimo;
		minimo = TempoMinimo(operacoes);
		printf("O tempo minimo e: %d", minimo);

		int maximo;
		maximo = TempoMaximo(operacoes);
		printf("O tempo maximo e: %d", maximo);

		float media;
		media = TempoMedioDeUmaOperacao(operacoes, 1);
		printf("O tempo medio e: %f", media);

		float media2;
		media2 = TempoMedioDeUmJob(inicio, 1);
		printf("O tempo medio e: %f", media2);

	}
	else
	{
		MostraMaquinasOperacoesJobs(inicio);
	}

	SaveMaquina(inicio, "dados.txt");
	SaveOperacao(inicio, "dados.txt");
	SaveJobs(inicio, "dados.txt");
	SaveAll(inicio, "dados.txt");

}
