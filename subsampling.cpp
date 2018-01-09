#include<subsampling.h>

int Subsampling(ON_3dPointArray points_before_subsampling, ON_3dPointArray *subsampled_points)
{
	
	size_t size_points_before_subsampling = points_before_subsampling.SizeOfArray();

	std::vector<Point> points_cgal;
	for (size_t i = 0; i < size_points_before_subsampling; i++)
	{
		points_cgal.push_back(Point(points_before_subsampling.At(i)->x, points_before_subsampling.At(i)->y, points_before_subsampling.At(i)->z));
	}

	points_cgal.erase(CGAL::hierarchy_simplify_point_set(points_cgal.begin(), points_cgal.end(),
		                                                 10, // Max cluster size
		                                                 0.1), // Max surface variation
		                                                 points_cgal.end());

	size_t size_subsampled_points = points_cgal.size();

	for (size_t i = 0; i < size_subsampled_points; i++)
	{
		(*subsampled_points).Append(ON_3dPoint(points_cgal[i].x(), points_cgal[i].y(), points_cgal[i].z()));

	}
	return 0;
	
}