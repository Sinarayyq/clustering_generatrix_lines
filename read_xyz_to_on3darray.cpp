#include <read_xyz_to_on3darray.h>


int ReadXYZFile(const char *cfilename)
{
	ON_3dPointArray subsampled_points;
	char a[100];
	double x = 0, y = 0, z = 0;

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
			subsampled_points.Append(ON_3dPoint(x, y ,z));
		}

	} while (!in.eof());

	return 0;
}