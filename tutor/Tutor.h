#pragma once

constexpr auto g_TutorPrecache =
{
	"gfx/career/icon_!.tga",
	"gfx/career/icon_!-bigger.tga",
	"gfx/career/icon_i.tga",
	"gfx/career/icon_i-bigger.tga",
	"gfx/career/icon_skulls.tga",
	"gfx/career/round_corner_ne.tga",
	"gfx/career/round_corner_nw.tga",
	"gfx/career/round_corner_se.tga",
	"gfx/career/round_corner_sw.tga",
	"resource/TutorScheme.res",
	"resource/UI/TutorTextWindow.res"
};

constexpr auto g_TutorSound =
{
    "events/enemy_died.wav",
    "events/friend_died.wav",
    "events/task_complete.wav",
    "events/tutor_msg.wav"
};

class CTutor
{
public:
    void Spawn();

    void ServerActivate();
    void ServerDeactivate();
	void StartFrame();

    static void ShowTutor();
	static void Hidetutor();

	edict_t* FindEntity(const char* Search);
    
    void TutorText(edict_t *pEntity, int Color, int Time, const char *Format, ...);
	void TutorClose(edict_t *pEntity);

private:
    bool m_bStarted = false;
	float m_TutorTimeLeft[MAX_CLIENTS + 1] = { 0.0f };
};

extern CTutor gTutor;