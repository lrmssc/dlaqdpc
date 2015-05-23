////  LevelWin.cpp//  dianliwangguomanyouji////  Created by szsycx on 3/17/15.////#include "LevelWin.h"#include "ui/CocosGUI.h"#include "GameScene.h"#include "LevelScene.h"using namespace cocos2d::ui;RepeatForever * LevelWin::getBlink(){    auto blink = Blink::create(2,3);    auto repeat = RepeatForever::create(blink);    return repeat;}bool LevelWin::init(){    if(!Layer::init()){        return false;    }        bool isMusicPlay = UserDefault::getInstance()->getBoolForKey("music",true);    if(isMusicPlay){        bool isMale = UserDefault::getInstance()->getBoolForKey("male", true);        if(isMale){            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("levelwin/levelwinm.mp3");            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("levelwin/levelwinm.mp3");        }else{            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("levelwin/levelwinf.mp3");        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("levelwin/levelwinf.mp3");        }    }        Size visibleSize = Director::getInstance()->getVisibleSize();    int beanNumber = UserDefault::getInstance()->getIntegerForKey("bean",1);    int currentSeason = UserDefault::getInstance()->getIntegerForKey("current_season",1);    int currentLevel = UserDefault::getInstance()->getIntegerForKey("current_level", 1);    int maxLevel = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("max_level%d",currentSeason).c_str(), 1);    int trueMaxLevel = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("true_max_level%d",currentSeason).c_str(), 1);        bool haveDone;    if(currentLevel==5||currentLevel==10){//level 6 11 is magic game        haveDone = UserDefault::getInstance()->getBoolForKey(StringUtils::format("magic%d%d",currentSeason,currentLevel+1).c_str(),false);    }else{        haveDone = false;    }        log("currentSeason %d currentLevel %d maxlevel %d true maxlevel %d",currentSeason,currentLevel,maxLevel,trueMaxLevel);        if(currentLevel==trueMaxLevel){        if(beanNumber+20<9999){            beanNumber+=20;        }else{            beanNumber = 9999;        }    }else{        if(beanNumber+5<9999){            beanNumber+=5;        }else{            beanNumber = 9999;        }    }        if(maxLevel<12){        if(currentLevel==maxLevel){            if(haveDone){                UserDefault::getInstance()->setIntegerForKey(StringUtils::format("max_level%d",currentSeason).c_str(), maxLevel+2);                if(maxLevel+2>=trueMaxLevel){                    UserDefault::getInstance()->setIntegerForKey(StringUtils::format("true_max_level%d",currentSeason).c_str(), trueMaxLevel+2);                                   }            }else{                UserDefault::getInstance()->setIntegerForKey(StringUtils::format("max_level%d",currentSeason).c_str(), maxLevel+1);                if(maxLevel+1>=trueMaxLevel){                    UserDefault::getInstance()->setIntegerForKey(StringUtils::format("true_max_level%d",currentSeason).c_str(), trueMaxLevel+1);                }                            }                    }    }          UserDefault::getInstance()->setIntegerForKey("bean", beanNumber);    UserDefault::getInstance()->flush();    Director::getInstance()->resume();                    auto title = Sprite::create("levelwin/title.png");    title->setPosition(Vec2(visibleSize.width*4.0/10.0,visibleSize.height-title->getContentSize().height));    addChild(title);        Sprite * sprite;    bool isMale = UserDefault::getInstance()->getBoolForKey("male",true);    if(isMale){        sprite = Sprite::create("levelwin/userm.png");    }else{        sprite = Sprite::create("levelwin/userf.png");    }    sprite->setPosition(Vec2(visibleSize.width*7.0/10.0,visibleSize.height/2.0));    addChild(sprite);        log("current level= %d , trueMaxLevel %d ",currentLevel , trueMaxLevel);    if(currentLevel<trueMaxLevel){         log("currentLevel<trueMaxLevel");        auto reward = Sprite::create("levelwin/reward5.png");        reward->setPosition(Vec2(visibleSize.width*4.2f/10.0f,visibleSize.height*6.6/10.0));        addChild(reward);    }else{         log("currentLevel>=trueMaxLevel");        auto reward = Sprite::create("levelwin/reward.png");        reward->setPosition(Vec2(visibleSize.width*4.2f/10.0f,visibleSize.height*6.6/10.0));        addChild(reward);    }        restart = Button::create("levelwin/restart.png");    restart->setPosition(Vec2(visibleSize.width*3.5/10.0,visibleSize.height*2.0/10.0));    restart->addTouchEventListener([&](Ref* pSender ,Widget::TouchEventType type){        if(type==Widget::TouchEventType::ENDED){                                    Director::getInstance()->replaceScene(GameScene::createScene());            Director::getInstance()->resume();        }    });    addChild(restart);        log("true maxlevl %d current = %d",trueMaxLevel ,currentLevel);    if(trueMaxLevel==12 && currentLevel==12){        next = Button::create("levelwin/next.png");        next->addTouchEventListener([&](Ref* pSender ,Widget::TouchEventType type){            if(type==Widget::TouchEventType::ENDED){                                                                log("season win");                    addChild(BarrierLayer::create());                    addChild(SeasonWin::create());                                                }        });    }else{        next = Button::create("levelwin/next.png");        next->addTouchEventListener([&](Ref* pSender ,Widget::TouchEventType type){            if(type==Widget::TouchEventType::ENDED){                                                                log("level win");                    bool  isPlayMusic = UserDefault::getInstance()->getBoolForKey("music", true);                    if(isPlayMusic){                        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("xuqu.mp3");                        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("xuqu.mp3", true);                    }                    Director::getInstance()->resume();                    Director::getInstance()->replaceScene(LevelScene::createScene());                                                                                    }        });    }                next->setPosition(Vec2(visibleSize.width*6.5/10.0,visibleSize.height*2.0/10.0));    addChild(next);         zhidao = Button::create("levelwin/youknow.png");    zhidao->addTouchEventListener([&](Ref* pSender ,Widget::TouchEventType type){        if(type==Widget::TouchEventType::ENDED){            zhidaoBg->setVisible(true);            buttonOk->setVisible(true);            next->setVisible(false);            restart->setVisible(false);            zhidaoWord->setVisible(true);        }    });    auto sequence = Sequence::create(ScaleTo::create(0.5, 1.1),ScaleTo::create(0.5, 0.9),NULL);    auto repeat = RepeatForever::create(sequence);    zhidao->setPosition(Vec2(visibleSize.width*4.0/10.0,visibleSize.height*4.0/10.0));//    auto sequence = Sequence::create(ScaleTo::create(0.5, 1.1),ScaleTo::create(0.5, 0.9),NULL);//    auto repeat = RepeatForever::create(sequence);    zhidao->runAction(repeat);    addChild(zhidao);            auto * name = Text::create(UserDefault::getInstance()->getStringForKey("name", "小明"), "fonts/zhongwen.ttf", 70);    name->setAnchorPoint(Vec2(0,0));    string a = UserDefault::getInstance()->getStringForKey("name", "小明");    log("name =  %s",a.c_str());    name->setPosition(Vec2(visibleSize.width*6.5/10.0,visibleSize.height*8.4/10.0));    addChild(name);        zhidaoBg = Sprite::create("levelwin/youknowbg.png");    zhidaoBg->setPosition(Vec2(visibleSize.width/2.0, visibleSize.height*4.5/10.0));    zhidaoBg->setVisible(false);    addChild(zhidaoBg);        zhidaoWord = Text::create("", "fonts/zhongwen.ttf", 40);    zhidaoWord->setPosition(Vec2(visibleSize.width*2.0/10.0,visibleSize.height*5.0/10.0));    zhidaoWord->setColor(Color3B(93,44,24));    zhidaoWord->setAnchorPoint(Vec2(0,0.5));    addChild(zhidaoWord);                buttonOk = Button::create("yes.png");    buttonOk->setVisible(false);    buttonOk->addTouchEventListener([&](Ref* pSender ,Widget::TouchEventType type){        if(type==Widget::TouchEventType::ENDED){            zhidaoWord->setVisible(false);            zhidaoBg->setVisible(false);            buttonOk->setVisible(false);            next->setVisible(true);            restart->setVisible(true);        }    });        buttonOk->setPosition(Vec2(visibleSize.width*5.0/10.0,visibleSize.height*1.0/10.0));    addChild(buttonOk);        zhidaoWord->setVisible(false);    switch (currentSeason) {        case 1:        {            switch(currentLevel){                case 1:                    zhidaoWord->setString("你知道吗？\n\n1875年，世界上第一座发电厂在法国\n巴黎北火车站建成，为附近照明供电。");                    break;                case 2:                    zhidaoWord->setString("你知道吗？\n\n我们使用二次能源比使用一次能源利用\n效率更高，也更加清洁和环保。电能就\n是最常见的二次能源。");                                        break;                case 3:                    zhidaoWord->setString("你知道吗？\n\n1859年，世界第一口油井在美国宾夕\n法尼亚州投入使用，美国因此成为早期\n主要的石油生产国和消费国。");                                        break;                case 4:                    zhidaoWord->setString("你知道吗？\n\n1892年，英国人霍普金森首先根据电\n力企业的成本特点提出两部制电价，后\n被世界各国普遍采用，因而欧美各国又\n称之为霍普金森电价制。");                                        break;                case 5:                    zhidaoWord->setString("你知道吗？\n\n小鸟站在电线上时，是站在一根电线上，\n两只爪子间电压几乎为零，因而身上没\n有电流通过。但如果它啄铁塔，铁塔和\n导线间的高电压会把它瞬间烧焦");                                        break;                case 7:                    zhidaoWord->setString("你知道吗？\n\n目前，全球核电主要利用的是核裂变技\n术，更加安全、清洁的核聚变是未来核\n电的发展方向，但受技术制约，前景尚\n不明朗。");                                        break;                case 8:                    zhidaoWord->setString("你知道吗？\n\n火力发电是最早得到实用的发电技术，\n也是世界上最重要的发电方式。");                                        break;                case 9:                    zhidaoWord->setString("你知道吗？\n\n电力系统的功率分为有功功率、无功功\n率和视在功率，单位分别是瓦、乏和\n伏·安。");                                        break;                case 10:                    zhidaoWord->setString("你知道吗？\n\n电力系统中包括一次设备和二次设备，\n一次设备直接生产和输、配电能，二次\n设备负责对一次设备进行监察，测量，\n控制，保护和调节等。");                                        break;                case 12:                    zhidaoWord->setString("你知道吗？\n\n直流特高压线路就好比高速公路，她的输\n送负荷更大、输送距离更远；\n交流特高压线路好比各个路口，她更灵活，因而要将二\n者有机地结合起来才能推动特高压这艘航空母舰。");                                        break;            }                    }            break;        case 2:        {            switch(currentLevel){                case 1:                    zhidaoWord->setString("你知道吗？\n\n能量守恒定律即热力学第一定律，指在\n一个封闭（孤立）系统的总能量保持不\n变。其中总能量一般说来已不再只是动\n能与势能之和，而是静止能量（固有能\n量）、动能、势能三者的总量。");                    break;                case 2:  zhidaoWord->setString("你知道吗？\n\n1986年，发生在前苏联统治下乌克兰\n境内切尔诺贝利核电站的核子反应堆事\n故，被认为是历史上最严重的核电事\n故，也是首例被国际核事件分级表评\n为第七级事件的特大事故。");                    break;                case 3:  zhidaoWord->setString("你知道吗？\n\nPM2.5是指大气中直径不大于2.5微米\n的颗粒悬浮物，能被肺泡吸收并进入血\n液，影响人体健康。");                    break;                case 4:  zhidaoWord->setString("你知道吗？\n\n秦山核电站是我国自行设计、建造和运\n营管理的第一座核电站，采用压水反应\n堆，电功率为300兆瓦。");                    break;                case 5:  zhidaoWord->setString("你知道吗？\n\n自建分布式光伏电站需要的主要设备包\n括：太阳能电池板、逆变器、控制开关\n等。");                    break;                case 7:  zhidaoWord->setString("你知道吗？\n\n我国火力发电始于1882年在上海建立\n的中国第一座发电厂，安装了一套蒸汽\n机驱动的发电机组，仅比世界第一座火\n力发电厂——法国巴黎北火车站电厂晚\n了12年。");                    break;                case 8:  zhidaoWord->setString("你知道吗？\n\n蔬果电池产生电流的大小直接和酸性物\n质浓度相关，酸性物质浓度越高的蔬果\n产生的电流越大。");                    break;                case 9:  zhidaoWord->setString("你知道吗？\n\n“自发自用，余电上网”是指分布式光\n伏发电系统所发电力主要是由电力用户\n自己使用，多余电量馈入电网。它是分\n布式光伏发电的一种商业模式。");                    break;                case 10:  zhidaoWord->setString("你知道吗？\n\n光生伏特效应是指半导体在受到光照射\n时产生电动势的现象。");                    break;                case 12:  zhidaoWord->setString("你知道吗？\n垃圾发电是把各种垃圾收集后，进行分类\n处理。其中，一是对燃烧值较高的进行高温焚烧，二是对不\n能燃烧的有机物进行发酵、厌氧处理，最后干\n燥脱硫，产生甲烷，即沼气，再经燃烧，把热能转化为蒸气，推动涡轮机转动，带动发电机产生电能。");                    break;            }                    }            break;        case 3:        {            switch(currentLevel){                case 1:zhidaoWord->setString("你知道吗？\n\n人体在汗湿、皮肤破裂等情况下长时间\n接触电源，即使是在安全电压下也有可\n能发生电击伤害哦。");                    break;                case 2:zhidaoWord->setString("你知道吗？\n\n妇女、儿童的皮肤比较细嫩，表皮角质\n外层比较薄，因而人体电阻较小，则触\n电时通过的电流就更大，所以造成的伤\n害更严重。");                    break;                case 3:zhidaoWord->setString("你知道吗？\n\n带电电线掉落在地上时，会形成一个以\n落地电线端头为中心的同心圆电场，人\n一旦进入该电场内就会造成跨步电压电\n击伤害。");                    break;                case 4:zhidaoWord->setString("你知道吗？\n\n漏电保护器可防止由于电器设备和电气\n线路漏电引起的触电事故。");                    break;                case 5:zhidaoWord->setString("你知道吗？\n\n用铜丝或铁丝代替保险丝，就起不到保\n护线路、电器及人身安全的作用啦。");                    break;                case 7:zhidaoWord->setString("你知道吗？\n\n变压器不是玩具，随意攀爬会导致触电\n残疾或者身亡的事故哦。");                    break;                case 8:zhidaoWord->setString("你知道吗？\n\n插头、插座出现烧焦发黑现象时，千万\n不能继续使用，很容易发生漏电事故呢。");                    break;                case 9:zhidaoWord->setString("你知道吗？\n\n雷雨天时雷电会沿着电源线、室外天线\n等进入室内，所以雷雨天时应关闭电视\n机等电器，切勿接触天线、水管、金属\n门窗等，减少使用座机和手机。");                    break;                case 10:zhidaoWord->setString("你知道吗？\n\n在电力线附近放风筝、钓鱼，容易造成\n触电或停电事故。");                    break;                case 12:zhidaoWord->setString("你知道吗？\n\n电线从门窗缝隙穿过时，可能会受到挤\n压和摩擦导致绝缘层破损，造成触电事\n故哦。");                    break;            }                    }            break;        case 4:        {            switch(currentLevel){                case 1:zhidaoWord->setString("你知道吗？\n\n一只11瓦节能灯的照明效果，相当于\n60瓦的白炽灯。如果全国使用12亿\n只节能灯，节约的电量相当于三峡水电\n站的年发电量。");                    break;                case 2:zhidaoWord->setString("你知道吗？\n\n提前淘米并浸泡10分钟，再用电饭\n锅煮，可大大缩短米熟的时间，节电\n约10%。");                    break;                case 3:zhidaoWord->setString("你知道吗？\n\n现在居民家中大多使用大屏幕彩电，我\n们应适当调节彩电的色彩、音量、对比\n度等，这样才能在最佳观看效果的基础\n上，实现省电又延长电视寿命。同时要\n注意，不能用拔电源插头的方法开关电\n视，不宜频繁开关电视。");                    break;                case 4:zhidaoWord->setString("你知道吗？\n\n电力需求侧管理是指电力公司采取有效\n的激励、诱导措施以及适宜的运作方式\n,与客户共同提高终端用电效率和改变\n用电方式,在满足相同用电功能的同时\n减少电量消耗和电力需求,达到节约资\n源和保护环境的目的,实现最低成本能\n源服务。");                    break;                case 5:zhidaoWord->setString("你知道吗？\n\n煮饭时使用热水或温水，可省电30%;\n电饭锅用毕立即拔下插头，既能减少耗\n电量，又能延长使用寿命。");                    break;                case 7:zhidaoWord->setString("你知道吗？\n\n处理不锈钢厨具表面油渍不必使用洗涤\n剂，只需洒上少许面粉，再用软布擦洗，\n就能光亮如新，还能节水环保。");                    break;                case 8:zhidaoWord->setString("你知道吗？\n\n电冰箱不要塞满食物，储藏量以八分满\n为宜，以免负荷过重，阻碍冷气流通，\n影响效果。");                    break;                case 9:zhidaoWord->setString("你知道吗？\n\n地球一小时（英语：Earth Hour）是一\n个全球性节能活动，提倡于每年三月的\n最后一个星期六当地时间晚上20:30，\n家庭及商界用户关上不必要的电灯及耗\n电产品一小时。");                    break;                case 10:zhidaoWord->setString("你知道吗？\n\n从合理用电和洗涤效果角度看，一般波\n轮式和搅拌式洗衣机水温设置以30~40\n摄氏度为宜，滚筒式洗衣机水温设置以\n50~60摄氏度为宜（所洗衣服不太脏\n时）。");                    break;                case 12:zhidaoWord->setString("你知道吗？\n\n擅自操作供电企业的计量装置（包括负\n荷管理装置）的居民用户，应每次承担\n500元的违约使用电费。");                    break;            }                    }            break;        case 5:        {            switch(currentLevel){                case 1:zhidaoWord->setString("你知道吗？\n\n输电线路可分为两大类，即架空线路和\n电力电缆线路，架空线路是将导线、避\n雷线架设在杆塔上，它是由导线、地线、\n杆塔、绝缘子、金具等元件组成；电\n缆线路则是由电力电缆和电缆接头组成。");                    break;                case 2:zhidaoWord->setString("你知道吗？\n配电线路是指20千伏及以下的配电\n网中的架空线路、电缆线路及其附属设\n备等。配电设备是指20千伏及以下的\n配电网中的配电站、开闭所、箱式变电\n站、柱上变压器、柱上开关（包括柱上\n断路器、柱上负荷开关）、环网单元、\n电缆分支箱、低压配电箱、电表计量箱、\n充电桩等。");                    break;                case 3:zhidaoWord->setString("你知道吗？\n\n很多人会疑惑输变电设施周围到底有没\n有辐射。其实，我国输变电设施的电力\n频率是50赫兹，只有频率超过3000\n赫兹的电力才会以电磁波形式传播形成\n辐射。因此，大家不必担心变电站或高\n压线对健康产生影响。");                    break;                case 4:zhidaoWord->setString("你知道吗？\n\n电力网的额定电压，与其输送距离、输\n送功率有关。电压越高，输送功率越大，\n输送距离越长。");                    break;                case 5:zhidaoWord->setString("你知道吗？\n\n我国能源资源与消费呈逆向分布，因而\n决定了我国能源资源必须在全国范围内\n进行优化配置。特高压输电具有输送容\n量大、能量损耗小、占用土地少、输送\n距离长等优点，因此，我国必须发展特\n高压输电。");                    break;                case 7:zhidaoWord->setString("你知道吗？\n\n智能电网是将先进的传感量测技术、信\n息通信技术、分析决策技术、自动控制\n技术和能源电力技术相结合，并与电网\n基础设施高度集成而形成的新型现代化\n电网。");                    break;                case 8:zhidaoWord->setString("你知道吗？\n\n柔性直流输电技术是以电压源换流器、\n可关断器件和脉宽调制技术为基础的新\n一代输电技术。");                    break;                case 9:zhidaoWord->setString("你知道吗？\n\n分布式发电是指相对小型的发电/储能装\n置布置在用户现场或附近的发电/功能方\n式。");                    break;                case 10:zhidaoWord->setString("你知道吗？\n\n微电网是由分布式发电系统、储能系统\n和负荷等构成，可同时提供电能和热能\n的网络。");                    break;                case 12:zhidaoWord->setString("你知道吗？\n\n坚强智能电网的三个基本技术特征是：\n信息化、自动化、互动化。");                    break;            }                    }            break;        case 6:        {            switch(currentLevel){                case 1:zhidaoWord->setString("你知道吗？\n\n长期以来，世界能源发展过度依赖化石\n能源，导致资源紧张、气候变化、环境\n污染等问题日益突出，形势十分严峻。\n用清洁能源替代化石能源，是人类社会\n发展的必然。");                                        break;                case 2:zhidaoWord->setString("你知道吗？\n\n清洁替代，是指在能源开发上，以清洁\n能源替代化石能源，走低碳绿色发展道\n路;电能替代，是指在能源消费上，以电\n能替代煤炭、石油、天然气等化石能源\n的直接消费。");                                        break;                case 3:zhidaoWord->setString("你知道吗？\n\n温室气体指的是大气中能吸收地面反射\n的太阳辐射，并重新发射辐射的一些气\n体。化石能源燃烧是全球温室气体排放\n的主要来源。");                                        break;                case 4:zhidaoWord->setString("你知道吗？\n\n全球能源互联网是以特高压电网为骨干\n网架（通道），以输送清洁能源为主导，\n全球互联泛在的坚强智能电网。");                                        break;                case 5:zhidaoWord->setString("你知道吗？\n\n在德国柏林举行的2013国际智能电网\n论坛上，中国特高压输电标准被定为国\n际标准。");                                        break;                case 7:zhidaoWord->setString("你知道吗？\n\n潮汐能是利用海水涨落及潮水流动所产\n生的能量，目前世界最大的潮汐发电厂\n是韩国建造的始华湖潮汐发电厂。");                                        break;                case 8:zhidaoWord->setString("你知道吗？\n\n目前全球只有美国等少数国家实现了非\n常规油气的大规模开发，而由于地质条\n件等原因，中国页岩气的开采成本是美\n国的2～3倍。");                                        break;                case 9:zhidaoWord->setString("你知道吗？\n\n构建全球能源互联网主要包括洲内联网、\n洲际联网和全球互联三个发展阶段。");                                        break;                case 10:zhidaoWord->setString("你知道吗？\n\n特高压和智能电网发展已被纳入中国国\n民经济和社会发展规划、国家能源规划\n及相关专项规划，成为国家能源发展的\n战略重点，有力地推动了电网创新实践。");                                        break;                case 12:zhidaoWord->setString("你知道吗？\n\n能源问题，是国际政治、经济、外交、\n国防、气候变化博弈的焦点，解决它需要\n国与国的合作，人与人的分享，需要\n一个漫长而曲折的过程。但，千里之行\n始于足下。");                                        break;            }                    }            break;    }    return true;}