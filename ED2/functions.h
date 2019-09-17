#ifndef FUNCTIONS_H_
#define FUNCTION_H_
#define arquivoRotas "rotas.dat"
#define arquivoDatabase "databaseToHaskell.txt"

using namespace std;

void writeRota(Rota *r);
void rewriteRotas(Rota *r, int length);
void readRotas(Rota *r, int length);
double gerarHash(double codigo);
void printFileRotas();
void printArrayRotas(Rota *r, int length);
int codigoExiste(int codigo);
int tratarCodigo(int codigo);
void editarInfo(Rota *r);
void editarRota(double hash);
void selectEdicao(Rota *r);
void pesquisarCodigo(double hash);
void pesquisaCidadeOrigem(char cidadeOrigem[]);
void pesquisaCidadeDestino(char cidadeDestino[]);
void ordenarRotas();
void gerarDataBase();
void quickSort(Rota *r, int left, int right);
int sizeOfFileRotas();
void pause();

void writeRota(Rota *r){
    FILE *file = fopen(arquivoRotas, "a+b");
    fwrite(r, sizeof(Rota), 1, file);
    fclose(file);
    cout << endl << "\t\t\tRota cadastrada com sucesso!" << endl;
}

void rewriteRotas(Rota *r, int length){
    FILE *file = fopen(arquivoRotas, "w+b");
    fwrite(r, sizeof(Rota), length, file);
    fclose(file);
}

void readRotas(Rota *r, int length){
    FILE *file = fopen(arquivoRotas, "r+b");
    fread(r, sizeof(Rota), length, file);
    fclose(file);
}

double gerarHash(double codigo){
    return log1p(codigo);
}

void charToUpper(char c[]){
    for(int i = 0; c[i] != '\0'; i++)
        c[i] = toupper(c[i]);

}

void printFileRotas(){
    FILE *file = fopen(arquivoRotas, "r+b");
    Rota *r = new Rota();
    cout << "\t\t\t============= ROTAS ============" << endl;
    while((fread(r, sizeof(Rota), 1, file)) == 1){
        cout << "\t\t\t      " << r->cidade_Origem << " -> " << r->cidade_Destino << endl;
        cout << "\t\t\tCodigo Hash....: " << r->cod_Hash << endl;
        cout << "\t\t\tCodigo Cadastro: " << r->cod_Cadastro << endl;
        cout << "\t\t\tCidade Origem..: " << r->cidade_Origem << endl;
        cout << "\t\t\tCidade Destino.: " << r->cidade_Destino << endl;
        cout << "\t\t\tDistancia......: " << r->distancia << " KM" << endl;
        cout << "\t\t\t--------------------------------" << endl << endl;
    }
    fclose(file);
    delete(r);
}

void printArrayRotas(Rota *r, int length){
    cout << endl;
    for(int i = 0; i < length; i++){
        cout << "\t\t\tCodigo Hash....: " << r[i].cod_Hash << endl;
        cout << "\t\t\tCodigo Cadastro: " << r[i].cod_Cadastro << endl;
        cout << "\t\t\tCidade Origem..: " << r[i].cidade_Origem << endl;
        cout << "\t\t\tCidade Destino.: " << r[i].cidade_Destino << endl;
        cout << "\t\t\tDistancia......: " << r[i].distancia << " KM" << endl;
        cout << "\t\t\t---------------------------------" << endl;
    }
}

int codigoExiste(int codigo){
    double hash = gerarHash(codigo);
    FILE *file = fopen(arquivoRotas, "r+b");
    Rota *r = new Rota();
    while((fread(r, sizeof(Rota), 1, file)) == 1){
        if(r->cod_Hash == hash){
            return 1;
        }
    }
    fclose(file);
    delete(r);
    return 0;
}

int tratarCodigo(int codigo){
    if(codigoExiste(codigo) == 1){
        cout << "\t\t\tERRO: O codigo ja existe. Digite um codigo valido!" << endl;
        return 0;
    }
    return 1;
}

void editarInfo(Rota *r){
    int opc;
    do{
        system("cls");
        cout << "\t\t\t============= EDICAO ============" << endl;
        printArrayRotas(r, 1);
        cout << "\t\t\t1- Alterar Codigo de cadastro" << endl;
        cout << "\t\t\t2- Alterar Cidade de origem" << endl;
        cout << "\t\t\t3- Alterar Cidade de Destino" << endl;
        cout << "\t\t\t4- Alterar Distancia" << endl;
        cout << "\t\t\t5- Finalizar" << endl;
        cout << "\t\t\t> ";
        cin >> opc;
        switch(opc){
        case 1:
            do{
                cout << "\t\t\tNovo Codigo de Cadastro: ";
                cin >> r->cod_Cadastro;
            }while(tratarCodigo(r->cod_Cadastro) != 1);
            r->cod_Hash = gerarHash(r->cod_Cadastro);
            break;
        case 2:
            fflush(stdin);
            cout << "\t\t\tNova Cidade de origem: ";
            cin.getline(r->cidade_Origem,VETMAX);
            charToUpper(r->cidade_Origem);
            break;
        case 3:
            fflush(stdin);
            cout << "\t\t\tNova Cidade de destino: ";
            cin.getline(r->cidade_Destino,VETMAX);
            charToUpper(r->cidade_Destino);
            break;
        case 4:
            do{
                cout << "\t\t\tNova Distancia (KM): ";
                cin >> r->distancia;
            }while(r->distancia <= 0);
            break;
        case 5:
            break;
        default:
            cout << "\t\t\tOpção Invalida." << endl;
        }
    }while(opc != 5);
}

void editarRota(double hash){
    FILE *file = fopen(arquivoRotas, "r+b");
    Rota *r = new Rota();
    int i = 0;
    while((fread(r, sizeof(Rota), 1, file)) == 1){
        if(r->cod_Hash == hash){
            editarInfo(r);
            fseek(file, i*sizeof(Rota), SEEK_SET);
            fwrite(r, sizeof(Rota), 1, file);
            fclose(file);
            ordenarRotas();
            gerarDataBase();
            delete(r);
            cout << "\t\t\tRota alterada com sucesso!" << endl;
            return;
        }
        i++;
    }
    cout << "\t\t\tRota nao encontrada!" << endl;
    pause();
    delete(r);
}

void selectEdicao(Rota *r){
    char edc;
    cout << endl << "\t\t\tDeseja editar esta rota? (S/N): ";
    cin >> edc;
    if(edc == 'S' || edc == 's'){
        system("cls");
        editarRota(r->cod_Hash);
    }
}

void pesquisarCodigo(double hash){
    FILE *file = fopen(arquivoRotas, "r+b");
    Rota *r = new Rota();
    while(fread(r, sizeof(Rota), 1, file) == 1){
        if(r->cod_Hash == hash){
            system("cls");
            cout << "\t\t\tRota encontrada!" << endl << endl;
            fclose(file);
            printArrayRotas(r, 1);
            selectEdicao(r);
            delete r;
            return;
        }
    }
    delete r;
    cout << "\t\t\tRota nao encontrada!" << endl;
}

void pesquisaCidadeOrigem(char cidadeOrigem[]){
    FILE *file = fopen(arquivoRotas, "r+b");
    Rota *r = new Rota();
    while(fread(r, sizeof(Rota), 1, file) == 1){
        if(strcmp(r->cidade_Origem, cidadeOrigem) == 0){
            printArrayRotas(r, 1);
        }
    }
    delete r;
    fclose(file);
}

void pesquisaCidadeDestino(char cidadeDestino[]){
    FILE *file = fopen(arquivoRotas, "r+b");
    Rota *r = new Rota();
    while(fread(r, sizeof(Rota), 1, file) == 1){
        if(strcmp(r->cidade_Destino, cidadeDestino) == 0){
            printArrayRotas(r, 1);
        }
    }
    delete r;
    fclose(file);
}

void gerarDataBase(){
    FILE *seq = fopen(arquivoDatabase, "w+");
    FILE *file = fopen(arquivoRotas, "r+b");
    Rota *r = new Rota();
    while(fread(r, sizeof(Rota), 1, file) == 1){
        fprintf(seq, "%s\n%s\n%.2f\n", r->cidade_Origem, r->cidade_Destino, r->distancia);
    }
    fclose(seq);
    fclose(file);
    delete r;
}

void ordenarRotas(){
    int length = sizeOfFileRotas();
    Rota *r = new Rota[length];
    readRotas(r, length);
    quickSort(r, 0, length - 1);
    rewriteRotas(r, length);
    delete [] r;
}

void quickSort(Rota *r, int left, int right) {
    int i, j;
    Rota x, y;
    i = left;
    j = right;
    x = r[(left + right) / 2];
    while(i <= j) {
        while(r[i].cod_Cadastro < x.cod_Cadastro && i < right) {
            i++;
        }
        while(r[j].cod_Cadastro > x.cod_Cadastro && j > left) {
            j--;
        }
        if(i <= j) {
            y = r[i];
            r[i] = r[j];
            r[j] = y;
            i++;
            j--;
        }
    }
    if(j > left) {
        quickSort(r, left, j);
    }
    if(i < right) {
        quickSort(r, i, right);
    }
}

int sizeOfFileRotas(){
    FILE *file = fopen(arquivoRotas, "r+b");
    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    length = length/sizeof(Rota);
    fclose(file);
    return length;
}

void pause(){
    fflush(stdin);
    cout << "\t\t\t[ Pressione enter para voltar! ]" << endl;
    getchar();
}
#endif // FUNCTIONS_H_
