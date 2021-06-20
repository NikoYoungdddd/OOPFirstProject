#include"Player.h"

Player* Player::sharedPlayer = nullptr;
extern int startToCountDown;


Player::Player()
{
    playerHP = MAX_PLAYER_HP;
    playerGold = 3;
    //此处改为了5
    myPlayer = nullptr;
    enemyHP = MAX_PLAYER_HP;
    playerExp = 0;
    playerGrade = 1;
    downPrepareTime = PREPARE_TIME;
    isAI = 0;
    server = 0;
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
    myPlayer->setPosition(98 + myPlayer->getContentSize().width / 2, 98 * 10 - myPlayer->getContentSize().height / 2);
    this->addChild(myPlayer);
    labelPlayerGold = Label::createWithTTF(StringUtils::format("%d", playerGold), "fonts/Marker Felt.ttf", 24);
    labelPlayerGold->setPosition(98 + myPlayer->getContentSize().width / 3 + labelPlayerGold->getContentSize().width / 2,
        98 * 10 - myPlayer->getContentSize().height / 2 - 98 / 4);
    addChild(labelPlayerGold);
    labelPlayerGrade = Label::createWithTTF(StringUtils::format("%d", playerGrade), "fonts/Marker Felt.ttf", 24);
    labelPlayerGrade->setPosition(98 + myPlayer->getContentSize().width / 3 + labelPlayerGrade->getContentSize().width / 2,
        98 * 10 - myPlayer->getContentSize().height / 2 + 98 / 4);
    addChild(labelPlayerGrade);
    Sprite* bloodSp = Sprite::create("blood.png");
    bloodBar = ProgressTimer::create(bloodSp);
    bloodBar->setType(ProgressTimer::Type::BAR);
    bloodBar->setMidpoint(Point(0, 0.5));
    bloodBar->setBarChangeRate(Point(1, 0));
    bloodBar->setPercentage(100.f);
    bloodBar->setPosition(98 + myPlayer->getContentSize().width / 2 + 98 / 4 + bloodBar->getContentSize().width / 2,
        98 * 10 - myPlayer->getContentSize().height / 2 - 98 / 4);
    addChild(bloodBar);
    Sprite* ExpSp = Sprite::create("exp.png");
    ExpBar = ProgressTimer::create(ExpSp);
    ExpBar->setType(ProgressTimer::Type::BAR);
    ExpBar->setMidpoint(Point(0, 0.5));
    ExpBar->setBarChangeRate(Point(1, 0));
    ExpBar->setPercentage(0.f);
    ExpBar->setPosition(98 + myPlayer->getContentSize().width / 2 + 98 / 4 + bloodBar->getContentSize().width / 2,
        98 * 10 - myPlayer->getContentSize().height / 2);
    addChild(ExpBar);
    labelPlayerHP = Label::createWithTTF(StringUtils::format("%d/%d", playerHP, MAX_PLAYER_HP), "fonts/Marker Felt.ttf", 20);
    labelPlayerHP->setPosition(98 + myPlayer->getContentSize().width / 2 + 98 / 4 + bloodBar->getContentSize().width / 2,
        98 * 10 - myPlayer->getContentSize().height / 2 - 98 / 4);
    addChild(labelPlayerHP);
    labelPlayerExp = Label::createWithTTF(StringUtils::format("%d/%d", playerExp, playerExpPerGrade[playerGrade - 1]), "fonts/Marker Felt.ttf", 20);
    labelPlayerExp->setPosition(98 + myPlayer->getContentSize().width / 2 + 98 / 4 + bloodBar->getContentSize().width / 2,
        98 * 10 - myPlayer->getContentSize().height / 2);
    addChild(labelPlayerExp);

    auto AIPlayer = Sprite::create(ENEMY_WINDOW);
    AIPlayer->setPosition(98 * 8 + AIPlayer->getContentSize().width / 2, 98 * 10 - AIPlayer->getContentSize().height / 2);
    this->addChild(AIPlayer);
    Sprite* AIbloodSp = Sprite::create("bloodEnemy.png");
    AIbloodBar = ProgressTimer::create(AIbloodSp);
    AIbloodBar->setType(ProgressTimer::Type::BAR);
    AIbloodBar->setMidpoint(Point(0, 0.5));
    AIbloodBar->setBarChangeRate(Point(1, 0));
    AIbloodBar->setPercentage(100.f);
    AIbloodBar->setPosition(98 * 8 + AIPlayer->getContentSize().width / 2 + AIbloodBar->getContentSize().width / 2,
        98 * 10 - AIPlayer->getContentSize().height / 2 - 98 / 6.0f * 0.75f);
    addChild(AIbloodBar);
    labelAIHP = Label::createWithTTF(StringUtils::format("%d/%d", enemyHP, MAX_PLAYER_HP), "fonts/Marker Felt.ttf", 20);
    labelAIHP->setPosition(98 * 8 + AIPlayer->getContentSize().width / 2 + AIbloodBar->getContentSize().width / 2,
        98 * 10 - AIPlayer->getContentSize().height / 2 - 98 / 6.0f * 0.75f);
    addChild(labelAIHP);

    this->scheduleUpdate();

    return true;
}


void  Player::update(float dt)
{
    labelPlayerGold->setString(StringUtils::format("%d", playerGold));
    labelPlayerGrade->setString(StringUtils::format("%d", playerGrade));
    labelPlayerExp->setString(StringUtils::format("%d/%d", playerExp, playerExpPerGrade[playerGrade - 1]));
    labelPlayerHP->setString(StringUtils::format("%d/%d", playerHP, MAX_PLAYER_HP));
    bloodBar->setPercentage(static_cast<float>(playerHP) / MAX_PLAYER_HP * 100.f);
    AIbloodBar->setPercentage(static_cast<float>(enemyHP) / MAX_PLAYER_HP * 100.f);
    labelAIHP->setString(StringUtils::format("%d/%d", enemyHP, MAX_PLAYER_HP));
    ExpBar->setPercentage(static_cast<float>(playerExp) / playerExpPerGrade[playerGrade - 1] * 100.f);
    while (playerExp >= playerExpPerGrade[playerGrade - 1])
    {
        playerExp -= playerExpPerGrade[playerGrade - 1];
        //ExpBar->setPercentage(static_cast<float>(playerExp) / playerExpPerGrade[playerGrade - 1] * 100.f);
        playerGrade++;
    }
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

    heroOnReadyNum++;
}


Sprite* Player::getPlayer()
{
    if (nullptr == myPlayer)
        return nullptr;
    return myPlayer;
}


void Player::playerUpgrade()
{
    if (playerGold >= 2)
    {
        playerExp += 2;
        playerGold -= 2;
    }
}
