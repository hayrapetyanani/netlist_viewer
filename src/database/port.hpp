/**
* @class Port - provides abstract interface for Instance Ports
* and Module Ports
**/
#ifndef PORT_HPP
#define PORT_HPP

#include <string>

class Port
{
public:
	enum Type
	{	
		in, 
		out
	};	

	Port(std::string n, Type t);
	const std::string& name() const; 
	Type type() const; 
	void setName(const std::string& n);
	void setType(Type t);

private:

	std::string name_;
	Type type_;
};

#endif //PORT_HPP
