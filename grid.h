#ifndef GRID_H
#define GRID_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <vector>
#include <string>
#include <random>
#include <ostream>
#include "cell.h"

template<typename Cell_Type>
class Grid_base {
public:
	friend std::ostream & operator<<(std::ostream &os, Grid_base<Cell_Type>& g);
	Grid_base<Cell_Type>(int r, int c);

	Cell_Type* at(int row, int column);

	virtual Cell_Type* random_cell();

	int size() { return rows * columns; }
	void to_img(int cell_size = 10, std::string file_name = "maze.png");
	std::vector<Cell_Type *> deadends();
	virtual std::string contents_of(Cell_Type cell);
	virtual cv::Scalar background_color_for(Cell_Type cell);

	int rows;
	int columns;
	std::vector<std::vector<Cell_Type>> grid;

protected:
	std::vector<std::vector<Cell_Type>> prepare_grid();
	void configure_cells();
	bool isolated_cell(Cell_Type* c);
};


template<typename Cell_Type>
Grid_base<Cell_Type>::Grid_base(int r, int c) : rows(r), columns(c)
{
	grid = prepare_grid();
	configure_cells();
}

template<typename Cell_Type>
cv::Scalar Grid_base<Cell_Type>::background_color_for(Cell_Type cell)
{
	return cv::Scalar(255, 255, 255);
}

template<typename Cell_Type>
std::string Grid_base<Cell_Type>::contents_of(Cell_Type cell)
{
	return " ";
}

template<typename Cell_Type>
bool Grid_base<Cell_Type>::isolated_cell(Cell_Type* c)
{
	return c->north == nullptr && c->south == nullptr && c->west == nullptr && c->east == nullptr;
}

template<typename Cell_Type>
std::ostream & operator<<(std::ostream &os, Grid_base<Cell_Type>& g)
{
	os << "+";
	for (int i = 0; i < g.columns; i++)
		os << "---+";
	os << std::endl;

	for (auto itr = g.grid.begin(); itr != g.grid.end(); itr ++)
	{
		std::string top = "|";
		std::string bottom = "+";
		for (auto itc = itr->begin(); itc != itr->end(); itc ++)
		{
			std::string body = " " + g.contents_of(*itc) + " ";
			std::string east_boundary = itc->is_linked(itc->east) ? " " : "|";
			top += (body + east_boundary);
			std::string south_boundary = itc->is_linked(itc->south) ? "   " : "---";
			std::string corner = "+";
			bottom += (south_boundary + corner);
		}
		os << top << std::endl;
		os << bottom << std::endl;
	}
	return os;
}

using Grid = Grid_base<Cell>;
#endif
