/**
* @class Instance Port - inherits from module Port and keeps pointer to master module Port
**/
#ifndef INSTANCE_PORT_HPP
#define INSTANCE_PORT_HPP

#include "port.hpp" 

class InstancePort : public Port
{
public:
	InstancePort(std::string n, Type t, const Port* mPort = NULL);
	const Port* masterPort() const ; 
	void setMasterPort(const Port* mPort);
	
private:
	/// pointer to the master module port.
	const Port* masterPort_;	
};

#endif // INSTANCE_PORT_HPP
