#pragma once


struct float2_cus
{
	float2_cus(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}

	float x;
	float y;
};

struct float3_cus
{
	float3_cus(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : x(_x), y(_y), z(_z) {}

	float x;
	float y;
	float z;
};



class Render
{
public:
	Render();
	~Render();

	void InitGL(int argc, char* argv[]);
	/*void DisplayGL();
	void IdleGL();
	void KeyboardGL(unsigned char c, int x, int y);
	void MouseGL(int button, int state, int x, int y);
	void MotionGL(int x, int y);
	void ReshapeGL(int w, int h);

	void DrawRectangle(float width, float height);
	void DrawCircle(float radius, int numSides = 8);
	void drawParticle(float2_cus p1, float2_cus p2, float2_cus p3);*/

//	bool initGL(int *argc, char **argv, const unsigned int window_width = 512, const unsigned int window_height = 512);
//	void display();
//	void timerEvent(int value);
//	void cleanup();
//	void keyboard(unsigned char key, int, int);
//	void mouse(int button, int state, int x, int y);
//	void motion(int x, int y);
};

