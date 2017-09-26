add_executable(NetDemo
    NetDemo.cpp
)

target_link_libraries(NetDemo
    ${BOOST_LIBS}
)

target_include_directories(NetDemo
    PUBLIC ${BOOST_INCLUDEDIR}
)

add_executable(tcpClient
    tcpClient.cpp
)

target_link_libraries(tcpClient
    ${BOOST_LIBS}
)

target_include_directories(tcpClient
    PUBLIC ${BOOST_INCLUDEDIR}
)