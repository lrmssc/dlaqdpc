////  BarrierLayer.cpp//  dianliwangguomanyouji////  Created by szsycx on 3/17/15.////#include "BarrierLayer.h"BarrierLayer::BarrierLayer(){}BarrierLayer::~BarrierLayer(){}bool BarrierLayer::init(){    if(!Layer::init()){        return false;    }    //添加一个半灰色的层    LayerColor* backLayerColor = LayerColor::create(Color4B(20, 20, 20, 180));    this->addChild(backLayerColor);    //添加向下触摸屏蔽    auto callback = [](Touch * ,Event *)    {        return true;    };    auto listener = EventListenerTouchOneByOne::create();    listener->onTouchBegan = callback;    listener->setSwallowTouches(true);    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);    setTag(100);    return true;}