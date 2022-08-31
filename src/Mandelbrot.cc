// A simple OpenGL program that draws a fractal.
//In this programm currently Mandelbrot set is drawn upon execution

#include "GL/freeglut.h"
#include "GL/gl.h"
#include <array>
#include <iostream>
#include "../lib/Palette.h"

using namespace std;

void drawFrac()
{
	array<float, 3> color;

	//glClearColor(0.4, 0.4, 0.4, 0.4);
	glClear(GL_COLOR_BUFFER_BIT);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	const unsigned int window_size_x = 1920;
	const unsigned int window_size_y = 1080;

	for (int x = 0; x <= window_size_x; x++)
	{
		for (int y = 0; y <= window_size_y; y++) 
		{
			//re_z = x_pos;
			double x_pos = ((double) x/window_size_x-0.5)*4. + 0.5;
			double y_pos = ((double) y/window_size_y-0.5)*4.;

			double c_x = ((double) x/window_size_x-0.5)*4.0;
			double c_y = ((double) y/window_size_y-0.5)*4.0;

			double re_z = 0.0;
			double im_z = 0.0;

			long int iter = 0;
			
			//cout << re_z << " " << im_z << " " << iter << " " << endl;

			const unsigned int iter_max = 100;

			while (iter <= iter_max && re_z*re_z +im_z*im_z <= 4.0)
			{

				double re_z_temp = re_z*re_z - im_z*im_z + c_x;
				im_z = 2*re_z*im_z + c_y;
				re_z = re_z_temp;

				iter++;
			}

			if (iter < iter_max)
			{
				float col_val = (float) iter/iter_max;

				color[0] = OceanPalette.R(col_val);
				color[1] = OceanPalette.G(col_val);
				color[2] = OceanPalette.B(col_val);

				glColor3f(color[0], color[1], color[2]);
			}

			else glColor3f(0, 0, 0);

			glBegin(GL_POINTS);
			glVertex2f(x_pos, y_pos);
			glEnd();

		}
	}

	glFlush();
}

int main(int argc, char **argv)
{

	const int window_size_x = 1920;
	const int window_size_y = 1080;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(window_size_x, window_size_y);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL - Mandelbrot set");
	glutDisplayFunc(drawFrac);
    glutMainLoop();

    return 0;
}
