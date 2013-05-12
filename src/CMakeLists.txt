set (CMAKE_CXX_FLAGS "-std=c++11")

set (HEADERS
	BitContainer.h
	Game.h
	Point.h
)

set (SOURCES
	BitContainer.cpp
	Game.cpp
	Point.cpp
)

add_library (DiaballikEngine ${SOURCES} 
	${HEADERS} 
)