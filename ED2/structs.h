#ifndef STRUCTS_H_
#define STRUCTS_H_
#define VETMAX 100

typedef struct{
    double cod_Hash;
    int cod_Cadastro;
    int cod_Municipio;
    char cidade_Origem[VETMAX];
    char cidade_Destino[VETMAX];
    float distancia;
} Rota;

#endif // STRUCTS_H_


