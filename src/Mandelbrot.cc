// A simple OpenGL program that draws a fractal.
//In this programm currently Mandelbrot set is drawn upon execution

#include "GL/freeglut.h"
#include "GL/gl.h"
#include <array>
#include <iostream>
#include "../lib/Palette.h"

struct
{
	int x_pos = 0;
	int y_pos = 0;
}mouse;

struct
{
	const unsigned int size_x = 1920;
	const unsigned int size_y = 1080;
}window;

double zoom = 1.;
double max_iter_change = 2.;

using namespace std;

void drawFrac()
{
	array<float, 3> color;

	//glClearColor(0.4, 0.4, 0.4, 0.4);
	glClear(GL_COLOR_BUFFER_BIT);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	if (zoom > max_iter_change*2) max_iter_change*=2;
	else if (zoom < max_iter_change/2) max_iter_change/=2;

	for (int x = 0; x <= window.size_x; x++)
	{
		for (int y = 0; y <= window.size_y; y++) 
		{
			//pooint position
			double x_pos = ((double) x/window.size_x-0.5)*4. + 0.5;
			double y_pos = ((double) y/window.size_y-0.5)*4.;

			double c_x = ((double) (x - 0.5 + mouse.x_pos/2)/zoom/window.size_x-0.5)*4.0;
			double c_y = ((double) (y - 0.5 + mouse.y_pos/2)/zoom/window.size_y-0.5)*4.0;

			double re_z = 0.0;
			double im_z = 0.0;

			long int iter = 0;
			
			double iter_max = 100.*pow(max_iter_change - 1., 2);

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

void mouseClick(int btn, int state, int x, int y) {
	if (state == GLUT_DOWN)
	{
		switch(btn)
		{
		case GLUT_LEFT_BUTTON:
			break;

		case GLUT_RIGHT_BUTTON:
			break;

		case GLUT_MIDDLE_BUTTON:
			break;

		case 3:
			zoom *= 1.05;
			std::cout << "Zoom now is " << zoom << "\r";
			std::cout.flush();
			break;

		case 4:
			zoom /= 1.05;
			std::cout << "Zoom now is " << zoom << "\r";
			std::cout.flush();
			break;

		default:
			break;
		}
	}
	mouse.x_pos = x;
	mouse.y_pos = y;
	
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(window.size_x, window.size_y);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL - Mandelbrot set");
	glutDisplayFunc(drawFrac);

	glutMouseFunc(mouseClick);

	glutMainLoop();

	return 0;
}
