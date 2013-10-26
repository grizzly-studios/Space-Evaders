#ifndef I_LOGIC_HPP
#define	I_LOGIC_HPP

#include <tr1/memory>

namespace gs {

class ILogic {
public:
	virtual void update() = 0;
	virtual void generateLevel() = 0;
};

typedef std::tr1::shared_ptr<ILogic> ILogicPtr;

}

#endif	/* I_LOGIC_HPP */
