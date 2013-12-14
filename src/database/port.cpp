#include "port.hpp"
#include "instance.hpp"

Port::Port(std::string n, Type t)
    : name_(n)
    , type_(t)	
{}

const std::string& 
Port::name() const { 
    return name_;
}

Port::Type 
Port::type() const { 
    return type_; 
}

void 
Port::setName(const std::string& n)
{
    name_ = n;
}	

void 
Port::setType(Type t)
{
    type_ = t;
}


void
Port::setInstance(Instance* inst)
{
    instance_ = inst;
}

const Instance* 
Port::instance() const
{
    return instance_;
}
