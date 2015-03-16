rock_library(gazebo_model
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(gazebo_model_bin Main.cpp
    DEPS gazebo_model)

