#include <LogIt.h>
#include <VeryHipEvents/EventRecorder.h>

using namespace VeryHipEvents;
using namespace Log;

class FancyEvent: public Event
{
    virtual std::string toXmlElement() const
	{
	    return "<event "+basicAttributes()+" />";
	}
};

int main ()
{
    Recorder::initialize (4, 1E3);
    record_event<FancyEvent> ();

    
    
    Recorder::dump ("out.xml");
}
