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
class Grid_base;

// Forward declare this friend:
template<typename Cell_Type>
std::ostream & operator<<(std::ostream &os, Grid_base<Cell_Type>& g);

template<typename Cell_Type>
class Grid_base {
public:
	friend std::ostream & operator<< <Cell_Type> (std::ostream &os, Grid_base<Cell_Type>& g);
	Grid_base(int r, int c);

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

template<typename Cell_Type>
std::vector<std::vector<Cell_Type>> Grid_base<Cell_Type>::prepare_grid()
{
	std::vector<std::vector<Cell_Type>> v({});
	for (int i = 0; i < rows; i++)
	{
		std::vector<Cell_Type> vv({});
		for (int j = 0; j < columns; j++)
		{
			Cell_Type c(i, j);
			vv.push_back(c);

		}
		v.push_back(vv);
	}

	return v;
}


template<typename Cell_Type>
void Grid_base<Cell_Type>::configure_cells()
{
	for (auto itr = grid.begin(); itr != grid.end(); itr++)
	{
		for (auto itc = itr->begin(); itc != itr->end(); itc++)
		{
			int r = itc->row;
			int c = itc->column;
			itc->north = at(r - 1, c);
			itc->south = at(r + 1, c);
			itc->west = at(r, c - 1);
			itc->east = at(r, c + 1);
		}
	}
}

template<typename Cell_Type>
Cell_Type* Grid_base<Cell_Type>::at(int row, int column)
{
	if (row < 0 || row >= rows)
		return nullptr;
	if (column < 0 || column >= columns)
		return nullptr;
	return &grid[row][column];
}


template<typename Cell_Type>
Cell_Type* Grid_base<Cell_Type>::random_cell()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist_r(0, rows - 1), dist_c(0, columns - 1);
	return at(dist_r(gen), dist_c(gen));
}


template<typename Cell_Type>
std::vector<Cell_Type *> Grid_base<Cell_Type>::deadends()
{
	std::vector<Cell_Type *> l({});
	for (auto itr = grid.begin(); itr != grid.end(); itr++)
	{
		for (auto itc = itr->begin(); itc != itr->end(); itc++)
		{
			if (itc->links.size() == 1)
			{
				l.push_back(&(*itc));
			}
		}
	}
	return l;
}

template<typename Cell_Type>
void Grid_base<Cell_Type>::to_img(int cell_size, std::string file_name)
{
	int img_width = cell_size * columns;
	int img_height = cell_size * rows;
	cv::Scalar wall(0, 0, 0);
	cv::Scalar background(255, 255, 255);

	cv::Mat Im = cv::Mat(img_width + 1, img_height + 1, CV_8UC3, background);

	// 1 -> background
	// 2 -> walls
	int mode[] = {1, 2};
	for (auto m : mode) {
	for (auto itr = grid.begin(); itr != grid.end(); itr++)
	{
		for (auto itc = itr->begin(); itc != itr->end(); itc++)
		{
			if (isolated_cell(&(*itc)))
				continue;

			int x1 = itc->column * cell_size;
			int y1 = itc->row * cell_size;
			int x2 = (itc->column + 1) * cell_size;
			int y2 = (itc->row + 1) * cell_size;

			if (m == 1)
			{
				cv::Scalar bg_color = background_color_for(*itc);
				cv::rectangle(Im, cv::Point(x1, y1), cv::Point(x2, y2), bg_color, -1);
			} else {
				if (itc->north == nullptr)
					cv::line(Im, cv::Point(x1, y1), cv::Point(x2, y1), wall);
				if (itc->west == nullptr)
					cv::line(Im, cv::Point(x1, y1), cv::Point(x1, y2), wall);
				if (!itc->is_linked(itc->east))
					cv::line(Im, cv::Point(x2, y1), cv::Point(x2, y2), wall);
				if (!itc->is_linked(itc->south))
					cv::line(Im, cv::Point(x1, y2), cv::Point(x2, y2), wall);
			}
		}
	}
	}
	
	cv::imwrite(file_name, Im);
}

using Grid = Grid_base<Cell>;
#endif
