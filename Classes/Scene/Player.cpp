#include"Player.h"
Player* Player::sharedPlayer = nullptr;

Player::Player()
{
    playerHP = MAX_PLAYER_HP;
    playerGold = 5;
    //此处改为了5
    myPlayer = nullptr;
}

Player* Player::getInstance()
{
    if (nullptr == sharedPlayer)
    {
        sharedPlayer = new Player();
        sharedPlayer->init();
        sharedPlayer->autorelease();
    }

    return sharedPlayer;
}

bool Player::init()
{
    if (!Layer::init())
    {
        return true;
    }

    myPlayer = Sprite::create(PLAYER_WINDOW);
    myPlayer->setPosition(98 + myPlayer->getContentSize().width / 2, 98*10 - myPlayer->getContentSize().height / 2);
    this->addChild(myPlayer);
    labelPlayerGold = Label::createWithTTF(StringUtils::format("%d", playerGold), "fonts/Marker Felt.ttf", 24);
    labelPlayerGold->setPosition(98 + myPlayer->getContentSize().width / 3+ labelPlayerGold->getContentSize().width / 2,
        98 * 10 - myPlayer->getContentSize().height / 2 - 98 / 4);
    addChild(labelPlayerGold);
	Sprite* bloodSp = Sprite::create("blood.png");
	bloodBar = ProgressTimer::create(bloodSp);
	bloodBar->setType(ProgressTimer::Type::BAR);
	bloodBar->setMidpoint(Point(0, 0.5));
	bloodBar->setBarChangeRate(Point(1, 0));
	bloodBar->setPercentage(100.f);
    bloodBar->setPosition(98 + myPlayer->getContentSize().width / 2+98/4+bloodBar->getContentSize().width/2, 
        98 * 10 - myPlayer->getContentSize().height / 2-98/4);
	addChild(bloodBar);
    this->scheduleUpdate();

    return true;
}

void  Player::update(float dt)
{
	bloodBar->setPercentage(static_cast<float>(playerHP) / MAX_PLAYER_HP * 100.f);
}

void Player::addHeroClick(const std::string& heroName)
{
	if ("Tank.png" == heroName)
		heroOnReady.push_back(Type_Tank);
	else if ("Assasion.png" == heroName)
		heroOnReady.push_back(Type_Assasion);
	else if ("ADC.png" == heroName)
		heroOnReady.push_back(Type_ADC);
	else if ("AP.png" == heroName)
		heroOnReady.push_back(Type_AP);
	else if ("AOE.png" == heroName)
		heroOnReady.push_back(Type_AOE);

    heroOnReadyNum ++;
}


Sprite* Player::getPlayer()
{
    if (nullptr == myPlayer)
        return nullptr;
    return myPlayer;
}

void Player::playerUpgrade()
{
    ;
}
