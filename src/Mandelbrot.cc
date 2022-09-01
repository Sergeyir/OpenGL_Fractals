// A simple OpenGL program that draws a fractal.
//In this programm currently Mandelbrot set is drawn upon execution

#include "GL/freeglut.h"
#include "GL/gl.h"
#include <array>
#include <iostream>
#include "../lib/Palette.h"

using namespace std;

struct
{
	double iter_max = 10.;
	double zoom = 1.;
}option;

struct
{
	unsigned int size_x = 1920;
	unsigned int size_y = 1080;
}window;

struct
{
	int x_pos = 0.;
	int y_pos = 0.;
}mouse;

void quit()
{
	exit(0);
}

void show_options(double zoom, double iter_max)
{
	std::cout << "Zoom: " << zoom << "     Iter max: " << iter_max << "     " << "\r";
	std::cout.flush();
}

void drawFrac()
{
	window.size_x = glutGet(GLUT_WINDOW_WIDTH);
	window.size_y = glutGet(GLUT_WINDOW_HEIGHT);

	show_options(option.zoom, option.iter_max);
	array<float, 3> color;

	//glClearColor(0.4, 0.4, 0.4, 0.4);
	glClear(GL_COLOR_BUFFER_BIT);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	double shift_x = -mouse.x_pos-window.size_x/2.;
	double shift_y = -mouse.y_pos-window.size_y/2.;

	for (int x = 0; x <= window.size_x; x++)
	{
		for (int y = 0; y <= window.size_y; y++) 
		{
			//pooint position
			double x_pos = ((double) x/window.size_x-0.5)*4.+0.5;
			double y_pos = ((double) y/window.size_y-0.5)*4.;

			double c_x = ((double) (x+shift_x)/option.zoom/window.size_x)*4.0;
			double c_y = ((double) (y+shift_y)/option.zoom/window.size_y)*4.0;

			double re_z = 0.0;
			double im_z = 0.0;

			long int iter = 0;
			
			while (iter <= option.iter_max && re_z*re_z +im_z*im_z <= 4.0)
			{

				double re_z_temp = re_z*re_z - im_z*im_z + c_x;
				im_z = 2*re_z*im_z + c_y;
				re_z = re_z_temp;

				iter++;
			}

			if (iter < option.iter_max)
			{
				float col_val = (float) iter/option.iter_max;

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

void mouseClick(int key, int state, int x, int y) {
	if (state == GLUT_DOWN)
	{
	cout << x << " " << y << endl;
		switch(key)
		{
		case 3:
			option.zoom *= 1.05;
			break;

		case 4:
			option.zoom /= 1.05;
			break;

		default:
			return;
		}
		mouse.x_pos = x;
		mouse.y_pos = y;
	
		glutPostRedisplay();
	}
}

void special_keys(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_DOWN:
			option.iter_max /= 2;
			break;

		case GLUT_KEY_UP:
			option.iter_max *= 2;
			break;

		case GLUT_KEY_LEFT:
			option.iter_max--;
			break;

		case GLUT_KEY_RIGHT:
			option.iter_max++;
			break;

		default:
			return;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27: //escape key
			quit();
			break;

		default:
			return;
	}
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
	glutSpecialFunc(special_keys);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
