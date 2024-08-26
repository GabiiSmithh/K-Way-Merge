#include <iostream>
#include "big_file.h"
#include <iostream>
#include "BufferEntrada.h"
#include "BufferSaida.h"
#include "ordenacao_externa.h"


int main(int argc, char** argv) {
    //Gerar o arquivo binário se necessário
    gerar_array_iv("itens_venda.dat", 512000, 42);

    const char* arquivo_entrada = "entrada1.dat";
    const char* arquivo_saida = "saida1.txt";

    gerar_arquivo_legivel(arquivo_entrada, arquivo_saida);

    std::cout << "Arquivo legível gerado: " << arquivo_saida << std::endl;

    return 0;
}
