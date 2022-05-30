/*****************************************************************//**
 * @file: Ficheiros.c
 * @author: André Filipe da Silva Castro
 * @e-mail: andrefilipedasilvacastro123@gmail.com
 * @e-mail: a22768@alunos.ipca.pt
 * @date:  16 May 2022
 *********************************************************************/

#include "Funcoes.h"

#pragma region GereDataFile


/**
 * .
 * @brief Preserva informação de uma maquina
 * @param [in] Apontador para o inicio da lista
 * @param fileName nome do ficheiro
 * @return
 */

bool SaveMaquina(ListaMaquinas* h, char* fileName) {
	if (h == NULL) return false;
	FILE* fp;

	if ((fp = fopen(fileName, "wb")) == NULL) return false;
	ListaMaquinas* aux = h;
	while (aux) {
		fwrite(&aux->maquina, sizeof(aux->maquina), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}


/**
 * .
 * @brief Preserva informação de* uma operacao
 * @param [in] Apontador para o inicio da lista
 * @param fileName
 * @return
 */
bool SaveOperacao(ListaOperacoes* h, char* fileName) {
	if (h == NULL) return false;
	FILE* fp;

	if ((fp = fopen(fileName, "wb")) == NULL) return false;
	ListaOperacoes* aux = h;
	while (aux) {
		fwrite(&aux->operacao, sizeof(aux->operacao), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}



/**
 * .
 * @brief Preserva informação do Job
 * @param [in] Apontador para o inicio da lista
 * @param fileName
 * @return
 */
bool SaveJobs(ListaJobs* h, char* fileName) {
	if (h == NULL) return false;
	FILE* fp;

	if ((fp = fopen(fileName, "wb")) == NULL) return false;
	ListaJobs* aux = h;
	while (aux) {
		fwrite(&aux->job, sizeof(aux->job), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}


/**
 * .
 * @brief Grava jobs e respectivas operacoes e maquinas
 * @param [in] Apontador para o inicio da lista
 * @param fileName
 * @return
 */
bool SaveAll(ListaJobs* h, char* fileName) {
	if (h == NULL) return false;
	FILE* fp;

	if ((fp = fopen(fileName, "wb")) == NULL) return false;

	//grava n registos no ficheiro
	ListaJobs* auxJobs = h;
	TodaInformacao auxFile;	//struct para gravar em ficheiro!
	while (auxJobs) {
		//Colocar no registo de ficheiro a inf que está no registo de memória
		auxFile.codigoJob = auxJobs->job.codigoJob;
		ListaOperacoes* auxOperacoes = auxJobs->listaOperacoes;
		ListaMaquinas* auxMaquinas = auxOperacoes->listaMaquinas;
		while (auxOperacoes) {
			auxFile.codigoOperacao = auxOperacoes->operacao.codigoOperacao;
			fwrite(&auxFile, sizeof(auxFile), 1, fp);
			while (auxMaquinas) {
				auxFile.codigoMaquina = auxMaquinas->maquina.codigoMaquina;
				auxFile.tempo = auxMaquinas->maquina.tempo;
				fwrite(&auxFile, sizeof(auxFile), 1, fp);
				auxMaquinas = auxMaquinas->next;
			}
			auxOperacoes = auxOperacoes->next;
		}
		auxJobs = auxJobs->next;
	}

	fclose(fp);
	return true;
}



/**
 * .
 * @brief Carrega informação sobre Jobs
 * @param fileName
 * @param [out] Apontador para o inicio da lista
 */
ListaJobs* GetAllJobs(char* fileName) {
	FILE* fp;
	ListaJobs* h = NULL;
	ListaJobs* aux;
	Job j;

	if ((fp = fopen(fileName, "rb")) == NULL) return NULL;
	while (fread(&j, sizeof(j), 1, fp)) {
		if (ProcuraJob(h, j.codigoJob) == NULL) {
			aux = CriaNodoListaJobs(&j);
			h = InsereJobsListaJobs(h, aux);
			continue;
		}
	}
	fclose(fp);
	return h;
}



/**
 * .
 * @brief Carrega informação sobre as Operações
 * @param fileName
 * @param [out] Apontador para o inicio da lista
 */
ListaOperacoes* GetAllOperacoes(char* fileName) {
	FILE* fp;
	ListaOperacoes* h = NULL;
	ListaOperacoes* aux;
	Operacao o;

	if ((fp = fopen(fileName, "rb")) == NULL) return NULL;
	while (fread(&o, sizeof(o), 1, fp)) {
		if (ProcuraJob(h, o.codigoOperacao) == NULL) {
			aux = CriaNodoListaOperacoes(&o);
			h = InsereOperacaoListaOperacao(h, aux);
			continue;
		}
	}
	fclose(fp);
	return h;
}

/**
 * @brief Carrega informação sobre as Maquinas
 * @param fileName
 * @param [out] Apontador para o inicio da lista
 */

ListaJobs* GetAllMaquinas(char* fileName) {
	FILE* fp;
	ListaMaquinas* h = NULL;
	ListaMaquinas* aux;
	Maquina m;

	if ((fp = fopen(fileName, "rb")) == NULL) return NULL;
	while (fread(&m, sizeof(m), 1, fp)) {
		if (ProcuraMaquina(h, m.codigoMaquina) == NULL) {
			aux = CriaNodoListaMaquinas(&m);
			h = InsereMaquinaListaMaquina(h, aux);
			continue;
		}
	}
	fclose(fp);
	return h;
}


/**
 * .
 * @brief arrega todas as maquinas e operacoes para cada job
 * @param fileName
 * @param [in] Apontador para o inicio da lista
 * @param [out] Apontador para o inicio da lista
 */

ListaJobs* GetAll(char* fileName, ListaJobs* h) {

	FILE* fp;
	ListaJobs* aux = h;
	Job j;

	if (h == NULL) return NULL;

	if ((fp = fopen(fileName, "rb")) == NULL) return NULL;

	TodaInformacao auxFile;

	while (fread(&auxFile, sizeof(auxFile), 1, fp)) {
		//aux = ProcuraJobs(h, auxFile.job.codigoJob);
		//ListaJobs* InsereOperacoesJobs(ListaJobs * h, Operacao * o, int codJob);
		h = InsereOperacaoJobs(h, &auxFile.codigoOperacao, auxFile.codigoJob);
		aux->listaOperacoes = InsereMaquinaOperacao(aux->listaOperacoes, &auxFile.codigoMaquina, auxFile.codigoJob);
	}
	fclose(fp);
	return h;
}


/**
 * .
 * @brief Carrega dados de entrada.
 * @param fileName
 * @param [out] Apontador para o inicio da lista
 */
ListaJobs* GetData(char* fileName) {
	FILE* fp;
	ListaJobs* h = NULL;
	ListaJobs* aux;	//auxiliar
	ListaOperacoes* aux2;
	ListaMaquinas* aux3;
	Job j;			//auxiliar
	Operacao o;     //auxiliar
	Maquina m;      //auxiliar

	char linhaFicheiro[MAX];

	if ((fp = fopen(fileName, "r")) == NULL) return NULL;

	while (fgets(linhaFicheiro, MAX, fp) != NULL)
	{
		fscanf(linhaFicheiro, "%d[^;];%d[^;];%d[^;];%d", &j.codigoJob, &o.codigoOperacao, &m.codigoMaquina, &m.tempo);

		if (ProcuraJob(h, j.codigoJob) == NULL) {

			aux = CriaNodoListaJobs(&j);
			h = InsereJobsListaJobs(h, aux);
		}
		if (ProcuraOperacao(h, o.codigoOperacao) == NULL) {

			aux2 = CriaNodoListaOperacoes(&o);
			h = InsereOperacaoListaOperacao(h, aux2);
		}
		if (ProcuraMaquina(h, m.codigoMaquina) == NULL) {

			aux3 = CriaNodoListaMaquinas(&m);
			h = InsereMaquinaListaMaquina(h, aux3);
		}

		strcpy(j.nome, "ainda por defenir");
		strcpy(o.nome, "ainda por defenir");

		//Insere operacao
		h = InsereOperacaoJobs(h, &o, j.codigoJob);

		//insere maquina
		h = InsereMaquinaOperacao(h, &m, o.codigoOperacao);

		continue;
	}

	fclose(fp);
	return h;

}


#pragma endregion
