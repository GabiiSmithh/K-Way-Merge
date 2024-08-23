#pragma once

#include <vector>
#include <stddef.h>
#include "big_file.h"

using namespace std;

class BufferEntrada {
    public:
        BufferEntrada(const std::vector<ITEM_VENDA>& dados); //Construtor
        ITEM_VENDA proximo(); //Retorna o proximo registro sem avançar
        ITEM_VENDA consumir(); //Retorna o proximo registro e avança no buffer
        bool vazio(); //Bufffer vazio?
        ~BufferEntrada();

    private:
        vector<ITEM_VENDA> dados; //Vetor de dados
        size_t tamanhoBuffer;
        size_t posicao; //posição no buffer
        size_t totalRegistros; //Total de Registros no arquivo
};

class BufferSaida {
    public:
        BufferSaida(size_t tamanhoBuffer); //Construtor
        void inserir(const ITEM_VENDA& registro); //Insere um registro
        void despejar(std::vector<ITEM_VENDA>& dados); //Escreve o conteúdo
        const vector<ITEM_VENDA>& getSaida() const; //Retorna registros armazenados
        ~BufferSaida();

    private:
        vector<ITEM_VENDA> buffer; //Vetor do buffer de saida
        size_t posicao; //posição no buffer
        size_t tamanhoBuffer;
};