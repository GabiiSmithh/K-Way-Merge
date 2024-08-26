#include "bufferEntrada.h"
#include "bufferSaida.h"

void intercalacaoKvias(BufferEntrada** buffersEntrada, int k, BufferSaida& bufferSaida) {
    while (true) {
        ITEM_VENDA* menor = nullptr;  //Armazenar o menor registro encontrado
        int menorIndice = -1;         // Índice do buffer que contém o menor registro

        for (int i = 0; i < k; i++) {
            if (!buffersEntrada[i]->vazio()) { // Se o buffer de entrada atual não está vazio
                ITEM_VENDA* atual = buffersEntrada[i]->proximo();

                if (menor == nullptr || atual->id < menor->id) {
                    menor = atual;  // Atualiza o ponteiro para o menor registro
                    menorIndice = i; // Atualiza o índice do buffer que contém o menor registro
                }
            }
        }

        // Todos os buffers estão vazios e o processo de intercalação está completo
        if (menor == nullptr) {
            break;  // Sai do loop principal
        }
        bufferSaida.inserir(*buffersEntrada[menorIndice]->consumir()); // Insere o menor registro encontrado no buffer de saída e o consome do buffer de entrada correspondente
    }
    bufferSaida.despejar();
}
