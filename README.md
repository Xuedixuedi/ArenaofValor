

1. 

   # Arena of Valor项目说明文档

   > 同济大学软件学院2019年面向对象程序设计课程大项目

   ## 项目信息

   - 项目选题：**王者荣耀（2D）**

   - 项目成员：

     - 1752459 曾泽
     - 1751926 王泽钜
     - 1752985 刘雪迪
     - 1750655 李嘉杰

   - 项目Github地址：<https://github.com/Xuedixuedi/ArenaofValor>

   - 项目进度时间线：

     ![Gant](http://r.photo.store.qq.com/psb?/V1021wgV0HsjE6/sDZZ2M6dQymreB66Kl4kBmIZm1AZ0Ktp3BeMQrU*B0o!/r/dMMAAAAAAAAA)

     ![未命名文件.png](https://i.loli.net/2019/07/01/5d19d162d561167050.png)

   ## 项目开发文档

   - 选用引擎：**Cocos2d-x 3.17.2**

   - 辅助软件：Tiled Map Editor 1.1.5、Adobe Photoshop CC 2019

   - 支持平台：Windows

   - 小组分工：

     |  姓名  |                           分工                           | 贡献比例 |
     | :----: | :------------------------------------------------------: | :------: |
     |  曾泽  | 英雄、野怪、技能飞行物、小兵及英雄AI、装备系统、战绩系统 |   100%   |
     | 王泽钜 |  遥杆、英雄、英雄技能、游戏场景逻辑、鼠标键盘交互、网络  |   100%   |
   | 刘雪迪 |           开始界面交互、素材及数据文件、地图、           |   100%   |
     | 李嘉杰 |                 小兵寻路算法、跨平台研究                 |   100%   |

   - 类的设计及继承关系：

     ![img](http://m.qpic.cn/psb?/V1021wgV0HsjE6/Xju3IHhg632Jyq2TVhj*4TImCSqedtAP1krWUyBfc9E!/b/dLYAAAAAAAAA&bo=.wWAAlMGpQIDCaI!&rf=viewer_4)

   - 评分项完成度

     - 基础功能
       - [x] 支持联网
       - [x] 1v1地图
       - [x] 妲己、亚瑟、后羿三种英雄类型
       - [x] 支持近程、远程小兵
       - [x] 支持以补兵、推塔、击败英雄、时间方式获得金钱
       - [x] 支持经验、等级系统
       - [x] 支持装备系统及装备查看
       - [x] 支持战绩及英雄当前属性查看
       - [x] 支持小兵、防御塔AI
       - [x] 支持电脑AI
       - [x] 支持拖拽轮盘及WASD操作英雄
     - 进阶功能
       - [x] 支持聊天
       - [x] 支持多人对决
       - [x] 支持三种野怪
       - [x] 三种英雄各支持三个主动技能及一个被动技能
       - [x] 支持技能等级成长系统
       - [x] 支持泉水
       - [x] 支持生命值及法力值等级成长系统
     - C++新特性
       - [x] 类型推断
       - [x] 基于范围的for循环
       - [x] 智能指针
       - [x] Lambda表达式
     - 其他亮点
       - [x] 游戏还原度高
         - 英雄形象、属性、技能、装备属性等与王者荣耀游戏还原度高（详情见游戏文档）
         - 普通攻击及技能伤害生效时间为投掷物到达被攻击对象时而非技能释放时
         - 使用王者荣耀原声音效，提升游戏体验
       - [x] 细节丰富，画面精致
         - 英雄及小兵普通攻击及释放技能时均有动画效果
         - 玩家在普通攻击及释放技能同时无法移动
         - 玩家及小兵普通攻击的投掷物始终指向目标
         - 释放技能鼠标出现辅助瞄准点，技能释放的方位由英雄->鼠标瞄准点向量方向决定
         - 英雄及小兵普通攻击及释放技能时保证英雄及小兵始终朝向攻击目标
         - 优化我方小兵击杀对方英雄记录为我方英雄助攻
       - [x] PLIST文件的使用
       
         + 利用PLIST文件存储英雄默认属性、英雄成长属性和技能成长属性。利用cocos2d-x读取PLIST文件的功能，将数据写入PLIST文件而非代码中，增强了数据的可读性和可修改性
       - [x] 小兵及英雄AI路径的标注工具
         + 用Python开发了小兵寻路工具，从Tiled工具生成的tmx文件提取特定图层，进行路径标记，以此代替寻路算法。![1560536076668](<http://r.photo.store.qq.com/psb?/V1021wgV0HsjE6/PQpxt15nfy3Nw1btEJQIznnkvK1eoikU5H0VTgukzDQ!/r/dMUAAAAAAAAA>)

   - 代码亮点

     1. Const.h头文件的使用

        将游戏里关于英雄、小兵、防御塔等常量属性放在`Const.h`头文件中

       ```c++
       #define TOWER_MIN_ATTACK_INTERVAL	  2
       #define TOWER_HP					      8000
       #define TOWER_ATTACK_RADIUS            500
       #define TOWER_ARMOR				      300
       #define TOWER_MAGIC_DEFNESE            100
       #define TOWER_ATTACK				      470
       ```

     2. LoadingScene 类的使用

         将游戏中需要播放的动画在打开游戏时预加载，减少游戏时的卡顿。

      ```c++
      auto animation_02 = Animation::create();
      	for (int i = 1; i < 4; ++i)
      	{
      		animation_02->addSpriteFrameWithFileName
                  (StringUtils::format("pictures\\hero\\%s\\%supRight%d.png", 
                                       heroName.getCString(), 
                                       heroName.getCString(), i));
      	}
      	AnimationCache::getInstance()->addAnimation(animation_02, 
                           StringUtils::format("%sMoveUpRight", heroName.getCString()));
      ```

     3. AI路径的标注工具

      ```python
          if mode == 0 and event == cv2.EVENT_LBUTTONDOWN:
              if (img[y][x].tolist()== COLOR_AVAI):
                  print("Point左键点击", img[y][x].tolist())
                  if pnts.count([x//MULTIPLE,y//MULTIPLE]) == 0:
                      pnts.append([x//MULTIPLE,y//MULTIPLE])
                      print(pnts)
                      #print(Graph[:len(pnts)][:len(pnts)])
                      cv2.rectangle(img, (x//MULTIPLE*MULTIPLE, y//MULTIPLE*MULTIPLE), (x//MULTIPLE*MULTIPLE+MULTIPLE, y//MULTIPLE*MULTIPLE+MULTIPLE), COLOR_POINT, -1)
                      SaveHis()
      ```

     4. 多线程的使用

      ```c++
      		boost::thread t(boost::bind(&boost::asio::io_context::run, io_context));
      		t.detach();
      ```

     5. PLIST文件的使用

      ```xml
              <key>HouYi</key>
              <dict>
                  <key>HPRecoverRate</key>
                  <integer>9</integer>
                  <key>MPRecoverRate</key>
                  <integer>4</integer>
                  <key>MovingSpeed</key>
                  <integer>360</integer>
              </dict>
      ```

   + 踩坑记录

     1. 打包发布**Release版本**时需要将原存放在**Resource**文件夹中存放plist文件和txt文件的**data**文件夹移动到**Resource**文件夹之外，否则运行游戏时会因为` abort()`函数的调用中断。

     2. 同一小组不同成员开发时应保证Visual Studio的版本相同。VS2019创建的项目转移到只有VS2017的电脑上会因平台工具集差异导致编译错误。
     3. 播放背景音乐所需要用的`SimpleAudioEngine`中调节音量大小的函数` setBackgroundMusicVolume`是空函数，若要调节背景音乐的大小需要自行补全代码。


## Arena of Valor 游戏文档

### 游戏简介

**Arena of Valor**是一款团队公平竞技多人线上战斗竞技场游戏（MOBA）游戏。支持单人人机作战、多人联机PK对战模式。

### 游戏玩法

共两位玩家，或一位玩家与电脑。其为1对1 [SOLO](https://zh.wikipedia.org/wiki/单挑)地图模式。地图为直筒型，两头各为双方玩家的复活点（泉水），水晶基地位于复活点前，基地塔前仅有一座防御塔；泉水仅提供回血回蓝效果，不提供加速增益效果；不可使用**回城**；不可使用**恢复**。队伍必须破坏路上的防御塔，而防御塔通常被放在可以抵达敌方水晶基地塔的主要路线上，当玩家独自靠近防御塔时，会承受来自防御塔的高强度攻击。且双方水晶都会定时派出小兵前往战场。每个玩家通过**杀死敌方小兵、敌方英雄或野区的中立怪物**来升级自己的英雄等级及获得金钱增益。击杀敌人也可以使自己的英雄在游戏中取得金币，以便**购买装备**来加强英雄的能力。获胜条件是**破坏敌方的水晶**。

#### 单机模式

玩家单击单机模式按钮后，自行选择我方英雄和敌方英雄。待游戏加载完毕后控制我方英雄与电脑AI对战。如果对方水晶被摧毁则我方获胜，反之电脑获胜。

#### 联机模式

玩家单击联机模式按钮后，待匹配到另一名玩家同样单击联机模式后同时跳转至选择英雄界面，待双方同时选择完英雄后进入游戏场景。按照先选好英雄的一方为蓝方，后选好英雄的一方为红方原则进行1V1对战。先摧毁对方水晶的玩家获胜。

   ### 基本操作

|              操作              |                            效果                            |
| :----------------------------: | :--------------------------------------------------------: |
|          按下`WSAD`键          |               控制我方英雄上、下、左、右移动               |
|          点击鼠标左键          |                  英雄自动选择目标普通攻击                  |
|  点击技能图标旁的 **+** 按钮   |                        对应技能升级                        |
|          按下`123`键           |                   释放英雄一、二、三技能                   |
| 当鼠标出现蓝色瞄准圈时点击鼠标 |               按英雄->鼠标的向量方向释放技能               |
|          点击金币按钮          |                        打开商店面板                        |
|    点击带物品描述的装备图标    |                          购买物品                          |
|      点击商店底部装备图标      |                        出售已购装备                        |
|       点击**消息框**按钮       |                     与对方玩家发起聊天                     |
|        点击上方菜单按钮        | 查看我方英雄与对方英雄的击杀/死亡/助攻以及我方英雄当前属性 |

### 英雄属性

   - 默认属性

| 英雄名 | 定位&攻击类型 | 回血速率 | 回蓝速率 | 移动速率 |
| :----: | :-----------: | :------: | :------: | :------: |
|  亚瑟  |   坦克&近程   |    14    |    0     |   390    |
|  妲己  |   法师&远程   |    10    |    5     |   360    |
|  后羿  |   射手&远程   |    10    |    5     |   360    |

   - 成长属性

| 英雄名 |    生命值     |    法力值    |  法术防御   |    护甲    |   物理攻击   |
| :----: | :-----------: | :----------: | :---------: | :--------: | :----------: |
|  亚瑟  | 3622+316*等级 |      0       | 50+8.5*等级 | 98+22*等级 | 164+13*等级  |
|  妲己  | 3229+186*等级 | 490+109*等级 | 50+8.5*等级 | 86+17*等级 | 170+8.5*等级 |
|  后羿  | 3182+200*等级 | 440+96*等级  | 80+8.5*等级 | 86+18*等级 | 180+16*等级  |

### 画面概览

+ 开局界面

  ![0615开局](https://i.loli.net/2019/07/01/5d19cbb49b12931083.gif)

+ 英雄移动

  ![dajimove](https://i.loli.net/2019/07/01/5d19d0d8ccca173453.gif) ![HOUYIMOVE](http://m.qpic.cn/psb?/V1021wgV0HsjE6/QSBtTdFJ183gID0ym8w73cFL8XyPZJccL5KEyrVU8c8!/b/dDYBAAAAAAAA&bo=1gDUANYA1AACOR0!&rf=viewer_4) ![YASEMOVE](https://i.loli.net/2019/07/01/5d19d1263cf3c68391.gif) 

+ 英雄释放技能

  ![DAJIATTACK_2_](https://i.loli.net/2019/07/01/5d19d0df8b40c88810.gif) ![HOUYIATTACK_2_](http://m.qpic.cn/psb?/V1021wgV0HsjE6/TB3BjXGX5oaadAXhIF6JaSDK*dZYsL6Rku81mgQ8bBg!/b/dMAAAAAAAAAA&bo=9AOSAfQDkgECmb0!&rf=viewer_4)

   

## 致谢

1. 感谢原上海市第一貂蝉（现因学业繁忙弃游）对游戏demo的用户体验提出建设性改进建议。
2. 感谢不定期出现在国康路全家。国康路coco的助教探班。
3. 感谢不厌其烦读完文档的您对本项目的资瓷。
