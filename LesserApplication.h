#ifndef LESSERAPPLICATION_H_
#define LESSERAPPLICATION_H_

#include <Wt/WApplication.h>

class LesserApplication : public Wt::WApplication
{
	public:
		LesserApplication(const Wt::WEnvironment& env);
		virtual ~LesserApplication();
};

#endif
