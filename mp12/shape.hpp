/**
 * Introduction to C++ ECE 220 SP 22 MP12 bmn4
 * 
 * Last MP for 220 :( ggs.
 * 
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>    

using namespace std;

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 
  	Shape(string name) {
		name_ = name;
	}
	
  	string getName() {
		return name_;
	}
	
  	virtual double getArea() const = 0;
  	virtual double getVolume() const = 0;
	
private:
  string name_;


};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape{
public:
  	Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle") {
		width_ = width;
		length_ = length;
	}
	
  	double getArea() const {
		return (double) width_ * length_;
	}
	
  	double getVolume() const {
		return 0;
	}
	
	Rectangle<T> operator + (const Rectangle<T>& rec) {
		return Rectangle<T>(width_ + rec.getWidth(), length_ + rec.getLength());
	}
	
	Rectangle<T> operator - (const Rectangle<T>& rec) {
		return Rectangle<T>(max( (T) 0, width_ - (T) rec.getWidth()), max( (T) 0, length_ - (T) rec.getLength()));
	} 
	
	T getWidth() const { 
		return width_;
	}
	
	T getLength() const { 
		return length_;
	}
private:
	T width_;
    T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape{
public:
  	Circle(double radius):Shape("Circle") {
		radius_ = radius;
	}
	
  	double getArea() const{
		return M_PI * radius_ * radius_;
	}
	
 	double getVolume() const{
		return 0;
	}
	
  	Circle operator + (const Circle& cir){
		return Circle(radius_ + cir.getRadius());
	}
	
	Circle operator - (const Circle& cir){
		return Circle( max(0.0, radius_ - cir.getRadius()) );
	} 

	double getRadius() const { 
		return radius_;
	}
	
private:
	double radius_;

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape{
public:
  	Sphere(double radius):Shape("Sphere") {
		radius_ = radius;
	}

  	double getVolume() const {
		return (4.0/3.0) * radius_ * radius_ * radius_ * M_PI;
	}	
	
  	double getArea() const {
		return 4.0 * radius_ * radius_ * M_PI;
	}

	Sphere operator + (const Sphere& sph) {
		return Sphere(radius_ + sph.getRadius());
	}

	Sphere operator - (const Sphere& sph) {
		return Sphere(max(0.0, radius_ - sph.getRadius()));
	} 
	
	double getRadius() const {
		return radius_;
	}

private:
	double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape{
public:
  	RectPrism(double width, double length, double height):Shape("RectPrism") {
		width_ = width;
		length_ = length;
		height_ = height;
	}
	
  	double getVolume() const {
		return length_ * width_ * height_;
	}
  	
	double getArea() const {
		return 2.0 * (length_ * width_ + length_ * height_ + width_ * height_);
	}
	
	RectPrism operator + (const RectPrism& rectp){
		return RectPrism(width_ + rectp.getWidth(), length_ + rectp.getLength(), height_ + rectp.getHeight());
	}
	
	RectPrism operator - (const RectPrism& rectp){
		return RectPrism(max(0.0, width_ - rectp.getWidth()), max(0.0, length_ - rectp.getLength()), max(0.0, height_ - rectp.getHeight()));
	}	
	
	double getWidth() const { 
		return width_;
	}
	
	double getLength() const { 
		return length_;
	}
	
	double getHeight() const { 
		return height_;
	}
private:
  	double length_;
  	double width_;
  	double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
	//@@Insert your code here

	list<Shape*> shapeList = list<Shape*>(0, NULL);

	int numShapes;

	string name;
	double dims[3];

	ifstream ifs(file_name, std::ifstream::in);

	// Flush Length
	ifs >> numShapes;
	
	for (int i = 0; i < numShapes; i++) {
		ifs >> name; 

		if(name == "Rectangle") {
			ifs >> dims[0] >> dims[1];
			shapeList.push_back(new Rectangle<double>(dims[0], dims[1]));
		} else if(name == "Circle") {
			ifs >> dims[0];
			shapeList.push_back(new Circle(dims[0]));
		} else if(name == "RectPrism") {
			ifs >> dims[0] >> dims[1] >> dims [2];
			shapeList.push_back(new RectPrism(dims[0], dims[1], dims[2]));
		} else if(name == "Sphere") {
			ifs >> dims[0];
			shapeList.push_back(new Sphere(dims[0]));
		}
	}

	return shapeList;
}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here

	for(list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++) {
		if((**it).getArea() > max_area) {
			max_area = (**it).getArea();
		}
	}
	
	return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here

	for(list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++) {
		if((**it).getVolume() > max_volume) {
			max_volume = (**it).getVolume();
		}
	}
	
	return max_volume;
}
#endif

