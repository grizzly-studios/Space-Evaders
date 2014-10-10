/* 
 * File:   MenuPointerChange.h
 * Author: Rob Parker
 *
 * Created on November 19, 2013, 19:08 PM
 */

#ifndef MENU_POINTER_CHANGE_H
#define	MENU_POINTER_CHANGE_H

#include "Event.hpp"


namespace gs {

class MenuPointerChange : public Event {
public:
	MenuPointerChange(int _pos) : pos(_pos) {};

	virtual EventEnum getType() const {
		return MENU_POINTER_CHANGE;
	}

	int getPos() const {
		return pos;
	}

private:
	int pos;
};

}

#endif	/* MENU_POINTER_CHANGE_H */

