#ifndef SHAPE_H_
#define SHAPE_H_

class Shape
{
public:
	virtual void draw() = 0;
	virtual void area() = 0;
	virtual void perimeter() = 0;
	virtual ~Shape() {};
protected:
	double area_, perimeter_;
private:
	
}

#endif
