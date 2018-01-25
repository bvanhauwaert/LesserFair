#include "Player.h"

#include <memory>
#include <mutex>
#include <vector>

namespace
{
	std::mutex playerListLock;
	std::vector<std::unique_ptr<Player>> players;
}


Player::Player(const std::string& secret, const std::string& name)
{
	data.secret = secret;
	data.name = Wt::WString::fromUTF8(name);
}

Player::~Player()
{
}

PlayerData Player::playerData() const
{
	std::lock_guard<std::mutex> guard(dataLock);
	return data;
}

void Player::changeName(const Wt::WString& name)
{
	std::lock_guard<std::mutex> guard(dataLock);
	data.name = name;
}

Player* Player::getExisting(const std::string& secret)
{
	std::lock_guard<std::mutex> guard(playerListLock);
	for (const auto& player : players)
		if (player->data.secret == secret)
			return player.get();
	return 0;
}

Player* Player::createNew(const std::string& secret)
{
	std::lock_guard<std::mutex> guard(playerListLock);
	players.push_back(std::make_unique<Player>(secret, "Mystery guest "+std::to_string(players.size()+1)));
	return players.back().get();
}
