//
//  Game1Scene.h
//  MyGame
//
//  Created by 子安貴一 on 2015/04/01.
//
//

#ifndef __MyGame__Game1Scene__
#define __MyGame__Game1Scene__

#include <stdio.h>
#include "cocos2d.h"
#include "Icon.h"

class Game1 : public cocos2d::Layer
{
protected:
    Game1();
    virtual ~Game1();
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    /**
     * グリッド座標上でのクッキーの取り出し
     * 該当しない場合はnullptr
     */
    Icon* getIconAt(const cocos2d::Vec2& position);
    
    /**
     * 画面上でのクッキーの取り出し
     * 該当しない場合はnullptr
     */
    Icon* getIconAtByWorld(const cocos2d::Vec2& worldPosition);
    
    enum GameState{
        //何もしていない状態
        NONE,
        //最初のパターンを選んでいる段階
        SELECT,
        //選んだパターン通りに指を動かしている段階
        PLAYING
    };
    
    CC_SYNTHESIZE(cocos2d::Vector<Icon *>, _icons, Icons);
    CC_SYNTHESIZE(GameState, _gameState, GameState);
    CC_SYNTHESIZE(std::vector<Icon::Kind>, _iconPattern, IconPattern);
    CC_SYNTHESIZE_RETAIN(Icon *, _currentIcon, CurrentIcon);
    CREATE_FUNC(Game1);
private:
    int score;
    //選んだアイコンの数
    int selectingIcon;
    
    void clearFieldState();
    
    void finishGame1();
};


#endif /* defined(__MyGame__Game1Scene__) */
