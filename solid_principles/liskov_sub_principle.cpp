#include <iostream>
#include <vector>

using namespace std;

class Rectangle
{
protected:
	int width;
	int height;

public:
	Rectangle(int w, int h) :width(w), height(h) {}
	virtual int getWidth() { return width; }
	virtual void setWidth(int value) /*final*/ { width = value; }
	virtual int getHeight() { return height; }
	virtual void setHeight(int value) /*final*/ { height = value; }
	virtual int area() { return width * height; }
};
class Square : public Rectangle
{
public:
	Square(int sz) : Rectangle(sz, sz) {
	}
	void setHeight(int value) { width = height = value; }
	void setWidth(int value) { width = height = value; }
};

class SquareEx : public Rectangle
{
public:
	SquareEx(int sz) : Rectangle(sz,sz) {
	}
	void setSize(int value) { width = height = value;}
};

void testProcess(Rectangle& rect) 
{
	int wd = rect.getWidth();
	rect.setHeight(10);
	cout << endl << "expect area : " << wd * 10 << " output area : " << rect.area() << endl;
	
}
void testProcessEx(Rectangle& rect)
{
	int wd = rect.getWidth();
	rect.setHeight(10);
	cout << endl << "expect area : " << wd * 10 << " output area : " << rect.area() << endl;

}
//to avoid such case use rectangle factory
class RectangleFactory
{
public:
	static Rectangle CreateReactangle(int width, int height) { return Rectangle(width, height); }
	static Rectangle CreateSquare(int sz) { return SquareEx(sz); }
};
int main()
{
    // Should avoid funciton such as setHeight in square class , added SquareEx to fix this kind of issue but still square can not 
    // substitute rectangle smoothly
	Rectangle rect(5,5);
	testProcess(rect);
	Square square(5);
	testProcess(square);	

	Rectangle rectEx = RectangleFactory::CreateReactangle(5, 5);
	testProcessEx(rectEx);
	Rectangle sqrEx = RectangleFactory::CreateSquare(5);
	testProcessEx(sqrEx);
	return 0;
}