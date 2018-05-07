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
#include <cmath>
#include "rand.h"
#include "cell.h"
#include "polar_cell.h"
#include "hex_cell.h"

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
	Grid_base(int r);

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
Grid_base<Cell_Type>::Grid_base(int r) : rows(r), columns(r)
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
	return &grid[row][column % grid[row].size()];
}

template<>
Polar_cell* Grid_base<Polar_cell>::at(int row, int column)
{
	if (row < 0 || row >= rows)
		return nullptr;
	return &grid[row][column % grid[row].size()];
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

template <>
std::vector<std::vector<Polar_cell>> Grid_base<Polar_cell>::prepare_grid()
{
	std::vector<std::vector<Polar_cell>> v({});
	double row_height = 1.0 / rows;

	Polar_cell pc(0, 0);
	std::vector<Polar_cell> r1({ pc });
	v.push_back(r1);

	for (int row = 1; row < rows; row++)
	{
		double radius = ((double) row) / rows;
		double circumference = 2.0 * 3.1415926 * radius;

		int previous_count = v[row - 1].size();
		double estimated_cell_width = circumference / previous_count;

		// Ratio: always be either 1 or 2;
		int r = std::floor(estimated_cell_width / row_height);
		int cells = previous_count * r;

		std::vector<Polar_cell> this_row;
		for (int c = 0; c < cells; c++)
		{
			Polar_cell p(row, c);
			this_row.push_back(p);
		}
		v.push_back(this_row);
	}

	return v;
}

template <>
void Grid_base<Polar_cell>::configure_cells()
{
	for (auto itr = grid.begin(); itr != grid.end(); itr++)
	{
		for (auto itc = itr->begin(); itc != itr->end(); itc++)
		{
			int r = itc->row;
			int c = itc->column;
			if (r > 0)
			{
				itc->cw = at(r, c + 1);
				itc->ccw = at(r, c - 1);

				// the ratio:
				int ra = grid[r].size() / grid[r - 1].size();
				Polar_cell* parent = at(r - 1, c / ra);
				parent->outward.push_back(&(*itc));
				itc->inward = parent;
			}
		}
	}
}


template <>
Polar_cell* Grid_base<Polar_cell>::random_cell()
{
	int r = random(0, rows - 1);
	int c = random(0, grid[r].size() - 1);
	return at(r, c);
}

template <>
void Grid_base<Polar_cell>::to_img(int cell_size, std::string file_name)
{
	int img_size = 2 * rows * cell_size;

	cv::Scalar wall(0, 0, 0);
	cv::Scalar background(255, 255, 255);

	cv::Mat Im = cv::Mat(img_size + 1, img_size + 1, CV_8UC3, background);

	int center = img_size / 2;

	for (auto itr = grid.begin(); itr != grid.end(); itr++)
	{
		for (auto itc = itr->begin(); itc != itr->end(); itc++)
		{

			double theta = 2 * 3.1415926 / grid[itc->row].size();
			double inner_radius = itc->row * cell_size;
			double outer_radius = (itc->row + 1.0) * cell_size;
			double theta_ccw = itc->column * theta;
			double theta_cw = (itc->column + 1) * theta;

			int ax = center + (int)(inner_radius * std::cos(theta_ccw));
			int ay = center + (int)(inner_radius * std::sin(theta_ccw));

			int bx = center + (int)(outer_radius * std::cos(theta_ccw));
			int by = center + (int)(outer_radius * std::sin(theta_ccw));

			int cx = center + (int)(inner_radius * std::cos(theta_cw));
			int cy = center + (int)(inner_radius * std::sin(theta_cw));

			int dx = center + (int)(outer_radius * std::cos(theta_cw));
			int dy = center + (int)(outer_radius * std::sin(theta_cw));

			if (!itc->is_linked(itc->inward))
				cv::line(Im, cv::Point(ax, ay), cv::Point(cx, cy), wall);
			if (!itc->is_linked(itc->cw))
				cv::line(Im, cv::Point(cx, cy), cv::Point(dx, dy), wall);

		}
	}

	cv::circle(Im, cv::Point(center, center), rows * cell_size, wall);
	
	cv::imwrite(file_name, Im);
}

template <>
void Grid_base<Hex_cell>::configure_cells()
{
	for (auto itr = grid.begin(); itr != grid.end(); itr++)
	{
		for (auto itc = itr->begin(); itc != itr->end(); itc++)
		{
			int row = itc->row;
			int col = itc->column;

			int north_diagonal, south_diagonal;

			if (col % 2 == 0) {
				north_diagonal = row - 1;
				south_diagonal = row;
			} else {
				north_diagonal = row;
				south_diagonal = row + 1;
			}

			itc->northwest = at(north_diagonal, col - 1);
			itc->north = at(row - 1, col);
			itc->northeast = at(north_diagonal, col + 1);
			itc->southwest = at(south_diagonal, col - 1);
			itc->south = at(row + 1, col);
			itc->southeast = at(south_diagonal, col + 1);
		}
	}
}

template<>
void Grid_base<Hex_cell>::to_img(int cell_size, std::string file_name)
{
	double a_size = cell_size / 2.0;
	double b_size = cell_size * std::sqrt(3) / 2.0;

	double width = cell_size * 2;
	double height = b_size * 2;

	int img_width = (int)(3 * a_size * columns + a_size + 0.5);
	int img_height = (int)(height * rows + b_size + 0.5);

	cv::Scalar wall(0, 0, 0);
	cv::Scalar background(255, 255, 255);

	cv::Mat Im = cv::Mat(img_height + 1, img_width + 1, CV_8UC3, background);

	// 1 -> background
	// 2 -> walls
	int mode[] = {1, 2};
	for (auto m : mode) {
	for (auto itr = grid.begin(); itr != grid.end(); itr++)
	{
		for (auto itc = itr->begin(); itc != itr->end(); itc++)
		{
			double cx = cell_size + 3 * itc->column * a_size;
			double cy = b_size + itc->row * height;
			if (itc->column % 2 != 0)
			{
				cy += b_size;
			}

			// f/n = far/near
			// n/s/e/w = north/south/east/west
			int x_fw = (int)(cx - cell_size);
			int x_nw = (int)(cx - a_size);
			int x_ne = (int)(cx + a_size);
			int x_fe = (int)(cx + cell_size);

			int y_n = (int)(cy - b_size);
			int y_m = (int)(cy);
			int y_s = (int)(cy + b_size);

			if (m == 1) {
			}
			else {
				/*
				if (itc->row == 0) {
					cv::line(Im, cv::Point(x_nw, y_n), cv::Point(x_ne, y_n), wall);
					cv::line(Im, cv::Point(x_fw, y_m), cv::Point(x_nw, y_n), wall);
				}

				if (itc->row == rows - 1) {
					cv::line(Im, cv::Point(x_fw, y_m), cv::Point(x_nw, y_s), wall);
				}
				*/

				if (itc->southwest == nullptr) {
					cv::line(Im, cv::Point(x_fw, y_m), cv::Point(x_nw, y_s), wall);
				}
				if (itc->northwest == nullptr) {
					cv::line(Im, cv::Point(x_fw, y_m), cv::Point(x_nw, y_n), wall);
				}
				if (itc->north == nullptr) {
					cv::line(Im, cv::Point(x_nw, y_n), cv::Point(x_ne, y_n), wall);
				}
				if (!itc->is_linked(itc->northeast)) {
					cv::line(Im, cv::Point(x_ne, y_n), cv::Point(x_fe, y_m), wall);
				}
				if (!itc->is_linked(itc->southeast)) {
					cv::line(Im, cv::Point(x_fe, y_m), cv::Point(x_ne, y_s), wall);
				}
				if (!itc->is_linked(itc->south)) {
					cv::line(Im, cv::Point(x_ne, y_s), cv::Point(x_nw, y_s), wall);
				}
			}
		}
	}
	}
	
	cv::imwrite(file_name, Im);
}

using Grid = Grid_base<Cell>;
using Polar_grid = Grid_base<Polar_cell>;
using Hex_grid = Grid_base<Hex_cell>;
#endif
