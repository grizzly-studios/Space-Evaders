#include "Event.hpp"

using namespace gs;

std::ostream & operator<<(std::ostream &logger, const Event& event)
{
    return logger << EventEnumText[event.getType()];
}
