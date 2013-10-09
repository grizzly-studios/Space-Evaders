#ifndef EVENT_ENUM_H
#define	EVENT_ENUM_H

#include <string>

namespace gs {

enum EventEnum {
	BISCUIT_EVENT,
	CHEESE_EVENT
};

inline std::string EventEnumToString(EventEnum eventEnum) {
	std::string str = "UNKNOWN_EVENT";

	switch (eventEnum) {
	case BISCUIT_EVENT:
		str = "BISCUIT";
		break;
	case CHEESE_EVENT:
		str = "CHEESE";
		break;
	}

	return str;
}

}

#endif	/* EVENT_ENUM_H */
