#include "module.hpp"

Module::Module(std::string n)
: name_(n)
{}

const std::string& 
Module::name() const 
{ 
    return name_;
}

    void 
Module::setName(const std::string& n) 
{
    name_ = n;
}	

    void 
Module::addPort(const Port& port) 
{
    ports_.push_back(port);
}

const Module::PortCollection& 
Module::ports() const 
{ 
    return ports_; 
}

    Instance* 
Module::addInstance(const std::string& name, const Module* master) 
{
    Instance* inst = new Instance(name, master, this);
    instances_.push_back(inst);
    return inst;
}

void 
Module::addInstance(Instance* inst)
{
	instances_.push_back(inst);
}

void
Module::removeInstance(const std::string& name)
{
	int position = 0;
	for(unsigned int i = 0; i < instances_.size(); ++i)
	{
        	if(instances_[i]->name() == name)
		{
			position = i;
			break;
		}
	}		
	instances_.erase(instances_.begin() + position);
 
}

const Module::InstanceCollection&
Module::instances() const 
{ 
    return instances_; 
}

    Instance*
Module::getInstance(const std::string name)
{
    for( unsigned int i = 0; i < instances_.size(); ++i)
        if(instances_[i]->name() == name)
            return instances_[i];
    return NULL;
}

    void 
Module::addNet(const Net& net) 
{
    //TODO: add assertion that the net connects 
    //two instances of this module
    nets_.push_back(net);
}

const Module::NetCollection&
Module::nets() const { 
    return nets_; 
}

Module::~Module()
{
    for( unsigned int i = 0; i < instances_.size(); ++i)
        delete instances_[i];
}


    bool 
Module::operator==(const Module& other)
{
    return this->name_ == other.name_;    
}
