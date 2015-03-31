//
//  RankingScene.h
//  MyGame
//
//  Created by 子安貴一 on 2015/03/31.
//
//

#ifndef __RankingScene__
#define __RankingScene__

#include <stdio.h>
#include "cocos2d.h"

class Ranking : public cocos2d::Layer
{
protected:
    Ranking();
    virtual ~Ranking();
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(Ranking);
};

#endif /* defined(__MyGame__RankingScene__) */
