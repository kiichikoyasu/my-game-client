//
//  Icon.cpp
//  MyGame
//
//  Created by 子安貴一 on 2015/04/01.
//
//

#include "Icon.h"
#include <random>

USING_NS_CC;

Icon::Icon(){
    
}

Icon::~Icon(){
    
}

bool Icon::init(){
    
    std::random_device device;
    auto engine = std::mt19937(device());
    auto dist = std::uniform_int_distribution<>(0, (int)Icon::Kind::COUNT - 1);
    
    auto kind = dist(engine);
    auto pictureName = "";
    
    switch(static_cast<Icon::Kind>(kind)){
        case Icon::Kind::TWITTER:
            pictureName = "Twitter.png";
            break;
        case Icon::Kind::CANDYBAR:
            pictureName = "CandyBar.png";
            break;
        case Icon::Kind::CAMERA:
            pictureName = "Camera.png";
            break;
        default:
            break;
    }
    
    if(!Sprite::initWithFile(pictureName)){
        return false;
    }
    
    this->setScale(0.2098);

    return true;
}

Vec2 Icon::convertToGridSpace(const cocos2d::Vec2& stagePosition){
    
    auto size = this->getContentSize() * this->getScale();
    
    auto x = floor(stagePosition.x / size.width);
    auto y = floor(stagePosition.y / size.height);
    
    return std::move(Vec2(x, y));
}

Vec2 Icon::convertToStageSpace(const cocos2d::Vec2& gridPosition){
    
    auto size = this->getContentSize() * this->getScale();
    
    return std::move((gridPosition + Vec2::ONE * 0.5) * size.height);
    
}

void Icon::setIconPosition(const Vec2& position){
    _iconPosition = position;
}

void Icon::adjustPosition(){
    auto position = _iconPosition;
    
    this->setPosition(Icon::convertToStageSpace(position));
}

