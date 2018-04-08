#ifndef GRID_H
#define GRID_H

#include <opencv2/core.hpp>
#include <vector>
#include <ostream>
#include <string>
#include "cell.h"

class Grid {
public:
	friend std::ostream & operator<<(std::ostream &os, Grid& g);
	Grid(int r, int c) : rows(r), columns(c)
	{
		grid = prepare_grid();
		configure_cells();
	}

	Cell* at(int row, int column);

	Cell* random_cell();

	int size() { return rows * columns; }
	void to_img(int cell_size = 10, std::string file_name = "maze.png");
	std::vector<Cell *> deadends();
	virtual std::string contents_of(Cell cell);
	virtual cv::Scalar background_color_for(Cell cell);

	int rows;
	int columns;
	std::vector<std::vector<Cell>> grid;
protected:
	virtual std::vector<std::vector<Cell>> prepare_grid();
	void configure_cells();
};

#endif
