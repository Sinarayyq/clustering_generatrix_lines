//Sinara YANG
//This functions are used to read lines information(head and tail) into vector.


#pragma once

#ifndef CLUSTERING_H
#define CLUSTERING_H



#include <iostream>
#include <vector>
#include <Eigen/Geometry> 
#include <math.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/grid_simplify_point_set.h>

//#include <opengl.h>

#include <visualize_pcl.h>

//#include <pcl/common/common_headers.h>
//#include <pcl/features/normal_3d.h>
//#include <pcl/io/pcd_io.h>
//#include <pcl/visualization/pcl_visualizer.h>
//#include <pcl/console/parse.h>



typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 Point_3;
typedef K::Line_3 Line_3;
typedef K::Plane_3 Plane_3;


int ComputeDistanceAndLocationOfEveryTwoLines(std::vector<Line_3> lines, std::vector<std::vector<Point_3>> *location, std::vector<std::vector<double>> *distance, double length_of_panel);

int FindCylinderBorders(std::vector<std::vector<Point_3>> location, std::vector<std::vector<double>> distance, std::vector<bool> *pick);

//int VisualizeLinesAndPoints(std::vector<Line_3> lines,
//	std::vector<std::vector<Point_3>> location,
//	std::vector<std::vector<Line_3>> mid_lines);

#endif