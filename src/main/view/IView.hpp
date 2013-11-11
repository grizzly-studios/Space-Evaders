#ifndef I_VIEW_HPP
#define	I_VIEW_HPP

#include <memory>

namespace gs {

class IView {
public:
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

typedef std::shared_ptr<IView> IViewPtr;

}

#endif	/* I_VIEW_HPP */
