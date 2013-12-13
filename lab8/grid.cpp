#include <iostream>
#include <string>
#include <vector>

typedef std::vector<char> GridRow;
typedef std::vector<GridRow> Grid;

void InitGrid(Grid& grid, int width, int height, char symbol = ' ')
{
    grid.clear();
    grid.resize(height);
    for(size_t i = 0; i < grid.size(); ++i)
    {
        grid[i].clear();
        grid[i].resize(width, symbol);
    }
}

void DrawRectangle(Grid& grid, char symbol, int x, int y, int width, int height)
{
    //Reject out of bounds rectangles.
    if(grid.empty() || grid.size() < static_cast<size_t>(y + height) || grid[0].size() < static_cast<size_t>(x + width))
    {
        return;
    }

    for(int h = y; h < (y + height); ++h)
    {
        GridRow& row(grid[h]);
        for(int w = x; w < (x + width); ++w)
        {
            row[w] = symbol;
        }
    }
}

void PrintGrid(const Grid& grid)
{
    for(size_t h = 0; h < grid.size(); h++)
    {
        const GridRow& row(grid[h]);
        for(size_t w = 0; w < row.size(); w++)
        {
            std::cout << row[w];
        }
        std::cout << std::endl;
    }
}

int main()
{
    int height = 13, width = 15, i = 1;
    std::string syms, sym = "$#*@";
    Grid grid;
    InitGrid(grid, width, height, sym.at(0));
    sym = sym + sym.at(0);
    sym.erase(0,1);
    while(height >= 0 && width >= 0)
    {
        width = width - 2;
        height = height - 2;
        DrawRectangle(grid, sym.at(0), i, i, width, height);
        sym = sym + sym.at(0);
        sym.erase(0,1);
        i++;
    }
    PrintGrid(grid);

    return 0;
}