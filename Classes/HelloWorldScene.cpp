﻿/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// 初期化
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

	// 乱数の初期化
	//Random r = new Random();
	srand(time(nullptr));

	//for (int i = 0; i < 5; i++)
	//{
	//	sprite[i] = Sprite::create("neko.png");
	//	this->addChild(sprite[i]);
	//	sprite[i]->setPosition(Vec2(100*i, visibleSize.height / 2.0f));
	//	sprite[i]->setScale(0.1f);

	//	float mx, my;

	//	// -300～+300の乱数
	//	mx = (float)rand()/ RAND_MAX * 600 -300;
	//	my = (float)rand()/ RAND_MAX * 600 -300;

	//	MoveBy* action1 = MoveBy::create(2.0f, Vec2(mx, my));
	//	sprite[i]->runAction(action1);
	//}

	//////////////////sprite
	sprite = Sprite::create("neko.png");
	this->addChild(sprite);
	sprite->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	sprite->setScale(0.1f);

	//////////////////sprite2
	sprite2 = Sprite::create("lion.jpg");
	this->addChild(sprite2);
	sprite2->setPosition(Vec2(300, 300));
	sprite2->setScale(0.1f);

	//////////////////action1
	JumpBy* action1 = JumpBy::create(1.0f, Vec2(300, 0), 300, 1);
	sprite->runAction(action1->clone());
	sprite2->runAction(action1->clone());

	////JumpBy* action1 = JumpBy::create(2.0f, Vec2(-300, -300), 300,2);
	////EaseBounceInOut* action2 = EaseBounceInOut::create(action1);

	//ScaleTo* action1 = ScaleTo::create(1.0f, 5.0f);
	//JumpTo* action1 = JumpTo::create(1.5f, Vec2(200, 100), 500.0f, 2);
	//sprite->setOpacity(0);
	//FadeIn* action1 = FadeIn::create(1.0f);
	//ccBezierConfig conf;
	//conf.controlPoint_1 = Vec2(500, 500);
	//conf.controlPoint_2 = Vec2(500, 100);
	//conf.endPosition = Vec2(200, 100);
	//BezierTo* action1 = BezierTo::create(3.0f, conf);

	// 完全不透明
	//sprite->setOpacity(255);

	// 画像の左下が(0,0)
	// 画像の右上が(1,0)の座標系で
	// 基準点を指定する
	//sprite->setAnchorPoint(Vec2(0.0f, 1.0f));

	//                       R  G  B
	//sprite->setColor(Color3B(0, 0, 255));

	// 左右反転
	//sprite->setFlippedX(true);

	//                      開始X  Y  　W   H
	//sprite->setTextureRect(Rect(0, 32, 32, 32));

	//sprite2 = Sprite::create("lion.jpg");
	//this->addChild(sprite2);
	//sprite2->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	//sprite2->setScale(2.0f);

	// updateを有効化する
	this->scheduleUpdate();


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::update(float delta)
{

}