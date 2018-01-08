#include "LesserApplication.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>

LesserApplication::LesserApplication(const Wt::WEnvironment& env)
	: Wt::WApplication(env)
{
	setTitle("The Lesser Fair Game");
	root()->addWidget(std::make_unique<Wt::WText>("Hello world!"));
}

LesserApplication::~LesserApplication()
{
}

