
add_executable(TickTock
    dev/TickTock.cpp
)

target_link_libraries(TickTock
    ${BOOST_LIBS}
)

target_include_directories(TickTock
    PUBLIC ${BOOST_INCLUDEDIR}
)

# # # # # # # # # # # # # # # # # # # # # # # #

add_executable(NetDemo
    network/NetDemo.cpp
)

target_link_libraries(NetDemo
    ${BOOST_LIBS}
)

target_include_directories(NetDemo
    PUBLIC ${BOOST_INCLUDEDIR}
)

add_executable(tcpServer
    network/tcpServer.cpp
)

target_link_libraries(tcpServer
    ${BOOST_LIBS}
)

target_include_directories(tcpServer
    PUBLIC ${BOOST_INCLUDEDIR}
)

add_executable(Timers
    network/Timers.cpp
)

target_link_libraries(Timers
    ${BOOST_LIBS}
)

target_include_directories(Timers
    PUBLIC ${BOOST_INCLUDEDIR}
)
