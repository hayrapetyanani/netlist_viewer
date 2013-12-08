/**
* @class Project 
**/

#ifndef PROJECT_HPP
#define PROJECT_HPP

#include "module.hpp"
#include <vector>

class Project 
{
private:
	Project(){}

public:
    typedef std::vector<Module*> ModuleCollection;

    static Project* get();

    Module* addModule(const std::string& str);
    void removeModule(const std::string& str);
    const ModuleCollection& getModules();

    ~Project();
private:
    typedef ModuleCollection::iterator ModuleIterator;
    typedef ModuleCollection::const_iterator ConstModuleIterator;

	ModuleCollection modules_;
	static Project* project_;
};

#endif // MODULE_HPP
