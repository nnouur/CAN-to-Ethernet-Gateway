#include "GlobalBuffer.hpp"

static GlobalBuffer g_buffer;
GlobalBuffer& GetGlobalBuffer() { return g_buffer; }
