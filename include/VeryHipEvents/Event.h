// @author pnikiel
// @desc   see github.com/pnikiel/VeryHipEvents

#ifndef __EVENT_H__
#define __EVENT_H__

#include <string>
#include <time.h>


namespace EventRecorder
{

  // TODO: remove?
    const size_t EVENT_SIZE = 256;
    
    class Event
    {
    public:
	Event();
	
	virtual std::string toXmlElement() const = 0;
	std::string basicAttributes () const;
	
    private:
	timespec m_timeStamp;
	pid_t    m_threadId;
	
    };


}

#endif // __EVENT_H__
