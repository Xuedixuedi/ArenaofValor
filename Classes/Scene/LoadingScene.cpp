#include "LoadingScene.h"
#include "HelloWorldScene.h"


cocos2d::Scene* LoadingScene::createScene()
{
	return LoadingScene::create();
}


bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}


	return true;
}

void LoadingScene::onEnterTransitionDidFinish()
{
	LoadingAnimation();
}

void LoadingScene::LoadingAnimation()
{
	String heroName = "HouYi";

	auto animation_00 = Animation::create();
	animation_00->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sup1.png", heroName.getCString(), heroName.getCString()));
	animation_00->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sup2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_00, StringUtils::format("%sMoveUp", heroName.getCString()));

	auto animation_01 = Animation::create();
	animation_01->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%supLeft1.png", heroName.getCString(), heroName.getCString()));
	animation_01->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%supLeft2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_01, StringUtils::format("%sMoveUpLeft", heroName.getCString()));

	auto animation_02 = Animation::create();
	animation_02->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%supRight1.png", heroName.getCString(), heroName.getCString()));
	animation_02->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%supRight2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_02, StringUtils::format("%sMoveUpRight", heroName.getCString()));

	auto animation_03 = Animation::create();
	animation_03->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sleft1.png", heroName.getCString(), heroName.getCString()));
	animation_03->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sleft2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_03, StringUtils::format("%sMoveLeft", heroName.getCString()));

	auto animation_04 = Animation::create();
	animation_04->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sright1.png", heroName.getCString(), heroName.getCString()));
	animation_04->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sright2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_04, StringUtils::format("%sMoveRight", heroName.getCString()));

	auto animation_05 = Animation::create();
	animation_05->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdown1.png", heroName.getCString(), heroName.getCString()));
	animation_05->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdown2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_05, StringUtils::format("%sMoveDown", heroName.getCString()));

	auto animation_06 = Animation::create();
	animation_06->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdownLeft1.png", heroName.getCString(), heroName.getCString()));
	animation_06->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdownLeft2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_06, StringUtils::format("%sMoveDownLeft", heroName.getCString()));

	auto animation_07 = Animation::create();
	animation_07->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdownRight1.png", heroName.getCString(), heroName.getCString()));
	animation_07->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdownRight2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_07, StringUtils::format("%sMoveDownRight", heroName.getCString()));

	auto animation_08 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_08->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackUp%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_08->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sup1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_08, StringUtils::format("%sAttackUp", heroName.getCString()));

	auto animation_09 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_09->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackDown%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_09->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sdown1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_09, StringUtils::format("%sAttackDown", heroName.getCString()));

	auto animation_10 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_10->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackLeft%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_10->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sleft1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_10, StringUtils::format("%sAttackLeft", heroName.getCString()));

	auto animation_11 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_11->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackRight%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_11->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sright1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_11, StringUtils::format("%sAttackRight", heroName.getCString()));

	auto animation_12 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_12->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackUpRight%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_12->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%supRight1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_12, StringUtils::format("%sAttackUpRight", heroName.getCString()));

	auto animation_13 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_13->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackUpLeft%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_13->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%supleft1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_13, StringUtils::format("%sAttackUpLeft", heroName.getCString()));

	auto animation_14 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_14->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackDownRight%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_14->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sdownRight1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_14, StringUtils::format("%sAttackDownRight", heroName.getCString()));

	auto animation_15 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_15->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackDownLeft%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_15->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sdownLeft1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_15, StringUtils::format("%sAttackDownLeft", heroName.getCString()));


	heroName = "YaSe";

	auto animation_16 = Animation::create();
	animation_16->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sup1.png", heroName.getCString(), heroName.getCString()));
	animation_16->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sup2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_16, StringUtils::format("%sMoveUp", heroName.getCString()));

	auto animation_17 = Animation::create();
	animation_17->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%supLeft1.png", heroName.getCString(), heroName.getCString()));
	animation_17->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%supLeft2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_17, StringUtils::format("%sMoveUpLeft", heroName.getCString()));

	auto animation_18 = Animation::create();
	animation_18->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%supRight1.png", heroName.getCString(), heroName.getCString()));
	animation_18->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%supRight2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_18, StringUtils::format("%sMoveUpRight", heroName.getCString()));

	auto animation_19 = Animation::create();
	animation_19->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sleft1.png", heroName.getCString(), heroName.getCString()));
	animation_19->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sleft2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_19, StringUtils::format("%sMoveLeft", heroName.getCString()));

	auto animation_20 = Animation::create();
	animation_20->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sright1.png", heroName.getCString(), heroName.getCString()));
	animation_20->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sright2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_20, StringUtils::format("%sMoveRight", heroName.getCString()));

	auto animation_21 = Animation::create();
	animation_21->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdown1.png", heroName.getCString(), heroName.getCString()));
	animation_21->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdown2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_21, StringUtils::format("%sMoveDown", heroName.getCString()));

	auto animation_22 = Animation::create();
	animation_22->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdownLeft1.png", heroName.getCString(), heroName.getCString()));
	animation_22->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdownLeft2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_22, StringUtils::format("%sMoveDownLeft", heroName.getCString()));

	auto animation_23 = Animation::create();
	animation_23->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdownRight1.png", heroName.getCString(), heroName.getCString()));
	animation_23->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdownRight2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_23, StringUtils::format("%sMoveDownRight", heroName.getCString()));

	auto animation_24 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_24->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackUp%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_24->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sup1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_24, StringUtils::format("%sAttackUp", heroName.getCString()));

	auto animation_25 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_25->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackDown%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_25->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sdown1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_25, StringUtils::format("%sAttackDown", heroName.getCString()));

	auto animation_26 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_26->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackLeft%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_26->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sleft1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_26, StringUtils::format("%sAttackLeft", heroName.getCString()));

	auto animation_27 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_27->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackRight%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_27->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sright1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_27, StringUtils::format("%sAttackRight", heroName.getCString()));

	auto animation_28 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_28->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackUpRight%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_28->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%supRight1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_28, StringUtils::format("%sAttackUpRight", heroName.getCString()));

	auto animation_29 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_29->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackUpLeft%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_29->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%supleft1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_29, StringUtils::format("%sAttackUpLeft", heroName.getCString()));

	auto animation_30 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_30->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackDownRight%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_30->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sdownRight1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_30, StringUtils::format("%sAttackDownRight", heroName.getCString()));

	auto animation_31 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_31->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackDownLeft%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_31->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sdownLeft1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_31, StringUtils::format("%sAttackDownLeft", heroName.getCString()));

	heroName = "DaJi";

	auto animation_32 = Animation::create();
	animation_32->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%supLeft1.png", heroName.getCString(), heroName.getCString()));
	animation_32->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%supLeft2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_32, StringUtils::format("%sMoveUpLeft", heroName.getCString()));

	auto animation_33 = Animation::create();
	animation_33->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%supRight1.png", heroName.getCString(), heroName.getCString()));
	animation_33->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%supRight2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_33, StringUtils::format("%sMoveUpRight", heroName.getCString()));

	auto animation_34 = Animation::create();
	animation_34->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sleft1.png", heroName.getCString(), heroName.getCString()));
	animation_34->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sleft2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_34, StringUtils::format("%sMoveLeft", heroName.getCString()));

	auto animation_35 = Animation::create();
	animation_35->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sright1.png", heroName.getCString(), heroName.getCString()));
	animation_35->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sright2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_35, StringUtils::format("%sMoveRight", heroName.getCString()));

	auto animation_36 = Animation::create();
	animation_36->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdown1.png", heroName.getCString(), heroName.getCString()));
	animation_36->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdown2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_36, StringUtils::format("%sMoveDown", heroName.getCString()));

	auto animation_37 = Animation::create();
	animation_37->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdownLeft1.png", heroName.getCString(), heroName.getCString()));
	animation_37->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdownLeft2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_37, StringUtils::format("%sMoveDownLeft", heroName.getCString()));

	auto animation_38 = Animation::create();
	animation_38->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdownRight1.png", heroName.getCString(), heroName.getCString()));
	animation_38->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdownRight2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_38, StringUtils::format("%sMoveDownRight", heroName.getCString()));

	auto animation_39 = Animation::create();
	animation_39->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sup1.png", heroName.getCString(), heroName.getCString()));
	animation_39->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sup2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_39, StringUtils::format("%sMoveUp", heroName.getCString()));

	auto animation_40 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_40->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackUp%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_40->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sup1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_40, StringUtils::format("%sAttackUp", heroName.getCString()));

	auto animation_41 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_41->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackDown%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_41->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sdown1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_41, StringUtils::format("%sAttackDown", heroName.getCString()));

	auto animation_42 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_42->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackLeft%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_42->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sleft1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_42, StringUtils::format("%sAttackLeft", heroName.getCString()));

	auto animation_43 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_43->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackRight%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_43->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sright1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_43, StringUtils::format("%sAttackRight", heroName.getCString()));

	auto animation_44 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_44->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackUpRight%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_44->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%supRight1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_44, StringUtils::format("%sAttackUpRight", heroName.getCString()));

	auto animation_45 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_45->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackUpLeft%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_45->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%supleft1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_45, StringUtils::format("%sAttackUpLeft", heroName.getCString()));

	auto animation_46 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_46->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackDownRight%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_46->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sdownRight1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_46, StringUtils::format("%sAttackDownRight", heroName.getCString()));

	auto animation_47 = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		animation_47->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sAttackDownLeft%d.png", heroName.getCString(), heroName.getCString(), i));
	}
	animation_47->addSpriteFrameWithFile(StringUtils::format("pictures\\hero\\%s\\%sdownLeft1.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_47, StringUtils::format("%sAttackDownLeft", heroName.getCString()));


	String skillAnimationName = "HouYiSkill2";
	auto skillAnimation = Animation::create();
	for (int i = 1; i < 5; ++i)
	{
		skillAnimation->addSpriteFrameWithFile(StringUtils::format("pictures/hero/HouYi/%s%d.png", skillAnimationName.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(skillAnimation, skillAnimationName.getCString());



	String soldierType = "RedMelee";

	auto animation_51 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_51->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sUp%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_51, StringUtils::format("%sMoveUp", soldierType.getCString()));

	auto animation_52 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_52->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sDown%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_52, StringUtils::format("%sMoveDown", soldierType.getCString()));

	auto animation_53 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_53->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sLeft%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_53, StringUtils::format("%sMoveLeft", soldierType.getCString()));

	auto animation_54 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_54->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sRight%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_54, StringUtils::format("%sMoveRight", soldierType.getCString()));

	auto animation_55 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_55->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackUp%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_55->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sUp1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_55, StringUtils::format("%sAttackUp", soldierType.getCString()));

	auto animation_56 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_56->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackDown%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_56->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sDown1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_56, StringUtils::format("%sAttackDown", soldierType.getCString()));

	auto animation_57 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_57->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackLeft%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_57->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sLeft1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_57, StringUtils::format("%sAttackLeft", soldierType.getCString()));

	auto animation_58 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_58->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackRight%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_58->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sRight1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_58, StringUtils::format("%sAttackRight", soldierType.getCString()));


	soldierType = "RedRemote";

	auto animation_59 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_59->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sUp%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_59, StringUtils::format("%sMoveUp", soldierType.getCString()));

	auto animation_60 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_60->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sDown%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_60, StringUtils::format("%sMoveDown", soldierType.getCString()));

	auto animation_61 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_61->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sLeft%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_61, StringUtils::format("%sMoveLeft", soldierType.getCString()));

	auto animation_62 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_62->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sRight%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_62, StringUtils::format("%sMoveRight", soldierType.getCString()));

	auto animation_63 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_63->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackUp%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_63->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sUp1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_63, StringUtils::format("%sAttackUp", soldierType.getCString()));

	auto animation_64 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_64->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackDown%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_64->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sDown1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_64, StringUtils::format("%sAttackDown", soldierType.getCString()));

	auto animation_65 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_65->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackLeft%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_65->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sLeft1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_65, StringUtils::format("%sAttackLeft", soldierType.getCString()));

	auto animation_66 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_66->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackRight%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_66->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sRight1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_66, StringUtils::format("%sAttackRight", soldierType.getCString()));

	soldierType = "BlueRemote";

	auto animation_67 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_67->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sUp%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_67, StringUtils::format("%sMoveUp", soldierType.getCString()));

	auto animation_68 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_68->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sDown%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_68, StringUtils::format("%sMoveDown", soldierType.getCString()));

	auto animation_69 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_69->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sLeft%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_69, StringUtils::format("%sMoveLeft", soldierType.getCString()));

	auto animation_70 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_70->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sRight%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_70, StringUtils::format("%sMoveRight", soldierType.getCString()));

	auto animation_71 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_71->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackUp%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_71->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sUp1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_71, StringUtils::format("%sAttackUp", soldierType.getCString()));

	auto animation_72 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_72->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackDown%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_72->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sDown1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_72, StringUtils::format("%sAttackDown", soldierType.getCString()));

	auto animation_73 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_73->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackLeft%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_73->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sLeft1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_73, StringUtils::format("%sAttackLeft", soldierType.getCString()));

	auto animation_74 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_74->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackRight%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_74->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sRight1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_74, StringUtils::format("%sAttackRight", soldierType.getCString()));

	soldierType = "BlueMelee";

	auto animation_75 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_75->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sUp%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_75, StringUtils::format("%sMoveUp", soldierType.getCString()));

	auto animation_76 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_76->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sDown%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_76, StringUtils::format("%sMoveDown", soldierType.getCString()));

	auto animation_77 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_77->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sLeft%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_77, StringUtils::format("%sMoveLeft", soldierType.getCString()));

	auto animation_78 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_78->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sRight%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_78, StringUtils::format("%sMoveRight", soldierType.getCString()));

	auto animation_79 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_79->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackUp%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_79->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sUp1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_79, StringUtils::format("%sAttackUp", soldierType.getCString()));

	auto animation_80 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_80->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackDown%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_80->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sDown1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_80, StringUtils::format("%sAttackDown", soldierType.getCString()));

	auto animation_81 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_81->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackLeft%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_81->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sLeft1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_81, StringUtils::format("%sAttackLeft", soldierType.getCString()));

	auto animation_82 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_82->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackRight%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_82->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sRight1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_82, StringUtils::format("%sAttackRight", soldierType.getCString()));

	changeScene();
}

void LoadingScene::changeScene()
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}
