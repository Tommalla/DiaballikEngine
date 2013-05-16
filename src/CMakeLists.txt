set (CMAKE_CXX_FLAGS "-std=c++11")

set (HEADERS
	BitContainer.h
	Board.h
	constants.h
	enums.h
	functions.h
	Game.h
	Move.h
	Point.h
)

set (SOURCES
	BitContainer.cpp
	Board.cpp
	Game.cpp
	Move.cpp
	Point.cpp
)

add_library (DiaballikEngine ${SOURCES} 
	${HEADERS} 
)