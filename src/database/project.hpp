/**
* @class Project 
**/

#ifndef PROJECT_HPP
#define PROJECT_HPP

#include "module.hpp"
#include "node.hpp"
#include "edge.hpp"

#include <vector>

class Project 
{
private:
	Project(){}

public:
    typedef std::vector<Module*> ModuleCollection;
    typedef std::vector<Net*> NetCollection;

    static Project* get();

    Module* addModule(const std::string& str);
    Net* addNet(const std::string& str, const Port* inPort, const Port* outPort);
    const NetCollection& getNets();
    Module* getModule(const std::string& str); 
    bool removeModule(const std::string& str);
    const ModuleCollection& getModules();
    bool checkIfModuleExists(const std::string& str);	
    Module* getModuleByName(const std::string& str);	

    ~Project();

public:
	typedef std::vector<node*> nodes;
	typedef std::vector<edge*> edges;

public:
	void add_node(node*);
	void add_edge(edge*);
	void remove_edge(edge*);
	void remove_node(node*);
	node* find_node(const std::string&);
	nodes get_nodes();
	edges get_edges();
	
	std::string get_name();
	void set_name(const std::string&);
    void loadGraph();
private:
	ModuleCollection modules_;
	NetCollection nets_;
	static Project* project_;
	std::string m_name;
	nodes m_nodes;
	edges m_edges;

};

#endif // MODULE_HPP
