#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE


#ifdef WIN32
#include <Windows.h>
#endif

#include "Typedef.h"

//数值掩码
#define	LOGIC_MASK_COLOR			0xF0								//花色掩码
#define	LOGIC_MASK_VALUE			0x0F								//数值掩码

//////////////////////////////////////////////////////////////////////////
//扑克类型
#define CT_SINGLE					1									//单牌类型
#define CT_ONE_LONG					2									//对子类型
#define CT_TWO_LONG					3									//两对类型
#define CT_THREE_TIAO				4									//三条类型
#define	CT_SHUN_ZI					5									//顺子类型
#define CT_TONG_HUA					6									//同花类型
#define CT_HU_LU					7									//葫芦类型
#define CT_TIE_ZHI					8									//铁支类型
#define CT_TONG_HUA_SHUN			9									//同花顺型
#define CT_KING_TONG_HUA_SHUN		10									//皇家同花顺

//////////////////////////////////////////////////////////////////////////

//数目定义
#define FULL_COUNT					    52									//全牌数目
#define MAX_COUNT						2									//最大数目
#define MAX_CENTERCOUNT					5									//最大数目

//////////////////////////////////////////////////////////////////////////
#define CountArray(array) ((sizeof(array))/(sizeof(array[0])))
#define ZeroMemory(src,len) (memset((src), 0, (len)))
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y)) 

struct Card
{
	BYTE value;
	bool used;
	int index;

	Card()
	{
		used = false;
		index = -1;
	}
};

//////////////////////////////////////////////////////////////////////////
//胜利信息结构
/*struct UserWinList
{
	BYTE bSameCount;
	WORD wWinerList[GAME_PLAYER];
};*/

//分析结构
struct tagAnalyseResult
{
	BYTE 							cbFourCount;						//四张数目
	BYTE 							cbThreeCount;						//三张数目
	BYTE 							cbLONGCount;						//两张数目
	BYTE							cbSignedCount;						//单张数目
	BYTE 							cbFourLogicVolue[1];				//四张列表
	BYTE 							cbThreeLogicVolue[1];				//三张列表
	BYTE 							cbLONGLogicVolue[2];				//两张列表
	BYTE 							cbSignedLogicVolue[5];				//单张列表
	BYTE							cbFourCardData[MAX_CENTERCOUNT];			//四张列表
	BYTE							cbThreeCardData[MAX_CENTERCOUNT];			//三张列表
	BYTE							cbLONGCardData[MAX_CENTERCOUNT];		//两张列表
	BYTE							cbSignedCardData[MAX_CENTERCOUNT];		//单张数目
};
//////////////////////////////////////////////////////////////////////////

//游戏逻辑
class GameLogic
{
	//函数定义
public:
	//构造函数
	GameLogic();
	//析构函数
	virtual ~GameLogic();

	static Card						CardList[52];
	static void initCardList();
	//变量定义
private:
	static BYTE						m_cbCardData[FULL_COUNT];				//扑克定义

	//控制函数
public:
	//排列扑克
	void SortCardList(BYTE cbCardData[], BYTE cbCardCount);
	//混乱扑克
	VOID RandCardList(BYTE cbCardBuffer[], BYTE cbBufferCount);
	//生成特殊牌型
	VOID RandSpecialCard(BYTE cbCardBuffer[], BYTE cbBufferCount, short jackcardtype);
	VOID RandSpecialThree(BYTE cbCardBuffer[], BYTE cbBufferCount);
	VOID RandSpecialShunzi(BYTE cbCardBuffer[], BYTE cbBufferCount);
	VOID RandSpecialTongHua(BYTE cbCardBuffer[], BYTE cbBufferCount);
	VOID RandSpecialHulu(BYTE cbCardBuffer[], BYTE cbBufferCount);
	VOID RandSpecialFour(BYTE cbCardBuffer[], BYTE cbBufferCount);
	VOID RandSpecialTong(BYTE cbCardBuffer[], BYTE cbBufferCount);
	VOID RandSpecialKingTong(BYTE cbCardBuffer[], BYTE cbBufferCount);

	void RandSpecialCardList(BYTE cbCardBuffer[], BYTE cbBufferCount, const std::vector<int>& res);
	//类型函数
public:
	//获取类型
	BYTE GetCardType(BYTE cbCardData[], BYTE cbCardCount);
	//获取两张牌的类型
	BYTE GetTwoCardType(BYTE cbCardData[], BYTE cbCardCount);
	//获取数值
	static BYTE GetCardValue(BYTE cbCardData) { return cbCardData&LOGIC_MASK_VALUE; }
	//获取花色
	static BYTE GetCardColor(BYTE cbCardData) { return cbCardData&LOGIC_MASK_COLOR; }

	//获取倍数
	BYTE GetTimes(BYTE cbCardData[], BYTE cbCardCount);

	//功能函数
public:
	//逻辑数值
	static BYTE GetCardLogicValue(BYTE cbCardData);
	//对比扑克
	BYTE CompareCard(BYTE cbFirstData[], BYTE cbNextData[], BYTE cbCardCount);
	//分析扑克
	void AnalysebCardData(const BYTE cbCardData[], BYTE cbCardCount, tagAnalyseResult & AnalyseResult);
	//7返5
	BYTE FiveFromSeven(BYTE cbHandCardData[],BYTE cbHandCardCount,BYTE cbCenterCardData[],BYTE cbCenterCardCount,BYTE cbLastCardData[],BYTE cbLastCardCount);
	//6返5
	BYTE FiveFromSix(BYTE cbHandCardData[],BYTE cbHandCardCount,BYTE cbCenterCardData[],BYTE cbCenterCardCount,BYTE cbLastCardData[],BYTE cbLastCardCount);
	//查找最大
	//bool SelectMaxUser(BYTE bCardData[GAME_PLAYER][MAX_CENTERCOUNT],UserWinList &EndResult,const LONG lAddScore[]);
};

//////////////////////////////////////////////////////////////////////////

#endif

