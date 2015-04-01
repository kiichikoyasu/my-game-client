//
//  Game1Scene.cpp
//  MyGame
//
//  Created by 子安貴一 on 2015/04/01.
//
//

#include "Game1Scene.h"
#include "network/HttpClient.h"
#include "Icon.h"

USING_NS_CC;
using namespace cocos2d::network;

const int HORIZONTAL_COUNT = 7;
const int VERTICAL_COUNT = 9;

Scene* Game1::createScene(){
    auto scene = Scene::create();
    auto layer = Game1::create();
    scene->addChild(layer);
    return scene;
}

Game1::Game1()
: _icons(NULL){
    
}

Game1::~Game1(){
}

bool Game1::init(){

    if(!Layer::init()){
        return false;
    }
    
    auto director = Director::getInstance();
    
    Size visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    
    
    for(int i = 0; i < HORIZONTAL_COUNT; ++i){
        for(int j = 1; j < VERTICAL_COUNT; ++j){
            auto sprite = Icon::create();
            sprite->setIconPosition(Vec2(i, j));
            sprite->adjustPosition();
            this->addChild(sprite);
        }
    }
    
    
    return true;
}