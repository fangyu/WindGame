// 
// PageId.h
// FirstGame
//
// Created by zhangsq on 14-9-4
//

#ifndef __FirstGame__PageId__
#define __FirstGame__PageId__

/*
 * This file defines the uniform page id shaed by game client and server
 */

namespace UniformPageId
{

enum PageId
{
        DUMMY_PAGE = -1, 				// invalid page id
        CARD_LIST  =  0,				// 卡牌列表
        GHOST_LIST =  1,				// 魂魄列表
        EMBATTLE   =  2,				// 布阵页
        RUNESCAPE  =  3,				// 章节列表
        EQUIPMENT_LIST = 4,				// 装备列表
        SKILL_LIST = 5,					// 技能列表
        DUEL = 6,                       // 封神（决斗）
        ACTIVITY_AWARD = 7,				// 每日任务
        MARKET = 8,                     // 卡牌招募
        APPRENTICE = 9,					// 有福同享
        EIGHT_GRAPH = 10,				// 八卦阵
        FORTUNE = 11,   	            // 财神到
        MONTHLY_CARD = 12,				// 月卡（充值）
        SIGN_IN = 13,					// 每日签到
        JEWELLERY = 14,					// 宝石
        EXPLOIT = 15,					// 诛仙阵探宝
        MYSTERY_MARKET = 16,			// 神秘宝库（神秘商店）
        CARD_SELECT = 17,				// 更换卡牌
        FIGHT_POS = 18,					// 阵容页
        PARAGRAPH_LIST = 19,			// 关卡列表
        LADDER = 20,					// 混战（天梯）
        MISSION_LAYER = 21,				// 成长任务
        BACK_PACK_LIST = 22,			// 道具列表（背包）
        FRIEND_LIST = 23,				// 好友列表
        DYNAMIC_RUNESCAPE = 24,			// 动态关卡（秘境）
        JUE_DI = 25,					// 绝地
        DU_JIE = 26,					// 渡劫
        BLOOD_FIGHT = 27,				// 六道轮回（闯关）
        SHOP_LIST = 28,					// 商店列表
        RECENT_MESSAGE = 29,			// 近期消息
        HOME_PAGE = 30,					// 首页
        ITEM_SHOP = 31,                 // 道具商店
        PACK_SHOP = 32,                 // 礼包商店
        DUEL_AWARD = 33,				// 兑换仙丹
        EQUIP_FRAGMENT = 34,            // 装备碎片
        CONSUME_RANK = 35               // 消耗排行
};

}

#endif

