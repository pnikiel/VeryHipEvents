# @author   pnikiel
# @date     Feb 2017

# Note:
# This CMakeLists should be included from your parent CMakeLists.txt
# If you build this standalone, then you will just build tests.

add_library( VeryHipEvents OBJECT 
  src/EventRecorder.cpp
  src/Event.cpp
  )

add_executable( very_hip_events_test test/test.cpp
  $<TARGET_OBJECTS:VeryHipEvents>
)
target_link_libraries( very_hip_events_test -lrt)

