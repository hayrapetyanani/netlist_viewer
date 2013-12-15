#include "project.hpp"

#include <algorithm>
#include <assert.h>
#include <iostream>

Project* Project::project_ = NULL;

Project*
Project::get()
{
    if (project_ == NULL)
        project_ = new Project();
    return project_;
}

Module* 
Project::addModule(const std::string& str) {
    modules_.push_back(new Module(str));
    return modules_.back();
}

Module* 
Project::getModule(const std::string& str) 
{
    for (unsigned int i = 0; i < modules_.size(); ++i)
        if (modules_[i]->name() == str)
            return modules_[i];

    return NULL;
}
Net*
Project::addNet(const std::string& str, const Port* inPort, const Port* outPort)
{
    Net* net = new Net(str, inPort, outPort);
    nets_.push_back(net);
    return net;
}

const Project::NetCollection& 
Project::getNets()
{
    return nets_;
}
Project::~Project()
{
    for (unsigned int i = 0; i < modules_.size(); ++i)
        delete modules_[i];
}

bool
Project::removeModule(const std::string& str) 
{
    for (unsigned int i = 0; i < modules_.size(); ++i)
        if (modules_[i]->name() == str)
        {
            delete modules_[i];
            modules_.erase(modules_.begin() + i);
            return true;
        }
    return false;
}

bool
Project::checkIfModuleExists(const std::string& str) 
{
    for (unsigned int i = 0; i < modules_.size(); ++i) 
    {
	if (modules_[i]->name() == str)
	{
		return true;
	}
    }

    return false;	
}

Module* 
Project::getModuleByName(const std::string& str)
{
    for (unsigned int i = 0; i < modules_.size(); ++i) 
    {
	if (modules_[i]->name() == str)
	{
		return modules_[i];
	}
    }

    return NULL;
}

const Project::ModuleCollection& 
Project::getModules()
{
    return modules_;
}

void 
Project::add_node(node* m)
{
	assert(0 != m);
	//assert(m.node.end() == 
	//		std::find(m_node.begin(), m_node.end(), m));
	m_nodes.push_back(m);
}

void 
Project::remove_node(node* m)
{
	assert(0 != m);
	//assert(m.node.end() == 
	//		std::find(m_node.begin(), m_node.end(), m));
	std::remove(m_nodes.begin(), m_nodes.end(),m);
}

void 
Project::add_edge(edge* e)
{
	assert(0 != e);
	m_edges.push_back(e);
}

void 
Project::remove_edge(edge* e)
{
	assert(0 != e);
	std::remove(m_edges.begin(), m_edges.end(), e);
}

node* 
Project::find_node(const std::string& n)
{
	for (size_t i = 0; i != m_nodes.size(); ++i) {
		if (m_nodes[i]->get_name() == n) {
			return m_nodes[i];
		}
	}
	return 0;
}

Project::nodes 
Project::get_nodes()
{
	return m_nodes;
}
	
Project::edges 
Project::get_edges()
{
	return m_edges;
}

std::string 
Project::get_name()
{
	return m_name;	
}

void 
Project::set_name(const std::string& n)
{
	assert(!n.empty());
	m_name = n;
}

void 
Project::loadGraph()
{
    int coord = 10;
    for (unsigned int i = 0; i < modules_.size(); ++i)
    {
        Module* currentModule = modules_[i];
        const Module::InstanceCollection& insts = currentModule->instances();
        for( unsigned int j = 0; j < insts.size(); ++j)
        {
            Instance* inst = insts[j];
            node* inst_node = new node(inst->name(), coord, coord);
            add_node(inst_node);
            coord += 30;                                 
        }
    }

    for (unsigned int i = 0; i < nets_.size(); ++i)
    {
        Net* net = nets_[i];
        const Instance* source = net->source()->instance();  
        node* sourceNode = find_node(source->name());
        assert(sourceNode != NULL);
        const Net::Ports dests = net->destinations();
        for (unsigned int j = 0; j < dests.size(); ++j)
        {
            const Instance* inst = dests[j]->instance();
            assert(inst != NULL);
            node* dest = find_node(inst->name());
            edge* newEdge = new edge(sourceNode, dest);
            add_edge(newEdge);
        }

    }
}
