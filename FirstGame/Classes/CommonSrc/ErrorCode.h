#ifndef ERRORCODE_H_
#define ERRORCODE_H_
 
enum ERROR_CODE
{
	ERROR_CODE_OK                                                     =     0,	//OK

	ERROR_CODE_COMMON_SERVER_ERROR                                    =     1,	//服务器错误

	ERROR_CODE_COMMON_CARD_FULL                                       =     2,	//卡牌已满

	ERROR_CODE_COMMON_GHOST_FULL                                      =     3,	//魂魄已满

	ERROR_CODE_COMMON_SKILL_FULL                                      =     4,	//技能已满

	ERROR_CODE_COMMON_EQUIP_FULL                                      =     5,	//装备已满

	ERROR_CODE_PLAYER_ALREADY_EXISTS                                  =   201,	//创建玩家：该玩家已存在

	ERROR_CODE_DB_ERROR                                               =   202,	//创建玩家：DB错误

	ERROR_CODE_PLAYER_NAME_LENGTH_ERROR                               =   203,	//创建玩家：名称长度

	ERROR_CODE_PLAYER_NAME_TYPE_ERROR                                 =   204,	//创建玩家：名称中文

	ERROR_CODE_PLAYER_NAME_CONTAIN_SENSITIVE_WORDS                    =   205,	//创建玩家：敏感词汇

	ERROR_CODE_CARDINDEX_NOT_EXIST                                    =   206,	//创建玩家：客户端填写的首选卡牌索引号不存在

	ERROR_CODE_PLAYER_NAME_DUPLICATE_ERROR                            =   207,	//创建玩家：数据库执行失败

	ERROR_CODE_PLAYER_NOT_EXIST                                       =   208,	//创建玩家：玩家不存在

	ERROR_CODE_VERIFY_ERROR                                           =   209,	//创建玩家：帐号验证失败

	ERROR_CODE_SERVER_OVERLOAD                                        =   210,	//创建玩家：服务器人数已满

	ERROR_CODE_VERIFY_PAYMENT_RECEIPT_EXPIRE                          =   301,	//支付：订单号过期

	ERROR_CODE_VERIFY_PAYMENT_VERIFY_FAILED                           =   302,	//支付：订单号验证失败

	ERROR_CODE_VERIFY_PAYMENY_RECEIPT_NOT_MATCH                       =   303,	//支付：订单号和验证码不匹配

	ERROR_CODE_VERIFY_PAYMENT_GOODS_INFO_NOT_FOUND                    =   304,	//支付：商品名不存在

	ERROR_CODE_REPEATED_LOGIN_ERROR                                   =   401,	//通知：帐户名和SESSIONKEY不匹配

	ERROR_CODE_PLAYER_BANNED_ERROR                                    =   402,	//通知：禁号

	ERROR_CODE_SERVER_STOP_RUNNING_ERROR                              =   403,	//通知：服务器停止运行

	ERROR_CODE_SESSIONKEY_EXPIRED                                     =   404,	//通知：SESSIONKEY过期

	ERROR_CODE_SERVER_UNDER_MAINTANCE                                 =   405,	//通知：处在维护中

	ERROR_CODE_VERIFY_CODE_FAILED                                     =   501,	//登录：验证失败

	ERROR_CODE_VERIFY_CODE_INVALID_DATA                               =   502,	//登录：电话号码错误

	ERROR_CODE_CHECK_GOLD_NO_PLAYER                                   =   601,	//检查基本信息：玩家不存在

	ERROR_CODE_PHONE_LOGIN_INVALID_PASSWORD                           =   701,	//电话号码登录：验证失败

	ERROR_CODE_PHONE_LOGIN_DB_ERROR                                   =   702,	//电话号码登录：数据库执行失败

	ERROR_CODE_PHONE_LOGIN_FAILED                                     =   703,	//电话号码登录：号码不合法或密码少于六位

	ERROR_CODE_REGISTER_FAILED                                        =   801,	//注册：注册失败

	ERROR_CODE_REGISTER_INVALID_DATA                                  =   802,	//注册：号码不合法或密码少于六位

	ERROR_CODE_REGISTER_OK                                            =   803,	//注册：成功（特殊保留，客户端可能要用，之前为200）

	ERROR_CODE_REGISTER_ALREADY_DONE                                  =   804,	//注册：注册已经完成（之前值为400）

	ERROR_CODE_CHECK_NAME_ALREADY_EXIST                               =   901,	//检查名字：名字已存在

	ERROR_CODE_CHECK_NAME_DB_ERROR                                    =   902,	//检查名字：数据库异常

	ERROR_CODE_CHECK_NAME_INVALID                                     =   903,	//检查名字：名字非法

	ERROR_CODE_CHECK_CDKEY_INVALID_KEY                                =  1001,	//CDK相关：CDK非法

	ERROR_CODE_CHECk_CDKEY_PACKET_FULL                                =  1002,	//CDK相关：背包已满

	ERROR_CODE_CHECK_CDKEY_SER_ERROR                                  =  1003,	//CDK相关：系统错误

	ERROR_CODE_SWAP_FIGHTING_CARD_ALREADY_ON_FIGHT_POS                =  1101,	//卡牌相关：卡牌已上阵无法再上阵

	ERROR_CODE_SWAP_FIGHTING_CARD_ERROR_FIGHT_POS                     =  1102,	//卡牌相关：阵位槽不对

	ERROR_CODE_SWAP_FIGHTING_CARD_NULL_CARD                           =  1103,	//卡牌相关：卡牌为空

	ERROR_CODE_SWAP_FIGHTING_CARD_NOTFRIEND                           =  1104,	//卡牌相关：对方不是好友无法借对方的卡

	ERROR_CODE_SWAP_FIGHTING_CARD_PLAYERISNULL                        =  1105,	//卡牌相关：好友不存在

	ERROR_CODE_SWAP_FIGHTING_CARD_SERVERERROR                         =  1106,	//卡牌相关：系统错误

	ERROR_CODE_SWAP_FIGHTING_FRIND_DO_NOT_HAVE_THIS_CARD              =  1107,	//卡牌相关：好友无这张卡

	ERROR_CODE_SWAP_FIGHTING_FRIND_DO_NOT_HAVE_THIS_CARD_TALENT_SKILL =  1108,	//卡牌相关：好友天赋技能出错

	ERROR_CODE_SWAP_FIGHTING_FRIND_HELP_CARD_IS_FULL                  =  1109,	//卡牌相关：助阵卡牌为空

	ERROR_CODE_SWAP_FIGHTING_LADDER_FRIENDSCARDLIMIT                  =  1110,	//卡牌相关：好友卡牌已满

	ERROR_CODE_SWAP_FIGHTING_LADDER_ONEFRIEND_ONECARDLIMIT            =  1111,	//卡牌相关：一个好友仅限一张卡

	ERROR_CODE_SWAP_FIGHTING_LADDER_NOTFRIENDS                        =  1112,	//卡牌相关：不是好友

	ERROR_CODE_SWAP_FIGHTING_LADDER_FIGHTINGNUM                       =  1113,	//卡牌相关：阵位数目错误

	ERROR_CODE_SWAP_FIGHTING_LADDER_NOTONEDAY                         =  1114,	//卡牌相关：不是同一天，需要客户端刷新

	ERROR_CODE_SWAP_FIGHTING_LADDER_SERVERERROR                       =  1115,	//卡牌相关：天梯阵容相关操作系统错误

	ERROR_CODE_SWAP_FIGHTING_POS_ERROR_FIGHT_POS                      =  1201,	//阵位相关：布阵时阵位号不对

	ERROR_CODE_SWAP_FIGHTING_POS_LARGER_THAN_MAX_FIGHT_POS            =  1202,	//阵位相关：布阵时阵位数不匹配

	ERROR_CODE_SWAP_FIGHTING_POS_LADDER_NOTONEDAY                     =  1203,	//阵位相关：不是同一天，需要客户端刷新

	ERROR_CODE_SWAP_FIGHTING_POS_LADDER_SERVERERROR                   =  1204,	//阵位相关：天梯阵容出错

	ERROR_CODE_GHOST_RECRUIT_ERROR_GHOST_INDEX                        =  1301,	//魂魄相关：魂魄索引号不对

	ERROR_CODE_GHOST_RECRUIT_ERROR_CARD_ID                            =  1302,	//魂魄相关：魂魄ID不对

	ERROR_CODE_GHOST_RECRUIT_GHOST_NUM_LESS                           =  1303,	//魂魄相关：招募时魂魄不够

	ERROR_CODE_GHOST_RECRUIT_QUALITY                                  =  1304,	//魂魄相关：尚未开放此星级卡牌招募

	ERROR_CODE_GHOST_RECRUIT_CARD_ALREADY_EXIST                       =  1305,	//魂魄相关：该卡牌已经存在

	ERROR_CODE_PASS_EXPERIENCE_INVALID_CARD_INDEX                     =  1401,	//传功相关：卡牌ID不对

	ERROR_CODE_PASS_EXPERIENCE_INVALID_PASS_TYPE                      =  1402,	//传功相关：传功类型不对

	ERROR_CODE_PASS_EXPERIENCE_INVALID_DISTRIBUTE_CARD_LEVEL          =  1403,	//传功相关：散功弟子小于2级

	ERROR_CODE_PASS_EXPERIENCE_INVALID_DISTRIBUTE_CARD_ON_FIGHTPOS    =  1404,	//传功相关：散功弟子在阵上

	ERROR_CODE_PASS_EXPERIENCE_NOT_ENOUGH_ITEM                        =  1405,	//传功相关：传功丹不足

	ERROR_CODE_SKILL_UPGRADE_UPGRADEINDEX                             =  1501,	//技能相关：所升级的技能不合法

	ERROR_CODE_SKILL_UPGRADE_DEPLETIONINDEX                           =  1502,	//技能相关：升级时消耗的技能不合法

	ERROR_CODE_SKILL_UPGRADE_DEPLETIONSAMEINDEX                       =  1503,	//技能相关：消耗的技能有相同的索引号

	ERROR_CODE_SKILL_UPGRADE_DEPLETIONNUM                             =  1504,	//技能相关：消耗的技能数目不对

	ERROR_CODE_SKILL_UPGRADE_MONEY                                    =  1505,	//技能相关：升级所需银两不足

	ERROR_CODE_SKILL_CONFIG_INDEX                                     =  1506,	//技能相关：配置技能不合法

	ERROR_CODE_SKILL_CONFIG_INBORNINDEX                               =  1507,	//技能相关：配置的技能是天赋技能

	ERROR_CODE_SKILL_CONFIG_LADDERFIGHTPOS_ISNULL                     =  1508,	//技能相关：天梯阵容配技能时天梯阵容还不存在

	ERROR_CODE_SKILL_WRONG_FIGHT_POS                                  =  1509,	//技能相关：配置技能时阵位Index不合法

	ERROR_CODE_SKILL_CONFIG_TALENT_SKILL                              =  1510,	//技能相关：要更换的技能是天赋技能

	ERROR_CODE_SKILL_TYPE_ERROR                                       =  1511,	//技能相关：配置技能时技能槽号不合法

	ERROR_CODE_SKILL_CONFIG_NULL_CARD_SKILL                           =  1512,	//技能相关：配置技能时该阵位无有效卡牌

	ERROR_CODE_SKILL_ALREADY_ON_FIGHT_POS                             =  1513,	//技能相关：配置技能时该技能和天赋技能或其他技能相同

	ERROR_CODE_SKILL_NULL_SKILL_MANAGER                               =  1514,	//技能相关：配置技能时技能管理器不合法

	ERROR_CODE_SKILL_LADDER_NOTONEDAY                                 =  1516,	//技能相关：配置天梯阵容时出现不是同一天，需要客户端刷新的问题

	ERROR_CODE_SKILL_ALREADY_MAX_LEVEL                                =  1517,	//技能相关：升级技能时该技能已到最大等级

	ERROR_CODE_SKILL_SELL_INDEX                                       =  1518,	//技能相关：出售的技能不合法

	ERROR_CODE_SKILL_SELL_NUM                                         =  1519,	//技能相关：出售的数量不合法

	ERROR_CODE_SKILL_SELL_SAMEINDEX                                   =  1520,	//技能相关：出售的技能中存在同一个技能

	ERROR_CODE_SKILL_SELL_CARD                                        =  1521,	//技能相关：出售的技能已配置在阵位上

	ERROR_CODE_SKILL_SELL_INBORNINDEX                                 =  1522,	//技能相关：出售的技能为天赋技能

	ERROR_CODE_EQUIPMENT_UPGRADE_INDEX                                =  1601,	//装备相关：所升级的装备不合法

	ERROR_CODE_EQUIPMENT_UPGRADE_LEVEL                                =  1602,	//装备相关：所升级的装备到达了等级上限

	ERROR_CODE_EQUIPMENT_UPGRADE_MONEY                                =  1603,	//装备相关：升级所需银两不足

	ERROR_CODE_EQUIPMENT_UPGRADE_RAPIDVIPLIMIT                        =  1604,	//装备相关：未达到快速强化所需VIP等级

	ERROR_CODE_EQUIPMENT_SELL_INDEX                                   =  1605,	//装备相关：出售的装备不合法

	ERROR_CODE_EQUIPMENT_SELL_NUM                                     =  1606,	//装备相关：出售的装备数量不合法

	ERROR_CODE_EQUIPMENT_SELL_SAMEINDEX                               =  1607,	//装备相关：出售的装备中存在相同装备

	ERROR_CODE_EQUIPMENT_SELL_CARD                                    =  1608,	//装备相关：出售的装备已经配置在阵容上

	ERROR_CODE_EQUIPMENT_CONFIG_INDEX                                 =  1609,	//装备相关：配置装备不合法

	ERROR_CODE_EQUIPMENT_CONFIG_TYPE                                  =  1610,	//装备相关：配置的装备类型不对，比如武器槽配配衣服

	ERROR_CODE_EQUIPMENT_CONFIG_LADDERFIGHTPOS_ISNULL                 =  1611,	//装备相关：配置装备在天梯阵容时，该天梯阵容还不存在

	ERROR_CODE_EQUIPMENT_WRONG_FIGHT_POS                              =  1612,	//装备相关：配置装备所属的阵位不合法

	ERROR_CODE_EQUIPMENT_TYPE_ERROR                                   =  1613,	//装备相关：配置的装备槽号不对

	ERROR_CODE_EQUIPMENT_CONFIG_NULL_CARD_EQUIPMENT                   =  1614,	//装备相关：配置装备所属的阵位上无有效的卡牌

	EROOR_CODE_EQUIPMENT_NULL_EQUIPMENT_MANAGER                       =  1615,	//装备相关：配置装备时装备管理器为空

	ERROR_CODE_EQUIPMENT_LADDER_NOTONEDAY                             =  1616,	//装备相关：配置天梯阵容时出现不是同一天，需要客户端刷新的问题

	ERROR_CODE_RUNESCAPE_POWER_EMPTY                                  =  1701,	//江湖相关：体力不足

	ERROR_CODE_RUNESCAPE_INVAILD_PARAM                                =  1702,	//江湖相关：参数错误

	ERROR_CODE_RUNESCAPE_CHALLEGNUM_EMPTY                             =  1703,	//江湖相关：剩余挑战次数不足

	ERROR_CODE_RUNESCAPE_RECOVERY_SATUS_ERROR                         =  1704,	//江湖相关：吃鸡状态不对

	ERROR_CODE_RUNESCAPE_VIP_LOW_SERIAL_FIGHT                         =  1705,	//江湖相关：连闯时VIP等级不足

	ERROR_CODE_RUNESCAPE_VIP_CD_IN_TIME                               =  1706,	//江湖相关：连闯时间还在CD

	ERROR_CODE_RUNESCAPE_CHALLEGNUM_NOT_EMPTY                         =  1707,	//江湖相关：还有挑战次数不能购买

	ERROR_CODE_RUNESCAPE_VIP_LOW_CHALLEGNUM                           =  1708,	//江湖相关：VIP等级不够无法购买挑战次数

	ERROR_CODE_RUNESCAPE_LESSGOLDEN_CHALLEGNUM                        =  1709,	//江湖相关：元宝不足无法购买

	ERROR_CODE_RUNESCAPE_INVAILD_CLEAR_CD                             =  1710,	//江湖相关：VIP不足无法清除连闯CD时间

	ERROR_CODE_RUNESCAPE_COST_GLODEN_FAILED                           =  1711,	//江湖相关：消费元宝失败

	ERROR_CODE_RUNESCAPE_END                                          =  1712,	//江湖相关：目前已经通关

	ERROR_CODE_RUNESCAPE_EXCEED_CLEAR_LIMIT                           =  1713,	//江湖相关：达到清关次数上限

	ERROR_CODE_RUNESCAPE_POWER_NOT_EMPTY                              =  1714,	//江湖相关：购买体力时体力不为0

	ERROR_CODE_RUNESCAPE_EXCEED_BUYPOWER_LIMIT                        =  1715,	//江湖相关：超过最大购买次数限制

	ERROR_CODE_RUNESCAPE_BUYPOWER_PARAM_ERROR                         =  1716,	//江湖相关：参数错误

	ERROR_CODE_RUNESCAPE_BUYPOWER_OK                                  =  1717,	//江湖相关：购买成功

	ERROR_CODE_RUNESCAPE_BUYPOWER_NOT_ENOUGH_GOLD                     =  1718,	//江湖相关：购买体力时元宝不足

	ERROR_CODE_DUEL_CHALLENG_VITALITY                                 =  1801,	//论剑相关：元气不足

	ERROR_CODE_DUEL_CHALLENG_RANK_CHANGED                             =  1802,	//论剑相关：名次已经改变了，需刷新数据

	ERROR_CODE_DUEL_CHALLENG_DEFENDERID                               =  1803,	//论剑相关：防守者的playerID不正确

	ERROR_CODE_DUEL_ERROR_PLAYER_ID                                   =  1804,	//论剑相关：PlayerID不正确

	ERROR_CODE_DUEL_REFRESH_SCORE_NO_STATIC_FRESH_TIME_INFO           =  1805,	//论剑相关：静态表没有这个名次的刷新时间

	ERROR_CODE_DUEL_EXCHANGE_TRANING_ERROR_EXCHANGE_TYPE              =  1806,	//论剑相关：错误的兑换培养丹类型，1兑换5个，2兑换50个

	ERROR_CODE_DUEL_EXCHANGE_TRANING_ERROR_SCORE_NOT_ENOUGH           =  1807,	//论剑相关：兑换培养丹积分不够

	ERROR_CODE_DUEL_RECEIVE_PRIZE_ERROR_TYPE                          =  1808,	//论剑相关：领取的奖品类型错误

	ERROR_CODE_DUEL_RECEIVE_RANK_NOT_ACHIEVED                         =  1809,	//论剑相关：没有达到领取该奖品的排名

	ERROR_CODE_DUEL_REFRESH_DUEL_BASE_INFO_FAILED                     =  1810,	//论剑相关：刷新基本信息失败

	ERROR_CODE_DUEL_PRIZE_ALREADY_GET                                 =  1811,	//论剑相关：奖品已经领取过

	ERROR_CODE_DUEL_CHALLENG_DUELNUM                                  =  1812,	//论剑相关：挑战次数不足

	ERROR_CODE_DUEL_LEVEL_LESS                                        =  1813,	//论剑相关：进入论剑等级不够

	EROOR_CODE_DUEL_PRIZE_SERVER_ERROR                                =  1814,	//论剑相关：发奖时服务器异常

	ERROR_CODE_DUEL_CHALLENG_SERVERERROR                              =  1815,	//论剑相关：挑战时服务器异常

	ERROR_CODE_CARDMARKET_ITEM_LACK                                   =  1901,	//抽卡相关：道具不足

	ERROR_CODE_CARDMARKET_INCDTIME                                    =  1902,	//抽卡相关：CD时间未到

	ERROR_CODE_CARDMARKET_LEAVETIMES_LACK                             =  1903,	//抽卡相关：剩余免费次数不足

	ERROR_CODE_CARDMARKET_TYPE_WRONG                                  =  1904,	//抽卡相关：抽卡类型错误

	ERROR_CODE_CARDMARKET_NOT_FIND                                    =  1905,	//抽卡相关：未找到该卡ID

	ERROR_CODE_CARDMARKET_OTHER                                       =  1906,	//抽卡相关：其他错误

	ERROR_CODE_CARDMARKET_CONSUME_WRONG                               =  1909,	//抽卡相关：数据错误

	ERROR_CODE_BLOODYBATTLE_TIME_OUT                                  =  2001,	//血战相关：已经过了一天，需要刷新

	ERROR_CODE_BLOODYBATTLE_POSITIONTYPE_CHANGE                       =  2002,	//血战相关：阵位数发生变化

	ERROR_CODE_BLOODYBATTLE_LEAVETIMES_LACK                           =  2003,	//血战相关：剩余次数不足

	ERROR_CODE_BLOODYBATTLE_SCREENMODE_WRONG                          =  2004,	//血战相关：数据不同步

	ERROR_CODE_BLOODYBATTLE_ADDITIONTYPE_WRONG                        =  2005,	//血战相关：数据不同步

	ERROR_CODE_BLOODYBATTLE_LEVEL_TOO_SMALL                           =  2006,	//血战相关：等级不足

	ERROR_CODE_BLOODYBATTLE_STAR_LACK                                 =  2007,	//血战相关：星星不足

	ERROR_CODE_BLOODYBATTLE_BAG_FULL                                  =  2008,	//血战相关：背包已满

	ERROR_CODE_BLOODYBATTLE_MAX_PASS                                  =  2009,	//血战相关：满关

	ERROR_CODE_BILLBOARD_LIST_EMPTY                                   =  2010,	//血战相关：排行榜为空

	ERROR_CODE_BILLBOARD_OPPROTO_ERROR                                =  2011,	//血战相关：数据错误

	ERROR_CODE_BILLBOARD_RANK_EMPTY                                   =  2012,	//血战相关：数据错误

	ERROR_CODE_CARD_TRAIN_INVALID_TYPE                                =  2101,	//卡牌培养：不正确的培养类型

	ERROR_CODE_CARD_TRAIN_NOT_ENOUGH_TRAINNING_DAN                    =  2102,	//卡牌培养：培养丹数量不足

	ERROR_CODE_CARD_TRAIN_NOT_ENOUGH_GOLD                             =  2103,	//卡牌培养：元宝不足

	ERROR_CODE_CARD_TRAIN_TRAINNING_OR_GOLD_FAILD                     =  2104,	//卡牌培养：扣除培养丹或元宝失败

	ERROR_CODE_CARD_TRAIN_INVALID_CARD_INDEX                          =  2105,	//卡牌培养：卡牌index不合法

	ERROR_CODE_CARD_TRAIN_LOW_THAN_MIN                                =  2106,	//卡牌培养：卡牌属性比最小熟悉还低

	ERROR_CODE_CARD_TRAIN_REDUCE_TYPE_INVALID                         =  2107,	//卡牌培养：随机生成减少类型失败

	ERROR_CODE_CARD_TRAIN_ADD_TYPE_INVALID                            =  2108,	//卡牌培养：随机生成增加类型失败

	ERROR_CODE_CARD_TRAIN_REDUCE_VALUE_INVALID                        =  2109,	//卡牌培养：随机生成减少值失败

	ERROR_CODE_CARD_TRAIN_ADD_VALUE_INVALID                           =  2110,	//卡牌培养：随机生成增加值失败

	ERROR_CODE_CARD_TRAIN_POTENTIONAL_MINUS                           =  2111,	//卡牌培养：潜力值为负数

	ERROR_CODE_CARD_TRAIN_CONFIRM_INVALID_TYPE                        =  2112,	//卡牌培养：确认类型错误

	ERROR_CODE_CARD_TRAIN_NOT_MY_CARD                                 =  2113,	//卡牌培养：不是自己的卡牌

	ERROR_CODE_CARD_QUALITY_UPGRADE_CARD_ID_INVALID                   =  2201,	//卡牌升星：卡牌静态ID不合法

	ERROR_CODE_CARD_QUALITY_UPGRADE_CARD_SILVER_IS_NOT_ENOUGH         =  2202,	//卡牌升星：银两不足

	ERROR_CODE_CARD_QUALITY_UPGRADE_CARD_FERTILIZER_COUNT_ILLEGAL     =  2203,	//卡牌升星：肥料数目不合法

	ERROR_CODE_CARD_QUALITY_UPGRADE_FERTILIZER_CARD_ID_INVALID        =  2204,	//卡牌升星：肥料卡牌ID不合法

	ERROR_CODE_CARD_QUALITY_UPGRADE_FERTILIZER_CARD_ON_FIGHT_POS      =  2205,	//卡牌升星：肥料卡牌在阵位上

	ERROR_CODE_CARD_QUALITY_UPGRADE_CARD_REACH_MAX_QUALITY            =  2206,	//卡牌升星：卡牌达到最高品质

	ERROR_CODE_CARD_QUALITY_UPGRADE_FERTILIZER_GHOST_ID_INVALID       =  2207,	//卡牌升星：肥料魂魄ID不合法

	ERROR_CODE_CARD_QUALITY_UPGRADE_DUPLITE_CARD_ID                   =  2208,	//卡牌升星：重复的肥料卡牌ID

	ERROR_CODE_CARD_QUALITY_UPGRADE_DUPLITE_GHOST_ID                  =  2209,	//卡牌升星：重复的肥料魂魄ID

	ERROR_CODE_CARD_QUALITY_UPGRAD_FERTILIZER_IS_NOT_MINE             =  2210,	//卡牌升星：肥料卡牌不是自己的卡牌

	ERROR_CODE_CARD_QUALITY_UPGRADE_CARD_YOU_HAVE                     =  2211,	//卡牌升星：已经拥有了目标星级的卡牌

	ERROR_CODE_CARD_QUALITY_UPGRADE_CARD_SERVER_ERROR                 =  2212,	//卡牌升星：服务器内部错误

	ERROR_CODE_CARD_QUALITY_UPGRADE_CARD_LEVEL_NOT_ENOUGH             =  2213,	//卡牌升星：卡牌等级不够

	ERROR_CODE_ITEM_BUY_DATAERROR                                     =  2301,	//道具相关：提交的购买数据错误

	ERROR_CODE_ITEM_BUY_NOTSELLING                                    =  2302,	//道具相关：不在售卖中

	ERROR_CODE_ITEM_BUY_PRICECHANGED                                  =  2303,	//道具相关：价格已发生改变

	ERROR_CODE_ITEM_BUY_GOLDNOTENOUGH                                 =  2304,	//道具相关：元宝不足

	ERROR_CODE_ITEM_BUY_BUYLIMIT                                      =  2305,	//道具相关：已达购买上限

	ERROR_CODE_ITEM_BUY_NUMLIMITORSERVERERROR                         =  2306,	//道具相关：购买失败

	ERROR_CODE_ITEM_USING_NUM                                         =  2307,	//道具相关：使用的道具数量不足

	ERROR_CODE_ITEM_USING_DAYUSEABLELIMIT                             =  2308,	//道具相关：每天使用次数的限制

	ERROR_CODE_ITEM_USING_TYPE                                        =  2309,	//道具相关：使用的道具类型不对

	ERROR_CODE_ITEM_USING_ADDDUELNUM                                  =  2310,	//道具相关：无法使用决斗贴，因为还有足够次数

	ERROR_CODE_ITEM_OPEN_NULLITEM                                     =  2311,	//道具相关：开启的道具还不存在

	ERROR_CODE_ITEM_OPEN_NOTPACKSORKEYBOX                             =  2312,	//道具相关：错误的道具类型，只允许开始箱子（钥匙）或礼包

	ERROR_CODE_ITEM_OPEN_KEYORBOXNOTENOUGH                            =  2313,	//道具相关：对应的箱子或钥匙不足

	ERROR_CODE_ITEM_OPEN_KEYBOXNOTMATCH                               =  2314,	//道具相关：钥匙箱子不匹配

	ERROR_CODE_ITEM_OPEN_SUCCESSIVE_NUM                               =  2315,	//道具相关：连开箱子的数目不对

	ERROR_CODE_ITEM_OPEN_SUCCESSIVE_KEYORBOXNOTENOUGH                 =  2316,	//道具相关：连开宝箱所需箱子或钥匙不足

	ERROR_CODE_ITEM_OPEN_SUCCESSIVE_VIPLIMIT                          =  2317,	//道具相关：连开宝箱VIP不足

	ERROR_CODE_ITEM_OPEN_SERVER_EXEERROR                              =  2318,	//道具相关：执行开启箱子出错，lua或内存

	ERROR_CODE_ITEM_USING_LADDER_NOTIN                                =  2319,	//道具相关：降低疲劳值时获取天梯部件失败

	ERROR_CODE_ITEM_USING_LADDER_NOTNEED                              =  2320,	//道具相关：无需降低疲劳值，如疲劳值很低

	ERROR_CODE_ITEM_USING_SERVERERROR                                 =  2321,	//道具相关：使用道具时系统错误

	ERROR_CODE_ITEM_OPEN_SERVERERROR                                  =  2322,	//道具相关：打开箱子或礼包时系统错误

	ERROR_CODE_ITEM_USING_PLAYER_LEVEL_LIMIT                          =  2323,	//道具相关：使用等级限制

	ERROR_CODE_ITEM_ADD_ONECARDEXP_CARD_NOTEXIST                      =  2324,	//道具相关：单个弟子不存在，card不存在

	ERROR_CODE_ITEM_ADD_ONECARDEXP_CARD_HAD_MAX_EXP                   =  2325,	//道具相关：单个加经验时，该卡牌经验已满

	ERROR_CODE_ITEM_ADD_EXP_PLAYER_LEVEL_MAX                          =  2326,	//道具相关：玩家已到最大等级，无法增加经验

	ERROR_CODE_ITEM_ADD_ONECARDEXP_ALL_CARD_HAD_MAX_EXP               =  2327,	//道具相关：所有弟子都已满级

	ERROR_CODE_MESSAGESYSTEM_PARAM_ERROR                              =  2401,	//消息系统：系统错误

	ERROR_CODE_MESSAGESYSTEM_AWARD_NOEXIST                            =  2402,	//消息系统：奖励ID错误

	ERROR_CODE_MESSAGESYSTEM_AWARD_HASACCEPT                          =  2403,	//消息系统：重复领取奖励

	ERROR_CODE_FRIENDS_SYSTEM_INVLIAD_PALYER_ID                       =  2501,	//好友系统：PlayerID不合法

	ERROR_CODE_FRIENDS_SYSTEM_NULL_FRIEND_INFO                        =  2502,	//好友系统：好友信息为空，不在好友单例管理之中，创建角色时没有插入好友系统表结构之中

	ERROR_CODE_FRIENDS_SYSTEM_SERACH_CONTENT_ZERO_SIZE                =  2503,	//好友系统：搜索内容为空

	ERROR_CODE_FRIENDS_SYSTEM_NOT_MY_FRIENDS                          =  2504,	//好友系统：不是好友

	ERROR_CODE_FRIENDS_SYSTEM_PULL_FRIEND_FROM_DB_FAILED              =  2505,	//好友系统：从DB拉取好友失败

	ERROR_CODE_FRIENDS_SYSTEM_CONTENT_TOO_LONG_OR_NULL                =  2506,	//好友系统：内容过长

	ERROR_CODE_FRIENDS_SYSTEM_LEAVE_MSG_FAILED                        =  2507,	//好友系统：留言失败

	ERROR_CODE_FRIENDS_SYSTEM_FRIENDS_FULL                            =  2508,	//好友系统：好友已满

	ERROR_CODE_FRIENDS_SYSTEM_NOT_IN_INVITATION_LIST                  =  2509,	//好友系统：不在邀请列表

	ERROR_CODE_FRIENDS_INVITE_OR_LEAVEL_MSG_TO_SELF                   =  2510,	//好友系统：邀请自己或给自己留言

	ERROR_CODE_DUEL_RANK_INVALID                                      =  2511,	//好友系统：给论剑排名留言的排名不合法

	ERROR_CODE_FRIENDS_SYSTEM_IS_ALREADY_FRIENDS                      =  2512,	//好友系统：已经是好友

	ERROR_CODE_FRIENDS_SYSTEM_SERVER_ERROR                            =  2513,	//好友系统：好友系统出错

	ERROR_CODE_ACTIVITY_NOT_OPEN                                      =  2601,	//活动相关：活动没开放

	ERROR_CODE_ACTIVITY_ERROR_AWARD_ID                                =  2602,	//活动相关：领取奖励编号不正确

	EROOR_CODE_ACTIVITY_AWARD_NOT_EXIST                               =  2603,	//活动相关：玩家领取的编号的奖励不存在

	EROOR_CODE_ACTIVITY_ALREADY_EAT_GENSING                           =  2604,	//活动相关：已经吃过人参果了

	ERROR_CODE_ACTIVITY_NOT_INT_EAT_GENSING_TIME                      =  2605,	//活动相关：不在吃人参的时间段内

	ERROR_CODE_ACTIVITY_NOT_EXPIRED                                   =  2606,	//活动相关：活动还没有结束

	ERROR_CODE_ACTIVITY_WRONG_RECEIVE_POSITION                        =  2607,	//活动相关：八卦阵位置不正确

	ERROR_CODE_ACTIVITY_ALREADY_RECEIVE_POSITION                      =  2608,	//活动相关：此位置奖品已经领取

	ERROR_CODE_ACTIVITY_ALREADY_RECEIVE_TODAY                         =  2609,	//活动相关：今天已经领取过八卦阵

	ERROR_CODE_ACTIVITY_EXPIRED                                       =  2610,	//活动相关：活动结束了

	ERROR_CODE_ACTIVITY_GOLD_NOT_ENOUGH                               =  2611,	//活动相关：元宝不够

	ERROR_CODE_GUIDE_SYSTEM_PART_NULL                                 =  2701,	//新手引导：引导部件为空

	ERROR_CODE_GUIDE_SYSTEM_INVALID_PARAM                             =  2702,	//新手引导：参数错误

	ERROR_CODE_GUIDE_SYSTEM_REDO_ERROR                                =  2703,	//新手引导：你已经完成过该引导

	ERROR_CODE_GUIDE_CFG_NOT_FOUND                                    =  2704,	//新手引导： 找不到配置

	ERROR_CODE_GUIDE_SYSTEM_ERROR                                     =  2705,	//新手引导：引导系统错误

	ERROR_CODE_GM_ACTIVITY_OPEN_TIME_ILLEGAL                          =  2801,	//GM活动相关：GM开启时间不合法

	ERROR_CODE_LADDER_SYSTEM_ERROR                                    =  2901,	//天梯系统：系统错误

	ERROR_CODE_LADDER_INVALID_PARAM                                   =  2902,	//天梯系统：参数错误

	ERROR_CODE_LADDER_NO_ENEMY_FOUND                                  =  2903,	//天梯系统：没有找到合适的对手，请稍后再试

	ERROR_CODE_LADDER_NOT_ENOUGH_COIN                                 =  2904,	//天梯系统：小金库银两不足

	ERROR_CODE_LADDER_NOT_ENOUGH_SCORE                                =  2905,	//天梯系统：天梯积分不足

	ERROR_CODE_LADDER_NOT_HAVE_ENEMY                                  =  2906,	//天梯系统：你还未进行对手匹配呢，亲～

	ERROR_CODE_LADDER_ENEMY_DEFEND_CD                                 =  2907,	//天梯系统：对手处于防守CD中

	ERROR_CODE_LADDER_INVALID_FIGHT_BACK                              =  2908,	//天梯系统：非法的反击消息

	ERROR_CODE_LADDER_FIGHT_BACK_OVER_TIME                            =  2909,	//天梯系统：反击消息已经过期了

	ERROR_CODE_LADDER_NO_NEED_REDUCE_FATIGUE                          =  2910,	//天梯系统：疲劳值为0

	ERROR_CODE_LADDER_EMBATTLE_SLOT_LOW                               =  2911,	//天梯系统：4人阵才可以玩天梯哦

	ERROR_CODE_LADDER_CFG_NOT_FOUND                                   =  2912,	//天梯系统：找不到配置

	ERROR_CODE_LADDER_FATIGUE_OVERFLOW                                =  2913,	//天梯系统：你的疲劳值超过了80%，不允许战斗

	ERROR_CODE_LADDER_FIGHT_COIN_LOW                                  =  2914,	//天梯系统：小金库银两低于战斗保底金额，不允许战斗

	ERROR_CODE_LADDER_ENEMY_NOT_IN_MEMORY                             =  2915,	//天梯系统：找不到对手，无法战斗

	ERROR_CODE_LADDER_DATA_NOT_READY                                  =  2916,	//天梯系统：天梯数据未准备好，请稍后重试

	ERROR_CODE_LADDER_LADDER_PLAYER_NOT_FOUND                         =  2917,	//天梯系统：你还未参加天梯活动呢

	ERROR_CODE_LADDER_PLEASE_RE_FETCH                                 =  2918,	//天梯系统：请退出重新拉取天梯现场

	ERROR_CODE_LADDER_PLAYER_COIN_NOT_ENOUGH                          =  2919,	//天梯系统：玩家银两不足，不能兑换为小金库银两

	ERROR_CODE_LADDER_COIN_ENOUGH                                     =  2920,	//天梯系统：天梯小金库银两充足，不需要兑换

	ERROR_CODE_LADDER_CONVERT_TO_CARD_ITEM_FAILED                     =  2921,	//天梯系统：转换卡牌失败

	ERROR_CODE_LADDER_FIGHTINGPOS_SERVERERROR                         =  3001,	//天梯阵容相关：系统错误

	ERROR_CODE_LADDER_FIGHTINGPOS_NOTFRIEND                           =  3002,	//天梯阵容相关：非好友不允许借卡牌

	ERROR_CODE_LADDER_FIGHTINGPOS_LADDERFIGHTINGPOS_ISNULL            =  3003,	//天梯阵容相关：天梯阵容还不存在

	ERROR_CODE_LADDER_FIGHTINGPOS_LADDER_CONVERTFAILD                 =  3004,	//天梯阵容相关：阵容转换失败

	ERROR_CODE_LADDER_FIGHTINGPOS_SERVER_ERROR                        =  3005,	//天梯阵容相关：系统错误

	ERROR_CODE_LADDER_FIGHTINGPOS_NOTONEDAY                           =  3006,	//天梯阵容相关：操纵天梯阵容不在同一天，需要重新拉取天梯现场

	ERROR_CODE_LADDER_FIGHTINGPOS_ERROR_TYPE                          =  3007,	//天梯阵容相关：错误的操作类型，目前只有获取及重置两种类型

	ERROR_CODE_LADDER_FIGHTINGPOS_DBEEEOE                             =  3008,	//天梯阵容相关：DB出错

	ERROR_CODE_LADDER_NO_RANK_LIST                                    =  3101,	//天梯系统内部错误

	ERROR_CODE_CHAT_BAN                                               =  3201,	//聊天系统：已被禁言

	ERROR_CODE_CHAT_ITEM_LACK                                         =  3202,	//聊天系统：道具不足

	ERROR_CODE_CHAT_LENGTH_WRONG                                      =  3203,	//聊天系统：发言长度不合法

	ERROR_CODE_CHAT_OTHER                                             =  3204,	//聊天系统：异常错误

	ERROR_CODE_MISSION_SYSTEM_STATIC_DATA_NOT_FOUND                   =  3301,	//任务系统：找不到任务静态表数据

	ERROR_CODE_MISSION_SYSTEM_PRE_AWARD_NOT_RECV_ERROR                =  3302,	//任务系统：领奖不合法

	ERROR_CODE_MISSION_SYSTEM_INFO_NOT_FOUND                          =  3303,	//任务系统：任务ID未找到

	ERROR_CODE_MISSION_SYSTEM_NOT_RECEIVEABLE                         =  3304,	//任务系统：未达到领奖条件

	ERROR_CODE_MISSION_SYSTEM_SVR_ERROR                               =  3305,	//任务系统：系统错误

	ERROR_CODE_MYSTERY_SHOP_GODDESS_STONE_NOT_ENOUGH                  =  3401,	//神秘商店：女娲石数量不够

	ERROR_CODE_MYSTERY_SHOP_SERVER_ERROR                              =  3402,	//神秘商店：静态表错误

	ERROR_CODE_MYSTERY_SHOP_GOOD_NOT_ON_SALE                          =  3403,	//神秘商店：商品未在卖

	ERROR_CODE_MYSTERY_SHOP_BUY_TIMES_NOT_ENOUGH                      =  3404,	//神秘商店：神秘物品购买次数不足

	ERROR_CODE_MYSTERY_SHOP_GOODS_FULL                                =  3405,	//神秘商店：背包满了

	ERROR_CODE_MYSTERY_SHOP_NOT_OPNE                                  =  3406,	//神秘商店：神秘商店未开放

	ERROR_CODE_MYSTERY_SHOP_REFRESH_NOT_ENOUGH                        =  3407,	//神秘商店：手动刷新次数不足

	ERROR_CODE_MYSTERY_SHOP_BUY_TYPES_NOT_ENOUGH                      =  3408,	//神秘商店：兑换种类次数不足

	ERROR_CODE_MYSTERY_SHOP_GOOD_PRICE_ERROR                          =  3409,	//神秘商店：价格不正确

	ERROR_CODE_VIPCARD_SERVERERROR                                    =  3501,	//VIP卡：系统错误

	ERROR_CODE_VIPCARD_VIPCARDID_ISNOTEXIST                           =  3502,	//VIP卡：VIPCard的ID不存在

	ERROR_CODE_VIPCARD_LEVELORVIP_ISNOTENOUGH                         =  3503,	//VIP卡：等级或Vip等级不够

	ERROR_CODE_VIPCARD_NOTYETBUY                                      =  3504,	//VIP卡：未购买该Vip卡

	ERROR_CODE_VIPCARD_LEFTTIME                                       =  3505,	//VIP卡：VIP卡已过期

	ERROR_CODE_VIPCARD_HADAWARD                                       =  3506,	//VIP卡：当天已领教无法再领教

	ERROR_CODE_EQUIPFRAGMENT_SERVERERROR                              =  3601,	//装备碎片：服务器异常

	ERROR_CODE_EQUIPFRAGMENT_EQUIPID_ISNOTEXIST                       =  3602,	//装备碎片：装备ID不存在

	ERROR_CODE_EQUIPFRAGMENT_MERGENUM_LESSONE                         =  3603,	//装备碎片：合成数量少于1

	ERROR_CODE_EQUIPFRAGMENT_FRAGNUM_ISNOTENOUGH                      =  3604,	//装备碎片：合成时碎片不足

	ERROR_CODE_GEMSTONE_SERVERERROR                                   =  3701,	//宝石系统：服务器异常

	ERROR_CODE_GEMSTONE_GEMSTONE_ISNOTEXIST                           =  3702,	//宝石系统：升级宝石时该宝石不存在

	ERROR_CODE_GEMSTONE_COLOUR_MULTI                                  =  3703,	//宝石系统：多色不允许升级

	ERROR_CODE_GEMSTONE_UPGRADE_NOMORE                                =  3704,	//宝石系统：不允许再升级

	ERROR_CODE_GEMSTONE_UPGRADE_NEEDNUM                               =  3705,	//宝石系统：升级所需宝石不足

	ERROR_CODE_GEMSTONE_UPGRADE_MONEY_NOTENOUGH                       =  3706,	//宝石系统：升级所需银两不足

	ERROR_CODE_GEMSTONE_MERGE_GEMSTONE_ISNOTEXIST                     =  3707,	//宝石系统：合成宝石时某单色宝石不足

	ERROR_CODE_GEMSTONE_MERGE_LEVEL_ISNOTSAME                         =  3708,	//宝石系统：合成宝石时宝石等级不完全相同

	ERROR_CODE_GEMSTONE_MERGE_COLOUR_SAME                             =  3709,	//宝石系统：合成宝石时宝石颜色不对

	ERROR_CODE_GEMSTONE_MERGE_NOTABLE                                 =  3710,	//宝石系统：不允许合成

	ERROR_CODE_GEMSTONE_MERGE_MONEY_NOTENOUGH                         =  3711,	//宝石系统：合成时银两不足

	ERROR_CODE_GEMSTONE_DECOMPOSITE_GEMSTONE_ISNOTEXIST               =  3712,	//宝石系统：分解时宝石不存在

	ERROR_CODE_GEMSTONE_DECOMPOSITE_NOTABLE                           =  3713,	//宝石系统：无法分解

	ERROR_CODE_GEMSTONE_DECOMPOSITE_MONEY_NOTENOUGH                   =  3714,	//宝石系统：分解时银联不足

	ERROR_CODE_GEMSTONE_DECOMPOSITE_NOT_COLOUR                        =  3715,	//宝石系统：分解时不是彩色宝石，无效

	ERROR_CODE_EQUIP_GEMSTONE_SERVERERROR                             =  3801,	//装备镶嵌：服务器异常

	ERROR_CODE_EQUIP_GEMSTONE_EQUIPINDEX                              =  3802,	//装备镶嵌：装备不合法

	ERROR_CODE_EQUIP_GEMSTONE_DIGHOLE_NOTABLE                         =  3803,	//装备镶嵌：打孔序号不对或无法再打孔

	ERROR_CODE_EQUIP_GEMSTONE_DIGHOLE_ITEM_NOTENOUGH                  =  3804,	//装备镶嵌：打孔所需道具不足

	ERROR_CODE_EQUIP_GEMSTONE_EMBED_NOTABLE                           =  3805,	//装备镶嵌：无法镶嵌

	ERROR_CODE_EQUIP_GEMSTONE_EMBED_GEMSTONE_NOTENOUGH                =  3806,	//装备镶嵌：想镶嵌的宝石数量不足

	ERROR_CODE_EQUIP_GEMSTONE_REMOVE_NOTABLE                          =  3807,	//装备镶嵌：无法移除

	ERROR_CODE_EQUIP_GEMSTONE_REMOVE_ITEM_NOTENOUGH                   =  3808,	//装备镶嵌：移除所需道具不足

	ERROR_CODE_DYNAMICRUNE_SERVERERROR                                =  3901,	//动态关卡：服务器异常

	ERROR_CODE_DYNAMICRUNE_RUNE_NOTFIND                               =  3902,	//动态关卡：关卡不存在

	ERROR_CODE_DYNAMICRUNE_ITEM_NOTENOUGH                             =  3903,	//动态关卡：所需物品不充足

	ERROR_CODE_DYNAMICRUNE_LEVEL_LIMIT                                =  3904,	//动态关卡：等级不足

	ERROR_CODE_DYNAMICRUNE_NOT_INTIME                                 =  3905,	//动态关卡：不在开启时间

	ERROR_CODE_DYNAMICRUNE_NOT_MATCH                                  =  3906,	//动态关卡：关卡不匹配

	ERROR_CODE_DYNAMICRUNE_BAG_FULL                                   =  3907,	//动态关卡：背包满

	ERROR_CODE_DYNAMICRUNE_TIMES_LACK                                 =  3908,	//动态关卡：次数不足

	ERROR_CODE_DYNAMICRUNE_CANNOT_SERFIGHT                            =  3909,	//动态关卡：无法扫荡

	ERROR_CODE_DYNAMICRUNE_VIP_LACK                                   =  3910,	//动态关卡：VIP等级不足

	ERROR_CODE_CHECKIN_SERVEAR                                        =  4001,	//签到：服务器错误

	ERROR_CODE_CHECKIN_CHECKIN_NUM_ERROR                              =  4002,	//签到：MSG_C2M_GET_CHECKIN_INFO_SYN发来的checkNum错误

	ERROR_CODE_CHECKIN_HAD_RECEIVE_VIP                                =  4003,	//签到：已经领取Vip奖励，不可再次领取

	ERROR_CODE_CHECKIN_VIP_NOT_MULTIPLE                               =  4004,	//签到：无vip多倍奖励

	ERROR_CODE_CHECKIN_VIP_NOT_ENOUGH                                 =  4005,	//签到：vip等级不足无法领取vip多倍奖励

	ERROR_CODE_CHECKIN_SUPPLY_TODAY_NOT_RECEIVE                       =  4006,	//签到：今天还没签到，无法补签

	ERROR_CODE_CHECKIN_SUPPLY_NOTABLE                                 =  4007,	//签到：没有补签次数了

	ERROR_CODE_CHECKIN_SUPPLY_GOLD_NOTENOUGH                          =  4008,	//签到：元宝补签时元宝不足

	ERROR_CODE_HEROJUEDI_SERVER_ERROR                                 =  4101,	//绝地渡劫：服务器错误

	ERROR_CODE_HEROJUEDI_CHAPTEERID                                   =  4102,	//绝地渡劫：大关卡ID错误

	ERROR_CODE_HEROJUEDI_PARAGRAPHID                                  =  4103,	//绝地渡劫：小关卡ID错误

	ERROR_CODE_HEROJUEDI_CHALLENGNUM_NOTENOUGH                        =  4104,	//绝地渡劫：关卡挑战次数不足

	ERROR_CODE_HEROJUEDI_CHALLENGNUM_NOTABLE                          =  4105,	//绝地渡劫：无法挑战该关卡

	ERROR_CODE_HEROJUEDI_FIGHTALL_NOPARAGRAPH                         =  4106,	//绝地渡劫：没有可扫荡的关卡

	ERROR_CODE_HEROJUEDI_ADD_CHANCE_NOPARAGRAPH                       =  4107,	//绝地渡劫：没有需要增加挑战机会的关卡

	ERROR_CODE_HEROJUEDI_ADD_CHANCE_GOLD_NOTENOUGH                    =  4108,	//绝地渡劫：元宝不足

	ERROR_CODE_HEROJUEDI_OPEN_LEVEL                                   =  4109,	//绝地渡劫：未达到功能开放的等级

	ERROR_CODE_HEROJUEDI_FIGHTALL_LEVEL_OR_VIP                        =  4110,	//绝地渡劫：未达到扫荡所需等级或Vip等级

	ERROR_CODE_HEROJUEDI_FIGHT_CHAPTER_NEED_LEVEL                     =  4111,	//绝地渡劫：未达到挑战该关卡所需的等级

	ERROR_CODE_HEROJUEDI_ATTRIBUTE_UPGRADE_NOMORE                     =  4112,	//绝地渡劫：不能再升级

	ERROR_CODE_HEROJUEDI_ATTRIBUTE_UPGRADE_NEEDLEVEL                  =  4113,	//绝地渡劫：下一个境界所需的等级未达到

	ERROR_CODE_HEROJUEDI_ATTRIBUTE_UPGRADE_ITEM_NOTENOUGH             =  4114,	//绝地渡劫：渡劫所需境界点不充足

	ERROR_CODE_TREASURE_SERVERERROR                                   =  4201,	//诛仙探宝：服务器异常

	ERROR_CODE_TREASURE_LEVEL_LACK                                    =  4202,	//诛仙探宝：等级不足

	ERROR_CODE_TREASURE_MODE_WRONG                                    =  4203,	//诛仙探宝：数据错误

	ERROR_CODE_TREASURE_HERO_WRONG                                    =  4204,	//诛仙探宝：英雄数据错误

	ERROR_CODE_TREASURE_VIP_LACK                                      =  4205,	//诛仙探宝：VIP等级不足

	ERROR_CODE_TREASURE_POSITION_WRONG                                =  4206,	//诛仙探宝：位置错误

	ERROR_CODE_TREASURE_DATA_WRONG                                    =  4207,	//诛仙探宝：数据错误(静态表或lua错误)

	ERROR_CODE_TREASURE_MAX_LAYER                                     =  4208,	//诛仙探宝：已达到最底层

	ERROR_CODE_TREASURE_LAYER_FULL                                    =  4209,	//诛仙探宝：本层已满，无法继续探索(应该只可能在最后一层出现)

	ERROR_CODE_TREASURE_BUYTIMES_LIMIT                                =  4210,	//诛仙探宝：购买次数达到上限

	ERROR_CODE_TREASURE_GOLDCOIN_LACK                                 =  4211,	//诛仙探宝：元宝不足

	ERROR_CODE_TREASURE_TIMES_LACK                                    =  4212,	//诛仙探宝：复活次数不足

	ERROR_CODE_TREASURE_SILVER_LACK                                   =  4213,	//诛仙探宝：银两不足

	ERROR_CODE_TREASURE_RESET                                         =  4214,	//诛仙探宝：天数变更重置

	ERROR_CODE_INVITATION_CODE_SERVER_ERROR                           =  4301,	//有福同享：服务器异常

	ERROR_CODE_INVITATION_CODE_LEVEL                                  =  4302,	//有福同享：等级不够，无法进行确认、取消、删除、领奖操作

	ERROR_CODE_INVITATION_CODE_GOLD                                   =  4303,	//有福同享：强制删除时元宝不足

	ERROR_CODE_INVITATION_HTTP_101                                    =  4304,	//"有福同享：""服务器内部更新错误，请稍候重试"""

	ERROR_CODE_INVITATION_HTTP_201                                    =  4305,	//"有福同享：""邀请码不存在，请确认"""

	ERROR_CODE_INVITATION_HTTP_202                                    =  4306,	//"有福同享：""邀请码不能在当前渠道使用"""

	ERROR_CODE_INVITATION_HTTP_203                                    =  4307,	//有福同享：邀请码使用次数已达上限，请等待出师后再使用（对方三个邀请正在使用）

	ERROR_CODE_INVITATION_HTTP_204                                    =  4308,	//有福同享：已经使用过别人的邀请码，不能激活邀请码

	ERROR_CODE_INVITATION_HTTP_205                                    =  4309,	//有福同享：不要调皮，自己不能激活自己的邀请码

	ERROR_CODE_INVITATION_HTTP_206                                    =  4310,	//"有福同享：""邀请码使用次数已达上限""（对方10个邀请已用完）"

	ERROR_CODE_INVITATION_HTTP_301                                    =  4311,	//有福同享：邀请关系不存在，请确认

	ERROR_CODE_INVITATION_HTTP_302                                    =  4312,	//有福同享：当前奖励已经领取或者还不能领取，请确认

	ERROR_CODE_INVITATION_HTTP_401                                    =  4313,	//有福同享：邀请关系不存在，请确认

	ERROR_CODE_INVITATION_HTTP_402                                    =  4314,	//有福同享：当前未达到免费解除的条件，请确认

	ERROR_CODE_INVITATION_HTTP_403                                    =  4315,	//"有福同享：""邀请数已满，不能付费解除"""

	ERROR_CODE_INVITATION_HTTP_404                                    =  4316,	//有福同享：'有未领取的奖励，不能解除'

	ERROR_CODE_INVITATION_HTTP_500                                    =  4317,	//"有福同享：""服务器内部更新错误，请稍候重试"""

	ERROR_CODE_INVITATION_HTTP_501                                    =  4318,	//有福同享：被确认关系不存在

	ERROR_CODE_INVITATION_HTTP_502                                    =  4319,	//"有福同享：""参数缺失"""

	ERROR_CODE_INVITATION_HTTP_503                                    =  4320,	//"有福同享：""参数不能为空"""

	ERROR_CODE_INVITATION_HTTP_207                                    =  4321,	//有福同享：非新设备或新账户

	ERROR_CODE_INVITATION_HTTP_208                                    =  4322,	//有福同享：激活码过期失效

	ERROR_JIUYOU_SDK_SID_EMPTY                                        =  4401,	//九游SDK：客户端传过来SID为空

	ERROR_JIUYOU_SDK_WRONG_REQUEST                                    =  4402,	//九游SDK：请求参数错误

	ERROR_JIUYOU_SDK_HAVE_NOT_LOGIN                                   =  4403,	//九游SDK：还没有登陆

	ERROR_DANGLE_SDK_TOKEN_EMPTY                                      =  4501,	//当乐SDK：客户端传过来SID为空

	ERROR_DANGLE_SDK_WRONG_REQUEST                                    =  4502,	//当乐SDK：请求参数错误

	ERROR_DANGLE_SDK_HAVE_NOT_LOGIN                                   =  4503,	//当乐SDK：还没有登陆

	ERROR_91_SDK_UIN_SESSION_EMPTY                                    =  4601,	//91SDK：客户端传过来UIN或SESSION为空

	ERROR_91_SDK_WRONG_REQUEST                                        =  4602,	//91SDK：请求参数错误

	ERROR_91_SDK_HAVE_NOT_LOGIN                                       =  4603,	//91SDK：还没有登陆

	ERROR_DUOKU_SDK_UIN_SESSION_EMPTY                                 =  4701,	//多酷SDK：客户端传过来UIN或SESSION为空

	ERROR_DUOKU_SDK_WRONG_REQUEST                                     =  4702,	//多酷SDK：请求参数错误

	ERROR_DUOKU_SDK_HAVE_NOT_LOGIN                                    =  4703,	//多酷SDK：还没有登陆

	ERROR_360_SDK_UIN_SESSION_EMPTY                                   =  4801,	//360SDK：客户端传过来autheration_code为空

	ERROR_360_SDK_WRONG_REQUEST                                       =  4802,	//360SDK：请求参数错误

	ERROR_360_SDK_HAVE_NOT_LOGIN                                      =  4803,	//360SDK：还没有登陆

	ERROR_HUAWEI_SDK_UIN_SESSION_EMPTY                                =  4901,	//华为SDK：客户端传过来autheration_code为空

	ERROR_HUAWEI_SDK_WRONG_REQUEST                                    =  4902,	//华为SDK：请求参数错误

	ERROR_HUAWEI_SDK_HAVE_NOT_LOGIN                                   =  4903,	//华为SDK：还没有登陆

	ERROR_XIAOMI_SDK_UIN_SESSION_EMPTY                                =  5001,	//小米SDK：客户端传过来autheration_code为空

	ERROR_XIAOMI_SDK_WRONG_REQUEST                                    =  5002,	//小米SDK：请求参数错误

	ERROR_XIAOMI_SDK_HAVE_NOT_LOGIN                                   =  5003,	//小米SDK：还没有登陆

	ERROR_QQ_SDK_UIN_SESSION_EMPTY                                    =  5101,	//QQSDK：客户端传过来autheration_code为空

	ERROR_QQ_SDK_WRONG_REQUEST                                        =  5102,	//QQSDK：请求参数错误

	ERROR_QQ_SDK_HAVE_NOT_LOGIN                                       =  5103,	//QQSDK：还没有登陆

	ERROR_WANDOUJIA_SDK_UIN_SESSION_EMPTY                             =  5201,	//豌豆荚SDK：客户端传过来autheration_code为空

	ERROR_WANDOUJIA_SDK_WRONG_REQUEST                                 =  5202,	//豌豆荚SDK：请求参数错误

	ERROR_WANDOUJIA_SDK_HAVE_NOT_LOGIN                                =  5203,	//豌豆荚SDK：还没有登陆

	ERROR_TONGBUTUI_SDK_UIN_SESSION_EMPTY                             =  5301,	//同步推SDK：客户端传过来autheration_code为空

	ERROR_TONGBUTUI_SDK_WRONG_REQUEST                                 =  5302,	//同步推SDK：请求参数错误

	ERROR_TONGBUTUI_SDK_HAVE_NOT_LOGIN                                =  5303,	//同步推SDK：还没有登陆

	ERROR_PPHELPER_SDK_UIN_SESSION_EMPTY                              =  5401,	//PP助手SDK：客户端传过来autheration_code为空

	ERROR_PPHELPER_SDK_WRONG_REQUEST                                  =  5402,	//PP助手SDK：请求参数错误

	ERROR_PPHELPER_SDK_HAVE_NOT_LOGIN                                 =  5403,	//PP助手SDK：还没有登陆

	ERROR_OPPO_SDK_UIN_SESSION_EMPTY                                  =  5501,	//OPPOSDK：客户端传过来autheration_code为空

	ERROR_OPPO_SDK_WRONG_REQUEST                                      =  5502,	//OPPOSDK：请求参数错误

	ERROR_OPPO_SDK_HAVE_NOT_LOGIN                                     =  5503,	//OPPOSDK：还没有登陆

	ERROR_ANZHI_SDK_UIN_SESSION_EMPTY                                 =  5601,	//安智SDK：客户端传过来autheration_code为空

	ERROR_ANZHI_SDK_WRONG_REQUEST                                     =  5602,	//安智SDK：请求参数错误

	ERROR_ANZHI_SDK_HAVE_NOT_LOGIN                                    =  5603,	//安智SDK：还没有登陆

	ERROR_SDK_WRONG_REQUEST                                           =  5701,	//通用SDK：请求参数错误

	ERROR_CODE_CONSUMERANK_SEVERERROR                                 =  5801,	//消耗排行 : 服务器数据错误

	ERROR_CODE_CONSUMERANK_NOSTART                                    =  5802,	//消耗排行 : 活动尚未开始

	ERROR_CODE_CONSUMERANK_AWARDNOTEXIST                              =  5803,	//消耗排行 : 奖励不存在

};
 
#endif
