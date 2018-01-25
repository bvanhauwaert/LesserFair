#include "UserInterface.h"
#include "Player.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WCssStyleSheet.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>

UserInterface::UserInterface(Wt::WCssStyleSheet& styleSheet, Wt::WContainerWidget* r)
: me(0), root(r), dataWidget(0)
{
	setupStyleSheet(styleSheet);
	setupPlayArea();
}

void UserInterface::setPlayer(Player* m)
{
	me = m;
	updatePlayArea();
}

void UserInterface::updatePlayArea()
{
	if (!me)
		return;
	PlayerData data(me->playerData());
	dataWidget->bindString("name", data.name);
}

void UserInterface::setupPlayArea()
{
	auto playArea = root->addWidget(std::make_unique<Wt::WContainerWidget>());
	playArea->addStyleClass("playarea");
	dataWidget = playArea->addWidget(std::make_unique<Wt::WTemplate>(
		"<span class='rightalign'>${name}&nbsp;&nbsp;${changenamebutton}</span><br/>"));
	auto changeNameButton = dataWidget->bindWidget("changenamebutton", std::make_unique<Wt::WPushButton>("Modify"));
	changeNameButton->addStyleClass("actionbutton");
	changeNameButton->clicked().connect([this]()
		{
			onChangeNameClicked();
		});
}

void UserInterface::announceNewPlayer(const std::string& secret)
{
	auto text = std::make_unique<Wt::WTemplate>("Hi,<br/><br/>"
		"it seems this is your first time at the Lesser Fair Game. "
		"Fair enough! "
		"I'll name you ${secret}. Difficult, isn't it? I know, not fair. But it's just between us. "
		"Fortunately, the purpose of this game is easier. Just beat everyone.<br/><br/>"
		"Now then, let's get on with it!");
	text->bindString("secret", secret);
	announce(std::move(text));
}

void UserInterface::announcePlayerNotFound(const std::string& offeredSecret)
{
	auto text = std::make_unique<Wt::WTemplate>("Hi,<br/><br/>"
		"your cookies claim I named you ${secret}, but I don't remember any of that. "
		"Well, it doesn't bother me at all but hopefully you won't be bothered "
		"by the idea I'll have you start over. Not fair, really. But that's "
		"the name of the game!");
	text->bindString("secret", offeredSecret);
	announce(std::move(text));
}

void UserInterface::announce(std::unique_ptr<Wt::WTemplate> content)
{
	auto popup = root->insertWidget(0, std::make_unique<Wt::WContainerWidget>());
	popup->addStyleClass("announcement");
	popup->addWidget(std::move(content));
	auto closeButton = popup->addWidget(std::make_unique<Wt::WPushButton>("Close"));
	closeButton->addStyleClass("closebutton");
	closeButton->clicked().connect([this, popup]()
		{
			root->removeWidget(popup);
		});
}

void UserInterface::onChangeNameClicked()
{
	auto dialog = root->insertWidget(0, std::make_unique<Wt::WTemplate>("New name : ${newnameinput} ${modifybutton}"));
	dialog->addStyleClass("announcement");
	auto nameInput = dialog->bindWidget("newnameinput", std::make_unique<Wt::WLineEdit>());
	nameInput->addStyleClass("chatline");
	auto modifyButton = dialog->bindWidget("modifybutton", std::make_unique<Wt::WPushButton>("Modify"));
	modifyButton->addStyleClass("closebutton");
	modifyButton->clicked().connect([this, dialog, nameInput]()
		{
			me->changeName(nameInput->text());
			root->removeWidget(dialog);
			updatePlayArea();
		});
}

void UserInterface::setupStyleSheet(Wt::WCssStyleSheet& styleSheet)
{
	styleSheet.addRule(".announcement",
		"background-color: moccasin;"
		"border-color: red;"
		"border-style: solid;"
		"border-width: 1px;"
		"margin-top: 1em;"
		"margin-bottom: 1em;"
		"overflow: auto;"
		"padding: 1em");
	styleSheet.addRule(".actionbutton",
		"background-color: lightgreen;"
		"border-color: green;"
		"border-style: solid;"
		"border-width: 1px;"
		"float: right;"
		"padding: 0.3em");
	styleSheet.addRule(".closebutton",
		"background-color: lightblue;"
		"border-color: blue;"
		"border-style: solid;"
		"border-width: 1px;"
		"float: right;"
		"padding: 0.3em");
	styleSheet.addRule(".chatline",
		"margin-left: 1em;"
		"width: 30em;"
		"font-size: 1em;"
		"padding: 0.3em");
	styleSheet.addRule(".playarea",
		"background-color: gainsboro;"
		"border-color: gray;"
		"border-style: solid;"
		"border-width: 1px;"
		"margin-top: 1em;"
		"margin-bottom: 1em;"
		"overflow: auto;"
		"padding: 1em");
	styleSheet.addRule(".rightalign",
		"float: right;");
}
