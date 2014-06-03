#define BOOST_TEST_MODULE unit_tests

#include "utils.hpp"
#include "player.hpp"
#include "background.hpp"
#include "score_manager.hpp"
#include "timer.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

static bool customCompare (scorePair a, scorePair b)
{
	return a.s < b.s;
}

struct MyFixture{
	MyFixture()
	{
		// errors are reported in global fixture
		init(window, renderer);

		// TODO use a different score file for testing
		// delete score file
		if (remove( "../score.txt" ) != 0)
			perror( "error deleting file" );

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
	ScoreManager sm1(renderer);
	// setting high score in reverse order
	sm1.setHighScoreIfValid(0);
	sm1.setHighScoreIfValid(0); // high score shouldn't be saved
	BOOST_CHECK( sm1.getHighScores().size() == 0);

	sm1.setHighScoreIfValid(3);
	sm1.setHighScoreIfValid(2);
	sm1.setHighScoreIfValid(1);
	BOOST_CHECK( sm1.getHighScores().size() == 3);
	BOOST_CHECK_EQUAL( sm1.getHighScore(), 3 );

	for (int i = 0; i < 10; i++)
	{
		BOOST_CHECK( sm1.setHighScoreIfValid(i) );
	}

	// check whether the small scores are replaced correctly
	vector<scorePair> scores = sm1.getHighScores();
	sort(scores.begin(), scores.end(), customCompare);
	BOOST_CHECK_EQUAL(scores[0].s,2);
	BOOST_CHECK_EQUAL(scores[1].s,2);
	BOOST_CHECK_EQUAL(scores[2].s,3);
	BOOST_CHECK_EQUAL(scores[3].s,3);

	BOOST_CHECK_EQUAL( sm1.getHighScore(), 9 );
	BOOST_CHECK( sm1.setHighScoreIfValid(10) );
	BOOST_CHECK_EQUAL( sm1.getHighScore(), 10 );

	BOOST_CHECK( sm1.getHighScores().size() == 10);

	ScoreManager sm2(renderer); // this will read existing file
	BOOST_CHECK_EQUAL( sm2.getHighScore(), 10 );
	BOOST_CHECK( sm2.setHighScoreIfValid(20) );
	BOOST_CHECK_EQUAL( sm2.getHighScore(), 20 );
	BOOST_CHECK( sm2.setHighScoreIfValid(15) );
	BOOST_CHECK_EQUAL( sm2.getHighScore(), 20 );

	BOOST_CHECK( sm2.getHighScores().size() == 10);

}


BOOST_AUTO_TEST_CASE( timer_test )
{
	Timer timer;
	Uint32 tmpTime;

	timer.start();
	sleep(1);
	tmpTime = timer.getTicks();
	BOOST_CHECK( tmpTime > 995 && tmpTime < 1005 );

	timer.stop();

	timer.start();
	sleep(2);
	tmpTime = timer.getTicks();
	BOOST_CHECK( tmpTime > 1995 && tmpTime < 2005 );
}



