#include "instance_port.hpp"

InstancePort::InstancePort(std::string n, Type t, const Port* mPort)
    : Port(n, t)
    , masterPort_(mPort)
{}

const Port* 
InstancePort::masterPort() const 
{ 
    return masterPort_; 
}

void
InstancePort::setMasterPort(const Port* mPort) 
{
    masterPort_ = mPort;
}	

