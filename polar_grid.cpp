#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "polar_grid.h"
#include "polar_cell.h"

#include <cmath>

std::vector<std::vector<Polar_cell>> Polar_grid::prepare_grid()
{
	std::vector<std::vector<Polar_cell>> v({});
	return v;
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

			if (!itc->is_linked(itc->north))
				cv::line(Im, cv::Point(ax, ay), cv::Point(cx, cy), wall);
			if (!itc->is_linked(itc->east))
				cv::line(Im, cv::Point(cx, cy), cv::Point(dx, dy), wall);
		}
	}

	cv::circle(Im, cv::Point(center, center), rows * cell_size, wall);
	
	cv::imwrite(file_name, Im);
}


