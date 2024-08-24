#include <iostream>
#include <fstream>
#include <iomanip>
#include "big_file.h" // Substitua pelo nome correto do seu arquivo de cabeçalho

void gerar_arquivo_legivel(const char* arquivo_entrada, const char* arquivo_saida) {
    // Abrir o arquivo binário para leitura
    std::ifstream file_in(arquivo_entrada, std::ios::binary);
    if (!file_in) {
        std::cerr << "Erro ao abrir o arquivo binário para leitura: " << arquivo_entrada << std::endl;
        return;
    }

    // Abrir o arquivo de saída para escrita
    std::ofstream file_out(arquivo_saida);
    if (!file_out) {
        std::cerr << "Erro ao abrir o arquivo de saída para escrita: " << arquivo_saida << std::endl;
        return;
    }

    // Ler e processar os registros do arquivo binário
    ITEM_VENDA item;
    while (file_in.read(reinterpret_cast<char*>(&item), sizeof(ITEM_VENDA))) {
        // Escrever dados legíveis no arquivo de saída
        file_out << "ID: " << item.id << std::endl;
        file_out << "ID Venda: " << item.id_venda << std::endl;
        file_out << "Desconto: " << std::fixed << std::setprecision(2) << item.desconto << std::endl;
        file_out << "Data: " << item.data << std::endl;
        file_out << "Descrição: " << item.desc << std::endl;
        file_out << "--------------------------" << std::endl;
    }

    // Fechar os arquivos
    file_in.close();
    file_out.close();
}