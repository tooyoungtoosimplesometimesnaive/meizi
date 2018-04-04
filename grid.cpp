#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <vector>
#include <ostream>
#include <string>
#include <random>
#include "grid.h"

cv::Scalar Grid::background_color_for(Cell cell)
{
	return cv::Scalar(255, 255, 255);
}

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
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist_r(0, rows - 1), dist_c(0, columns - 1);
	return at(dist_r(gen), dist_c(gen));
}


std::vector<Cell *> Grid::deadends()
{
	std::vector<Cell *> l({});
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

void Grid::to_img(int cell_size, std::string file_name)
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
