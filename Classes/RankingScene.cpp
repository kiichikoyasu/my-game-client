//
//  RankingScene.cpp
//  MyGame
//
//  Created by 子安貴一 on 2015/03/31.
//
//

#include "RankingScene.h"
#include "network/HttpClient.h"

USING_NS_CC;
using namespace cocos2d::network;

Scene* Ranking::createScene(){
    
    auto scene = Scene::create();
    auto layer = Ranking::create();
    scene->addChild(layer);
    return scene;
}

Ranking::Ranking(){
    
}

Ranking::~Ranking(){
    
}

bool Ranking::init(){
    
    if(!Layer::init()){
        return false;
    }
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto request = new HttpRequest();
    std::string url = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    request->setUrl("http://localhost:3000/ranking");
    url = "http://localhost:3000/ranking";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    request->setUrl("http://10.0.2.2:3000/ranking");
    url = "http://10.0.2.2:3000/ranking";
#endif
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback([this](HttpClient* client, HttpResponse* response){
       
        log("responseCode:%ld %s", response->getResponseCode(), response->getHttpRequest()->getUrl());
        
        std::vector<char>* data = response->getResponseData();
        std::string result(data->begin(), data->end());
        log("responseData:%s", result.c_str());
        
    });
    
    auto client = HttpClient::getInstance();
    client->enableCookies(NULL);
    client->send(request);
    request->release();
    
    return true;

}