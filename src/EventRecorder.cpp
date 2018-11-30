#include <stdexcept>
#include <fstream>
#include <VeryHipEvents/EventRecorder.h>

namespace VeryHipEvents
{

  void Recorder::initialize (unsigned int  maxEvents, unsigned int memSize, bool initiallyEnabled)
    {
	m_events = new Event* [maxEvents];
	std::fill(m_events, m_events + maxEvents, nullptr);
	m_storage = new unsigned char [memSize];
	std::fill(m_storage, m_storage+memSize, 0);
	m_nextEvent = m_storage;
	m_storageSize = memSize;
	m_maxEvents = maxEvents;
	m_enabled = initiallyEnabled;
    }
    
    Event* Recorder::allocate (size_t sz)
    {
	unsigned int preEventNumber = m_eventsNumber.fetch_add( 1 );
	unsigned char* preEventPtr = m_nextEvent.fetch_add ( sz );
	
	int alreadyUsed = preEventPtr - m_storage;
	if (alreadyUsed<0)
	    throw std::logic_error("Sth went wrong -- pointer wrap-around?");

	if ( preEventNumber >= (m_maxEvents-1) || (size_t(alreadyUsed)+sz >= m_storageSize) )
	{
	    // adding this event would be too much for what storage we allocated
	    m_eventsNumber.fetch_sub(1);
	    
	    return 0;
	}
	m_events[preEventNumber] = (Event*)preEventPtr;
	return (Event*) preEventPtr;
    }

    void Recorder::dump (const std::string& fileName, const std::string& extraContent )
    {
	std::ofstream f (fileName);
	f << "<dump>" << std::endl;
	const unsigned int N = m_eventsNumber.load();
	for (unsigned int i=0; i<N; ++i)
	{
	    f << m_events[i]->toXmlElement() << std::endl;
	}
	if (extraContent != "")
	    f << extraContent << std::endl;
	f << "</dump>";
    }

    Event**                        Recorder::m_events ( 0);
    unsigned int                   Recorder::m_maxEvents ( 0);
    std::atomic_uint               Recorder::m_eventsNumber (0);
    std::atomic<unsigned char*>    Recorder::m_nextEvent (0);
    unsigned char*                 Recorder::m_storage (0);
    size_t                         Recorder::m_storageSize (0);
    bool                           Recorder::m_enabled (0);
}
