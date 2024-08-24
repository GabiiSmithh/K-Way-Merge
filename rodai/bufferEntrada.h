#pragma once

#include <cstdint>
#include <fstream>
#include "big_file.h"

class BufferEntrada {
private:
    ITEM_VENDA* buffer;
    std::ifstream arquivoEntrada;
    unsigned int nRegistros;
    unsigned int indiceAtual;
    unsigned int registrosLidos;
    unsigned int totalRegistros;

public:
    BufferEntrada(const char* nomeArquivo, unsigned int n);
    ~BufferEntrada();

    void lerProximoBloco();
    ITEM_VENDA* proximo();
    ITEM_VENDA* consumir();
    bool vazio();
};
