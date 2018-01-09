#include <visualize_pcl.h>

int VisualizeLinesAndPoints(std::vector<Line_3> lines,
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,
	std::vector<Line_3> mid_lines)
{
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
	viewer = visLines(lines, cloud, mid_lines);
	viewer->resetCamera();

	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
	viewer->close();

	return 0;
}

boost::shared_ptr<pcl::visualization::PCLVisualizer> visLines(std::vector<Line_3> lines,
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,
	std::vector<Line_3> mid_lines)
{
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("lines"));
	viewer->setBackgroundColor(0, 0, 0);
	viewer->addPointCloud<pcl::PointXYZ>(cloud, "sample cloud");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "sample cloud");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_LINE_WIDTH, 3, "sample cloud");
	viewer->addCoordinateSystem(1, "global");
	viewer->setCameraPosition(0, -1, 0,//double pos_x, double pos_y, double pos_z,                                    
		0, 0, 0,//double view_x, double view_y, double view_z,
		0, 0, 1);//double up_x, double up_y, double up_z, int viewport = 0););

	std::vector<int> colors;
	size_t size_mid_lines = mid_lines.size();
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_mid_lines = ConvertLinesToCloud(mid_lines);
	for (size_t j = 0; j < size_mid_lines * 2; j += 2)
	{
		viewer->addLine<pcl::PointXYZ>(cloud_mid_lines->points[j], cloud_mid_lines->points[j + 1], 255,0,0,std::to_string(static_cast<long long>(j)));
	}

	size_t size_lines = lines.size();
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_lines = ConvertLinesToCloud(lines);
	for (size_t j = 0; j < size_lines * 2; j += 2)
	{
		viewer->addLine<pcl::PointXYZ>(cloud_lines->points[j], cloud_lines->points[j + 1], 0,255,255,std::to_string(static_cast<long long>(size_mid_lines * 2 + j)));
	}

	viewer->resetCamera();
	return (viewer);
}

pcl::PointCloud<pcl::PointXYZ>::Ptr ConvertLinesToCloud(std::vector<Line_3> lines)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	size_t size_lines = lines.size();
	for (size_t i = 0; i < size_lines; i++)
	{
		cloud->push_back(pcl::PointXYZ(lines[i].point(0).x(), lines[i].point(0).y(), lines[i].point(0).z()));
		cloud->push_back(pcl::PointXYZ(lines[i].point(1).x(), lines[i].point(1).y(), lines[i].point(1).z()));
	}
	return cloud;
}