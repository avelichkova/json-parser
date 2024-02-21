add_library(json)

target_include_directories(
    json
    PUBLIC
    include/
)

target_sources(
    json
    PUBLIC
    JSONArray.cpp 
    JSONElement.cpp 
    JSONObject.cpp 
    JSONString.cpp 
    JSONTree.cpp 
    Tokenizer.cpp
    Runner.cpp
    Commands.cpp
    JSONPath.cpp
)
