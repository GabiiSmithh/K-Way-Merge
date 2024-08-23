#include "buffer.h"

using namespace std;

//BUFFER ENTRADA
BufferEntrada::BufferEntrada(const std::vector<ITEM_VENDA>& dados) // Construtor que inicializa o buffer com os dados em memória
    : dados(dados), tamanhoBuffer(tamanhoBuffer), posicao(0), totalRegistros(dados.size()) { // Inicializa a posição atual no início e define o tamanho total de registros
}

ITEM_VENDA BufferEntrada::proximo() {
    return dados[posicao]; // Retorna o registro na posição atual
}

ITEM_VENDA BufferEntrada::consumir() {
    ITEM_VENDA item = dados[posicao]; // Salva o registro atual
    posicao++; // Avança para o próximo registro
    return item; // Retorna o registro consumido
}

bool BufferEntrada::vazio() {
    return posicao >= totalRegistros; // Retorna true se todos os registros foram consumidos
}

//BUFFER SAIDA
BufferSaida::BufferSaida(size_t tamanhoBuffer)
    : tamanhoBuffer(tamanhoBuffer) {
    buffer.reserve(tamanhoBuffer); // Reserva espaço para o buffer
}

void BufferSaida::inserir(const ITEM_VENDA& registro) {
    buffer.push_back(registro); // Adiciona registro
    if (buffer.size() == tamanhoBuffer) { // Se estiver cheio
        vector<ITEM_VENDA> dados = buffer;
        despejar(dados);
    }
}

void BufferSaida::despejar(vector<ITEM_VENDA>& daods) {
    buffer.clear(); // Limpa o buffer
}

const vector<ITEM_VENDA>& BufferSaida::getSaida() const {
    return buffer; // Retorna o vetor que contém os registros
}