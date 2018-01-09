#include <read_txt_file.h>




int ReadXYZFile(const char *cfilename, std::vector<Line_3> *lines)
{
	std::vector<Point_3> points_on_lines;
	char a[100];
	double x = 0, y = 0, z = 0, x0, y0, z0;
	int count = 0;

	std::ifstream in(cfilename, std::ifstream::in);

	if (!in)
	{
		return -1;
	}

	do
	{
		in.getline(a, 100, '\n');

		if (sscanf(a, "%lf%lf%lf", &x, &y, &z) == 3)
		{
			/*if (count == 0)
			{
				x0 = x;
				y0 = y;
				z0 = z;
			}
			points_on_lines.push_back(Point_3(x - x0, y - y0, z - z0));*/
			points_on_lines.push_back(Point_3(x, y, z));
		}
		count++;
	} while (!in.eof());

	size_t size_of_lines = points_on_lines.size() / 2;
	for (size_t i = 0; i < size_of_lines; i++)
	{
		//std::cout << points_on_lines[i * 2] << " " << points_on_lines[i * 2 + 1] << std::endl;
		(*lines).push_back(Line_3(points_on_lines[i * 2], points_on_lines[i * 2 + 1]));
		//std::cout << (*lines)[i].point().x() << " " << (*lines)[i].point().y() << " " << (*lines)[i].point().z() << std::endl;
		//std::cout << (*lines)[i].to_vector().x() << " " << (*lines)[i].to_vector().y() << " " << (*lines)[i].to_vector().z() << std::endl;
	}

	return 0;
}


int OutputAsCSV(std::vector<std::vector<Point_3>> location)
{
	std::ofstream outdata;
	std::string name_file = "C:\\Users\\sinara\\Desktop\\location.csv";
	outdata.open(name_file, ios::out);
	outdata.clear();

	const size_t num_location = location.size();
	for (std::size_t i = 0; i < num_location; ++i)
	{
		const size_t num = location[i].size();
		outdata << " " << ",";
		for (std::size_t j = 0; j < i; ++j)
		{
			outdata << " " << ",";
		}
		for (std::size_t j = 0; j < num; ++j)
		{		
			outdata << "(" << location[i][j].x() << " " << location[i][j].y() << " " << location[i][j].z() << ")" << ",";
		}	
		outdata << std::endl;
	}
	return 0;
}

int OutputAsTXT(std::vector<std::vector<Point_3>> location)
{
	std::ofstream outdata;
	std::string name_file = "C:\\Users\\sinara\\Desktop\\location.txt";
	outdata.open(name_file, ios::out);
	outdata.clear();

	const size_t num_location = location.size();
	for (std::size_t i = 0; i < num_location; ++i)
	{
		const size_t num = location[i].size();
		for (std::size_t j = 0; j < num; ++j)
		{
			outdata << location[i][j].x() << " " << location[i][j].y() << " " << location[i][j].z() << std::endl;
		}
	}
	return 0;
}

int OutputAsCSV(std::vector<std::vector<double>> distance)
{
	std::ofstream outdata;
	std::string name_file = "C:\\Users\\sinara\\Desktop\\distance.csv";
	outdata.open(name_file, ios::out);
	outdata.clear();

	const size_t num_location = distance.size();
	for (std::size_t i = 0; i < num_location; ++i)
	{
		const size_t num = distance[i].size();
		outdata << " " << ",";
		for (std::size_t j = 0; j < i; ++j)
		{
			outdata << " " << ",";
		}
		for (std::size_t j = 0; j < num; ++j)
		{
			outdata << distance[i][j] << ",";
		}
		outdata << std::endl;
	}
	return 0;
}