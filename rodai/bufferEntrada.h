#pragma once

#include <cstdint>   
#include <fstream>  
#include "big_file.h" 

class BufferEntrada {
private:
    ITEM_VENDA* buffer;          // Array de registros ITEM_VENDA
    std::ifstream arquivoEntrada; // Leitura do arquivo
    unsigned int nRegistros;     // Número de registros que o buffer pode armazenar
    unsigned int indiceAtual;    // Índice do próximo registro a ser lido
    unsigned int registrosLidos; // Contador de registros lidos
    unsigned int totalRegistros; // Total de registros disponíveis

public:
    BufferEntrada(const char* nomeArquivo, unsigned int n); //Construtor
    ~BufferEntrada();
    void lerProximoBloco();
    ITEM_VENDA* proximo();
    ITEM_VENDA* consumir();
    bool vazio();
};
