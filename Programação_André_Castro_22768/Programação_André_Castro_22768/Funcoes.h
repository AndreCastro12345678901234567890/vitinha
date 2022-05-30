/*****************************************************************//**
 * @file:Funcoes.h
 * @author: André Filipe da Silva Castro 
 * @e-mail: andrefilipedasilvacastro123@gmail.com
 * @e-mail: a22768@alunos.ipca.pt
 * @date:  16 May 2022
 *********************************************************************/


#ifndef XXXX
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

#pragma region Variaveis

#define N 50
#define MAX 200

#pragma endregion

#pragma region Structs


 /**
  * @brief Informacao de uma maquina.
  */
typedef struct Maquina {

	int codigoMaquina; /**< codigo para identificar a maquina*/
	int tempo;/**<tempo que a maquina demora a executar a sua operacao*/

}Maquina;

/**
 * @brief Lista de maquinas
 * Informaçao sobre as maquinase apontador para a seguinte
 */
typedef struct ListaMaquinas {

	Maquina maquina;
	struct ListaMaquinas* next;

}ListaMaquinas;


/**
 * @brief Informaçao sobre uma operacao.
 */
typedef struct Operacao {

	int codigoOperacao;	/**<codigo para identificar a operacao*/
	char nome[N];

}Operacao;

/**
 * @brief Lista de operçoes.
 * Informaçoes sobre a operações, as maquinas e apontador para a seguinte
 */

typedef struct ListaOperacoes {

	Operacao operacao;
	ListaMaquinas* listaMaquinas;
	Operacao* next;	/*<apontador do sitio onde é armazenado a proxima operacao*/

}ListaOperacoes;


/**
 * @brief Informação de um Job
 */
typedef struct Job {

	int codigoJob; //codigo para identificar o job
	char nome[N];

}Job;


/**
 * @brief Lista de jobs.
 * Informação de um job, operçoes, maquinas e apontador para o seguite
 */
typedef struct ListaJobs {

	Job job;
	ListaOperacoes* listaOperacoes;/*<lista de operacoes que sao uzadas para realizar um job*/
	struct job* next;/*<apontador do sitio onde é armazenado o proximo job*/

}ListaJobs;


#pragma endregion

#pragma region InformaçãoFicheiro

/**
 * @brief Preserva a informação 
 */
typedef struct TodaInformacao {

	int codigoJob;
	int codigoOperacao;
	int codigoMaquina;
	int tempo;

}TodaInformacao;

#pragma endregion

#pragma region Funcoes
//funções para as maquinas
Maquina* CriaMaquina(int novoCod, int novoTempo);
ListaMaquinas* CriaNodoListaMaquinas(Maquina* c);
ListaMaquinas* InsereMaquinaListaMaquina(ListaMaquinas* h, Maquina* m);
ListaMaquinas* ProcuraMaquina(ListaMaquinas* inicio, int cod);
void MostraTodasMaquinas(ListaMaquinas* h);
void MostraUmaMaquina(ListaMaquinas* inicio, int cod);
ListaMaquinas* RemoveMaquina(ListaMaquinas* h, int cod);
ListaMaquinas* RemoveTodasMaquinas(ListaMaquinas* h);
ListaMaquinas* AlteraMaquina(ListaMaquinas* h, int cod, int novoTempo, int novoCod);

//funções para as operações
Operacao* CriaOperacao(int novoCod, char nome[N]);
ListaOperacoes* CriaNodoListaOperacoes(Operacao* o);
ListaOperacoes* InsereOperacaoListaOperacao(ListaOperacoes* h, Operacao* o);
ListaOperacoes* ProcuraOperacao(ListaOperacoes* inicio, int cod);
ListaOperacoes* InsereMaquinaOperacao(ListaOperacoes* h, Operacao* o, int cod);
void MostraTodasOperacoes(ListaOperacoes* h);
void MostraUmaOperacao(ListaOperacoes* inicio, int cod);
void MostraMaquinasOperacao(ListaOperacoes* inicio, int codOperacao);
void MostraMaquinasOperacoes(ListaOperacoes* inicio);
ListaOperacoes* RemoveOperacao(ListaOperacoes* h, int cod);
ListaOperacoes* RemoveOperacao2(ListaOperacoes* h, int cod);
ListaOperacoes* RemoveTodasOperacoes(ListaOperacoes* h);
ListaOperacoes* AlteraOperacao(ListaOperacoes* h, int cod, int novoCod, char* novoNome);

//funções para os Jobs
Job* CriaJobs(int novoCod, char nome[N]);
ListaJobs* CriaNodoListaJobs(Job* j);
ListaJobs* InsereJobsListaJobs(ListaJobs* h, Job* j);
ListaJobs* ProcuraJob(ListaJobs* inicio, int cod);
ListaJobs* InsereOperacaoJobs(ListaJobs* h, Job* j, int cod);
void MostraTodosJobs(ListaJobs* h);
void MostraUmJob(ListaJobs* inicio, int cod);
void MostraMaquinasOperacoesJob(ListaJobs* inicio, int codJob);
void MostraMaquinasOperacoesJobs(ListaJobs* inicio);
ListaJobs* RemoveJob(ListaJobs* h, int cod);
ListaJobs* RemoveJob2(ListaJobs* h, int cod);
ListaJobs* RemoveTodosJobs(ListaJobs* h);
ListaJobs* AlteraJob(ListaJobs* h, int cod, int novoCod, char* novoNome);

//funções calculo
int TempoMinimo(ListaOperacoes* InicioOperacao);
int TempoMaximo(ListaOperacoes* InicioOperacao);
float TempoMedioDeUmaOperacao(ListaOperacoes* InicioOperacao, int Cod);

//extra
float TempoMedioDeUmJob(ListaOperacoes* InicioOperacao);

//funções para guardar e receber dados
bool SaveMaquina(ListaMaquinas* h, char* fileName);
bool SaveOperacao(ListaOperacoes* h, char* fileName);
bool SaveJobs(ListaJobs* h, char* fileName);
bool SaveAll(ListaJobs* h, char* fileName);
ListaJobs* GetAllMaquinas(char* fileName);
ListaOperacoes* GetAllOperacoes(char* fileName);
ListaJobs* GetAllJobs(char* fileName);
ListaJobs* GetAll(char* fileName, ListaJobs* h);
ListaJobs* GetData(char* fileName);

#pragma endregion

#define XXXX
#endif

