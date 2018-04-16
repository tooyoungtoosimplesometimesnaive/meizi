#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "polar_grid.h"
#include "polar_cell.h"
#include "rand.h"

#include <vector>
#include <cmath>

std::vector<std::vector<Polar_cell>> Polar_grid::prepare_grid()
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

void Polar_grid::configure_cells()
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
				int r = grid[r].size() / grid[r - 1] .size();
				int parent = grid[r - 1][c / r];
				parent->outward.push_back(&(*itc));
				itc->inward = parent;
			}
		}
	}
}


Polar_cell* Polar_grid::random_cell()
{
	int r = random(0, rows - 1);
	int c = random(0, grid[r].size() - 1);
	return at(r, c);
}

void Polar_grid::to_img(int cell_size, std::string file_name)
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
			if (isolated_cell(&(*itc)))
				continue;

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

			/*
			if (!itc->is_linked(itc->north))
				cv::line(Im, cv::Point(ax, ay), cv::Point(cx, cy), wall);
			if (!itc->is_linked(itc->east))
				cv::line(Im, cv::Point(cx, cy), cv::Point(dx, dy), wall);
				*/
			if (!itc->is_linked(itc->inward))
				cv::line(Im, cv::Point(ax, ay), cv::Point(cx, cy), wall);
			if (!itc->is_linked(itc->cw))
				cv::line(Im, cv::Point(cx, cy), cv::Point(dx, dy), wall);

		}
	}

	cv::circle(Im, cv::Point(center, center), rows * cell_size, wall);
	
	cv::imwrite(file_name, Im);
}


