/**
* @class Net  - defines net or connection between two modules
* Net can have only one source, but many destinations
**/

#ifndef NET_HPP
#define NET_HPP

#include <string>
#include <vector>
#include "port.hpp"

class Net
{
public:
	typedef std::vector<const Port*> Ports;

	Net(std::string n, const Port* s, const Port* d);
	const std::string& name() const; 
	void setName(const std::string& n);
	void addDestination(const Port* dest);
	const Port* source() const; 
	const Ports& destinations() const; 

private:
	std::string name_;
	const Port* source_;
	Ports destinations_;
};

#endif // NET_HPP
