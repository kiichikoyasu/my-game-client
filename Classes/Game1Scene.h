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
    
    CC_SYNTHESIZE(cocos2d::Vector<Icon *>, _icons, Icons)
    CREATE_FUNC(Game1);
};


#endif /* defined(__MyGame__Game1Scene__) */
