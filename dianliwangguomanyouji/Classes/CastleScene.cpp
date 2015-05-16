////  CastleScreen.cpp//  SecondProject////  Created by szsycx on 3/8/15.////#include "CastleScene.h"#include "MenuScene.h"#include "LevelScene.h"cocos2d::Scene* CastleScene::createScene(){    auto scene = Scene::create();    auto layer = CastleScene::create();    scene->addChild(layer);    return scene;    }bool CastleScene::init(){        if(!Layer::init()){        return false;    }        int maxSeason = UserDefault::getInstance()->getIntegerForKey("season", 1);    int currentSeason = UserDefault::getInstance()->getIntegerForKey("current_season",maxSeason);        Size visibleSize = Director::getInstance()->getVisibleSize();        auto bg = Sprite::create("castle/bg.jpg");    bg->setPosition(Vec2(visibleSize.width/2.0,visibleSize.height/2.0));    this->addChild(bg);        back = Button::create("castle/back.png");    back->setPosition(Vec2(back->getContentSize().width*6.0/10.0,back->getContentSize().height*6.0/10.0));    back->addTouchEventListener([](Ref*pSender,Widget::TouchEventType type){        Director::getInstance()->replaceScene(MenuScene::createScene());    });    this->addChild(back);        season1 = Button::create("castle/c1.png");    season1->setPosition(Vec2(415,160));    season1->addTouchEventListener([](Ref*pSender,Widget::TouchEventType type){        if(type==Widget::TouchEventType::ENDED){        UserDefault::getInstance()->setIntegerForKey("current_season", 1);        UserDefault::getInstance()->flush();        Director::getInstance()->replaceScene(LevelScene::createScene());        }    });    this->addChild(season1);        season2 = Button::create("castle/c2.png");    season2->setPosition(Vec2(620,300));    season2->addTouchEventListener([](Ref*pSender,Widget::TouchEventType type){        if(type==Widget::TouchEventType::ENDED){        UserDefault::getInstance()->setIntegerForKey("current_season", 2);        UserDefault::getInstance()->flush();//        GameScreen::currentSeason = 2;            Director::getInstance()->replaceScene(LevelScene::createScene());        }    });    this->addChild(season2);        season3 = Button::create("castle/c3.png");    season3->setPosition(Vec2(820,350));    season3->addTouchEventListener([](Ref*pSender,Widget::TouchEventType type){        if(type==Widget::TouchEventType::ENDED){        UserDefault::getInstance()->setIntegerForKey("current_season", 3);        UserDefault::getInstance()->flush();//        GameScreen::currentSeason = 3;        Director::getInstance()->replaceScene(LevelScene::createScene());        }    });    this->addChild(season3);        season4 = Button::create("castle/c4.png");    season4->setPosition(Vec2(680,470));       season4->addTouchEventListener([](Ref*pSender,Widget::TouchEventType type){        if(type==Widget::TouchEventType::ENDED){        UserDefault::getInstance()->setIntegerForKey("current_season", 4);        UserDefault::getInstance()->flush();            Director::getInstance()->replaceScene(LevelScene::createScene());        }    });    this->addChild(season4);        season5 = Button::create("castle/c5.png");    season5->setPosition(Vec2(450,420));    season5->addTouchEventListener([](Ref*pSender,Widget::TouchEventType type){        if(type==Widget::TouchEventType::ENDED){        UserDefault::getInstance()->setIntegerForKey("current_season", 5);        UserDefault::getInstance()->flush();        Director::getInstance()->replaceScene(LevelScene::createScene());        }    });    this->addChild(season5);    season6= Button::create("castle/c6.png");    season6->setPosition(Vec2(510,550));    season6->addTouchEventListener([](Ref*pSender,Widget::TouchEventType type){        if(type==Widget::TouchEventType::ENDED){        UserDefault::getInstance()->setIntegerForKey("current_season", 6);        UserDefault::getInstance()->flush();        Director::getInstance()->replaceScene(LevelScene::createScene());        }    });    this->addChild(season6);        switch(currentSeason){        case 1:            season1->runAction(getForeverScale());            break;        case 2:            season2->runAction(getForeverScale());            break;        case 3:            season3->runAction(getForeverScale());            break;        case 4:            season4->runAction(getForeverScale());            break;        case 5:            season5->runAction(getForeverScale());            break;        case 6:            season6->runAction(getForeverScale());            break;    }    return true;}RepeatForever * CastleScene::getForeverScale(){    auto sequence = Sequence::create(ScaleTo::create(0.5, 1.1),ScaleTo::create(0.5, 0.9),NULL);    auto repeat = RepeatForever::create(sequence);    return repeat;}