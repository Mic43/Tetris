#pragma once
#include <GL/freeglut.h>
#include "Game.h"
#include "Camera.h"

class Scene
{
	float angleY = M_PI/2;
	float angleX = -M_PI/2;
	// actual vector representing the camera's direction
	float lx = 0, lz = 1.0f,ly = 0.0f;
	// XZ position of the camera
	float x = MaxColumns/2.0f, y = MaxRows / 2.0f, z = 20.0f;

	int m_width;
	int m_height;

	Camera camera;
	Game game;
	static const int tick_interval = 500; // co ile ms uaktualniac przebieg gry - jak szybko beda leciec klocki

	void InitOpengl(int* argc, char *argv[]);

	static Scene *currentScene;
	
	static void timer_wrapper(int value) // rejestracja timera, ktory bedzie uruchamiany co zadany interwal czasu
	{
		currentScene->Timer(value);
		glutTimerFunc(tick_interval, timer_wrapper, 0);
	}
	static void processSpecialKeysWrapper(int key, int xx, int yy)
	{
		currentScene->ProcessSpecialKeys(key, xx, yy);
	}
	static void resize_wrapper(int width, int height)
	{
		currentScene->Resize(width, height);
	}
	static void idle_wrapper()
	{
		currentScene->Idle();
	}
	static void display_wrapper()
	{
		currentScene->Display();
	}
	static void keyboard_wrapper(unsigned char key, int mouse_x, int mouse_y)
	{
		currentScene->Keyboard(key, mouse_x, mouse_y);
	}
	static void mouse_passive_wrapper(int mouse_x, int mouse_y)
	{
		currentScene->MousePassive(mouse_x, mouse_y);
	}
	static void mouse_button_wrapper(int button, int state, int mouse_x, int mouse_y)
	{
		currentScene->onMouseButton(button, state, mouse_x, mouse_y);
	}

	
	void Resize(int width, int height);
	int AngleChange();

	void Idle() {
		glutPostRedisplay();
	}

	void onMouseButton(int button, int state, int mouse_x, int mouse_y)
	{

	}

	void Keyboard(unsigned char key, int mouse_x, int mouse_y);
	void DrawBlocks();	 // rysuje plansze na podstawie informacji pobranych od logiki gry
	void UpdateTargetVector();
	void ProcessSpecialKeys(int key, int xx, int yy);

	void MousePassive(int mouse_x, int mouse_y) 
	{
		
	}

	void Display();
	void DrawCubeAt(Position3D pos, Color color, float size) const;
	void drawGrid();

	void Timer(int value) // funkcja uruchamia sie co staly interwal, zeby zapewnic przebieg gry
	{
		game.Tick();
	}

public:	
	Scene(int* argc, char *argv[])
	{
		currentScene = this;
		InitOpengl(argc, argv);
		UpdateTargetVector();
	}
	void Start()
	{
		game.ReStart();
		glutMainLoop();
	}
};
