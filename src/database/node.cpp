#include "project.hpp"
#include <cassert>
#include <algorithm>

std::string 
node::get_name()
{
	return m_name;	
}

void 
node::set_name(const std::string& n)
{
	assert(!n.empty());
	m_name = n;
}

node::node(const std::string& n, size_t x, size_t y)
	:m_name(n)
	,m_x(x)
	,m_y(y)
{

}

