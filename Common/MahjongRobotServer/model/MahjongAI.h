#ifndef _MahjongAI_H_
#define _MahjongAI_H_

#pragma once

#include "GameLogic.h"

class CMahjongAIBase
{
public:
	CMahjongAIBase();
	~CMahjongAIBase();
	//设置牌
	void SetCardData( const BYTE cbCardData[],BYTE byCardCount, tagWeaveItem wi[MAX_WEAVE], BYTE cbWeaveCount );	
	//获取最差牌
	BYTE GetBadlyCard();													
	//获取最大分
	int GetMaxScore();	
	//思考
	virtual void Think() = 0;

protected:
	//组合是否是边
	bool IsEdge( BYTE byCard1,BYTE byCard2 );
	
	//搜索相同牌
	bool SearchSameCard( BYTE byCardData,BYTE &byIndex1,BYTE &byIndex2 );
	//搜索连牌
	bool SearchLinkCard( BYTE byCardData,BYTE &byIndex1,BYTE &byIndex2 );

	//搜索两只同牌
	bool SearchSameCardRemain( BYTE byCardData,BYTE &byIndex,BYTE byStart );
	//搜索有卡连牌
	bool SearchLinkCardRemain( BYTE byCardData,BYTE byLinkType,BYTE &byIndex,BYTE byStart );

	//搜索牌
	BYTE FindIndex( BYTE byCardData,BYTE byStart = 0 );
	//在移除最佳三只后搜索牌
	BYTE FindIndexRemain( BYTE byCardData,BYTE byStart = 0 );

public:
	//移除牌
	bool RemoveCard( BYTE byCardIndex );
	//移除牌值
	bool RemoveCardData( BYTE byCardData );

protected:
	BYTE		m_byCardData[MAX_COUNT];				//原始牌
	BYTE		m_byCardCount;							//原始牌数

	bool		m_bSelect[MAX_COUNT];					//牌是否被选择

	BYTE		m_byThreeCard[MAX_COUNT];				//三张牌组合
	BYTE		m_byThreeCount;							//三张牌组合数
	BYTE		m_byGoodThreeCard[MAX_COUNT];			//最佳三张牌组合
	BYTE		m_byGoodThreeCount;						//最佳三张牌组合数

	BYTE		m_byTwoCard[MAX_COUNT];					//两只牌组合
	BYTE		m_byTwoCount;							//两只牌组合数
	BYTE		m_byGoodTwoCard[MAX_COUNT];				//最佳两只牌组合
	BYTE		m_byGoodTwoCount;						//最佳两只牌组合数

	BYTE		m_byRemainThree[MAX_COUNT];				//移去最佳三只组合后的牌
	BYTE		m_byRemainThreeCount;					//移去最佳三只组合后的牌数

	BYTE		m_byRemainTwo[MAX_COUNT];				//移去最佳三只组合及两只组合后的牌
	BYTE		m_byRemainTwoCount;						//移去最佳三只组合及两只组合后的牌数

	int			m_nMaxScoreThree;						//最佳三只牌组合分数
	int			m_nMaxScoreTwo;							//最佳两只牌组合分数
	int			m_nActionScore;							//模拟操作得分

	int			m_nScoreThree;							//临时三只牌组合分数
	int			m_nScoreTwo;							//临时两只牌组合分数

	bool		m_bHaveJiang;							//是否有将

	BYTE		m_byBadlyCard;							//最差牌

	//胡牌限制条件
	BYTE		m_cbColorCount;							//花色数目
	BYTE		m_cbColor[4];							//花色数目
	BYTE		m_cbMinColorCount;						//最少花色
};

class CMahjongAI:public CMahjongAIBase
{
public:
	CMahjongAI(void);
	~CMahjongAI(void);
	//思考
	virtual void Think();
	//从最佳三只牌组合中搜索最差牌
	BYTE GetBadlyIn3Card();
	//从最佳两只牌组合中搜索最差牌
	BYTE GetBadlyIn2Card();
	//设置禁止出的牌
	void SetEnjoinOutCard( const BYTE cbEnjoinOutCard[],BYTE cbEnjoinOutCount );
	//模拟操作
	void SetAction( BYTE byActionMask,BYTE byActionCard );
	//重置得分
	void ResetScore();

protected:
	//加权
	int AddScore( BYTE byCardData );
	//分析三只
	void AnalyseThree();
	//分析两只
	void AnalyseTwo();
	//分析单只
	void AnalyseOne();
	//从两只组合中分析
	void SearchTwo();
	//判断牌是否禁止出
	bool IsEnjoinOutCard( BYTE byCard );

protected:
	BYTE m_byEnjoinOutCard[MAX_COUNT];				//禁止出的牌
	BYTE m_byEnjoinOutCount;						//禁止出的牌数
};

#endif