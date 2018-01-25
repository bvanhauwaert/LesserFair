#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include <memory>
#include <string>

class Player;

namespace Wt
{
	class WContainerWidget;
	class WCssStyleSheet;
	class WTemplate;
}

class UserInterface
{
	public:
		UserInterface(Wt::WCssStyleSheet& styleSheet, Wt::WContainerWidget* root);

		void setPlayer(Player* m);
		void announceNewPlayer(const std::string& secret);
		void announcePlayerNotFound(const std::string& offeredSecret);
	private:
		void announce(std::unique_ptr<Wt::WTemplate> message);
		void setupPlayArea();
		void setupStyleSheet(Wt::WCssStyleSheet& styleSheet);
		void updatePlayArea();
		void onChangeNameClicked();

		Player* me;
		Wt::WContainerWidget* root;
		Wt::WTemplate* dataWidget;
};

#endif
