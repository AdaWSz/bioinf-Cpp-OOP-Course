#ifndef DISPLAY_H
#define DISPLAY_H
#include <string>
#include <vector>
#include "Cell.h"

std::string DrawPixel(bool top, bool bottom);
void RenderFrame(const std::vector<std::vector<Cell>>& data);

#endif
