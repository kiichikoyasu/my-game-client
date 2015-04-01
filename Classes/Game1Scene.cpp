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
#include <algorithm>
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;
using namespace cocos2d::network;
using namespace rapidjson;

const int HORIZONTAL_COUNT = 7;
const int VERTICAL_COUNT = 9;
const int PETTERN_SIZE = 3;

Scene* Game1::createScene(){
    auto scene = Scene::create();
    auto layer = Game1::create();
    scene->addChild(layer);
    return scene;
}

Game1::Game1()
: _icons(NULL)
, _gameState(GameState::NONE)
, _iconPattern(NULL)
, _currentIcon(NULL)
, selectingIcon(0)
, score(0){
    
}

Game1::~Game1(){
    CC_SAFE_RELEASE_NULL(_currentIcon);
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
            _icons.pushBack(sprite);
            this->addChild(sprite);
        }
    }
    
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = [&](Touch* touch, Event* event){
        auto position = touch->getLocation();
        auto icon = this->getIconAtByWorld(position);
        
        if(icon != nullptr){
//            log("touch bigan icon %f, %f", icon->getIconPosition().x, icon->getIconPosition().y);
            
            icon->setState(Icon::State::TOUCHED);
            _currentIcon = icon;
            _iconPattern.push_back(icon->getKind());
            _gameState = GameState::SELECT;
            
            return true;
        }
        
        return false;
    };
    
    listener->onTouchMoved = [&](Touch* touch, Event* event){
        auto position = touch->getLocation();
        auto icon = this->getIconAtByWorld(position);
        
        if(icon != nullptr){
//            log("touch moved icon %f, %f", icon->getIconPosition().x, icon->getIconPosition().y);
//            log("gameState is %u", _gameState);
            switch(_gameState){
                case GameState::NONE:
                    //何も反応しない
                    break;
                case GameState::SELECT:
                    if(icon == _currentIcon){
                        //前の時と同じアイコンなので何もしない
                    }else{
                        //違うアイコンに移った
                        _currentIcon = icon;
                        
                        if(_iconPattern.back() == icon->getKind()  || std::find(_iconPattern.begin(), _iconPattern.end(), icon->getKind()) != _iconPattern.end()){
                            //もうすでに選択していたアイコンをパターンとして選択してしまったら無効なのでゲーム状態を戻す
                            this->clearFieldState();
                        }else{
                            //新しいアイコンを選択した
                            _iconPattern.push_back(icon->getKind());
                            if(_iconPattern.size() == PETTERN_SIZE){
                                //3種類選んだのでゲーム開始
                                _gameState = GameState::PLAYING;
                                
                                _currentIcon->setState(Icon::State::TOUCHED);
                            }
                            //それ以外は3種類選ぶまで選んでもらう
                        }
                    }
                    break;
                case GameState::PLAYING:
                    if(icon == _currentIcon){
                        //前の時と同じアイコンなので何もしない
                    }else{
                        //違うアイコンに移った
                        if(icon->getState() == Icon::State::NONE){
                            //初めて触ったアイコン
                            //パターン通りか調べる
                            if(icon->getKind() == _iconPattern.at(selectingIcon % PETTERN_SIZE)){
                                //パターン通り
                                selectingIcon++;
                                score += 30 * selectingIcon;
                                _currentIcon = icon;
                                _currentIcon->setState(Icon::State::TOUCHED);
                            }else{
                                //パターンとは違う
                                //ゲーム終了
//                                log("score : %d", score);
                                this->finishGame1();
                                _gameState = GameState::NONE;
                                score = 0;
                                selectingIcon = 0;
                                _iconPattern.clear();
                                _currentIcon = NULL;
                                for(auto icon : _icons){
                                    icon->setState(Icon::State::NONE);
                                }
                            }
                        }else{
                            //すでに触っていたアイコンだった
                            //ゲーム終了
//                            log("score : %d", score);
                            this->finishGame1();
                            _gameState = GameState::NONE;
                            score = 0;
                            selectingIcon = 0;
                            _iconPattern.clear();
                            _currentIcon = NULL;
                            for(auto icon : _icons){
                                icon->setState(Icon::State::NONE);
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    };
    
    listener->onTouchEnded = [&](Touch* touch, Event* event){
        auto position = touch->getLocation();
        auto icon = this->getIconAtByWorld(position);

        if(icon != nullptr){
            switch(_gameState){
                case GameState::NONE:
                case GameState::SELECT:
                    // パターンの選択途中もしくは選択に失敗しているので、初期化する
                    this->clearFieldState();
                    break;
                case GameState::PLAYING:
                    //ゲーム終了
                    this->finishGame1();
                    break;
                default:
                    break;
            }
        }
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    return true;
}

Icon* Game1::getIconAt(const cocos2d::Vec2& position){
    for(auto& icon : _icons){
        if(position.equals(icon->getIconPosition())) {
            return icon;
        }
    }
    return nullptr;
}

Icon* Game1::getIconAtByWorld(const cocos2d::Vec2& worldPosition){
    for(auto& icon : _icons){
        if(icon->convertToGridSpace(worldPosition).equals(icon->getIconPosition())){
            return icon;
        }
    }
    return nullptr;
}

void Game1::clearFieldState(){
    _gameState = GameState::NONE;
    for(auto icon : _icons){
        icon->setState(Icon::State::NONE);
    }
    _iconPattern.clear();
    _currentIcon = NULL;
}

void Game1::finishGame1(){
    //時間がなくて名前をつけるところを実装できなかったので固定
    std::string name = "kiichi";
    
    // jsonの作成
    Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    
    rapidjson::Value object(rapidjson::kObjectType);
    object.AddMember<int>("point", score, allocator);
    object.AddMember<const char*>("name", name.c_str(), allocator);
    
    document.AddMember("ranking", object, allocator);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    
    const char* postData = buffer.GetString();
    
    log("json %s", postData);
    
    //ネットワークの準備
    HttpRequest* request = new HttpRequest();
    std::string url = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    url = "http://localhost:3000/ranking";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    url = "http://10.0.2.2:3000/ranking";
#endif
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::POST);
    request->setResponseCallback([](HttpClient* client,
                                    HttpResponse* response){
        log("responseCode:%ld %s", response->getResponseCode(), response->getHttpRequest()->getUrl());
        
        std::vector<char>* data = response->getResponseData();
        std::string result(data->begin(), data->end());
        log("responseData:%s", result.c_str());
        
        //todo Rankingに飛ぶ
    });
    
    std::vector<std::string> header;
    header.push_back("Content-Type: application/json");
    request->setHeaders(header);
    
    request->setRequestData(postData, strlen(postData));
    
    HttpClient::getInstance()->send(request);
    request->release();
}
