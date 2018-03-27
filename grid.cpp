#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <vector>
#include <ostream>
#include <string>
#include "grid.h"

std::string Grid::contents_of(Cell cell)
{
	return " ";
}

std::ostream & operator<<(std::ostream &os, Grid& g)
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
	
std::vector<std::vector<Cell>> Grid::prepare_grid()
{
	std::vector<std::vector<Cell>> v({});
	for (int i = 0; i < rows; i++)
	{
		std::vector<Cell> vv({});
		for (int j = 0; j < columns; j++)
		{
			Cell c(i, j);
			vv.push_back(c);

		}
		v.push_back(vv);
	}

	return v;
}


void Grid::configure_cells()
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

Cell* Grid::at(int row, int column)
{
	if (row < 0 || row >= rows)
		return nullptr;
	if (column < 0 || column >= columns)
		return nullptr;
	return &grid[row][column];
}


Cell* Grid::random_cell()
{
	int r = rand() % rows;
	int c = rand() % columns;
	return at(r, c);
}



void Grid::to_img(int cell_size)
{
	int img_width = cell_size * columns;
	int img_height = cell_size * rows;
	cv::Scalar wall(255, 0, 0);
	cv::Scalar background(255, 255, 255);

	cv::Mat Im = cv::Mat(img_width + 1, img_height + 1, CV_8UC3, background);

	for (auto itr = grid.begin(); itr != grid.end(); itr++)
	{
		for (auto itc = itr->begin(); itc != itr->end(); itc++)
		{
			int x1 = itc->column * cell_size;
			int y1 = itc->row * cell_size;
			int x2 = (itc->column + 1) * cell_size;
			int y2 = (itc->row + 1) * cell_size;

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
	
	cv::imwrite("maze.png", Im);
}
