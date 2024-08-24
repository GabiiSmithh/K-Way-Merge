#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include "big_file.h"
#include "bufferEntrada.h"
#include "bufferSaida.h"
#include "intercalacao.h"
#include "ordenacao_externa.h"

// Função para inicializar dados fictícios
void inicializarDados(std::vector<ITEM_VENDA>& dados, unsigned int n) {
    for (unsigned int i = 0; i < n; ++i) {
        dados[i].id = i + 1;
        dados[i].id_venda = (i % 10) + 1;
        dados[i].desconto = (i % 10) * 0.1f;
        dados[i].data = 20230000 + (i % 365);
        snprintf(dados[i].desc, sizeof(dados[i].desc), "Descrição %u", i);
    }
}

// Função para criar o arquivo temporário com dados fictícios
void criarArquivoTemporario(const std::string& nomeArquivo, unsigned int n, const std::vector<ITEM_VENDA>& dados) {
    std::ofstream arquivo(nomeArquivo, std::ios::binary);
    if (!arquivo) {
        std::cerr << "Erro ao criar o arquivo temporário: " << nomeArquivo << std::endl;
        std::perror("Detalhes do erro");
        exit(1);
    }

    arquivo.write(reinterpret_cast<const char*>(dados.data()), dados.size() * sizeof(ITEM_VENDA));
    arquivo.close();
}

// Função para gerar o arquivo de entrada com dados fictícios
void gerarArquivoEntrada(const std::string& nomeArquivo, unsigned int n) {
    std::vector<ITEM_VENDA> dados(n);
    inicializarDados(dados, n);

    std::ofstream arquivo(nomeArquivo, std::ios::binary);
    if (!arquivo) {
        std::cerr << "Erro ao criar o arquivo de entrada: " << nomeArquivo << std::endl;
        std::perror("Detalhes do erro");
        exit(1);
    }

    arquivo.write(reinterpret_cast<const char*>(dados.data()), dados.size() * sizeof(ITEM_VENDA));
    arquivo.close();
}

// Função principal de ordenação externa
void ordenacaoExterna(const char* arquivoEntrada, unsigned int B, unsigned int S, const char* arquivoSaida) {
    std::cout << "Gerando arquivo de entrada: " << arquivoEntrada << std::endl;
    gerarArquivoEntrada(arquivoEntrada, 10000);  // Ajuste o número de registros conforme necessário

    std::cout << "Abrindo arquivo de entrada: " << arquivoEntrada << std::endl;

    std::ifstream entrada(arquivoEntrada, std::ios::binary);
    if (!entrada) {
        std::cerr << "Erro ao abrir o arquivo de entrada: " << arquivoEntrada << std::endl;
        std::perror("Detalhes do erro");
        exit(1);
    }

    entrada.seekg(0, std::ios::end);
    unsigned int E = entrada.tellg();
    entrada.close();

    unsigned int K = std::ceil(static_cast<double>(E) / B);
    unsigned int registrosPorBuffer = ((B - S) / K) / sizeof(ITEM_VENDA);

    std::cout << "Tamanho do arquivo de entrada (E): " << E << std::endl;
    std::cout << "Número de partes (K): " << K << std::endl;
    std::cout << "Registros por buffer: " << registrosPorBuffer << std::endl;

    if (registrosPorBuffer <= 0) {
        std::cerr << "Erro: O número de registros por buffer é 0 ou negativo!" << std::endl;
        exit(1);
    }

    BufferEntrada* buffersEntrada[K];
    for (unsigned int i = 0; i < K; i++) {
        std::string nomeArquivoTemp = "temp" + std::to_string(i) + ".dat";

        // Inicializar dados fictícios
        std::vector<ITEM_VENDA> dados(registrosPorBuffer);
        inicializarDados(dados, registrosPorBuffer);
        
        // Criar arquivo temporário com dados
        criarArquivoTemporario(nomeArquivoTemp, registrosPorBuffer, dados);

        buffersEntrada[i] = new BufferEntrada(nomeArquivoTemp.c_str(), registrosPorBuffer);
    }

    BufferSaida bufferSaida(arquivoSaida, S / sizeof(ITEM_VENDA));
    if (!bufferSaida.isValid()) {
        std::cerr << "Erro ao criar o buffer de saída!" << std::endl;
        exit(1);
    }

    intercalacaoKvias(buffersEntrada, K, bufferSaida);

    // Limpar buffers de entrada e arquivos temporários
    for (unsigned int i = 0; i < K; i++) {
        delete buffersEntrada[i];
        std::string nomeArquivoTemp = "temp" + std::to_string(i) + ".dat";
        if (remove(nomeArquivoTemp.c_str()) != 0) {
            std::cerr << "Erro ao remover o arquivo temporário: " << nomeArquivoTemp << std::endl;
        }
    }
}
