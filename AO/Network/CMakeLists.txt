add_executable(NetDemo
    NetDemo.cpp
)

target_link_libraries(NetDemo
    ${BOOST_LIBS}
)

target_include_directories(NetDemo
    PUBLIC ${BOOST_INCLUDEDIR}
)