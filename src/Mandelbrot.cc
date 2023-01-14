// A simple OpenGL program that draws a fractal.
//In this programm currently Mandelbrot set is drawn upon execution

#include "GL/freeglut.h"
#include "GL/gl.h"
#include <iostream>
#include <string>
#include "../lib/Palette.h"

struct
{
	double iter_max = 10.;
	double zoom = 1.;
}option;

//default size
struct
{
	unsigned int size_x = 1920;
	unsigned int size_y = 1080;
}window;

struct
{
	double x_pos = 0.;
	double y_pos = 0.;
}mouse;

struct RGB
{
	double red;
	double green;
	double blue;
};

void quit()
{
	exit(0);
}

void DrawText(double x, double y, RGB color, void *font, const unsigned char *text)
{
	glColor3f(color.red, color.green, color.blue); 
	glRasterPos2f(x, y);
	glutBitmapString(font, text);
}

void DrawInfo()
{
	RGB color;
	color.red = 1;
	color.green = 0.8;
	color.blue = 0.3;

	std::string info = "Zoom: ";
	info.append(std::to_string(option.zoom));
	info.append("    Iter max: ");
	info.append(std::to_string((int) option.iter_max));
	const unsigned char* text = reinterpret_cast<const unsigned char *>( info.c_str() );

	DrawText(0.2, -0.9, color, GLUT_BITMAP_TIMES_ROMAN_24, text);
	DrawText(0.2, -0.95, color, GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>( "press esc to exit" ));
}

void drawFrac()
{
	
	//in case window size changes
	window.size_x = glutGet(GLUT_WINDOW_WIDTH);
	window.size_y = glutGet(GLUT_WINDOW_HEIGHT);

	RGB color;

	glClear(GL_COLOR_BUFFER_BIT);

	double shift_x = (mouse.x_pos)*(1.-1/option.zoom)-2./option.zoom;
	double shift_y = (mouse.y_pos)*(1.-1/option.zoom)-2./option.zoom;

	//Neon palette;
	//OceanPalette palette;
	CrimsonPalette palette;

	for (int x = 0; x <= window.size_x; x++)
	{
		for (int y = 0; y <= window.size_y; y++) 
		{
			//point position
			double x_pos = ((double) x/window.size_x-0.5)*2.;
			double y_pos = ((double) y/window.size_y-0.5)*2.;

			//c real and imaginary parts
			double re_c = ((double) x/option.zoom/window.size_x)*4.0 + shift_x;
			double im_c = ((double) y/option.zoom/window.size_y)*4.0 + shift_y;

			//z real and imaginary parts
			double re_z = 0.0;
			double im_z = 0.0;

			double iter = 0;
			
			while (iter <= option.iter_max && re_z*re_z +im_z*im_z <= 4.0)
			{
				//calculating f(z) = z^2 + c iteratevly
				double re_z_temp = re_z*re_z - im_z*im_z + re_c;
				im_z = 2.*re_z*im_z + im_c;
				re_z = re_z_temp;

				iter++;
			}

			if (iter < option.iter_max)
			{
				double col_val = (double) iter/option.iter_max;

				color.red = palette.R(col_val);
				color.green = palette.G(col_val);
				color.blue = palette.B(col_val);

				glColor3f(color.red, color.green, color.blue);
			}

			else glColor3f(0, 0, 0);

			glBegin(GL_POINTS);
			glVertex2f(x_pos, y_pos);
			glEnd();
		}
	}

	DrawInfo();
	glFlush();
}

void mousePosition(int x, int y)
{
	mouse.x_pos = ((double) x/glutGet(GLUT_WINDOW_WIDTH)-0.5)*2.;
	mouse.y_pos = (1. - (double) y/glutGet(GLUT_WINDOW_HEIGHT)-0.5)*2.;
}

void mouseClick(int key, int state, int x, int y) {

	if (state == GLUT_DOWN)
	{
		mousePosition(x,y);
		switch(key)
		{
		case 0:
			std::cout << mouse.x_pos << " " << mouse.y_pos << std::endl;
			return;
		case 3:
			option.zoom *= 1.05;
			break;

		case 4:
			option.zoom /= 1.05;
			break;

		default:
			return;
		}
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
