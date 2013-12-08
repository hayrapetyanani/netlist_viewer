#include "net.hpp"

Net::Net(std::string n, const Port* s, const Port* d)
    : name_(n)
    , source_(s)	
{
    destinations_.push_back(d);
}

const std::string& 
Net::name() const 
{ 
    return name_;
}

void 
Net::setName(const std::string& n)
{
    name_ = n;
}	

void 
Net::addDestination(const Port* dest)
{
    destinations_.push_back(dest);
}

const Port* 
Net::source() const 
{ 
    return source_; 
}

const Net::Ports& 
Net::destinations() const { 
    return destinations_; 
}


