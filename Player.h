#ifndef PLAYER_H_
#define PLAYER_H_

#include <mutex>
#include <string>

#include <Wt/WString.h>

struct PlayerData
{
	std::string secret;
	Wt::WString name;
};

class Player
{
	public:
		static Player* createNew(const std::string& secret);
		static Player* getExisting(const std::string& secret);

		Player(const std::string& secret, const std::string& name);
		~Player();
		
		PlayerData playerData() const;
		void changeName(const Wt::WString& name);

	private:
		mutable std::mutex dataLock;
		PlayerData data;
};

#endif
