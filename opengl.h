//Sinara YANG
//This functions are used to visualize in OPENGL.


#pragma once

#ifndef OPENGL_H
#define OPENGL_H


#include <glut.h>

//#include <clustering.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 Point_3;
typedef K::Line_3 Line_3;
typedef K::Plane_3 Plane_3;


int VisualizeInOpenGL(std::vector<Line_3> lines, std::vector<Point_3> mid_points, std::vector<Line_3> mid_lines);

#endif