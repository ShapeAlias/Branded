#ifndef _INPUT_H_
#define _INPUT_H_
class Input
{
public:
	Input();
	~Input();

	void init();

	void keyUp(unsigned int);
	void keyDown(unsigned int);

	bool isKeyDown(unsigned int );
	bool isKeyUp(unsigned int key) { return !isKeyUp(key); }
private:
	bool m_keys[256];
};
#endif