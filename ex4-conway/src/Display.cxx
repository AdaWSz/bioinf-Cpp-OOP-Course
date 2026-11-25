#include <Grid.h>
#include <iostream>

std::string DrawPixel(bool top, bool bottom) { // Printing the unicode bottom half-block ▄
    std::string pixel;
    if (top && bottom)
         pixel = "\033[37;47m\u2584"; // White bg, white char
    else if (top && !bottom)
        pixel = "\033[30;47m\u2584"; // White bg, black char
    else if (!top && bottom)
        pixel = "\033[37;40m\u2584"; // Black bg, white char
    else
        pixel = "\033[30;40m\u2584"; // Both black
    return pixel;
}

void RenderFrame(const std::vector<std::vector<Cell>>& data) {
    std::string frame;
    std::string pixel;

    for (int i=0; i < data.size(); ++i) {
        if (i+1 < data.size()) {
            for (int j=0; j < data[i].size(); ++j) {
                pixel = DrawPixel(data[i][j].GetStatus(),
                          data[i+1][j].GetStatus());
                frame += pixel;
            }
            frame += "\n";
        }
    }
    std::cout << frame << std::endl;
}
