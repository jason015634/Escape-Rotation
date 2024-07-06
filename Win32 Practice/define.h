#pragma once
#define SINGLE(type) public: \
						static type* GetInst()\
						{\
							static type mgr;\
							 return  &mgr;\
						}\
					private:\
						type(); \
						~type();
#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()

#define CLONE(type) type* Clone() {return new type(*this);}
#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key)  KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key)  KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key)  KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key)  KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define PI 3.1415926536f
#define TILE_SIZE 64
enum class GROUP_TYPE
{
	DEFAULT,
	TILE,
	LAZER    ,            
	GROUND,
	SPIKE,
	EmptyObj,
	PORTAL,
	LEVER,                            
	PLAYER,
	UI = 31,
	END = 32,
};

enum class SCENE_TYPE
{
	START,
	TOOL,
	TITLE,
	LEVEL,
	LEVEL_CUTSCENE,	// 레벨 선택시 컷씬 진입
	STAGE_12,	// Ending
	
	STAGE_01,
	STAGE_02,
	STAGE_03,
	STAGE_04,
	STAGE_05,
	STAGE_06,
	STAGE_07,
	STAGE_08,
	STAGE_09,
	STAGE_10,
	STAGE_11,
	
	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	WHITE,
	MAGENTA,
	END,

};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	HOLLOW,
	END
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	CUTSCENE_CHANGE,

	END,

};

//배경음
enum class BGM_SOUND
{
	Stage_BGM,
	Title_BGM,
	END,
};

//효과음
enum class SFX_SOUND
{
	Lever_Off,
	Lever_On,
	Platform_Destroy,
	Player_Jump,
	Portal,
	Rotate,
	UI_Click,
	END,
};

// 채널
enum class CH
{
	CH_BGM,
	CH_SFX,
	END,
};