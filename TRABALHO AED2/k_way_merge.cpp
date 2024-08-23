#include "buffer.h"
#include "k_way_merge.h"

using namespace std;

void kWayMerge(vector<BufferEntrada*>& buffersEntrada, BufferSaida& bufferSaida) {
    while (true) { //Enquanto as entradas não forem vazias
        BufferEntrada* menorBuffer = nullptr;  //Buffer com o menor elemento
        ITEM_VENDA menorItem;  //Armazena o menor item entre os buffers

        for (auto& buffer : buffersEntrada) { //Passa por todos os buffers
            if (buffer->vazio() == false) { //Se não estiver vazio
                if (menorBuffer == nullptr || buffer->proximo().id < menorItem.id) { //Se o menor ainda nn foi encontrado OU se o atual for menor que o menor anterior
                    menorBuffer = buffer;
                    menorItem = buffer->proximo();
                }
            }
        }
        if (menorBuffer == nullptr) { //Se não foi encontrado um menor sai do loop
            break;
        }
        bufferSaida.inserir(menorBuffer->consumir()); //Consome e insere no de saida
    }
    bufferSaida.despejar();
}
