#include "project.hpp"

#include <algorithm>
#include <assert.h>


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

Project::~Project()
{
    for (unsigned int i = 0; i < modules_.size(); ++i)
        delete modules_[i];
}

void 
Project::removeModule(const std::string& str) 
{
    //ModuleIterator it = std::find(modules_.begin(), modules_.end(), Module(str) );
    //assert(it != modules_.end()); 
    //modules_.erase(it);
}


const Project::ModuleCollection& 
Project::getModules()
{
    return modules_;
}
