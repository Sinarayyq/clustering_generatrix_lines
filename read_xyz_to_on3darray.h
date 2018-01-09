#pragma once
//Sinara YANG
//This functions are used to read coordinates of points from xyz file and keep them in Opennurbs library.


#pragma once

#ifndef READ_XYZ_TO_ON3DARRAY_H
#define READ_XYZ_TO_ON3DARRAY_H



#include<iostream>
#include<fstream>
#include<opennurbs.h>

int ReadXYZFile(const char *cfilename);

#endif