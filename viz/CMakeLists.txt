set(linkdir
    $ENV{AUTOPROJ_CURRENT_ROOT}/install/lib
)

link_directories(
    ${linkdir}
)

rock_vizkit_plugin(gazebo_model-viz
    GazeboVisualization.cpp
    MOC GazeboVisualization.hpp
    DEPS_PKGCONFIG robot_model-viz base-viz base-types  
    HEADERS GazeboVisualization.hpp
    LIBS robot_model-viz 
)