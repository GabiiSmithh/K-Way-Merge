#include "bufferEntrada.h"
#include <cstring> // Para std::memcpy
#include <iostream>

BufferEntrada::BufferEntrada(const char* nomeArquivo, unsigned int n)
    : nRegistros(n), indiceAtual(0), registrosLidos(0) {
    buffer = new ITEM_VENDA[nRegistros];
    arquivoEntrada.open(nomeArquivo, std::ios::binary);

    if (!arquivoEntrada) {
        std::cerr << "Erro ao abrir o arquivo de entrada!" << std::endl;
        std::perror("Detalhes do erro");
        exit(1);
    }

    arquivoEntrada.seekg(0, std::ios::end);
    totalRegistros = arquivoEntrada.tellg() / sizeof(ITEM_VENDA);
    arquivoEntrada.seekg(0, std::ios::beg);

    lerProximoBloco();
}

BufferEntrada::~BufferEntrada() {
    delete[] buffer;
    arquivoEntrada.close();
}

void BufferEntrada::lerProximoBloco() {
    if (registrosLidos < totalRegistros) {
        arquivoEntrada.read(reinterpret_cast<char*>(buffer), sizeof(ITEM_VENDA) * nRegistros);
        indiceAtual = 0;
    }
}

ITEM_VENDA* BufferEntrada::proximo() {
    if (indiceAtual < nRegistros) {
        return &buffer[indiceAtual];
    }
    return nullptr;
}

ITEM_VENDA* BufferEntrada::consumir() {
    ITEM_VENDA* registro = proximo();
    indiceAtual++;
    registrosLidos++;

    if (indiceAtual >= nRegistros) {
        lerProximoBloco();
    }

    return registro;
}

bool BufferEntrada::vazio() {
    return registrosLidos >= totalRegistros && indiceAtual >= nRegistros;
}
