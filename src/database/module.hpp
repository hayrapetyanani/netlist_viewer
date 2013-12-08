/**
* @class Module represents a module with the collection of its instances, 
* collection of nets between that instances and collection of ports.
**/

#ifndef MODULE_HPP
#define MODULE_HPP

#include <string>
#include <vector>
#include "port.hpp"
#include "instance.hpp"
#include "net.hpp"

class Module
{
public:
	typedef std::vector<Port> PortCollection;
	typedef std::vector<Instance*> InstanceCollection;
	typedef std::vector<Net> NetCollection;
	Module(std::string n);
	const std::string& name() const;	
	void setName(const std::string& n);	
	void addPort(const Port& port);
    const PortCollection& ports() const;
	Instance* addInstance(const std::string& name, const Module* master);
	const InstanceCollection& instances() const;
    Instance* getInstance(const std::string name);
	void addNet(const Net& net);
	const NetCollection& nets() const;
    ~Module();
    bool operator==(const Module& other);


	std::string name_;
	InstanceCollection instances_;
	NetCollection nets_;
	PortCollection ports_;
};

#endif // INSTANCE_HPP
