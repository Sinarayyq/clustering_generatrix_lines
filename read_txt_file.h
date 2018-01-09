//Sinara YANG
//This functions are used to read lines information(head and tail) into vector.


#pragma once

#ifndef READ_TXT_FILE_H
#define READ_TXT_FILE_H



#include <iostream>
#include <fstream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 Point_3;
typedef K::Line_3 Line_3;


int ReadXYZFile(const char *cfilename, std::vector<Line_3> *lines);

int OutputAsCSV(std::vector<std::vector<Point_3>> location);

int OutputAsTXT(std::vector<std::vector<Point_3>> location);

int OutputAsCSV(std::vector<std::vector<double>> distance);

#endif