#ifndef I_LOGIC_HPP
#define	I_LOGIC_HPP

#include <memory>

namespace gs {

class ILogic {
public:
	virtual void update(long int elapsed) = 0;
	virtual void generateLevel() = 0;
};

typedef std::shared_ptr<ILogic> ILogicPtr;

}

#endif	/* I_LOGIC_HPP */
