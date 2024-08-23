#include <algorithm> // Para sort
#include <vector>
#include <iostream>  // Para cerr
#include "ordenacaoExterna.h"
#include "buffer.h"
#include "k_way_merge.h"

using namespace std;

void ordenacaoExterna(vector<ITEM_VENDA>& dados, size_t B, size_t S, vector<ITEM_VENDA>& saida) {
    if (B <= S) { //Buffer de entrada é maior que buffer de saída
        cout << "Erro: O tamanho do buffer de entrada B deve ser maior que o tamanho do buffer de saída S." << endl;
        return; // Se não for, exibe um erro e retorna da função
    }

    size_t tamanhoRegistro = sizeof(ITEM_VENDA);
    size_t registrosEntrada = (B - S) / tamanhoRegistro; //Quantidade de registros que cada buffer de entrada pode armazenar
    size_t pedacos = (dados.size() + registrosEntrada - 1) / registrosEntrada; //Quantidade de pedaços necessários

    // Vetores para armazenar os pedaços e buffers de entrada
    vector<vector<ITEM_VENDA>> pedaços(pedacos);
    vector<BufferEntrada*> buffersEntrada(pedacos);

    // Divide os dados em pedaços e ordena cada pedaço
    size_t j = 0;
    for (size_t i = 0; i < pedacos; i++) {
        size_t registrosPedaco = min(registrosEntrada, dados.size() - j); //Número de registros para o pedaço atual
        pedaços[i].resize(registrosPedaco); //Cria o pedaço
        copy(dados.begin() + j, dados.begin() + j + registrosPedaco, pedaços[i].begin()); //Copia os registros para ele

        sort(pedaços[i].begin(), pedaços[i].end(), [](const ITEM_VENDA& a, const ITEM_VENDA& b) { //Ordena o pedaço por id
            return a.id < b.id;
        });
        buffersEntrada[i] = new BufferEntrada(pedaços[i]); // Cria o buffer de entrada para este pedaço
        j += registrosPedaco; // Atualiza o índice
    }
    BufferSaida bufferSaida(S); // Cria o buffer de saída com o tamanho especificado
    void kWayMerge(const vector<BufferEntrada>& buffersEntrada, vector<ITEM_VENDA>& pedaços, BufferSaida& bufferSaida); //Intercalação dos pedaços
    bufferSaida.despejar(saida); //Despeja o conteúdo restante do buffer de saída no vetor de saída

    for (size_t i = 0; i < pedacos; i++) {
        delete buffersEntrada[i];
    }
}
