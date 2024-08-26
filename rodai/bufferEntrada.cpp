#include "bufferEntrada.h"
#include <cstring>  
#include <iostream> 

BufferEntrada::BufferEntrada(const char* nomeArquivo, unsigned int n)
    : nRegistros(n), indiceAtual(0), registrosLidos(0) {
    buffer = new ITEM_VENDA[nRegistros]; // Alocar memória
    arquivoEntrada.open(nomeArquivo, std::ios::binary); // Abre o arquivo de entrada no modo binário

    if (!arquivoEntrada) { // Se foi aberto com sucesso
        std::cerr << "Erro ao abrir o arquivo de entrada!" << std::endl; // Se não abrir o arquivo
        std::perror("Detalhes do erro"); 
        exit(1);
    }

    arquivoEntrada.seekg(0, std::ios::end); // Move o ponteiro do arquivo para o final para calcular o total de registros
    totalRegistros = arquivoEntrada.tellg() / sizeof(ITEM_VENDA); // Calcula o número total de registros no arquivo
    arquivoEntrada.seekg(0, std::ios::beg); // Retorna o ponteiro para o início do arquivo

    lerProximoBloco();
}

BufferEntrada::~BufferEntrada() {
    delete[] buffer; // Libera a memória alocada para o buffer
    arquivoEntrada.close();
}

void BufferEntrada::lerProximoBloco() {
    if (registrosLidos < totalRegistros) { // Se ainda há registros a serem lidos do arquivo
        // Lê um bloco de registros do arquivo e armazena no buffer
        arquivoEntrada.read(reinterpret_cast<char*>(buffer), sizeof(ITEM_VENDA) * nRegistros);
        indiceAtual = 0; // Reseta para o início do buffer
    }
}

ITEM_VENDA* BufferEntrada::proximo() {
    if (indiceAtual < nRegistros) { // Se ainda há registros no buffer
        return &buffer[indiceAtual]; 
    }
    return nullptr; 
}

ITEM_VENDA* BufferEntrada::consumir() {
    ITEM_VENDA* registro = proximo(); // Obtém o próximo registro
    indiceAtual++;
    registrosLidos++;

    // Se o índice atual atingir o final do buffer, lê o próximo bloco de registros
    if (indiceAtual >= nRegistros) {
        lerProximoBloco();
    }

    return registro; // Retorna o registro consumido
}

bool BufferEntrada::vazio() {
    // Retorna true se todos os registros foram lidos e consumidos, false caso contrário
    return registrosLidos >= totalRegistros && indiceAtual >= nRegistros;
}
