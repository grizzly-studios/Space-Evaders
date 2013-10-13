#ifndef I_VIEW_H
#define	I_VIEW_H

#include <tr1/memory>

namespace gs {

class IView {
public:
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

typedef std::tr1::shared_ptr<IView> IViewPtr;

}

#endif	/* I_VIEW_H */
