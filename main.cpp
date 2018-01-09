//#include <fitting_3D_points_to_line.h>

#include <read_txt_file.h>
#include <clustering.h>

#include <CGAL/bounding_box.h>


//typedef K::Point_2 point;
//typedef Kernel::Point_2 Point_2;
//typedef Kernel::Segment_2 Segment_2;

//#include<fstream>
//#include<iomanip>
//#include<string>
//#include<vector>
//#include<Eigen/Dense>
//#include<Eigen/Core>
//#include<math.h>
//#include<opennurbs.h>
//
//int main()
//{
//	std::vector<ON_3dPoint> points_opennurbs;
//	points_opennurbs.push_back(ON_3dPoint(0, 1, 2));
//	points_opennurbs.push_back(ON_3dPoint(3, 4, 5));
//	points_opennurbs.push_back(ON_3dPoint(6, 7, 8));
//	points_opennurbs.push_back(ON_3dPoint(9, 10, 11));
//	points_opennurbs.push_back(ON_3dPoint(12, 13, 14));
//	
//	double error;
//	ON_3dPoint head, tail;
//
//	Fitting3DPointsToLine(points_opennurbs, &error, &head, &tail);
//	std::cout << "error = " << error << std::endl;
//	std::cout << "line = (" << head.x << "," << head.y << "," << head.z << ") -> (" << tail.x << "," << tail.y << "," << tail.z << ")" << std::endl;
//
//	system("pause");
//	return 0;
//}
std::vector<Point_3> ConvertLinesToPoints(std::vector<Line_3> lines)
{
	std::vector<Point_3> points;
	size_t size_lines = lines.size();
	for (size_t i = 0; i < size_lines; i++)
	{
		points.push_back(Point_3(lines[i].point(0).x(), lines[i].point(0).y(), lines[i].point(0).z()));
		points.push_back(Point_3(lines[i].point(1).x(), lines[i].point(1).y(), lines[i].point(1).z()));
	}
	return points;
}

double ComputeLengthOfPanel(std::vector<Line_3> lines)
{
	std::vector<Point_3> points = ConvertLinesToPoints(lines);

	K::Iso_cuboid_3 c3 = CGAL::bounding_box(points.begin(), points.end());
	std::cout << c3 << std::endl;
	

	return sqrt((c3.max() - c3.min()).squared_length());
}

int main()
{
	string load_file;
	getline(cin, load_file);
	//const char* input_file = "C:\\Users\\sinara\\Desktop\\clustering_lines.txt";
	//ON_3dPointArray subsampled_points;
	/* p1(1, 1), p2(10, 10);
	CGAL::squared_distance(p1, p2);*/
	std::vector<Line_3> lines;
	ReadXYZFile(load_file.c_str(), &lines);

	size_t number_of_lines = lines.size();
	std::vector<std::vector<Point_3>> location;    //of_nearest_points_on_lines
	std::vector<std::vector<double>> distance;      //of_nearest_points_on_lines

	double length_of_panel = ComputeLengthOfPanel(lines);
	std::cout << length_of_panel << std::endl;

	if (ComputeDistanceAndLocationOfEveryTwoLines(lines, &location, &distance, length_of_panel) != 0)
	{
		return -1;
	}

	OutputAsCSV(location);
	OutputAsTXT(location);
	OutputAsCSV(distance);

	std::vector<bool> pick;
	for (size_t i = 0; i < number_of_lines; i++)
	{
		pick.push_back(false);
	}
	
	FindCylinderBorders(location, distance, &pick);



	return 0;
}