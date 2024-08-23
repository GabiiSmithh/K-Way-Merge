#pragma once

#include <vector>
#include "buffer.h"

using namespace std;

void kWayMerge(const std::vector<BufferEntrada>& buffersEntrada, std::vector<ITEM_VENDA>& pedaços, BufferSaida& bufferSaida);
