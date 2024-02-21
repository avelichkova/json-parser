add_executable(
    app
)

target_link_libraries(
    app
    PUBLIC
    json
)

target_sources(
    app
    PUBLIC
    main.cpp
)