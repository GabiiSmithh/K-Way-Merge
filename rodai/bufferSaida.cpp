#include "bufferSaida.h"
#include <iostream>

BufferSaida::BufferSaida(const char* nomeArquivo, unsigned int n)
    : nRegistros(n), indiceAtual(0) {
    buffer = new ITEM_VENDA[nRegistros];
    arquivoSaida.open(nomeArquivo, std::ios::binary);

    if (!arquivoSaida) {
        std::cerr << "Erro ao abrir o arquivo de saída!" << std::endl;
        std::perror("Detalhes do erro");
        exit(1);
    }
}

BufferSaida::~BufferSaida() {
    despejar();
    delete[] buffer;
    arquivoSaida.close();
}

void BufferSaida::inserir(const ITEM_VENDA& registro) {
    buffer[indiceAtual++] = registro;
    if (indiceAtual >= nRegistros) {
        despejar();
    }
}

void BufferSaida::despejar() {
    if (indiceAtual > 0) {
        arquivoSaida.write(reinterpret_cast<char*>(buffer), sizeof(ITEM_VENDA) * indiceAtual);
        indiceAtual = 0;
    }
}
