#include <stdexcept>
#include <sstream>
#include <VeryHipEvents/Event.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <iomanip>

pid_t gettid()
{
    return syscall( SYS_gettid );
}

namespace EventRecorder
{

    Event::Event () :
	m_threadId( gettid() )
    {
	if ( clock_gettime( CLOCK_REALTIME, &m_timeStamp ) < 0)
	    throw std::runtime_error("clock_gettime() failed");
	
    }

    std::string Event::basicAttributes() const
    {
	std::stringstream ss;
	ss << "ts='" << m_timeStamp.tv_sec << "." << std::setw(9) << std::setfill('0') << m_timeStamp.tv_nsec << "' thread='" << m_threadId << "'";
	return ss.str();
    }

}
