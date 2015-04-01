//
//  Icon.h
//  MyGame
//
//  Created by 子安貴一 on 2015/04/01.
//
//

#ifndef __MyGame__Icon__
#define __MyGame__Icon__

#include <stdio.h>
#include "cocos2d.h"

class Icon :public cocos2d::Sprite{
protected:
    Icon();
    virtual ~Icon();
public:
    
    enum class Kind{
        TWITTER,
        CANDYBAR,
        CAMERA,
        COUNT
    };
    
    // アイコンが触られているかどうかの状態
    enum class State{
        //タッチされていない状態
        NONE,
        //タッチされている状態
//        TOUCHING,
        //タッチされたことがあるが今はタッチされていない状態
        TOUCHED
    };
    
    /**
     * ステージ上の座標をグリッド座標に変換
     */
    cocos2d::Vec2 convertToGridSpace(const cocos2d::Vec2& stagePosition);
    
    
    /**
     * グリッド座標をステージ座標に変換
     */
    cocos2d::Vec2 convertToStageSpace(const cocos2d::Vec2& gridPosition);
    
    /** 
     * アイコンのグリッド座標をセット
     */
    void setIconPosition(const cocos2d::Vec2& position);
    
    void adjustPosition();
    
    
    CC_SYNTHESIZE(State, _state, State);
    CC_SYNTHESIZE(Kind, _kind, Kind);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(cocos2d::Vec2, _iconPosition, IconPosition);
    
    virtual bool init();
    
    CREATE_FUNC(Icon);
};

#endif /* defined(__MyGame__Icon__) */
