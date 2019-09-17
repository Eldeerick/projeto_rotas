#include <iostream>
#include<stdlib.h>
#include<cstdio>
#include<string.h>
#include<time.h>
#include<math.h>
#include<locale.h>
#include<windows.h>
#include<iomanip>
#include"structs.h"
#include"functions.h"

using namespace std;

void menu(int &opc);
void cadastrarRota(Rota *r);
void menuPesquisa();
int tratarCodigo(int codigo);

int main() {
    SetConsoleTitle("Sistema de GPS");
    int opc;
    do {
        system("cls");
        menu(opc);
            switch(opc){
            case 1:{
                Rota *novaRota = new Rota();
                cadastrarRota(novaRota);
                writeRota(novaRota);
                ordenarRotas();
                gerarDataBase();
                printArrayRotas(novaRota, 1);
                delete novaRota;
                pause();
                break;
            }
            case 2:{
                int codigo;
                printFileRotas();
                cout << "\t\t\tInforme o codigo de cadastro da Rota: ";
                cin >> codigo;
                double hash = gerarHash(codigo);
                editarRota(hash);
                break;
            }
            case 3:{
                menuPesquisa();
                break;
            }
            case 4:{
                printFileRotas();
                pause();
                break;
            }
            case 5:{
                cout << "\t\t\tEncerrando o programa..." << endl;
                break;
            }
            default:
                cout << "\t\t\tOpcao Invalida!" << endl;
            }
    }while(opc != 5);
}

void menu(int &opc){
    cout << endl << "\t\t\t=========== MENU ===========" << endl;
    cout << "\t\t\t1- Cadastrar nova Rota" << endl;
    cout << "\t\t\t2- Editar Rota" << endl;
    cout << "\t\t\t3- Pesquisar Rota" << endl;
    cout << "\t\t\t4- Listar Rotas" << endl;
    cout << "\t\t\t> ";
    cin >> opc;
}

void menuPesquisa(){
    int opc;
    Rota *r = new Rota();
    system("cls");
    do{
        cout << endl << "\t\t\t=========== PESQUISA ===========" << endl;
        cout << "\t\t\t1- Pesquisar por Codigo de Cadastro" << endl;
        cout << "\t\t\t2- Pesquisar por Cidade de Origem" << endl;
        cout << "\t\t\t3- Pesquisar por Cidade de Destino" << endl;
        cout << "\t\t\t4- Voltar" << endl;
        cout << "\t\t\t> ";
        cin >> opc;
        switch(opc){
        case 1:
            cout << "\t\t\tInforme o Codigo de Cadastro: ";
            cin >> r->cod_Cadastro;
            r->cod_Hash = gerarHash(r->cod_Cadastro);
            pesquisarCodigo(r->cod_Hash);
            break;
        case 2:
            fflush(stdin);
            cout << "\t\t\tInforme o nome da Cidade de Origem: ";
            cin.getline(r->cidade_Origem, VETMAX);
            charToUpper(r->cidade_Origem);
            pesquisaCidadeOrigem(r->cidade_Origem);
            break;
        case 3:
            fflush(stdin);
            cout << "\t\t\tInforme o nome da Cidade de Destino: ";
            cin.getline(r->cidade_Destino, VETMAX);
            charToUpper(r->cidade_Destino);
            pesquisaCidadeDestino(r->cidade_Destino);
            break;
        case 4:
            break;
        default:
            cout << "\t\t\tOpcao Invalida!" << endl;
        }
        pause();
        system("cls");
    }while(opc != 4);
    delete r;
}

void cadastrarRota(Rota *r){
   do{
        cout << "\t\t\tCodigo do Cadastro........: ";
        cin >> r->cod_Cadastro;
   }while(tratarCodigo(r->cod_Cadastro) != 1);
    r->cod_Hash = gerarHash(r->cod_Cadastro);
    cout << "\t\t\tCodigo da Cidade..........: ";
    cin >> r->cod_Municipio;
    fflush(stdin);
    cout << "\t\t\tNome da Cidade Origem.....: ";
    cin.getline(r->cidade_Origem, VETMAX);
    charToUpper(r->cidade_Origem);
    fflush(stdin);
    cout << "\t\t\tNome da Cidade Destino....: ";
    cin.getline(r->cidade_Destino, VETMAX);
    charToUpper(r->cidade_Destino);
    do{
        cout << "\t\t\tDistancia entre as Cidades: ";
        cin >> r->distancia;
    }while(r->distancia <= 0);
}
