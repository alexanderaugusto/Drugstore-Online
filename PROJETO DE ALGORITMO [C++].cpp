#include <iostream>
#include <iomanip>
#include <clocale>
#include <cstring>
#include <fstream>
#include <windows.h>
#include <cmath>

using namespace std;

struct ELEMENTOS
{
	char NOMEREMEDIO[100];
	char INDICACAO[10000];
	char CONTRAINDICACAO[10000];
	int CODIGO;
	double PRECO;
	int QUANTIDADE;
	bool EXCLUIDO;
};

ELEMENTOS info;

fstream ARQUIVO;

void CADASTRAR()
{
	system("cls");

	int contQUANTIDADE = 0;
	int contPRECO = 0;
	int contCODIGO = 0;
	int TAMANHOCODIGO;

	ARQUIVO.seekp(0 , ARQUIVO.end);

	cout << "\t\t\tMuito bem! Preencha os dados abaixos:" << endl;
	cout << endl;

	cout << "\t\t\tNome do medicamento: ";
	cin.ignore();
	cin.getline(info.NOMEREMEDIO, 100);
	
	// VERIFICANDO QUANTIDADE
	do
	{
		if(contQUANTIDADE == 0)
		{
			cout << "\t\t\tQuantidade de medicamentos: ";
			cin >> info.QUANTIDADE;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
		}

		else
		{
			cout << "\t\t\tQuantidade inv�lido! Por favor, digite um n�mero v�lido." << endl;
			cout << "\t\t\tDigite aqui: ";
			cin >> info.QUANTIDADE;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cout << endl;
		}
		contQUANTIDADE++;
	}
	while(info.QUANTIDADE <= 0);
	
	// VERIFICANDO PRECO
	do
	{
		if(contPRECO == 0)
		{
			cout << "\t\t\tPre�o do medicamento por unidade: R$ ";
			cin >> info.PRECO;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
		}

		else
		{
			cout << "\t\t\tPre�o inv�lido! Por favor, digite um n�mero v�lido." << endl;
			cout << "\t\t\tDigite aqui: ";
			cin >> info.PRECO;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cout << endl;
		}
		contPRECO++;

	}
	while(info.PRECO <= 0);
	
	// VERIFICANDO PRINCIPAL INDICACAO
	cout << "\t\t\tPrincipal indica��o: ";
	cin.ignore();
	cin.getline(info.INDICACAO, 100);
	
	// VERIFICANDO CONTRA INDICACAO
	cout << "\t\t\tContra indica��o: ";
	cin.getline(info.CONTRAINDICACAO, 100);
	
	// VERIFICANDO CODIGO
	do
	{
		if(contCODIGO == 0)
		{
			cout << "\t\t\tC�digo(5-10): ";
			cin >> info.CODIGO;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cout << endl;
			TAMANHOCODIGO = floor(1 + log10(info.CODIGO));
			contCODIGO++;
		}

		else
		{
			cout << "\t\t\tC�digo inv�lido! O c�digo deve ter no m�nimo 5 caracteres e no m�ximo 10 caracteres." << endl;

			cout << "\t\t\tDigite novamente: ";
			cin >> info.CODIGO;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cout << endl;
			TAMANHOCODIGO = floor(1 + log10(info.CODIGO));
		}

	}
	while(TAMANHOCODIGO < 5 || TAMANHOCODIGO > 10);

	cout << "\t\t\tMEDICAMENTO EM ESTOQUE!" << endl;
	cout << endl;

	ARQUIVO.write((char*)&info, sizeof(info));

	system("pause");

}

void LISTAR()
{
	ELEMENTOS info;

	system("cls");

	cout << endl;
	cout << "\t\t\t\tLISTA DE MEDICAMENTOS: " << endl;
	cout << endl;
	cout << endl;

	ARQUIVO.seekg(0, ARQUIVO.beg);
	while(ARQUIVO.read((char *) &info, sizeof(info)))
	{
		if(info.EXCLUIDO == false)
		{
			cout << "\t\tNome do medicamento: " << info.NOMEREMEDIO << endl;
			cout << "\t\tUnidades dispon�veis: " << info.QUANTIDADE << " unidade(s)" << endl;
			{
				cout << fixed << setprecision(2);
				cout << "\t\tPre�o do medicamento(por unidade): R$ " << info.PRECO << " reais" << endl;
			}
			cout << "\t\tPrincipal indica��o: " << info.INDICACAO << endl;
			cout << "\t\tContra indica��o: " << info.CONTRAINDICACAO << endl;
			cout << "\t\tC�DIGO: " << info.CODIGO << endl;
			cout << endl;
			cout << "\t\t______________________________________________" << endl;
			cout << endl;
		}
	}
	ARQUIVO.clear();

	system("pause");

}

void EDITAR()
{
	system("cls");

	int COD;
	int ALTERA;
	int contALTERA = 0;
	int contCOD = 0;
	int contCODIGO = 0;
	int contPRECO = 0;
	int contQUANTIDADE = 0;
	int contPASSOUAQUI = 0;
	int TAMANHOCODIGO;

	do
	{
		if(contCOD == 0 && info.EXCLUIDO == false)
		{
			cout << "\t\t\tDeseja editar algum medicamento? Por favor, digite o c�digo dele abaixo " << endl;
			cout << "\t\t\tDigite aqui: ";
			cin >> COD;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cout << endl;
		}

		else
		{
			cout << "\t\t\tCaracter inv�lido! Por favor, digite um caracter v�lido. " << endl;
			cout << "\t\t\tDigite aqui: ";
			cin >> COD;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cout << endl;
		}
		contCOD++;
	}
	while(COD < 0);

	ARQUIVO.seekg(0, ARQUIVO.beg);
	while (ARQUIVO.read((char*)&info, sizeof(info)))
	{
		if (COD == info.CODIGO && info.EXCLUIDO == false)
		{
			cout << "\t\t\tMEDICAMENTO DE C�DIGO " << info.CODIGO << ":" << endl;
			cout << endl;
			cout << "\t\t\tNome do medicamento: " << info.NOMEREMEDIO << endl;
			cout << "\t\t\tUnidades dispon�veis: " << info.QUANTIDADE << " unidade(s)" << endl;
			{
				cout << fixed << setprecision(2);
				cout << "\t\t\tPre�o do medicamento(por unidade): R$ " << info.PRECO << " reais" << endl;
			}
			cout << "\t\t\tPrincipal indica��o: " << info.INDICACAO << endl;
			cout << "\t\t\tContra indica��o: " << info.CONTRAINDICACAO << endl;
			cout << endl;

			contPASSOUAQUI++;

			cout << "\t\t\tO QUE DESEJA EDITAR NESTE MEDICAMENTO? " << endl;
			cout << endl;
			cout << "\t\t\t1 - Nome do medicamento  " << endl;
			cout << "\t\t\t2 - Quantidade de medicamento " << endl;
			cout << "\t\t\t3 - Pre�o do medicamento  " << endl;
			cout << "\t\t\t4 - Principal indica��o do medicamento " << endl;
			cout << "\t\t\t5 - Contra indica��o do medicamento " << endl;
			cout << "\t\t\t6 - C�digo do medicamento " << endl;
			cout << endl;
			cout << endl;

			do
			{
				if(contALTERA == 0)
				{
					cout << "\t\t\tOp��o escolhida: ";
					cin >> ALTERA;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(256, '\n');
					}
					cout << endl;
				}
				else
				{
					cout << "\t\t\tCaracter inv�lido! Por favor, digite um caracter correspondente. " << endl;
					cout << "\t\t\tDigite aqui: ";
					cin >> ALTERA;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(256, '\n');
					}
					cout << endl;
				}
				contALTERA++;
			}
			while(ALTERA < 1 || ALTERA > 6);

			switch(ALTERA)
			{
			case 1:
				cout << "\t\t\tNovo nome do medicamento: ";
				cin.ignore();
				cin.getline(info.NOMEREMEDIO, 100);
				cout << endl;
				break;

			case 2:
				do
				{
					if(contQUANTIDADE == 0)
					{
						cout << "\t\t\tNova quantidade de medicamentos: ";
						cin.ignore();
						cin >> info.QUANTIDADE;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(256, '\n');
						}
						cout << endl;
					}

					else
					{
						cout << endl;
						cout << "\t\t\tQuantidade inv�lido! Por favor, digite um n�mero v�lido." << endl;
						cout << "\t\t\tDigite aqui: ";
						cin >> info.QUANTIDADE;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(256, '\n');
						}
						cout << endl;
					}
					contQUANTIDADE++;
				}
				while(info.QUANTIDADE <= 0);
				break;

			case 3:
				do
				{
					if(contPRECO == 0)
					{
						cout << "\t\t\tNovo pre�o do medicamento: ";
						cin.ignore();
						cin >> info.PRECO;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(256, '\n');
						}
						cout << endl;
					}

					else
					{
						cout << endl;
						cout << "\t\t\tPre�o inv�lido! Por favor, digite um n�mero v�lido." << endl;
						cout << "\t\t\tDigite aqui: ";
						cin >> info.PRECO;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(256, '\n');
						}
						cout << endl;
					}
					contPRECO++;
				}
				while(info.PRECO <= 0);
				break;

			case 4:
				cout << "\t\t\tNova indica��o do medicamento: ";
				cin.ignore();
				cin.getline(info.INDICACAO, 100);
				cout << endl;
				break;

			case 5:
				cout << "\t\t\tNova contra indica��o do medicamento: ";
				cin.ignore();
				cin.getline(info.CONTRAINDICACAO, 100);
				cout << endl;
				break;

			case 6:
				do
				{
					if(contCODIGO == 0)
					{
						cout << "\t\t\tC�digo(5-10): ";
						cin >> info.CODIGO;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(256, '\n');
						}
						cout << endl;
						TAMANHOCODIGO = floor(1 + log10(info.CODIGO));
						contCODIGO++;
					}

					else
					{
						cout << "\t\t\tC�digo inv�lido! O c�digo deve ter no m�nimo 5 caracteres e no m�ximo 10 caracteres." << endl;
						cout << "\t\t\tDigite novamente: ";
						cin >> info.CODIGO;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(256, '\n');
						}
						cout << endl;
						TAMANHOCODIGO = floor(1 + log10(info.CODIGO));
					}

				}
				while(TAMANHOCODIGO < 5 || TAMANHOCODIGO > 10);
				break;
			}


			ARQUIVO.seekp(ARQUIVO.tellp() - sizeof(info), ARQUIVO.beg);
			ARQUIVO.write((char*)&info, sizeof(info));
		}
	}
	ARQUIVO.clear();

	if(contPASSOUAQUI == 0)
	{
		cout << "\t\t\tN�o h� medicamentos com esse c�digo! Por favor, tente novamente." << endl;
		cout << endl;
	}

	system("pause");
}

void EXCLUIR()
{
	int COD;
	int CONFIRMA;
	int contCONFIRMA = 0;
	int contCOD = 0;
	int contPASSOUAQUI = 0;

	system("cls");

	do
	{
		if(contCOD == 0)
		{
			cout << "\t\t\tDeseja excluir algum medicamento? Por favor, digite o c�digo dele abaixo. " << endl;
			cout << "\t\t\tDigite aqui: ";
			cin >> COD;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cout << endl;
		}

		else
		{
			cout << "\t\t\tCaracter inv�lido! Por favor, digite um caracter v�lido. " << endl;
			cout << "\t\t\tDigite aqui: ";
			cin >> COD;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cout << endl;
		}
		contCOD++;
	}
	while(COD < 0);

	ARQUIVO.seekg(0, ARQUIVO.beg);
	while (ARQUIVO.read((char*)&info, sizeof(info)))
	{
		if (COD == info.CODIGO && info.EXCLUIDO == false)
		{
			cout << "\t\t\tMEDICAMENTO DE C�DIGO " << info.CODIGO << ":" << endl;
			cout << endl;
			cout << "\t\t\tNome do medicamento: " << info.NOMEREMEDIO << endl;
			cout << "\t\t\tUnidades dispon�veis: " << info.QUANTIDADE << " unidade(s)" << endl;
			{
				cout << fixed << setprecision(2);
				cout << "\t\t\tPre�o do medicamento(por unidade): R$ " << info.PRECO << " reais" << endl;
			}
			cout << "\t\t\tPrincipal indica��o: " << info.INDICACAO << endl;
			cout << "\t\t\tContra indica��o: " << info.CONTRAINDICACAO << endl;
			cout << endl;

			contPASSOUAQUI++;
			do
			{
				if(contCONFIRMA == 0)
				{
					cout << "\t\t\tDeseja mesmo excluir este medicamento?" << endl;
					cout << endl;
					cout << "\t\t\t1 - Desejo excluir" << endl;
					cout << "\t\t\t2 - N�o desejo excluir" << endl;
					cout << endl;
					cout << "\t\t\tDigite aqui: ";
					cin >> CONFIRMA;
					cout << endl;
				}

				else
				{
					cout << "\t\t\tCaracter inv�lido! Por favor, digite um caracter correspondente. " << endl;
					cout << "\t\t\tDigite aqui: ";
					cin >> CONFIRMA;
					cout << endl;
				}
				contCONFIRMA++;

			}
			while(CONFIRMA != 1  && CONFIRMA != 2);

			if (CONFIRMA == 1)
			{
				ARQUIVO.seekp(ARQUIVO.tellp() - sizeof(info), ARQUIVO.beg);
				info.EXCLUIDO = true;
				ARQUIVO.write((char*)&info, sizeof(info));
				cout << endl;
				cout << "\t\t\tARQUIVO EXCLU�DO COM SUCESSO" << endl;
				cout << endl;
			}
		}
	}
	ARQUIVO.clear();


	if (contPASSOUAQUI == 0)
	{
		cout << "\t\t\tN�o h� medicamentos com esse c�digo! Por favor, tente novamente." << endl;
		cout << endl;
	}

	system("pause");
}

void PESQUISAR()
{
	int COD;
	int contCOD = 0;
	int contPASSOUAQUI = 0;

	system ("cls");

	do
	{
		if(contCOD == 0)
		{
			cout << "\t\t\tQual medicamento voc� deseja pesquisar? " << endl;
			cout << "\t\t\tDigite o c�digo dele aqui: ";
			cin >> COD;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cout << endl;
		}

		else
		{
			cout << "\t\t\tCaracter inv�lido! Por favor, digite um caracter v�lido. " << endl;
			cout << "\t\t\tDigite aqui: ";
			cin >> COD;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cout << endl;
		}
		contCOD++;
	}
	while(COD < 0);


	ARQUIVO.seekg(0, ARQUIVO.beg);
	while (ARQUIVO.read((char*)&info, sizeof(info)))
	{
		if(COD == info.CODIGO && info.EXCLUIDO == false)
		{
			contPASSOUAQUI++;
			cout << "\t\t\tMEDICAMENTO DE C�DIGO " << info.CODIGO << ": " << endl;
			cout << endl;
			cout << "\t\t\tNome do medicamento: " << info.NOMEREMEDIO << endl;
			cout << "\t\t\tUnidades d�spon�veis: " << info.QUANTIDADE << endl;
			cout << "\t\t\tPre�o do medicamento(por unidade): R$ " << info.PRECO << endl;
			cout << "\t\t\tPrincipal indica��o: " << info.INDICACAO << endl;
			cout << "\t\t\tContra indica��o: " << info.CONTRAINDICACAO << endl;
			cout << endl;
		}
	}
	ARQUIVO.clear();

	if(contPASSOUAQUI == 0)
	{
		cout << "\t\t\tN�o h� medicamentos com esse c�digo! por favor, tente novamente. " << endl;
		cout << endl;
	}

	system("pause");

}

void COMPRAR()
{
	system("cls");

	int COD;
	int UNIDADE;
	int contUNIDADE = 0;
	double PRECOTOTAL;
	int PAGAMENTO;
	int contPAGAMENTO = 0;
	int contPASSOUAQUI = 0;
	char NOME[100];
	char CPF[100];
	int TAMANHOCPF;
	int contCPF = 0;
	int CONFIRMA;
	int contCONFIRMA = 0;
	int TAMANHOCARTAO;
	char NUMERODOCARTAO[100];
	int contCARTAO = 0;
	int contPARCELAS = 0;
	double PARCELAS;
	int contOPCAO = 0;
	int OPCAO;
	char EMAIL[100];
	int CONTINUAR;
	int contCONTINUAR = 0;

	do
	{
		system("cls");

		contUNIDADE = 0;
		contPAGAMENTO = 0;
		contPASSOUAQUI = 0;
		contCPF = 0;
		contCONFIRMA = 0;
		contCARTAO = 0;
		contPARCELAS = 0;
		contOPCAO = 0;

		do
		{
			if(contOPCAO == 0)
			{
				cout << "\t\t\tOl� cliente. Deseja comprar algum medicamento? Use o c�digo do medicamento abaixo para compra-lo" << endl;
				cout << endl;
				cout << "\t\t\tVoc� se lembra do c�digo do medicamento que deseja?" << endl;
				cout << endl;
				cout << "\t\t\t1 - Sim, eu lembro o c�digo e quero continuar" << endl;
				cout << "\t\t\t2 - N�o, eu esqueci o c�digo do medicamento que desejo" << endl;
				cout << endl;
				cout << "\t\t\tOp��o escolhida: ";
				cin >> OPCAO;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(256, '\n');
				}
				cout << endl;

				contOPCAO++;
			}

			else
			{
				cout << "\t\t\tOp��o inv�lida! Digite um numero correspondente." << endl;
				cout << "\t\t\tDigite aqui: ";
				cin >> OPCAO;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(256, '\n');
				}
				cout << endl;
			}
		}
		while(OPCAO != 1 && OPCAO != 2);

		if(OPCAO == 2)
		{
			LISTAR();

			system("cls");

			cout << "\t\t\tDigite o c�digo do medicamento que deseja para compra-lo" << endl;
			cout << "\t\t\tDigite aqui: ";
			cin >> COD;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cout << endl;

		}

		else if(OPCAO == 1)
		{
			cout << "\t\t\tDigite o c�digo do medicamento que deseja para compra-lo" << endl;
			cout << "\t\t\tDigite aqui: ";
			cin >> COD;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cout << endl;
		}

		ARQUIVO.seekg(0, ARQUIVO.beg);
		while (ARQUIVO.read((char*)&info, sizeof(info)))
		{
			if (COD == info.CODIGO && info.EXCLUIDO == false)
			{
				contPASSOUAQUI++;

				do
				{
					if(contCONFIRMA == 0)
					{
						cout << "\t\t\tMEDICAMENTO DE C�DIGO " << info.CODIGO << ":" << endl;
						cout << endl;
						cout << "\t\t\tNome do medicamento: " << info.NOMEREMEDIO << endl;
						cout << "\t\t\tUnidades dispon�veis: " << info.QUANTIDADE << " unidade(s)" << endl;
						{
							cout << fixed << setprecision(2);
							cout << "\t\t\tPre�o do medicamento(por unidade): R$ " << info.PRECO << " reais" << endl;
						}
						cout << "\t\t\tPrincipal indica��o: " << info.INDICACAO << endl;
						cout << "\t\t\tContra indica��o: " << info.CONTRAINDICACAO << endl;
						cout << endl;

						cout << "\t\t\t� isso mesmo que o senhor deseja? " << endl;
						cout << endl;
						cout << "\t\t\t1 - Sim" << endl;
						cout << "\t\t\t2 - N�o" << endl;

						cout << endl;
						cout << "\t\t\tOp��o escolhida: ";
						cin >> CONFIRMA;
						cout << endl;

						contCONFIRMA++;
					}

					else
					{
						cout << "Caracter inv�lido! Por favor, digite um caracter correspondente. " << endl;
						cout << "Digite aqui: ";
						cin >> CONFIRMA;
					}
				}
				while(CONFIRMA != 1 && CONFIRMA != 2);

				if(CONFIRMA == 1)
				{
					cout << "\t\t\tDigite seu nome: ";
					cin.ignore();
					cin.getline(NOME, 100);
					cout << endl;

					do
					{
						if(contUNIDADE == 0)
						{
							cout << "\t\t\tQuantas unidades deste medicamento o senhor(a) deseja?" << endl;
							cout << "\t\t\tDigite aqui: ";
							cin >> UNIDADE;
							cout << endl;
						}

						else
						{
							cout << "\t\t\tQuantidade n�o dispon�vel! Digite uma quantidade v�lida" << endl;
							cout << "\t\t\tDigite aqui: ";
							cin >> UNIDADE;
							cout << endl;
						}
						contUNIDADE++;
					}
					while(UNIDADE > info.QUANTIDADE || UNIDADE <= 0);

					info.QUANTIDADE = (info.QUANTIDADE) - (UNIDADE);
					PRECOTOTAL = (info.PRECO) * (UNIDADE);

					cout << fixed << setprecision(2);
					cout << "\t\t\tTotal � ser pago: " << " R$ " << PRECOTOTAL << " reais" << endl;

					ARQUIVO.seekp(ARQUIVO.tellp() - sizeof(info) );
					ARQUIVO.write((char*)&info, sizeof(info));

					do
					{
						if(contPAGAMENTO == 0)
						{
							cout << "\t\t\tEscolha uma das formas de pagamento abaixo: " << endl;
							cout << endl;
							cout << "\t\t\t1 - Boleto Banc�rio" << endl;
							cout << "\t\t\t2 - Cart�o" << endl;
							cout << endl;
							cout << "\t\t\tOp��o Escolhida: ";
							cin >> PAGAMENTO;
							cout << endl;
						}

						else
						{
							cout << "\t\t\tOp��o inv�lida! Por favor, digite um caracter v�lido." << endl;
							cout << "\t\t\tDigite aqui: ";
							cin >> PAGAMENTO;
							cout << endl;
						}
						contPAGAMENTO++;

					}
					while(PAGAMENTO < 1 && PAGAMENTO > 2 );

					if (PAGAMENTO == 1)
					{
						cout << "\t\t\tE-mail: ";
						cin.ignore();
						cin.getline(EMAIL, 100);

						do
						{
							if(contCPF == 0)
							{
								cout << "\t\t\tCPF(apenas n�meros): ";
								cin.getline(CPF, 100);
								TAMANHOCPF = strlen(CPF);
								cout << endl;

								contCPF ++;
							}

							else
							{
								cout << "\t\t\tCPF inv�lido! Um CPF deve conter 11 digitos. " << endl;
								cout << "\t\t\tDigite novamente: ";
								cin.getline(CPF, 100);
								TAMANHOCPF = strlen(CPF);
								cout << endl;
							}
						}
						while(TAMANHOCPF != 11);

						cout << endl;
						cout << "\t\t\tCOMPRA REALIZADA COM SUCESSO! (BOLETO COM 3 DIAS DE V�LIDADE: R$ " << PRECOTOTAL << " reais)" << endl;
						cout << endl;
						cout << "\t\t\tDICA: Impirma o boleto e pague em uma lot�rica mais pr�xima. " << endl;
						cout << "\t\t\tLembre-se: O produto s� ser� enviado ap�s a confirma��o de pagamento do boleto." << endl;
						cout << "\t\t\tEntrega: 3~7 dias �teis. " << endl;
						cout << endl;
						cout << "\t\t\tAgradecemos pela sua compra, senhor(a) " << NOME << ". Espero que goste dos nossos produtos! " << endl;
						cout << endl;
					}

					else if (PAGAMENTO == 2)
					{
						do
						{
							if(contCARTAO == 0)
							{
								cout << "\t\t\tN�mero do cart�o(apenas n�meros): ";
								cin.ignore();
								cin.getline(NUMERODOCARTAO, 100);
								TAMANHOCARTAO = strlen(NUMERODOCARTAO);
								cout << endl;

								contCARTAO ++;
							}

							else
							{
								cout << "\t\t\tN�mero inv�lido! N�mero de cart�o deve conter 16 digitos. " << endl;
								cout << "\t\t\tDigite novamente: ";
								cin.getline(NUMERODOCARTAO, 100);
								TAMANHOCARTAO = strlen(NUMERODOCARTAO);
								cout << endl;
							}
						}
						while(TAMANHOCARTAO != 16);

						do
						{
							if(contPARCELAS == 0)
							{
								cout << "\t\t\tParcelas: " << endl;
								cout << endl;
								cout << "\t\t\t1- 1x R$ " << PRECOTOTAL << " reais" << endl;
								cout << fixed << setprecision(2);
								cout << "\t\t\t2- 2x R$ " << PRECOTOTAL / 2 << " reais" << endl;
								cout << "\t\t\t3- 3x R$ " << PRECOTOTAL / 3 << " reais" << endl;
								cout << "\t\t\t4- 4x R$ " << PRECOTOTAL / 4 << " reais" << endl;
								cout << "\t\t\t5- 5x R$ " << PRECOTOTAL / 5 << " reais" << endl;
								cout << "\t\t\t6- 6x R$ " << PRECOTOTAL / 6 << " reais" << endl;
								cout << "\t\t\t7- 7x R$ " << PRECOTOTAL / 7 << " reais" << endl;
								cout << "\t\t\t8- 8x R$ " << PRECOTOTAL / 8 << " reais" << endl;
								cout << "\t\t\t9- 9x R$ " << PRECOTOTAL / 9 << " reais" << endl;
								cout << "\t\t\t10- 10x R$ " << PRECOTOTAL / 10 << " reais" << endl;
								cout << endl;
								cout << "\t\t\tOp��o escolhida: ";
								cin >> PARCELAS;
								cout << endl;

								contPARCELAS++;
							}

							else
							{
								cout << "\t\t\tCaracter inv�lido! Digite um caracter correspondente." << endl;
								cout << "\t\t\tDigite aqui: ";
								cin >> PARCELAS;
								cout << endl;
							}
						}
						while(PARCELAS < 1 || PARCELAS > 10);

						cout << "\t\t\tCOMPRA REALIZADA COM SUCESSO!" << endl;
						cout << endl;
						cout << "\t\t\tO produto ser� enviado em breve." << endl;
						cout << "\t\t\tEntrega: 3~7 dias �teis. " << endl;
						cout << endl;
						cout << "\t\t\tAgradecemos pela sua compra, senhor(a) " << NOME << ". Espero que goste dos nossos produtos! " << endl;
						cout << endl;
					}
				}
			}
		}
		ARQUIVO.clear();

		if(contPASSOUAQUI == 0)
		{
			cout << "\t\t\tN�o h� medicamentos com esse c�digo! Por favor, tente novamente." << endl;
			cout << endl;
		}

		system("pause");

		system("cls");

		contCONTINUAR = 0;

		do
		{
			if(contCONTINUAR == 0)
			{
				cout << "\t\t\tDeseja comprar mais algum medicamento? " << endl;
				cout << "\t\t\t1 - Sim" << endl;
				cout << "\t\t\t2 - N�o" << endl;
				cout << endl;
				cout << "\t\t\tOp��o escolhida: ";
				cin >> CONTINUAR;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(256, '\n');
				}
				cout << endl;

				contCONTINUAR++;
			}

			else
			{
				cout << "\t\t\tOp��o inv�lida! Digite um numero correspondente. " << endl;
				cout << "\t\t\tDigite novamente: ";
				cin >> CONTINUAR;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(256, '\n');
				}
				cout << endl;
			}
		}
		while(CONTINUAR != 1 && CONTINUAR != 2);

	}
	while(CONTINUAR == 1);

	system("pause");

}

int main()
{

	int MENU;
	int error = 0;

	ARQUIVO.open("CADASTRO DE MEDICAMENTOS.txt", ios::in | ios::out | ios::binary);
	if(ARQUIVO.is_open() == false)
	{
		cout << "ARQUIVO INEXISTENTE, CRIANDO ARQUIVO..." << endl;
		cout << endl;
		ARQUIVO.open("CADASTRO DE MEDICAMENTOS.txt", ios::in | ios::out | ios::binary | ios::trunc);
		system("pause");
		system("cls");
	}

	setlocale(LC_ALL, "Portuguese");

	do
	{
		system("cls");
		cout << endl;
		cout << "\t\t\t\t\t����������������������������������������������������" << endl;
		cout << "\t\t\t\t\t�                                                  �" << endl;
		cout << "\t\t\t\t\t�                                                  �" << endl;
		cout << "\t\t\t\t\t�                SEJAM BEM VINDOS!                 �" << endl;
		cout << "\t\t\t\t\t�                                                  �" << endl;
		cout << "\t\t\t\t\t�                 Farm�cia Online        	   �" << endl;
		cout << "\t\t\t\t\t�                     	           		   �" << endl;
		cout << "\t\t\t\t\t�                                                  �" << endl;
		cout << "\t\t\t\t\t�                Sa�de e Bem-Estar                 �" << endl;
		cout << "\t\t\t\t\t�                                                  �" << endl;
		cout << "\t\t\t\t\t�                                                  �" << endl;
		cout << "\t\t\t\t\t�---------------------- MENU ----------------------�" << endl;
		cout << "\t\t\t\t\t�                                                  �" << endl;
		cout << "\t\t\t\t\t�           1 - Cadastrar Medicamento(s)           �" << endl;
		cout << "\t\t\t\t\t�           2 - Listar Medicamento(s)              �" << endl;
		cout << "\t\t\t\t\t�           3 - Excluir Medicamento(s)             �" << endl;
		cout << "\t\t\t\t\t�           4 - Editar Medicamento(s)              �" << endl;
		cout << "\t\t\t\t\t�           5 - Pesquisar                          �" << endl;
		cout << "\t\t\t\t\t�           6 - Comprar Medicamento(s)		   �" << endl;
		cout << "\t\t\t\t\t�           7 - Sair                               �" << endl;
		cout << "\t\t\t\t\t�                                                  �" << endl;
		cout << "\t\t\t\t\t�                                                  �" << endl;
		cout << "\t\t\t\t\t����������������������������������������������������" << endl;
		cout << endl;
		cout << endl;

		do
		{
			if (error == 0)
			{
				cout << "\t\t\t\t\tEscolha uma das op��es mostradas acima utilizando o n�mero correspondente." << endl;
				cout << "\t\t\t\t\tDigite aqui: ";
				cin >> MENU;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(256, '\n');
				}

				cout << endl;
			}
			else
			{
				cout << "\t\t\t\t\tN�mero inv�lido! Por favor, digite um n�mero correspondente." << endl;
				cout << "\t\t\t\t\tDigite aqui: ";
				cin >> MENU;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(256, '\n');
				}
				cout << endl;
			}
			error++;
		}
		while (MENU < 1 || MENU > 7);

		error = 0;

		switch(MENU)
		{
		case 1:
			CADASTRAR();
			break;

		case 2:
			LISTAR();
			break;

		case 3:
			EXCLUIR();
			break;

		case 4:
			EDITAR();
			break;

		case 5:
			PESQUISAR();
			break;

		case 6:
			COMPRAR();
			break;

		case 7:
			system("exit");
			break;

		}
	}
	while (MENU != 7);

	ARQUIVO.close();

	return 0;
}
