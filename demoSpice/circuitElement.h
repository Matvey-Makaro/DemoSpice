#pragma once
class CircuitElement
{
public:
CircuitElement(double val):
	value{val} { }
double getValue() { return value; }
virtual char type() const { return 'N'; }
protected:
	double value;
	

private:
};