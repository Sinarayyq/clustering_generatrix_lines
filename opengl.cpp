#include <opengl.h>


void myDisplay(std::vector<Line_3> lines,std::vector<Point_3> mid_points,std::vector<Line_3> mid_lines)
{

}



int VisualizeInOpenGL(std::vector<Line_3> lines,
	std::vector<Point_3> mid_points,
	std::vector<Line_3> mid_lines)
{
	int argc = 1;
	char **argv;
	argv = (char **)malloc(sizeof(char**));
	*argv = "C:\\Development\\opencv_test\\source\\build\\Debug\\opencv_test.exe";
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("第一个 OpenGL 程序");
	//glutDisplayFunc(&myDisplay(std::vector<Line_3> lines,std::vector<Point_3> mid_points,std::vector<Line_3> mid_lines));
	glutMainLoop();

	return 0;
}