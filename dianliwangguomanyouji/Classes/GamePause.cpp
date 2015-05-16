////  GamePause.cpp//  dianliwangguomanyouji////  Created by szsycx on 3/17/15.////#include "GamePause.h"#include "GameScene.h"#include "BarrierLayer.h"#include "LevelScene.h"GamePause::GamePause(){}GamePause::~GamePause(){}bool GamePause::init(){    if(!Layer::init())        return false;    Size WinSize = Director::getInstance()->getVisibleSize();    Vec2 CenterPoint = Vec2(WinSize.width/2,WinSize.height/2);        auto bg = Sprite::create("game/bg.png");    bg->setPosition(CenterPoint);        auto continuebutton = Button::create("game/continue.png");    continuebutton->addTouchEventListener([=](Ref * pSender , Widget::TouchEventType type){        switch (type)        {            case cocos2d::ui::Widget::TouchEventType::ENDED:            {                getParent()->removeChildByTag(100);                getParent()->removeChildByTag(101);                Director::getInstance()->resume();            }                break;        }    });    auto restartbutton = Button::create("game/restart.png");    restartbutton->addTouchEventListener([=](Ref * pSender , Widget::TouchEventType type){        switch (type)        {            case cocos2d::ui::Widget::TouchEventType::ENDED:            {                //之前就停止了所有的scene,不回复下就算创建新场景也是pause的                Director::getInstance()->resume();                Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f,GameScene::createScene()));            }                break;        }    });    auto back = Button::create("game/back.png");    back->addTouchEventListener([=](Ref * pSender , Widget::TouchEventType type){        switch (type)        {            case cocos2d::ui::Widget::TouchEventType::ENDED:            {                //之前就停止了所有的scene,不回复下就算创建新场景也是pause的                Director::getInstance()->resume();                Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f,LevelScene::createScene()));            }                break;        }    });    continuebutton->setPosition(Vec2(WinSize.width/2.0,WinSize.height*6.25/10.0));    restartbutton->setPosition(Vec2(WinSize.width/2.0,WinSize.height*4.4/10.0));    back->setPosition(Vec2(WinSize.width/2.0,WinSize.height*2.55/10.0));    addChild(bg);    addChild(continuebutton);    addChild(restartbutton);    addChild(back);    setTag(101);    return true;}