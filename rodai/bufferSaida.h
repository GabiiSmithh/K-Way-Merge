#ifndef BUFFERSAIDA_H
#define BUFFERSAIDA_H

#include <fstream>
#include "big_file.h"  // Incluir o cabeçalho onde ITEM_VENDA está definido

class BufferSaida {
public:
    BufferSaida(const char* nomeArquivo, unsigned int n);
    ~BufferSaida();
    void inserir(const ITEM_VENDA& registro);
    bool isValid() const { return arquivoSaida.is_open(); }
    void despejar();  // Tornar esta função pública
private:
    std::ofstream arquivoSaida;
    ITEM_VENDA* buffer;
    unsigned int nRegistros;
    unsigned int indiceAtual;
};

#endif
