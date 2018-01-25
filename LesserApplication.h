#ifndef LESSERAPPLICATION_H_
#define LESSERAPPLICATION_H_

#include "UserInterface.h"

#include <Wt/WApplication.h>

class Player;

class LesserApplication : public Wt::WApplication
{
	public:
		LesserApplication(const Wt::WEnvironment& env);
		virtual ~LesserApplication();

	private:
		void setupPlayer();
		void createNewPlayer();
		void createNewPlayer(const std::string& secret);
		void startPlay(const std::string& secret);

		Player* me;
		UserInterface ui;
};

#endif
