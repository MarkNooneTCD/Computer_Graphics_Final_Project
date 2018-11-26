#define STB_IMAGE_IMPLEMENTATION
#include "Constants.hpp"
#include "Game.hpp"

using namespace std;

int main(int argc, char** argv) {
	// Set up the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(Constants::game_width, Constants::game_height);
	glutCreateWindow("Computer Graphics: The Finale");

	// Tell glut where the display function is
	glutDisplayFunc(display);
	glutIdleFunc(updateScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(keypress);

	// A call to glewInit() must be done after glut is initialized!
	GLenum res = glewInit();
	// Check for any errors
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
	}

	// Set up your objects and shaders
	init();
	// Begin infinite event loop
	glutMainLoop();
	return 0;
}
