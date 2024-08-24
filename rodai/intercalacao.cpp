#include "bufferEntrada.h"
#include "bufferSaida.h"

void intercalacaoKvias(BufferEntrada** buffersEntrada, int k, BufferSaida& bufferSaida) {
    while (true) {
        ITEM_VENDA* menor = nullptr;
        int menorIndice = -1;

        for (int i = 0; i < k; i++) {
            if (!buffersEntrada[i]->vazio()) {
                ITEM_VENDA* atual = buffersEntrada[i]->proximo();
                if (menor == nullptr || atual->id < menor->id) {
                    menor = atual;
                    menorIndice = i;
                }
            }
        }

        if (menor == nullptr) {
            break;
        }

        bufferSaida.inserir(*buffersEntrada[menorIndice]->consumir());
    }

    bufferSaida.despejar();
}
