#include "instance.hpp"
	
Instance::Instance(std::string n, const Module* mModule, const Module* pModule)
        : name_(n)
        , masterModule_(mModule)	
        ,parentModule_(pModule)	
{}

const std::string& 
Instance::name() const 
{ 
    return name_;
}

void 
Instance::setName(const std::string& n) 
{
    name_ = n;
}	

void 
Instance::addPort(const InstancePort& port) 
{
    ports_.push_back(port);
}

const Instance::InstPortCollection& 
Instance::ports() const 
{ 
    return ports_; 
}

const Module*
Instance::masterModule() const 
{ 
    return masterModule_; 
}

const Module*
Instance::parentModule() const 
{ 
    return parentModule_; 
}

void 
Instance::setMasterModule(const Module* module) 
{ 
    masterModule_ = module; 
}

void 
Instance::setParentModule(const Module* module) 
{ 
    parentModule_ = module; 
}
