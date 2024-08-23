#pragma once
#include <vector>
#include <cstddef>
#include "buffer.h"
#include "big_file.h"

using namespace std;

void ordenacaoExterna(vector<ITEM_VENDA>& dados, size_t B, size_t S, vector<ITEM_VENDA>& saida);
