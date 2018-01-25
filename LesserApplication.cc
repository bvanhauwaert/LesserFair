#include "LesserApplication.h"
#include "Player.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WEnvironment.h>
#include <Wt/WText.h>

#include <chrono>
#include <random>

LesserApplication::LesserApplication(const Wt::WEnvironment& env)
	: Wt::WApplication(env), me(0), ui(styleSheet(), root())
{
	setTitle("The Lesser Fair Game");
	setupPlayer();
}

LesserApplication::~LesserApplication()
{
}

static bool isValidCookie(const std::string& cookie)
{
	if (cookie.length() != 16)
		return false;
	for (const auto c : cookie)
		if (c < 'A' || c > 'Z')
			return false;
	return true;
}

static std::string newCookie()
{
	std::chrono::time_point<std::chrono::system_clock> now;
	now = std::chrono::system_clock::now();
	auto seed = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
	std::default_random_engine randomSource;
	randomSource.seed(static_cast<unsigned int>(seed));
	std::uniform_int_distribution<int> randomLetter('A', 'Z');
	std::string secret;
	for (auto i = 0; i<16; ++i)
		secret += static_cast<char>(randomLetter(randomSource));
	return secret;
}

void LesserApplication::setupPlayer()
{
	const std::string* cookie = environment().getCookie("LesserFair.secret");
	if (!cookie)
		createNewPlayer();
	else
	{
		me = Player::getExisting(*cookie);
		if (me)
			startPlay(*cookie);
		else
		{
			std::string secret = *cookie;
			if (!isValidCookie(secret))
				secret = newCookie();
			ui.announcePlayerNotFound(*cookie);
			createNewPlayer(secret);
		}
	}
}

void LesserApplication::createNewPlayer()
{
	std::string secret = newCookie();
	ui.announceNewPlayer(secret);
	createNewPlayer(secret);
}

void LesserApplication::createNewPlayer(const std::string& secret)
{
	me = Player::createNew(secret);
	startPlay(secret);
}

void LesserApplication::startPlay(const std::string& secret)
{
	setCookie("LesserFair.secret", secret, 24 * 3600 * 365 * 10);
	ui.setPlayer(me);
}


