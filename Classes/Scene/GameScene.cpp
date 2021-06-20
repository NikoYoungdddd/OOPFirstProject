#include "GameScene.h"

extern int BGMID;
extern bool ifBgmOn;
bool ifFinallyEnd = 0;//����������Ϸ����ʱ�Ľ�����֣���չ��gamescene
extern bool ifIsBattling;
bool ifClickLocked = 0;


/*ͼ�㣺��addchild�ڶ���������
* 0.map
* 1.��ť�����ְ�ť�ı���
* 2.���ְ�ť���ڲ�ͼ��
* 3.���֣�player
* 4.HeroLayerͼ��
*/
Scene* GameScene::createScene()
{
    return GameScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto map = TMXTiledMap::create("chessboard3.tmx");
    this->addChild(map, 0);

    if (!Scene::initWithPhysics())
    {
        return false;
    }
    if (ifBgmOn)
    {
        BGMID = AudioEngine::play2d(BGM_GAME, true, 0.3f);
    }
    else
    {
        BGMID = AudioEngine::play2d(BGM_GAME, true, .0);

    }
    auto MusicBt = Sprite::create(MUSIC_BUTTON_BACKGROUND);
    if (MusicBt == nullptr)
    {
        problemLoading("'button/musicItemBg.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - MusicBt->getContentSize().width / 2 * 3;
        float y = origin.y - MusicBt->getContentSize().height / 2 + 98 * 10;
        MusicBt->setPosition(Vec2(x, y));
        this->addChild(MusicBt, 1);
        //������Ϊ�˱�����ڿ�ָ��closeItem�����ã���ͼƬ�زĵ����ְ�ť������ر�ͼ������Ϊͳһ��С
    }
    auto musicItem = ui::Button::create(MUSIC_BUTTON_CONTENT,
        MUSIC_BUTTON_CONTENT);
    if (musicItem == nullptr)
    {
        problemLoading("'button/musicItemContent.png'");
    }
    else
    {
        if (!ifBgmOn)
            musicItem->setColor(Color3B(20, 20, 20));
        float x = origin.x + visibleSize.width - musicItem->getContentSize().width / 2 * 3;
        float y = origin.y - musicItem->getContentSize().height / 2 + 98 * 10;
        musicItem->setPosition(Vec2(x, y));
        musicItem->addClickEventListener([&](Ref*) { changMusicPlayEvent(); });
        this->addChild(musicItem, 2, 77);
    }
    auto UpgradeItem = ui::Button::create(UPGRADE_BUTTON,
        UPGRADE_BUTTON);
    UpgradeItem->setScale(UPGRADE_SCALE_IN_GAMESCENE);
    if (UpgradeItem == nullptr)
    {
        problemLoading("'button/upgradeItem.png'");
    }
    else
    {
        UpgradeItem->setPosition(Vec2(UpgradeItem->getContentSize().width / 2,
            98 * 10 - UpgradeItem->getContentSize().height / 2));
        UpgradeItem->addClickEventListener([&](Ref*) { Player::getInstance()->playerUpgrade(); });
        this->addChild(UpgradeItem, 1);
    }
    auto closeItem = MenuItemImage::create(
        CLOSE_BUTTON,
        CLOSE_BUTTON,
        CC_CALLBACK_1(GameScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'button/closeItem.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y - closeItem->getContentSize().height / 2 + 98 * 10;
        closeItem->setPosition(Vec2(x, y));
    }
    auto PurchaseItem = MenuItemImage::create(
        CHESS_PURCHASE_BUTTON,
        CHESS_PURCHASE_BUTTON,
        CC_CALLBACK_1(GameScene::menuToPurchaseLayer, this));

    if (PurchaseItem == nullptr ||
        PurchaseItem->getContentSize().width <= 0 ||
        PurchaseItem->getContentSize().height <= 0)
    {
        problemLoading("'button / ChessSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - PurchaseItem->getContentSize().width / 2;
        float y = origin.y + PurchaseItem->getContentSize().height / 2;
        PurchaseItem->setPosition(Vec2(x, y));
    }
   
    auto menu = Menu::create(closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    menuUnable = Menu::create(PurchaseItem,nullptr);
    menuUnable->setPosition(Vec2::ZERO);
    this->addChild(menuUnable, 1);

    auto player = Player::getInstance();
    this->addChild(player, 3);
    heroLayer = HeroLayer::create();
    this->addChild(heroLayer, 4);

    if (!Player::getInstance()->isAI)
    {
        auto chatLayer = ChatLayer::create();
        this->addChild(chatLayer, 3);
    }
    this->scheduleUpdate();
    if (!Player::getInstance()->isAI)
    {
        if (Player::getInstance()->server == SERVER)
        {
            log("start server");
            if (Server::getInstance()->OpenTCPServer(1))
            {
                log("start success");

                if (Server::getInstance()->AcceptClient())
                {
                    log("accept!");
                    {
                        ;
                    }
                }
            }
            else
                log("error");
        }
        else if (Player::getInstance()->server == CLIENT)
        {
            log("start");
            /*��ʼ���ͻ���*/
            if (Client::getInstance()->InitSocket(1))  //��ʼ���׽���
            {
                log("init success");
                /*���ӷ����*/
                if (Client::getInstance()->ConnectServer())     //���ӷ�����
                {
                    log("connect success");

                }
                else
                    log("connect erro");
            }
            //��������
        }
    }
    std::thread t1(&GameScene::ThreadRecv, this);
    t1.detach();
    return true;
}


void GameScene::update(float dt)
{
    if (Player::getInstance()->heroOnReadyNum > num)
    {
        auto heroType = Player::getInstance()->heroOnReady;

        for (unsigned int i = 0; i < heroType.size() - num; i++)
        {
            int type = *(heroType.begin() + num + i);
            heroLayer->createHeroOnReady(type);
        }
        num = Player::getInstance()->heroOnReadyNum;
    }
    if (ifFinallyEnd)
    {
        ifFinallyEnd = 0;
        if (Player::getInstance()->playerHP <= 0 || Player::getInstance()->enemyHP <= 0)
        {
            scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::EndToWin), 5.0f);
        }
    }
    if (ifIsBattling == 1 && ifClickLocked == 0)
    {
        ifClickLocked = 1;
        menuUnable->setEnabled(false);
    }
    if (ifIsBattling == 0 && ifClickLocked == 1)
    {
        ifClickLocked = 0;
        menuUnable->setEnabled(true);
    }


  //  ThreadRecv();

}


void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->pushScene(ExitScene::createScene());
}


void GameScene::menuToPurchaseLayer(Ref* pSender)
{
    heroLayer->eraseLablePrepareTime();
    Director::getInstance()->pushScene(PurchaseScene::createScene());
}


void GameScene::changMusicPlayEvent()
{
    AudioEngine::setVolume(BGMID, 0.3f);
    if (ifBgmOn) {
        ifBgmOn = false;
        this->getChildByTag(77)->setColor(Color3B(20, 20, 20));
        AudioEngine::pause(BGMID);
    }
    else
    {
        ifBgmOn = true;
        this->getChildByTag(77)->setColor(Color3B(240, 240, 240));
        AudioEngine::resume(BGMID);
    }
}


void GameScene::EndToWin(float dt)
{
    Director::getInstance()->replaceScene(EndScene::createScene());
}


void GameScene::ThreadRecv()
{
    while (1)
    {
        Sleep(100);
        int i = 0;
        if (Player::getInstance()->server == SERVER)
            i = Server::getInstance()->RecvDataAndJudge();
        if (Player::getInstance()->server == CLIENT)
            i = Client::getInstance()->RecvDataAndJudge();
        if (i != 0)
        {
            //log(iRet.data());
        }
    }
}