#include <boost/test/unit_test.hpp>
#include <gazebo_model/Dummy.hpp>

using namespace gazebo_model;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    gazebo_model::DummyClass dummy;
    dummy.welcome();
}
