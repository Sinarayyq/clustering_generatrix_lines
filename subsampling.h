#pragma once


#ifndef SUBSAMPLING_H
#define SUBSAMPLING_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/hierarchy_simplify_point_set.h>
#include <CGAL/IO/read_xyz_points.h>
#include <CGAL/IO/write_xyz_points.h>

#include <vector>
#include <fstream>
#include <opennurbs.h>

// types
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3 Point;

int Subsampling(ON_3dPointArray points_before_subsampling, ON_3dPointArray *subsampled_points);


#endif