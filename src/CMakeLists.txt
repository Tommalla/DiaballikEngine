set (CMAKE_CXX_FLAGS "-std=c++11")

set (HEADERS
	BitContainer.h
	Game.h
)

set (SOURCES
	BitContainer.cpp
	Game.cpp
)

add_library (DiaballikEngine ${SOURCES} 
	${HEADERS} 
)