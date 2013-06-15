set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set (HEADERS
	BitContainerInputStream.h
	BitContainerOutputStream.h
	BitContainer.h
	Board.h
	constants.h
	enums.h
	functions.h
	Game.h
	Move.h
	Point.h
	Singleton.h
)

set (SOURCES
	BitContainerInputStream.cpp
	BitContainerOutputStream.cpp
	BitContainer.cpp
	Board.cpp
	Game.cpp
	Move.cpp
	Point.cpp
)

add_library (DiaballikEngine ${SOURCES} 
	${HEADERS} 
)
