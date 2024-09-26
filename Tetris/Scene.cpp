#include "stdafx.h"
#include "Scene.h"
#include <GL/freeglut.h>
#include <string>

Scene* Scene::currentScene = 0;


void Scene::InitOpengl(int* argc, char *argv[])
{
	glutInit(argc, argv);
	glutInitWindowSize(900, 700);
	glutInitWindowPosition(40, 40);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow("Scena");

	glClearColor(0, 0, 0, 0);         //Zmiana koloru tła 

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glutTimerFunc(tick_interval,timer_wrapper,0);
	glutReshapeFunc(resize_wrapper);
	glutDisplayFunc(display_wrapper);
	glutIdleFunc(idle_wrapper);
	glutKeyboardFunc(keyboard_wrapper);
	glutPassiveMotionFunc(mouse_passive_wrapper);
	glutMouseFunc(mouse_button_wrapper);
	glutSpecialFunc(processSpecialKeysWrapper);

	camera.Reset();

}

void Scene::Resize(int width, int height)
{
	const float ar = (float)width / (float)height;
	
	m_width = width;
	m_height = height;
	
	glViewport(0, 0, width, height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Scene::Keyboard(unsigned char key, int mouse_x, int mouse_y)
{		
	
	switch (key)
	{
		case 'a':
		case 'A':
			game.TryMoveBlockLeft();
			break;
		case 'd':
		case 'D':
			game.TryMoveBlockRight();
			break;
		case 'w':
		case 'W':
			game.TryMoveBlockBack();
			break;
		case 's':
		case 'S':
			game.TryMoveBlockFront();
			break;
		case 'r':
		case 'R':
			game.TryRotateBlockRight();
			break;
		case '8':
			y += 1;			
			break;
		case '2':			
			y -= 1;
			break;	
		case 27: // ESC
			game.ReStart();
			break;
	}
}

void Scene::DrawBlocks()
{
	GameVisualState visualState = game.GetVisualState();
	// rysuje  szescian o odpowiednim kolorze na podstawie informacji przekazywanej przez funkcje GetVisualState
			
	float size = 1;
	for (int i = 0; i < MaxColumns; ++i)
	{
		for (int j = 0; j < MaxRows; ++j)
		{
			for (int k = 0; k < MaxDepth; ++k)
			{
						
				if (!visualState.values[i][j][k].IsBlack())
				{
					DrawCubeAt(Position3D(size*i, size*(MaxRows - j), size*k), visualState.values[i][j][k],size);					
				}
			}				
		}			
	}
}
// to bylo potrzebne w poprzedniej wersji, gdy kamera dzialala inaczej
void Scene::UpdateTargetVector()
{
	double sin1 = sin(angleX);
	double sin2 = sin(angleY);
	//
	double cos1 = cos(angleX);
	double cos2 = cos(angleY);
	
	//
	ly = cos1;
	lx = sin1 * cos2;
	lz = sin1 * sin2;
}
// oblsuga kamery
void Scene::ProcessSpecialKeys(int key, int xx, int yy) {
		
	float fraction = 1.0f;	

	std::string title("Camera poosition: ");
	title += std::to_string(angleX) + " " + std::to_string(angleY);
	glutSetWindowTitle(title.c_str());


		switch (key)
		{
		case GLUT_KEY_LEFT:
			camera.RotateYBy(-0.1f);
			break;
		case GLUT_KEY_RIGHT:
			camera.RotateYBy(0.1f);
			break;
		case GLUT_KEY_PAGE_UP:
			camera.RotateXBy(0.1f);
			break;
		case GLUT_KEY_PAGE_DOWN:
			camera.RotateXBy(-0.1f);
			break;
		case GLUT_KEY_UP:
			camera.IncreaseDistanceBy(-1);
			break;
		case GLUT_KEY_DOWN:
			camera.IncreaseDistanceBy(1);
			break;
		}

		UpdateTargetVector();
}

void Scene::Display()
{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		camera.Update();
			
		drawGrid();
		DrawBlocks();

		glutSwapBuffers();
}

void Scene::DrawCubeAt(Position3D pos,Color color,float size) const
{
		size /= 2;
		glPushMatrix();		
		glTranslatef(pos.column +size, pos.row - size , pos.depth + size);		
	
		glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
		// Top face (y = 1.0f)
		// Define vertices in counter-clockwise (CCW) order with normal pointing out

		glColor3f(color.r, color.g, color.b);     // Green
		glVertex3f(size, size, -size);
		glVertex3f(-size, size, -size);
		glVertex3f(-size, size, size);
		glVertex3f(size, size, size);

		// Bottom face (y = -size)
		glColor3f(color.r, color.g, color.b);     // Green

		glVertex3f(size, -size, size);
		glVertex3f(-size, -size, size);
		glVertex3f(-size, -size, -size);
		glVertex3f(size, -size, -size);

		// Front face  (z = size)
		glColor3f(color.r, color.g, color.b);     // Green

		glVertex3f(size, size, size);
		glVertex3f(-size, size, size);
		glVertex3f(-size, -size, size);
		glVertex3f(size, -size, size);

		// Back face (z = -size)
		glColor3f(color.r, color.g, color.b);     // Green

		glVertex3f(size, -size, -size);
		glVertex3f(-size, -size, -size);
		glVertex3f(-size, size, -size);
		glVertex3f(size, size, -size);

		// Left face (x = -size)
		glColor3f(color.r, color.g, color.b);     // Green

		glVertex3f(-size, size, size);
		glVertex3f(-size, size, -size);
		glVertex3f(-size, -size, -size);
		glVertex3f(-size, -size, size);

		// Right face (x = 1.0f)
		glColor3f(color.r, color.g, color.b);     // Green

		glVertex3f(size, size, -size);
		glVertex3f(size, size, size);
		glVertex3f(size, -size, size);
		glVertex3f(size, -size, -size);
		glEnd();  // End of drawing color-cube
		glPopMatrix();
		
}

void Scene::drawGrid() {


	for (int i = 0; i < 18; i++) {  //// Siatka podłoga 

		glPushMatrix();
		if (i < 9) { glTranslatef(0, 0, i); }
		if (i >= 9) { glTranslatef(i - 9, 0, 0); glRotatef(-90, 0, 1, 0); }
		glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glLineWidth(1);
		glVertex3f(0, 0, 0);
		glVertex3f(8, 0, 0);
		glEnd();
		glPopMatrix();
	}
	for (int i = 0; i < 18; i++) {  //// Siatka Lewej ściany

		glPushMatrix();
		if (i < 9) { glTranslatef(0, 0, i); }
		if (i >= 9) { glTranslatef(0, i - 9, 0); glRotatef(90, 1, 0, 0); }
		glBegin(GL_LINES);
		glColor3f(0.3, 0.3, 0.3);
		glLineWidth(1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 8, 0);
		glEnd();
		glPopMatrix();
	}
	for (int i = 0; i < 18; i++) {  //// Siatka Tylnej ściany

		glPushMatrix();
		if (i < 9) { glTranslatef(i, 0, 0); }
		if (i >= 9) { glTranslatef(0, i - 9, 0); glRotatef(-90, 0, 0, 1); }
		glBegin(GL_LINES);
		glColor3f(0.3, 0.3, 0.3);
		glLineWidth(1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 8, 0);
		glEnd();
		glPopMatrix();
	}
	for (int i = 0; i < 18; i++) {  //// Siatka Prawej ściany

		glPushMatrix();
		if (i < 9) { glTranslatef(0, 0, i); }
		if (i >= 9) { glTranslatef(0, i - 9, 0); glRotatef(90, 1, 0, 0); }
		glBegin(GL_LINES);
		glColor3f(0.3, 0.3, 0.3);
		glLineWidth(1);
		glVertex3f(8, 0, 0);
		glVertex3f(8, 8, 0);
		glEnd();
		glPopMatrix();
	}
	for (int i = 0; i < 18; i++) {  //// Siatka Przedniej ściany

		glPushMatrix();
		if (i < 9) { glTranslatef(i, 0, 0); }
		if (i >= 9) { glTranslatef(0, i - 9, 0); glRotatef(-90, 0, 0, 1); }
		glBegin(GL_LINES);
		glColor3f(0.3, 0.3, 0.3);
		glLineWidth(1);
		glVertex3f(0, 0, 8);
		glVertex3f(0, 8, 8);
		glEnd();
		glPopMatrix();
	}


}
