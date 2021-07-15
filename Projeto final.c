// Síntese
// Objetivo:"software de gerenciamento de voos e embarques"
// Alunos: Filipe Flanklin Ferreira De sousa

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include "conio.h"


//Entidades ***********************************************************
struct tViagem {
	int codVia; // chave primaria
	int diaV; // Dia da viagem
	int mesV; // Mes da viagem
	int anoV; // Ano da viagem
	int horaV;// Hora do imbarque 
	int minuV;// do embarque
	int qtdassentos; // Quantidade de assentos[
	char deletadoV; // ESPACOBRANCO=ok; *=deletado
	char origem[50];// origem da viajem
	char destino[50];// Destino da viajem
};
struct tEmbarque {
	
	int codEV; // Chave de acesso a viagem
	int codEM; // Chave de embarque
	int assentoEM;  // Assento do embarque
	int qtdbagm; // quantidade de bagagem de mão; max = 2;
	char deletadoEM; // Embarques excluidos
	char nomeP[50]; //Nome do passageniro
};
struct tAssento {
	int numeasst;// Números do assentos
	int	codASV;// codigo da viagem
	int codASE;//codigo do embarque
	int dipoA;// disponibilidade do assento = 0; indisponivel = 1;
	char deletadoAS;// Assento deletado
};
struct tBagagem{
	int codBA;// código da bagagem
	int codBAV;// Chave de acesso a viagem
	int codBAE;// Chave de embarque
	int peso;// peso da bagagem	
	int tipo;// tipo; 1 = despache; 0 = bagagem de mão
	char deletadoBA; // Bagagens excluidas
};
// Prototipo de funcao ********************************************************
int menuPrincipal(void);
int menuEntidade(char[],int);
FILE *abrirArquivo(char[]);
// viagem
void gravarViagem(struct tViagem, int, FILE *);
void excluirViagem(int , FILE *);
int consultarViagem(int, FILE *);
struct tViagem lerViagem(int, FILE *);
void listarViagem(FILE *,int);
int ExclusaoFisica(char [],FILE *);
// Embarque
void gravarEmbarque(struct tEmbarque, int, FILE *);
void listarEmbarque(FILE *,int,int);
int consultarEmbarque(int,int,FILE *,int);
struct tEmbarque lerEmbarque(int , FILE *);
void excluirEmbarque(int, FILE *);
int ExclusaoFisicaEM(char[],FILE *);
// Assento
void gravarAssento(struct tAssento, int, FILE *);
void listarAssento(FILE *,int);
int consultarAssento(int,int,FILE *,int);
struct tAssento lerAssento(int, FILE *);
int excluirTodosAssento(char[],int,FILE *);
int ExclusaoFisicaAS(char [],FILE *);
// Bagagem
void gravarBagagem(struct tBagagem, int, FILE *);
void listarBagagem(FILE *,FILE *,int ,int,int,int);
int consultarBagagem(int ,int ,int ,FILE * );
struct tBagagem lerBagagem(int , FILE *);
void excluirBagagem(int, FILE *);
int ExclusaoFisicaBA(char[],FILE *);
int excluirTodasBagagem(char[],int ,int , FILE *);
// main************************************************************************
int main(void) {
	FILE *arqVia, *arqEmb, *arqAss,*arqBag;
	struct tViagem viagem;
	struct tEmbarque embarque;
	struct tAssento assento;
	struct tBagagem	bagagem;
	int opcao, opcaoV,opcaoE,opcaoB, posicao,posicaoA,posicaoA2,codigoV,codigoE,codigoA,assentAtu;
	int diaAtual,mesAtual,atualAno,horaAtual,minuAtual,hora,i,troca= 0,codigoB;
	setlocale(LC_ALL, "");
	arqVia = abrirArquivo("viagem.dat");
	arqEmb = abrirArquivo("embarque.dat");
	arqAss = abrirArquivo("assento.dat");
	arqBag = abrirArquivo("bagagem.dat");
	SYSTEMTIME str_t;
    int anoAtual = str_t.wYear;
	if ((arqVia == NULL) || (arqEmb == NULL)){
		textcolor(12); printf("Erro de abertura do arquivo!!!"); textcolor(15);
		return 1;
	}
	do {
		system("cls");
		opcao = menuPrincipal();
		switch (opcao) {
			case 1: //viagem
				do {
					clrscr();
					opcaoV = menuEntidade ("viagens",0);
					switch(opcaoV){
						case 1: // incluir viagem
						system("cls");
							printf("\nIncluir Nova viagem\n");
							printf("\nDigite o código da viagem......: ");
							scanf("%d", &codigoV);
							posicao = consultarViagem(codigoV, arqVia);
							if (posicao != -1){
								textcolor(12);	printf("Erro: código já utilizado!\n");	textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							viagem.codVia = codigoV;
							printf("Digite a origem da viagem......: ");
							fflush(stdin);
							gets(viagem.origem);
							printf("Digite o destino da viagem......: ");
							fflush(stdin);
							gets(viagem.destino);
							printf("Digite a dia, mês e o ano da viagem.: ");
							scanf("%d/%d/%d", &viagem.diaV, &viagem.mesV,&viagem.anoV);
							if ((viagem.diaV > 30) || (viagem.diaV < 1) || (viagem.mesV < 1) || (viagem.mesV > 12) || (viagem.anoV < anoAtual)){
								textcolor(12); printf("\n ************* Dados de dia ou mês inválido ************* \n");	textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							else{
								printf("Digite a Horario do embarque......: ");
								scanf("%d:%d", &viagem.horaV,&viagem.minuV);
								if((viagem.horaV < 0) || (viagem.horaV > 24) || (viagem.minuV < 0) || (viagem.minuV > 59)){
									textcolor(12); printf("\n ************* Dados de hora inválido ************* \n");	textcolor(15);
									printf("\n\n*** Aperte enter para voltar ***\n\n");
									getchar();
									getchar();
									break;
								}
								else{
								printf("Digite a Quantidade de assentos: ");
								scanf("%d", &viagem.qtdassentos);
								gravarViagem(viagem,-1,arqVia);
								assento.numeasst = viagem.qtdassentos;	
								for (i =viagem.qtdassentos; i> 0;i--){
									assento.deletadoAS = ' ';
									assento.dipoA = 0; 
									assento.codASV = viagem.codVia;
									gravarAssento(assento,-1,arqAss);
									assento.numeasst--;
								}
								}
							}
							printf("\n\n*** Aperte enter para voltar ***\n\n");
							getchar();
							getchar();
						break;
						case 2:
							system("cls");
							printf("\n\n*** Excluir Viagem ***\n");
							listarViagem(arqVia,1);
							printf("\nDigite o código da viagem: ");
							scanf("%d", &codigoV);
							posicao = consultarViagem(codigoV, arqVia);
							if (posicao != -1)
								viagem = lerViagem(posicao, arqVia);
							else{
								textcolor(12); printf("Erro: código nao localizado\n");	textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							posicaoA = consultarEmbarque(codigoV,codigoE,arqEmb,1);
							if (posicaoA == -1){
								excluirTodosAssento("assento.dat",codigoV,arqAss);
								excluirViagem(posicao, arqVia);
								printf("Excluido com sucesso!\n");
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
							}
							else{
								textcolor(12); printf("Erro: Impossivel alterar, embarques registrados existentes");textcolor(15);
							printf("\n\n*** Aperte enter para voltar ***\n\n");
							getchar();
							getchar();
							}
						break;
						case 3:
							system("cls");
							printf("\n\n*** Consultar Viagem ***\n");
							listarViagem(arqVia,1);
							printf("\nDigite o código da viagem: ");
							scanf("%d", &codigoV);
							posicao = consultarViagem(codigoV, arqVia);
							if (posicao != -1) {
								viagem = lerViagem(posicao, arqVia);
								printf("--------------------------------------------\n\n");
								printf("Código da viagem: %d\n",viagem.codVia);
								printf("Origem da viagem: %s\n", viagem.origem);
								printf("Destino da viagem: %s\n", viagem.destino);
								printf("Data: %02d/%02d/%02d\n", viagem.diaV, viagem.mesV,viagem.anoV);
								printf("hora: %02d:%02d\n",viagem.horaV, viagem.minuV);
								printf("Quantidade de assentos disponíveis: %d\n",viagem.qtdassentos);
							}
							else{
								textcolor(12); printf("\nErro: código nao localizado!!!\n");textcolor(15);
							}
							printf("\n\n*** Aperte enter para voltar ***\n\n");
							getchar();
							getchar();
						break;
						case 4:
							system("cls");
							printf("\n\n*** Alterar Viagem ***\n");
							listarViagem(arqVia,1);
							printf("\nDigite o código da viagem: ");
							scanf("%d",&codigoV);
							posicao = consultarViagem(codigoV, arqVia);
							if (posicao != -1)
								viagem = lerViagem(posicao, arqVia);
							else{
								textcolor(12); printf("\nErro: código nao localizado!!!\n");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
								posicaoA = consultarEmbarque(codigoV,codigoE,arqEmb,1);
							if (posicaoA == -1){
								printf("--------------------------------------------\n\n");
								printf("Dados antigos - \n");
								printf("Origem da viagem: %s\n", viagem.origem);
								printf("Destino da viagem: %s\n", viagem.destino);
								printf("Data: %02d/%02d/%02d\n", viagem.diaV, viagem.mesV,viagem.anoV);
								printf("horario da viagem: %02d:%02d\n",viagem.horaV, viagem.minuV);
								printf("--------------------------------------------\n\n");
								printf("Digite a nova origem da viagem......: ");
								fflush(stdin);
								gets(viagem.origem);
								printf("Digite o novo destino da viagem......: ");
								fflush(stdin);
								gets(viagem.destino);
								printf("Digite a nova Data: ");
								scanf("%d/%d/%d", &viagem.diaV, &viagem.mesV,&viagem.anoV);
								if ((viagem.diaV > 30) || (viagem.diaV < 1) || (viagem.mesV < 1) || (viagem.mesV > 12) || (viagem.anoV < anoAtual)){
									textcolor(12);	printf("\n ************* Dados de dia ou mês inválido ************* \n");	textcolor(15);
									printf("\n\n*** Aperte enter para voltar ***\n\n");
									getchar();
									getchar();
									break;
								}
								else{
									printf("Digite o novo horario: ");
									scanf("%d:%d", &viagem.horaV,&viagem.minuV);
									if((viagem.horaV < 0) || (viagem.horaV > 24) || (viagem.minuV < 0) || (viagem.minuV > 59)){
										printf("\n ************* Dados de hora inválido ************* \n");textcolor(15);
										printf("\n\n*** Aperte enter para voltar ***\n\n");
										getchar();
										getchar();
										break;
									}
								}
									gravarViagem(viagem,posicao,arqVia);
									printf("\n\n*** Aperte enter para voltar ***\n\n");
									getchar();
									getchar();
							}
							else{
								textcolor(12);	printf("Erro: Impossivel alterar, embarques já registrados");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
							}
						break;
						case 5:
							system("cls");
							printf("\n\n*** Listar viagens ***\n\n");
							listarViagem(arqVia,0);
							printf("\n\n*** Aperte enter para voltar ***\n\n");
							getchar();
							getchar();
					}
			}while (opcaoV != 0);
			system("cls");
			break;	
			case 2:
				do{
					system("cls");
					opcaoE = menuEntidade("embarque",1);
					switch (opcaoE){
						case 1:
							system("cls");
							printf("\nIncluir Novo Embarque\n");
							listarViagem(arqVia,0);
							printf("\n\nDigite o código da sua viagem: ");
							scanf("%d",&codigoV);
							posicao = consultarViagem(codigoV, arqVia);
							if (posicao == -1){
								textcolor(12); printf("Erro: código não localizado\n");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							printf("Digite o Código do Embarque: ");
							scanf("%d",&codigoE);
							if (codigoE < 1){
								textcolor(12); printf("Erro: Código de embarque Invalido, Registre um código Maior que 0!!\n");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							posicao = consultarEmbarque(codigoV,codigoE,arqEmb,0);
							if (posicao != -1){
								textcolor(12); printf("Erro: Código de embarque já registrado!!\n");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}									
							embarque.codEM = codigoE;
							posicao = consultarViagem(codigoV, arqVia);
							if (posicao != -1) {
								viagem = lerViagem(posicao, arqVia);
								embarque.codEV = codigoV;
								printf("Digite o seu nome: ");
								fflush(stdin);
								gets(embarque.nomeP);
								printf("Digite a data atual: ");
								scanf("%d/%d/%d", &diaAtual,&mesAtual,&atualAno);
								if ((diaAtual > 30) || (diaAtual < 1) || (mesAtual < 1) || (mesAtual > 12)){
									textcolor(12);	printf("\n ************* Dados de dia ou mês inválido ************* \n");textcolor(15);
									printf("\n\n*** Aperte enter para voltar ***\n\n");
									getchar();
									getchar();
									break;
								}
								else if ((diaAtual != viagem.diaV) || (mesAtual != viagem.mesV) || (atualAno != viagem.anoV)){
									textcolor(12);	printf("\n ************* Dados de dia ou mês não correspondem a data da viagem ************* \n");textcolor(15);
									printf("\n\n*** Aperte enter para voltar ***\n\n");
									getchar();
									getchar();
									break;
								}
								else{
									printf("Digite a hora atual: ");
									scanf("%d:%d",&horaAtual,&minuAtual);
									int aux = viagem.minuV - minuAtual;
									if((horaAtual < 0) || (horaAtual > 24) || (minuAtual < 0) || (minuAtual > 59)){
										textcolor(12); printf("\n ************* Dados de hora inválido ************* \n");textcolor(1);
										printf("\n\n*** Aperte enter para voltar ***\n\n");
										getchar();
										getchar();
										break;
									}
									else if ((horaAtual == viagem.horaV) && (minuAtual == viagem.minuV) || (horaAtual > viagem.horaV) || (horaAtual == viagem.horaV - 1) && (aux < 0)){
										textcolor(12); printf("\n ************* Dados da hora não correspondem a hora da viagem ************* \n");textcolor(15);
										printf("\n\n*** Aperte enter para voltar ***\n\n");
										getchar();
										getchar();
										break;	
									}
									listarAssento(arqAss,codigoV);
									printf("\nDigite o número do assento: ");
									scanf("%d", &codigoA); 
									embarque.assentoEM = codigoA;										
									posicaoA = consultarAssento(codigoV,codigoA,arqAss,0);
									if ((posicaoA != -1)){
										assento = lerAssento(posicaoA,arqAss);
										assento.dipoA = 1;
										gravarAssento(assento,posicaoA,arqAss);
									}
									else{
										textcolor(12);	printf("\nErro: Assento não Encontrado ou Indisponivel!!!\n");textcolor(15);
										printf("\n\n*** Aperte enter para voltar ***\n\n");
										getchar();
										getchar();
										break;
									}
								}
								embarque.qtdbagm = 0;
								gravarEmbarque(embarque,-1,arqEmb);
							}
							else{
								textcolor(12); printf("\nErro: código nao localizado!!!\n");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
							}
							printf("\n\n*** Aperte enter para voltar ***\n\n");
							getchar();
							getchar();
						break;
						case 2:
							system("cls");
							printf("\n\n*** Excluir Embarque ***\n");
							listarViagem(arqVia,1);
							printf("\nDigite o código da viagem: ");
							scanf("%d", &codigoV);
							posicao = consultarViagem(codigoV, arqVia);
							if (posicao == -1){
								textcolor(12); printf("Erro: código nao localizado\n");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							listarEmbarque(arqEmb,1,codigoV);
							printf("\nDigite o código do embarque: ");
							scanf("%d",&codigoE);
							posicao = consultarEmbarque(codigoV,codigoE,arqEmb,1);
							if (posicao != -1){
								excluirTodasBagagem("bagagem.Dat",codigoV,codigoE,arqBag);
								embarque = lerEmbarque(posicao,arqEmb);
								assentAtu = embarque.assentoEM;
								posicaoA = consultarAssento(codigoV,assentAtu,arqAss,1);
								if (posicaoA != -1){
									assento = lerAssento(posicaoA,arqAss);
									assento.dipoA = 0;
									gravarAssento(assento,posicaoA,arqAss);
								}
								excluirEmbarque(posicao,arqEmb);
								printf("Excluido com sucesso!\n");
							}
							else{
								textcolor(12); printf("\nErro: código nao localizado!!!\n"); textcolor(15);
							}
							printf("\n\n*** Aperte enter para voltar ***\n\n");
							getchar();
							getchar();
						break;
						case 3:
							system("cls");
							printf("\n\n*** consultar Embarque ***\n");
							listarViagem(arqVia,1);
							printf("\nDigite o código da viagem: ");
							scanf("%d", &codigoV);
							posicao = consultarViagem(codigoV, arqVia);
							if (posicao == -1){
								textcolor(12);	printf("Erro: código nao localizado\n");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							listarEmbarque(arqEmb,1,codigoV);
							printf("\nDigite o código do embarque: ");
							scanf("%d",&codigoE);
							system("cls");
							printf("\n\n*** Consultar Viagem ***\n");
							posicao = consultarEmbarque(codigoV,codigoE,arqEmb,0);
							if (posicao != -1){
								embarque = lerEmbarque(posicao,arqEmb);
								printf("\nNome do Passageiro: %s\n",embarque.nomeP);
								printf("Código do Embarque: %d\n",embarque.codEM);
								printf("Número do assentro: %d\n",embarque.assentoEM);
							}
							else{
								textcolor(12);	printf("\nErro: código nao localizado!!!\n");textcolor(15);
							}
							printf("\n\n*** Aperte enter para voltar ***\n\n");
							getchar();
							getchar();
						break;
						case 4:
							system("cls");
							printf("\n\n*** Alterar Embarque ***\n");
							listarViagem(arqVia,1);
							printf("\nDigite o código da viagem: ");
							scanf("%d", &codigoV);
							posicao = consultarViagem(codigoV, arqVia);
							if (posicao == -1){
						    	textcolor(12);	printf("Erro: código nao localizado\n");textcolor(15);
						    	printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							listarEmbarque(arqEmb,1,codigoV);
							printf("\nDigite o código do embarque: ");
							scanf("%d",&codigoE);
							if (codigoE < 1){
								textcolor(12); printf("Erro: Código de embarque Invalido, Registre um código Maior que 0!!\n");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							posicao = consultarEmbarque(codigoV,codigoE,arqEmb,0);
							if (posicao == -1){
								textcolor(12);	printf("Erro: Código de embarque já registrado!!\n");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}	
							else{
								embarque = lerEmbarque(posicao,arqEmb);
								printf("Dados antigos - \n");
								printf("\nNome do Passageiro: %s\n",embarque.nomeP);
								printf("Número do assentro: %d\n",embarque.assentoEM);
								printf("\nNovo nome do passageiro: ");
								fflush(stdin);
								gets(embarque.nomeP);
								listarAssento(arqAss,codigoV);
								assentAtu = embarque.assentoEM;
								printf("\nDigite o novo número do assento: ");
								scanf("%d", &codigoA); 
								posicaoA = consultarAssento(codigoV,assentAtu,arqAss,1);
								if ((posicaoA != -1) && (assento.dipoA == 1)){
									assento = lerAssento(posicaoA,arqAss);
									assento.dipoA = 0;
									gravarAssento(assento,posicaoA,arqAss);
								}
								embarque.assentoEM = codigoA;										
								posicaoA = consultarAssento(codigoV,codigoA,arqAss,0);
								if ((posicaoA != -1) && (assento.dipoA == 0)){
									assento = lerAssento(posicaoA,arqAss);
									assento.dipoA = 1;
									gravarAssento(assento,posicaoA,arqAss);	
								}
								else{
									textcolor(12); printf("\nErro: Assento não Encontrado ou Indisponivel!!!\n");textcolor(15);
									printf("\n\n*** Aperte enter para voltar ***\n\n");
									getchar();
									getchar();
									break;
								}
								gravarEmbarque(embarque,posicao,arqEmb);
							}
							printf("\n\n*** Aperte enter para voltar ***\n\n");
							getchar();
							getchar();		
						break;
						case 5:
							system("cls");
							printf("\n\n*** listar Embarque ***\n");
							listarViagem(arqVia,1);
							printf("\nDigite o código da viagem: ");
							scanf("%d", &codigoV);
							posicao = consultarViagem(codigoV, arqVia);
							if (posicao == -1){
								textcolor(12); printf("Erro: código nao localizado\n");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							listarEmbarque(arqEmb,0,codigoV);
							printf("\n\n*** Aperte enter para voltar ***\n\n");
							getchar();
							getchar();
						break;
						case 6:
							system("cls");
							printf("\n\n*** listar Assento ***\n");
							listarViagem(arqVia,1);
							printf("\nDigite o código da viagem: ");
							scanf("%d", &codigoV);
							posicao = consultarViagem(codigoV, arqVia);
							if (posicao == -1){
								textcolor(12);	printf("Erro: código nao localizado\n");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							listarAssento(arqAss,codigoV);
							printf("\n\n*** Aperte enter para voltar ***\n\n");
							getchar();
							getchar();
						}
				}while(opcaoE != 0);
				system("cls");
			break;	
			case 3:
				do{
					system("cls");
					opcaoB = menuEntidade("Bagagem",0);
					switch (opcaoB){
						case 1:
							system("cls");
							printf("\nIncluir Bagagem\n");
							listarViagem(arqVia,1);
							printf("\nDigite o código da sua viagem: ");
							scanf("%d",&codigoV);
							system("cls");
							printf("\nIncluir Bagagem\n");
							posicao = consultarViagem(codigoV, arqVia);
							if (posicao == -1){
								textcolor(12); printf("Erro: código nao localizado\n");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							bagagem.codBAV = codigoV;
							system("cls");
							printf("\nIncluir Bagagem\n");
							listarEmbarque(arqEmb,1,codigoV);
							printf("\nDigite o Código do Embarque: ");
							scanf("%d",&codigoE);
							system("cls");
							printf("\nIncluir Bagagem\n");
							posicao = consultarEmbarque(codigoV,codigoE,arqEmb,0);
							if (posicao == -1){
								textcolor(12); printf("Erro: Código de embarque Invalido ou Inexistente!!\n");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							bagagem.codBAE = codigoE;
							embarque = lerEmbarque(posicao,arqEmb);
							printf("\nDigite o código da bagagem: ");
							scanf("%d",&codigoB);
							bagagem.codBA = codigoB;
							posicaoA = consultarBagagem(codigoB,codigoV,codigoE,arqBag);
							if (posicaoA != -1){
								textcolor(12); printf("Erro: Código da bagagem já registrado");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							else{
								do{
									printf("\nDigite o peso da sua bagagem (Acima de 10KG a bagagem e despachada): ");
									scanf("%d",&bagagem.peso);
									if (bagagem.peso < 1){
										textcolor(12);	printf("Erro: Peso digitado invalido!!!");textcolor(15);
										break;
									}	
									if (bagagem.peso > 10){
										bagagem.tipo = 1;// despache
										gravarEmbarque(embarque,posicao,arqEmb);
										gravarBagagem(bagagem,-1,arqBag);
									}
									else{
										bagagem.tipo = 0;
										if (embarque.qtdbagm == 2){
											textcolor(12);	printf("Erro: Quantidade maxima de 2 bagagens de mão atingidas!!!");textcolor(15);
										}
										else{
											bagagem.tipo = 0; // Mão
											embarque.qtdbagm++;
											gravarEmbarque(embarque,posicao,arqEmb);
											gravarBagagem(bagagem,-1,arqBag);
										}
									}
									printf("\n\n*** Aperte enter para voltar ***\n\n");
									getchar();
									getchar();
								}while (bagagem.peso < 0);
							}
						break;
						case 2:
							system("cls");
							printf("\n\n*** excluir Bagagem ***\n");
							listarViagem(arqVia,1);
							printf("\nDigite o código da viagem: ");
							scanf("%d", &codigoV);
							posicao = consultarViagem(codigoV, arqVia);
							if (posicao == -1){
								textcolor(12); printf("Erro: código nao localizado\n");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
									getchar();
									getchar();
								break;
							}
							system("cls");
							printf("\n\n*** excluir Bagagem ***\n");
							listarEmbarque(arqEmb,1,codigoV);
							printf("\nDigite o código do embarque: ");
							scanf("%d",&codigoE);
							posicao = consultarEmbarque(codigoV,codigoE,arqEmb,0);
							if (posicao == -1){
								textcolor(12); printf("Erro: Embarque não encontrado");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							else{
								system("cls");
								printf("\n\n*** excluir Bagagem ***\n");
								listarBagagem(arqEmb,arqBag,codigoE,codigoV,posicao,1);
								printf("\n\nDigite o código da bagagem que será excluida: ");
								scanf("%d",&codigoB);
								posicao = consultarEmbarque(codigoV,codigoE,arqEmb,0);
								posicaoA = consultarBagagem(codigoB,codigoV,codigoE,arqBag);
								embarque = lerEmbarque(posicao,arqEmb);
								if (posicaoA == -1){
									textcolor(12); printf("Erro: Código da bagagem Não localizado");textcolor(15);
									printf("\n\n*** Aperte enter para voltar ***\n\n");
									getchar();
									getchar();
									break;
								}
								else{
									bagagem = lerBagagem(posicaoA,arqBag);
									printf("\nDados da bagagem excluida - \n");
									if(bagagem.tipo == 0){
										printf("\nCódigo da bagagem: %d",bagagem.codBA);
										printf("\nPeso da bagagem de mão :%d",bagagem.peso);
										embarque.qtdbagm --;
										gravarEmbarque(embarque,posicao,arqEmb);
										excluirBagagem(posicaoA,arqBag);
										printf("\nBagagem de mão excluida com sucesso!");
									}
									else{
										printf("\nCódigo da bagagem: %d",bagagem.codBA);
										printf("\nPeso da bagagem despachada :%d\n",bagagem.peso);
										excluirBagagem(posicaoA,arqBag);
										printf("\nBagagem despachada excluida com sucesso!");
									}
								}
							}
							printf("\n\n*** Aperte enter para voltar ***\n\n");
							getchar();
							getchar();
						break;
						case 3:
							system("cls");
							printf("\n\n*** consultar Bagagem ***\n");
							listarViagem(arqVia,1);
							printf("\nDigite o código da viagem: ");
							scanf("%d", &codigoV);
							posicao = consultarViagem(codigoV, arqVia);
							if (posicao == -1){
								textcolor(12); printf("Erro: código nao localizado\n");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							system("cls");
							printf("\n\n*** consultar Bagagem ***\n");
							listarEmbarque(arqEmb,1,codigoV);
							printf("\nDigite o código do embarque: ");
							scanf("%d",&codigoE);
							posicao = consultarEmbarque(codigoV,codigoE,arqEmb,0);
							system("cls");
							printf("\n\n*** consultar Bagagem ***\n");
							if (posicao != -1){
								listarBagagem(arqEmb,arqBag,codigoE,codigoV,posicao,0);
							}
							else{
								textcolor(12); printf("\nErro: código nao localizado!!!\n");textcolor(15);
							}
							printf("\n\n*** Aperte enter para voltar ***\n\n");
							getchar();
							getchar();
							break;
						case 4:
							system("cls");
							printf("\n\n*** Alterar Bagagem ***\n");
							listarViagem(arqVia,1);
							printf("\nDigite o código da viagem: ");
							scanf("%d", &codigoV);
							system("cls");
							printf("\n\n*** Alterar Bagagem ***\n");
							posicao = consultarViagem(codigoV, arqVia);
							if (posicao == -1){
								textcolor(12); printf("Erro: código nao localizado\n");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							listarEmbarque(arqEmb,1,codigoV);
							printf("\nDigite o código do embarque: ");
							scanf("%d",&codigoE);
							system("cls");
							printf("\n\n*** Alterar Bagagem ***\n");
							posicao = consultarEmbarque(codigoV,codigoE,arqEmb,0);
							if (posicao == -1){
								textcolor(12); printf("Erro: Embarque não encontrado");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							else{
								listarBagagem(arqEmb,arqBag,codigoE,codigoV,posicao,1);
								printf("\n\nDigite o código da bagagem que será alterada: ");
								scanf("%d",&codigoB);
								posicao = consultarEmbarque(codigoV,codigoE,arqEmb,0);
								posicaoA = consultarBagagem(codigoB,codigoV,codigoE,arqBag);
								embarque = lerEmbarque(posicao,arqEmb);
								if (posicaoA == -1){
									textcolor(12); printf("Erro: Código da bagagem Não localizado");textcolor(15);
									printf("\n\n*** Aperte enter para voltar ***\n\n");
									getchar();
									getchar();
									break;
								}
								else{
									bagagem = lerBagagem(posicaoA,arqBag);
									printf("\nDados Atuais - \n");
									if(bagagem.tipo == 0){
										printf("\nCódigo da bagagem: %d",bagagem.codBA);
										printf("\nPeso da bagagem de mão :%d",bagagem.peso);
										embarque.qtdbagm --;
										gravarEmbarque(embarque,posicao,arqEmb);
									}
									else{
										printf("\nCódigo da bagagem: %d",bagagem.codBA);
										printf("\nPeso da bagagem despachada :%d\n",bagagem.peso);
									}
									printf("\nDigite o novo código da bagagem: ");
									scanf("%d",&codigoB);
									bagagem.codBA = codigoB;
									posicaoA2 = consultarBagagem(codigoB,codigoV,codigoE,arqBag);
									if ((posicaoA2 != -1) && (codigoB != bagagem.codBA)){
										textcolor(12); printf("Erro: Código da bagagem já registrado");textcolor(15);
										printf("\n\n*** Aperte enter para voltar ***\n\n");
										getchar();
										getchar();
										break;
									}
									else{
										do{
											printf("Digite o peso da sua bagagem (Acima de 10KG a bagagem e despachada): ");
											scanf("%d",&bagagem.peso);
											if (bagagem.peso < 1){
												textcolor(12);	printf("Erro: Peso digitado invalido!!!");textcolor(15);
												break;
											}	
											if (bagagem.peso > 10){
												bagagem.tipo = 1;// despache
												gravarBagagem(bagagem,posicaoA,arqBag);
											}
											else{
												if (embarque.qtdbagm == 2){
													textcolor(12); printf("Quantidade máxima de 2 bagagens de mão por assento atingida!!!");textcolor(15);
												}
												else{
													bagagem.tipo = 0; // Mão
													embarque.qtdbagm++;
													gravarEmbarque(embarque,posicao,arqEmb);
													gravarBagagem(bagagem,posicaoA,arqBag);
												}
											}
											printf("\n\n*** Aperte enter para voltar ***\n\n");
											getchar();
											getchar();
										}while (bagagem.peso < 0);
									}	
								}
							}
						break;
						case 5:
							system("cls");
							printf("\n\n*** listar Bagagem ***\n");
							listarViagem(arqVia,1);
							printf("\nDigite o código da viagem: ");
							scanf("%d", &codigoV);
							posicao = consultarViagem(codigoV, arqVia);
							if (posicao == -1){
								textcolor(12); printf("Erro: código nao localizado\n");textcolor(15);
								printf("\n\n*** Aperte enter para voltar ***\n\n");
								getchar();
								getchar();
								break;
							}
							system("cls");
							printf("\n\n*** listar Bagagem ***\n");
							listarBagagem(arqEmb,arqBag,codigoE,codigoV,posicao,2);	
							printf("\n\n*** Aperte enter para voltar ***\n\n");
							getchar();
							getchar();
					}		
				}while(opcaoB != 0);
				system("cls");
				break;
		}
	}while(opcao != 0);
	ExclusaoFisicaEM("embarque.dat",arqEmb);
	ExclusaoFisica("viagem.dat",arqVia);
	ExclusaoFisicaEM("bagagem.dat",arqBag);
	ExclusaoFisicaAS("assento.dat",arqAss);
	fclose(arqVia);
	fclose(arqEmb);
	fclose(arqAss);
	fclose(arqBag);
return 0;
}
//Menu Principal***************************************************************
int menuPrincipal(void){
	int opcao;
	printf("\n\n*** Menu ***\n\n");
	printf("1- Viagens\n");
	printf("2- Embarque\n");
	printf("3- Bagagem\n");
	printf("0- Sair\n\n");
	printf("Escolha uma Alternativa: ");
	scanf("%d", &opcao);
	return opcao;
}
// Menu de entidade (CRUD) ****************************************************
int menuEntidade(char entidade[],int tipo) {
	int opcao;
	printf("\n\n*** Menu de Cadastro de %s ***\n\n", entidade);
	printf("1. Incluir %s\n", entidade);
	printf("2. Excluir %s\n", entidade);
	printf("3. Consultar %s\n", entidade);
	printf("4. Alterar %s\n",entidade);
	printf("5. Listar %s\n", entidade);
	if (tipo == 1)
		printf("6. Listar Assentos\n");
	printf("0. Voltar\n\n");
	printf("Escolha uma Alternativa: ");
	scanf("%d", &opcao);
	return opcao;
}
// Abrir arquivo **************************************************************
FILE *abrirArquivo(char nome[]) {
	FILE *arq=fopen(nome, "r+b");
	if (arq == NULL)
		arq = fopen(nome, "w+b");
	return arq;
}
// Ler registro de viagem *************************************************
struct tViagem lerViagem(int pos, FILE *arqVia) {
	struct tViagem via;
	fseek(arqVia, sizeof(via)*pos, SEEK_SET); // posiciona no registro "pos"
	fread(&via, sizeof(via), 1, arqVia);
	return via;
}
// Gravar um registro de Viagem *******************************************
void gravarViagem(struct tViagem via, int pos, FILE *arqVia) {
	if (pos == -1) { // inclusao de um novo
		via.deletadoV = ' ';
		fseek(arqVia, 0, SEEK_END); // posiciona no final do arquivo
	}
	else
		fseek(arqVia, sizeof(via)*pos, SEEK_SET); // posiciona no registro "pos"
	fwrite(&via, sizeof(via), 1, arqVia);
}
// Consultar viagem **********************************************************
int consultarViagem(int cod, FILE *arqVia) {
	int i=0;
	struct tViagem via;
	fseek(arqVia, 0, SEEK_SET); // posiciona no inicio do arquivo
	while (fread(&via, sizeof(via), 1, arqVia)) {
		if ((via.deletadoV != '*') && (via.codVia == cod))
			return i; // achei
		i++;
	}
	return -1; // nao achei!
}
// excluir Viagem ****************************************************************
void excluirViagem(int pos, FILE *arqVia) {
	struct tViagem via=lerViagem(pos, arqVia);
	via.deletadoV = '*';
	gravarViagem(via, pos, arqVia);
}
// Listar viagens *************************************************************
void listarViagem(FILE *arqVia,int tipo) {
	struct tViagem via;
	fseek(arqVia, 0, SEEK_SET); // posiciona no inicio do arquivo
	while ((fread(&via, sizeof(via), 1, arqVia)) && (tipo == 0)){
		if (via.deletadoV != '*'){
			printf("--------------------------------------------\n\n");
			printf("Código da viagem: %d\n",via.codVia);
			printf("Origem da viagem: %s\n", via.origem);
			printf("Destino da viagem: %s\n", via.destino);
			printf("Data: %02d/%02d/%d\n", via.diaV, via.mesV,via.anoV);
			printf("horario da viagem: %02d:%02d\n",via.horaV, via.minuV);
			printf("Quantidade de assentos disponíveis: %d\n",via.qtdassentos);
		}
	}
	fseek(arqVia, 0, SEEK_SET); // posiciona no inicio do arquivo
	while ((fread(&via, sizeof(via), 1, arqVia)) && (tipo == 1)){
		if (via.deletadoV != '*'){
			printf("--------------------------------------------\n\n");
			printf("Código da viagem: %d\n",via.codVia);
		}
	}
}
// Excluir Fisicamente via*************************************************************
int ExclusaoFisica(char nome[],FILE *arqVia){
	FILE *arqAux=abrirArquivo("viagem.aux");
	struct tViagem via;
	if (arqAux == NULL)
		return 0;
	fseek(arqVia, 0, SEEK_SET); // posiciona no inicio do arquivo
	while (fread(&via, sizeof(via), 1, arqVia)) {
		if (via.deletadoV != '*'){
			fwrite(&via,sizeof(via),1,arqAux);
		}
	}
	fclose(arqVia);
	fclose(arqAux);
	remove(nome);
	rename("viagem.aux", nome);
	arqVia = abrirArquivo(nome);
	if (arqVia == NULL) {
		textcolor(12); printf("Erro de organizacao!!!");textcolor(15);
		return 0;
	}	
	
	return 1;
}
//Gravar embarque*********************************************************************************
void gravarEmbarque(struct tEmbarque emb, int pos, FILE *arqEmb) {
	if (pos == -1) { // inclusao de um novo
		emb.deletadoEM = ' ';
		fseek(arqEmb, 0, SEEK_END); // posiciona no final do arquivo
	}
	else
		fseek(arqEmb, sizeof(emb)*pos, SEEK_SET); // posiciona no registro "pos"
	fwrite(&emb, sizeof(emb), 1, arqEmb);
}
// listar embarque **************************************************
void listarEmbarque(FILE *arqEmb, int tipo,int cod) {
	struct tEmbarque emb;
	fseek(arqEmb, 0, SEEK_SET); // posiciona no inicio do arquivo
	while (fread(&emb, sizeof(emb), 1, arqEmb) && (tipo == 0)) {
		if ((emb.deletadoEM != '*') && (emb.codEV == cod)){
			printf("--------------------------------------------\n\n");
			printf("Nome do Passageiro: %s\n",emb.nomeP);
			printf("Código do Embarque: %d\n",emb.codEM);
			printf("Número do assentro: %d\n",emb.assentoEM);
		}
	}
	fseek(arqEmb, 0, SEEK_SET); // posiciona no inicio do arquivo
	while (fread(&emb, sizeof(emb), 1, arqEmb)  && (tipo == 1)) {
		if ((emb.deletadoEM != '*') && (emb.codEV == cod)){
			printf("--------------------------------------------\n\n");
			printf("Código do Embarque: %d\n",emb.codEM);
		}
	}
}
// consulta embarque expecifico*****************************************
int consultarEmbarque(int codV,int cod,FILE *arqEmb,int tipo) {
	int i=0;
	struct tEmbarque emb;
	fseek(arqEmb, 0, SEEK_SET); // posiciona no inicio do arquivo
	if (tipo == 0){
	while (fread(&emb, sizeof(emb), 1, arqEmb)) {
		if ((emb.deletadoEM != '*') && (emb.codEM == cod) && (emb.codEV == codV))
			return i; // achei
		i++;
	}
	return -1; // nao achei!
	}
	if (tipo == 1){
	while (fread(&emb, sizeof(emb), 1, arqEmb)) {
		if ((emb.deletadoEM != '*') && (emb.codEM == cod) && (emb.codEV == codV))
			return i; // achei
		i++;
	}
	return -1; // nao achei!
	}
}
// ler embarque******************************************************
struct tEmbarque lerEmbarque(int pos, FILE *arqEmb) {
	struct tEmbarque emb;
	fseek(arqEmb, sizeof(emb)*pos, SEEK_SET); // posiciona no registro "pos"
	fread(&emb, sizeof(emb), 1, arqEmb);
	return emb;
}
//Excluir logicamente embarque**********************************
void excluirEmbarque(int pos, FILE *arqEmb) {
	struct tEmbarque emb=lerEmbarque(pos, arqEmb);
	emb.deletadoEM = '*';
	gravarEmbarque(emb, pos, arqEmb);
}
// Excluir Fisicamente emb*************************************************************
int ExclusaoFisicaEM(char nome[],FILE *arqEmb){
	FILE *arqAux=abrirArquivo("embarque.aux");
	struct tEmbarque emb;
	if (arqAux == NULL)
		return 0;
	fseek(arqEmb, 0, SEEK_SET); // posiciona no inicio do arquivo
	while (fread(&emb, sizeof(emb), 1, arqEmb)) {
		if (emb.deletadoEM != '*'){
			fwrite(&emb,sizeof(emb),1,arqAux);
		}
	}
	fclose(arqEmb);
	fclose(arqAux);
	remove(nome);
	rename("embarque.aux", nome);
	arqEmb = abrirArquivo(nome);
	if (arqEmb == NULL) {
		textcolor(12); printf("Erro de organizacao!!!");textcolor(15);
		return 0;
	}	
	return 1;
}
// Gravar um registro de Viagem *******************************************
void gravarAssento(struct tAssento ass, int pos, FILE *arqAss) {
	if (pos == -1) { // inclusao de um novo
		fseek(arqAss, 0, SEEK_END); // posiciona no final do arquivo
	}
	else
		fseek(arqAss, sizeof(ass)*pos, SEEK_SET); // posiciona no registro "pos"
	fwrite(&ass, sizeof(ass), 1, arqAss);
}
//listar assentos**********************************************************
void listarAssento(FILE *arqAss,int cod) {
	struct tAssento ass;
	fseek(arqAss, 0, SEEK_SET); // posiciona no inicio do arquivo
	printf("\nNúmero dos Assentos disponiveis: ");
	while (fread(&ass, sizeof(ass), 1, arqAss)){
		if ((cod == ass.codASV) && (ass.dipoA == 0))
			printf("%d ",ass.numeasst);
	}
}
// Consultar Assento **********************************************************
int consultarAssento(int codV, int codA, FILE *arqAss,int tipo) {
	int i=0;
	struct tAssento ass;
	fseek(arqAss, 0, SEEK_SET); // posiciona no inicio do arquivo
	while ((fread(&ass, sizeof(ass), 1, arqAss)) && (tipo != 1)){
		if ((ass.dipoA == 0) && (ass.codASV == codV) && (ass.numeasst == codA))
			return i; // achei
		i++;
	}
	fseek(arqAss, 0, SEEK_SET); // posiciona no inicio do arquivo
	while ((fread(&ass, sizeof(ass), 1, arqAss)) && (tipo = 1)){
		if ((ass.dipoA == 1) && (ass.codASV == codV) && (ass.numeasst == codA))
			return i; // achei	
		i++;
	}
	return -1; // nao achei!
}
// ler embarque******************************************************
struct tAssento lerAssento(int pos, FILE *arqAss) {
	struct tAssento ass;
	fseek(arqAss, sizeof(ass)*pos, SEEK_SET); // posiciona no registro "pos"
	fread(&ass, sizeof(ass), 1, arqAss);
	return ass;
}
//Gravar Bagagem*********************************************************************************
void gravarBagagem(struct tBagagem bag, int pos, FILE *arqBag) {
	if (pos == -1){ // inclusao de um novo
		bag.deletadoBA = ' ';
		fseek(arqBag, 0, SEEK_END);
	} // posiciona no final do arquivo
	else
		fseek(arqBag, sizeof(bag)*pos, SEEK_SET); // posiciona no registro "pos"
	fwrite(&bag, sizeof(bag), 1, arqBag);
}
//Listar bagagem*********************************************************************************
void listarBagagem(FILE *arqEmb,FILE *arqBag,int codE,int codV,int pos,int tipo) {
	struct tBagagem bag;
	struct tEmbarque emb;
	emb = lerEmbarque(pos,arqEmb);
	fseek(arqBag, 0, SEEK_SET); // posiciona no inicio do arquivo
	printf("--------------------------------------------\n\n");
	if (tipo == 0){
			printf("Dono das bagagens: %s\n",emb.nomeP);
		while (fread(&bag, sizeof(bag), 1, arqBag)){
			if ((codE == bag.codBAE) && (codV == bag.codBAV) && (bag.deletadoBA != '*')){
				if (bag.tipo == 0){
					printf("\nCódigo da bagagem: %d",bag.codBA);
					printf("\nBagagem de mão, peso = %d KG\n",bag.peso);
				}
				else{
					printf("\nCódigo da bagagem: %d",bag.codBA);
					printf("\nBagagem despachada, peso = %d KG\n",bag.peso);
				}
			}
		}
		printf("\n\n--------------------------------------------");
	}
	if (tipo == 1){
		printf("Dono das bagagens: %s\n",emb.nomeP);
		while (fread(&bag, sizeof(bag), 1, arqBag)){
			if ((codE == bag.codBAE) && (codV == bag.codBAV) && (bag.deletadoBA != '*') && (bag.tipo == 0)){
				printf("\nCódigo da bagagem: %d",bag.codBA);
				printf("\nBagagem de mão, peso = %d Kg",bag.peso);
				printf("\n\n--------------------------------------------");
			}
			else if ((codE == bag.codBAE) && (codV == bag.codBAV) && (bag.deletadoBA != '*') && (bag.tipo == 1)){
				printf("\nCódigo da bagagem: %d",bag.codBA);
				printf("\nBagagem despachada, peso = %d Kg\n",bag.peso);
				printf("\n\n--------------------------------------------");	
			}		
		}
	}
	if (tipo == 2){	
		while (fread(&bag, sizeof(bag), 1, arqBag)){
			fseek(arqEmb, 0, SEEK_SET);
			if ((bag.deletadoBA != '*') && (codV == bag.codBAV)){
				if (bag.tipo == 0) {
					while (fread(&emb, sizeof(emb), 1, arqEmb)) {
						if ((emb.codEV == bag.codBAV) && (emb.codEM == bag.codBAE))
							printf("Dono das bagagens: %s",emb.nomeP);
						}
					printf("\nCódigo da bagagem: %d",bag.codBA);
					printf("\nBagagem de mão, peso = %d Kg\n",bag.peso);
				}
				else{
					while (fread(&emb, sizeof(emb), 1, arqEmb)) {
						if ((emb.codEV == bag.codBAV) && (emb.codEM == bag.codBAE))
							printf("Dono das bagagens: %s",emb.nomeP);
						}
					printf("\nCódigo da bagagem: %d",bag.codBA);
					printf("\nBagagem despachada, peso = %d Kg\n",bag.peso);
				}
				printf("\n\n--------------------------------------------\n\n");
			}	
		}
	}
}
//consultar bagagem*********************************************************************************
int consultarBagagem(int codB,int codV,int codE,FILE * arqBag) {
	int i=0;
	struct tBagagem bag;
	fseek(arqBag, 0, SEEK_SET); // posiciona no inicio do arquivo
	while (fread(&bag, sizeof(bag), 1, arqBag)) {
		if ((codE == bag.codBAE) && (codV == bag.codBAV) && (codB == bag.codBA) && (bag.deletadoBA != '*'))
			return i; // achei
		i++;
	}
	return -1; // nao achei!
}
// Ler Bagagem *************************************************
struct tBagagem lerBagagem(int pos, FILE *arqBag) {
	struct tBagagem bag;
	fseek(arqBag, sizeof(bag)*pos, SEEK_SET); // posiciona no registro "pos"
	fread(&bag, sizeof(bag), 1, arqBag);
	return bag;
}
//Excluir logicamente bagagem**********************************
void excluirBagagem(int pos, FILE *arqBag) {
	struct tBagagem bag=lerBagagem(pos, arqBag);
	bag.deletadoBA = '*';
	gravarBagagem(bag, pos, arqBag);
}
// Excluir Fisicamente bag*************************************************************
int ExclusaoFisicaBA(char nome[],FILE *arqBag){
	FILE *arqAux=abrirArquivo("bagagem.aux");
	struct tBagagem bag;
	if (arqAux == NULL)
		return 0;
	fseek(arqBag, 0, SEEK_SET); // posiciona no inicio do arquivo
	while (fread(&bag, sizeof(bag), 1, arqBag)) {
		if (bag.deletadoBA != '*'){
			fwrite(&bag,sizeof(bag),1,arqAux);
		}
	}
	fclose(arqBag);
	fclose(arqAux);
	remove(nome);
	rename("bagagem.aux", nome);
	arqBag = abrirArquivo(nome);
	if (arqBag == NULL) {
		textcolor(12); printf("Erro de organizacao!!!");textcolor(15);
		return 0;
	}
	return 1;
}
//Excluir logicamente todas as bagagens de um embarque**********************************
int excluirTodasBagagem(char nome[],int codV,int codE, FILE *arqBag){
	FILE *arqAux=abrirArquivo("bagagem.aux");
	struct tBagagem bag;
	if (arqAux == NULL)
		return 0;
	fseek(arqBag, 0, SEEK_SET); // posiciona no inicio do arquivo
	while (fread(&bag, sizeof(bag), 1, arqBag)) {
		if ((bag.deletadoBA != '*') && (codV != bag.codBAV) && (codE != bag.codBAE)){
			fwrite(&bag,sizeof(bag),1,arqAux);
		}
	}
	fclose(arqBag);
	fclose(arqAux);
	remove(nome);
	rename("bagagem.aux", nome);
	arqBag = abrirArquivo(nome);
	if (arqBag == NULL) {
		textcolor(12); printf("Erro de organizacao!!!");textcolor(15);
		return 0;
	}
	return 1;
}
//Excluir Assentos de uma viagem**********************************
int excluirTodosAssento(char nome[],int codV, FILE *arqAss){
	FILE *arqAux=abrirArquivo("assento.aux");
	struct tAssento ass;
	if (arqAux == NULL)
		return 0;
	fseek(arqAss, 0, SEEK_SET); // posiciona no inicio do arquivo
	while (fread(&ass, sizeof(ass), 1, arqAss)) {
		if ((ass.deletadoAS != '*') && (ass.codASV != codV)){
			fwrite(&ass,sizeof(ass),1,arqAux);
		}
	}
	fclose(arqAss);
	fclose(arqAux);
	remove(nome);
	rename("assento.aux", nome);
	arqAss = abrirArquivo(nome);
	if (arqAss == NULL) {
		textcolor(12); printf("Erro de organizacao!!!");textcolor(15);
		return 0;
	}	
	return 1;
}

// Excluir Fisicamente ass*************************************************************
int ExclusaoFisicaAS(char nome[],FILE *arqAss){
	FILE *arqAux=abrirArquivo("assento.aux");
	struct tAssento ass;
	if (arqAux == NULL)
		return 0;
	fseek(arqAss, 0, SEEK_SET); // posiciona no inicio do arquivo
	while (fread(&ass, sizeof(ass), 1, arqAss)) {
		if (ass.deletadoAS != '*'){
			fwrite(&ass,sizeof(ass),1,arqAux);
		}
	}
	fclose(arqAss);
	fclose(arqAux);
	remove(nome);
	rename("assento.aux", nome);
	arqAss = abrirArquivo(nome);
	if (arqAss == NULL) {
		textcolor(12); printf("Erro de organizacao!!!");textcolor(15);
		return 0;
	}	
	return 1;
}
