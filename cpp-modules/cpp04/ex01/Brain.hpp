#ifndef BRAIN_HPP
#define BRAIN_HPP

# include <iostream>
# include <string>

class Brain
{
	public:
		std::string	ideas[100];

		Brain();
		Brain(Brain const &Object);
		Brain &operator=(Brain const &rhs);
		~Brain();

		void setIdea(int idx, const std::string &idea);
    const std::string &getIdea(int idx) const;
};

#endif