#ifndef BUFFERSAIDA_H
#define BUFFERSAIDA_H

#include <fstream>
#include "big_file.h" 

class BufferSaida {
public:
    BufferSaida(const char* nomeArquivo, unsigned int n);
    ~BufferSaida();
    void inserir(const ITEM_VENDA& registro);
    bool isValid() const { return arquivoSaida.is_open(); }
    void despejar();
private:
    std::ofstream arquivoSaida;
    ITEM_VENDA* buffer;
    unsigned int nRegistros;
    unsigned int indiceAtual;
};

#endif
