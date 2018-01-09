//Sinara YANG
//This functions are used to visualize in pcl.


#pragma once

#ifndef VISUALIZE_PCL_H
#define VISUALIZE_PCL_H



#include <pcl/common/common_headers.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>

#include <clustering.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 Point_3;
typedef K::Line_3 Line_3;
typedef K::Plane_3 Plane_3;


int VisualizeLinesAndPoints(std::vector<Line_3> lines, 
							pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,
	                        std::vector<Line_3> mid_lines);

boost::shared_ptr<pcl::visualization::PCLVisualizer> visLines(std::vector<Line_3> lines,
															  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,
															  std::vector<Line_3> mid_lines);

pcl::PointCloud<pcl::PointXYZ>::Ptr ConvertLinesToCloud(std::vector<Line_3> lines);


#endif