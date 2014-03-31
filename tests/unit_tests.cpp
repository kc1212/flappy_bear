#define BOOST_TEST_MODULE unit_tests

#include "utils.hpp"
#include "player.hpp"
#include "background.hpp"
#include <boost/test/unit_test.hpp>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

struct MyFixture{
	MyFixture()
	{
		// errors are reported in global fixture
		init(window, renderer);
		BOOST_TEST_MESSAGE("global setup");
	}

	~MyFixture()
	{
		BOOST_TEST_MESSAGE("global teardown");
		close(window, renderer);
	}
};

BOOST_GLOBAL_FIXTURE( MyFixture )

BOOST_AUTO_TEST_CASE( player_test )
{
	Player p1("../assets/foo.png", renderer, 240, 140);
	BOOST_CHECK(!p1.hasJumped());

	p1.jump();
	BOOST_CHECK(p1.hasJumped());
	BOOST_CHECK_EQUAL(p1.getV(), V_0);
}


