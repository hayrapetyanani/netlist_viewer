#ifndef NODE
#define NODE

#include<string>
#include<vector>


class node
{
private:
	std::string m_name;
	size_t m_x;
	size_t m_y;

public:
	//set-get methods
	std::string get_name();
	void set_name(const std::string&);
	size_t get_x() {
		return m_x;
	}

	size_t get_y() {
		return m_y;
	}
public:
	node(const std::string& name, size_t, size_t);

};

#endif
