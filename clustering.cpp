#include <clustering.h>

int ComputeDistanceAndLocationOfEveryTwoLines(std::vector<Line_3> lines, std::vector<std::vector<Point_3>> *location, std::vector<std::vector<double>> *distance, double length_of_panel)
{
	size_t size_of_lines = lines.size();
	if (size_of_lines < 2)
	{
		std::cout << "Unsufficient lines" << std::endl;
		return -1;
	}
	
	Point_3 point1, point2;
	Line_3 L1, L2;
	Plane_3 plane1, plane2;
	std::vector<Line_3> mid_lines;
	
	//std::vector<Point_3> mid_points;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	//cloud->width = size_of_lines * (size_of_lines - 1) / 2;
	//cloud->height = 1;
	//cloud->is_dense = false;
	//cloud->resize(cloud->width * cloud->height);

	int count_parallel = 0;
	for (size_t i = 0; i < size_of_lines - 1; i++)
	{
		L1 = lines[i];
		std::vector<Point_3> temp_location;
		std::vector<double> temp_distance;
		for (size_t j = i + 1; j < size_of_lines; j++)
		{
			L2 = lines[j];
			Point_3 mid_L1((L1.point(0).x() + L1.point(1).x()) / 2, (L1.point(0).y() + L1.point(1).y()) / 2, (L1.point(0).z() + L1.point(1).z()) / 2);
			Point_3 mid_L2((L2.point(0).x() + L2.point(1).x()) / 2, (L2.point(0).y() + L2.point(1).y()) / 2, (L2.point(0).z() + L2.point(1).z()) / 2);
			if (sqrt((mid_L1 - mid_L2).squared_length()) > length_of_panel / 10)
			{
				continue;
			}
			std::cout << sqrt((mid_L1 - mid_L2).squared_length()) << std::endl;
			Plane_3 plane1(L1, L1.point(0) + L2.to_vector());             // get plane p1 that contains l1 and is parallel to l2 
			Plane_3 plane2(L1, L1.point(0) + plane1.orthogonal_vector()); // get plane p2 that contains l1 and is perpendicular to p1 
			
			CGAL::Object result = CGAL::intersection(plane2, L2);         // get intersection point1 between plane2 and L2 					
			if (!CGAL::assign(point1, result))
			{
				Point_3 test;
				temp_location.push_back(test);
				//std::cout << test.x() << " " << test.y() << " " << test.z() << std::endl;
				count_parallel++;
				temp_distance.push_back(sqrt(CGAL::squared_distance(L1, L2)));
				//lines_temp.push_back(Line_3(L1.point(0), L1.point(1) + 10 * L1.to_vector()));
				//lines_temp.push_back(Line_3(L2.point(0), L2.point(1) + 10 * L2.to_vector()));

				Point_3 projected_L1_on_L2(L2.projection(L1.point(0)));
				/*mid_lines.push_back(Line_3(Point_3(projected_L1_on_L2.x() - lines[0].point(0).x(),
												   projected_L1_on_L2.y() - lines[0].point(0).y(),
												   projected_L1_on_L2.z() - lines[0].point(0).z()), 
										   Point_3(L1.point(0).x() - lines[0].point(0).x(),
												   L1.point(0).y() - lines[0].point(0).y(),
												   L1.point(0).z() - lines[0].point(0).z())));*/
				/*Point_3 mid((projected_L1_on_L2.x() + L1.point(0).x()) / 2,
					(projected_L1_on_L2.y() + L1.point(0).y()) / 2,
					(projected_L1_on_L2.z() + L1.point(0).z()) / 2);
				cloud->push_back(pcl::PointXYZ(mid.x(), mid.y(), mid.z()));*/
				
				continue;	
			}
			//std::cout << CGAL::assign(point1, result);
			point2 = L1.projection(point1);                       // get intersection i2 on l1 		
			Point_3 mid((point1.x() + point2.x()) / 2, (point1.y() + point2.y()) / 2, (point1.z() + point2.z()) / 2);  // final point is (i1+i2)/2 	
			temp_location.push_back(mid);
			temp_distance.push_back(sqrt(CGAL::squared_distance(point1, point2)));

			//lines_temp.push_back(Line_3(L1.point(j%2), point2));
			//lines_temp.push_back(Line_3(L2.point(j%2), point1));

			cloud->push_back(pcl::PointXYZ(mid.x() - lines[0].point(0).x(), mid.y() - lines[0].point(0).y(), mid.z() - lines[0].point(0).z()));
			mid_lines.push_back(Line_3(Point_3(point1.x() - lines[0].point(0).x(),
											   point1.y() - lines[0].point(0).y(),
											   point1.z() - lines[0].point(0).z()), 
								       Point_3(point2.x() - lines[0].point(0).x(),
										       point2.y() - lines[0].point(0).y(),
											   point2.z() - lines[0].point(0).z())));

		}
		(*location).push_back(temp_location);
		(*distance).push_back(temp_distance);
		
	}

	std::vector<Line_3> lines_temp;
	for (size_t i = 0; i < size_of_lines; i++)
	{
		lines_temp.push_back(Line_3(Point_3(lines[i].point(0).x() - lines[0].point(0).x(),
			                                lines[i].point(0).y() - lines[0].point(0).y(), 
		                                   	lines[i].point(0).z() - lines[0].point(0).z()), 
									Point_3(lines[i].point(1).x() - lines[0].point(0).x(),
											lines[i].point(1).y() - lines[0].point(0).y(),
											lines[i].point(1).z() - lines[0].point(0).z())));
	}
	//VisualizeInOpenGL(lines, mid_points, mid_lines);
	//VisualizeLinesAndPoints(lines, cloud, mid_lines);
	std::cout << " count_parallel = " << count_parallel << std::endl;
	VisualizeLinesAndPoints(lines_temp, cloud, mid_lines);
	
	return 0;
}

int FindCylinderBorders(std::vector<std::vector<Point_3>> location, std::vector<std::vector<double>> distance, std::vector<bool> *pick)
{
	std::vector<Point_3> points;
	size_t row = location.size();
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < row - i; j++)
		{
			points.push_back(Point_3(location[i][j].x(), location[i][j].y(), location[i][j].z()));
		}
	}

	//double  maximum_distances_subsampled_points= 25;
	//CGAL::grid_simplify_point_set(points.begin(), points.end(), maximum_distances_subsampled_points);


	std::vector<std::size_t> indices(points.size());
	for (std::size_t i = 0; i < points.size(); ++i) 
	{
		indices[i] = i;
	}

	double cell_size = 100;
	std::vector<std::size_t>::iterator end;
	end = CGAL::grid_simplify_point_set(indices.begin(),
		                                indices.end(),
		                                CGAL::make_property_map(points),
		                                cell_size);

	std::size_t k = end - indices.begin();

	std::cerr << "Keep " << k << " of " << indices.size() << "indices" << std::endl;

		std::vector<Point_3> tmp_points(k);
		for (std::size_t i = 0; i<k; ++i) 
		{
			std::cerr << "indices[" << i << "] = " << indices[i] << std::endl;
			tmp_points[i] = points[indices[i]];
		}


	return 0;
}

