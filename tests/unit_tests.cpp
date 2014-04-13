#define BOOST_TEST_MODULE unit_tests

#include "utils.hpp"
#include "player.hpp"
#include "background.hpp"
#include "score_manager.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

struct MyFixture{
	MyFixture()
	{
		// errors are reported in global fixture
		init(window, renderer);
		BOOST_TEST_MESSAGE( "global setup" );
	}

	~MyFixture()
	{
		BOOST_TEST_MESSAGE( "global teardown" );
		close( window, renderer );
	}
};

BOOST_GLOBAL_FIXTURE( MyFixture )

BOOST_AUTO_TEST_CASE( player_test )
{
	Player p1( "../assets/black-bubble.png", renderer, 240, 140 );
	BOOST_CHECK( !p1.hasJumped() );

	p1.jump();
	BOOST_CHECK( p1.hasJumped() );
	BOOST_CHECK_EQUAL( p1.getV(), V_0 );
}

BOOST_AUTO_TEST_CASE( file_io_test )
{
	ScoreManager sm;
	BOOST_CHECK( sm.setHighScoreIfValid(10) ); // set high score to 10
	BOOST_CHECK_EQUAL( sm.getHighScore(), 10 );

	ScoreManager sm2;
	BOOST_CHECK_EQUAL( sm2.getHighScore(), 10 );
	BOOST_CHECK( sm2.setHighScoreIfValid(20) );
	BOOST_CHECK_EQUAL( sm2.getHighScore(), 20 );
	BOOST_CHECK( sm2.setHighScoreIfValid(15) );
	BOOST_CHECK_EQUAL( sm2.getHighScore(), 20 );
}
