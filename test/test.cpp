#include <LogIt.h>
#include <EventRecorder/EventRecorder.h>

using namespace EventRecorder;
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
    Log::initializeLogging ();
    Recorder::initialize (4, 1E3);
    record_event<FancyEvent> ();

    
    
    Recorder::dump ("out.xml");
}