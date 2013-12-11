#ifndef EDGE
#define EDGE

#include<string>
#include<vector>
#include<utility>


class node;
class edge
{
private:
	std::pair<node*, node*> m_nodes;

public:
	//set-get methods

public:
	edge(node*, node*);

};

#endif
