#include <iostream>
#include "big_file.h"

#include <iostream>
#include "BufferEntrada.h"
#include "BufferSaida.h"
#include "ordenacao_externa.h" // Inclua o arquivo de ordenação externa aqui

/*int main(int argc, char** argv) {
    if (argc != 5) {
        std::cerr << "Uso: " << argv[0] << " <arquivoEntrada> <B> <S> <arquivoSaida>" << std::endl;
        return 1;
    }

    const char* arquivoEntrada = argv[1];
    unsigned int B = std::stoi(argv[2]); // Número máximo de bytes para armazenar registros
    unsigned int S = std::stoi(argv[3]); // Tamanho do buffer de saída em bytes
    const char* arquivoSaida = argv[4];

    // Chama a função de ordenação externa
    ordenacaoExterna(arquivoEntrada, B, S, arquivoSaida);

    std::cout << "Ordenação externa concluída. O arquivo de saída é: " << arquivoSaida << std::endl;

    return 0;
}*/


int main(int argc, char** argv) {
    //Gerar o arquivo binário se necessário
    gerar_array_iv("itens_venda.dat", 512000, 42);

    const char* arquivo_entrada = "entrada1.dat";
    const char* arquivo_saida = "saida1.txt";

    gerar_arquivo_legivel(arquivo_entrada, arquivo_saida);

    std::cout << "Arquivo legível gerado: " << arquivo_saida << std::endl;

    return 0;
}
