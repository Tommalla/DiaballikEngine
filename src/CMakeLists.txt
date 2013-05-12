set (CMAKE_CXX_FLAGS "-std=c++11")

set (HEADERS
	BitContainer.h
	Board.h
	Game.h
	Point.h
)

set (SOURCES
	BitContainer.cpp
	Board.cpp
	Game.cpp
	Point.cpp
)

add_library (DiaballikEngine ${SOURCES} 
	${HEADERS} 
)