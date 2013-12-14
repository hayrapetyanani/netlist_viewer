#include "edge.hpp"
#include <cassert>
#include <algorithm>


edge::edge(node* a, node* b)
	:m_nodes(std::make_pair(a, b))
{

}


node* 
edge::firstNode()
{
    return m_nodes.first;
}

node*
edge::secondNode()
{
    return m_nodes.second;
}
