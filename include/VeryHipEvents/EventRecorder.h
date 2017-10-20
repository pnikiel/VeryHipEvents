// @author pnikiel
// @desc   see github.com/pnikiel/VeryHipEvents

#ifndef __EVENTRECORDER_H__
#define __EVENTRECORDER_H__

#include <atomic>
#include <VeryHipEvents/Event.h>

namespace EventRecorder
{


  

    
    class Recorder
    {
    public:
      static void initialize (unsigned int maxEvents, unsigned int memSize, bool initiallyEnabled=true);
	static Event* allocate(size_t sz);
	static void dump( const std::string& fileName, const std::string& extraContent="" );
	static inline bool isEnabled() { return m_enabled; }
	static void enable () { m_enabled = true; }
	static void disable () { m_enabled = false; }
	
    private:
	static std::atomic_uint            m_eventsNumber;
	static std::atomic<unsigned char*> m_nextEvent;
	static unsigned int                m_maxEvents;
	static Event**                     m_events;
	static unsigned char*              m_storage;
	static size_t                      m_storageSize;
	static bool                        m_enabled;
	
    };


    template <typename T, typename... Args>
    inline void record_event ( Args... args  )
    {
      if (! Recorder::isEnabled() )
	return;
      T* t = (T*) Recorder::allocate(sizeof (T));
      if (t)
	new (t) T ( std::forward<Args>(args)... );
    }
    

};


#endif // __EVENTRECORDER_H__
