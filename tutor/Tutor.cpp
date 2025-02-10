#include "precompiled.h"

CTutor gTutor;

void CTutor::Spawn()
{
    if (!this->m_bStarted)
    {
        for (auto const Path : g_TutorPrecache)
        {
            auto File = strdup(Path);

            g_engfuncs.pfnPrecacheGeneric(File);

            free(File);
        }

        for (auto const Path : g_TutorSound)
        {
            auto File = strdup(Path);

            g_engfuncs.pfnPrecacheSound(File);

            free(File);
        }

        this->m_bStarted = true;
    }
}

void CTutor::ServerActivate()
{
    g_engfuncs.pfnAddServerCommand("cs_tutor_show", this->ShowTutor);
    g_engfuncs.pfnAddServerCommand("cs_tutor_hide", this->Hidetutor);
}

void CTutor::ServerDeactivate()
{
    this->m_bStarted = false;
}

void CTutor::StartFrame()
{
    for (int i = 1; i <= gpGlobals->maxClients; i++)
    {
        edict_t *pEntity = INDEXENT(i);

        if (!FNullEnt(pEntity))
        {
            if (!(pEntity->v.flags & FL_DORMANT))
            {
                if (this->m_TutorTimeLeft[i] > 0.0f)
                {
                    if (gpGlobals->time >= this->m_TutorTimeLeft[i])
                    {
                        this->TutorClose(pEntity);
                    }
                }
            }
        }
    }
}

void CTutor::ShowTutor()
{
    if (g_engfuncs.pfnCmd_Argc() == 5)
    {
        auto User = g_engfuncs.pfnCmd_Argv(1);

        if (User)
        {
            if (User[0u] != '\n')
            {
                auto pEntity = gTutor.FindEntity(User);

                if (!FNullEnt(pEntity))
                {
                    auto Message = g_engfuncs.pfnCmd_Argv(4);

                    if (Message)
                    {
                        if (Message[0u] != '\n')
                        {
                            // Type 0 -> GREEN  -> INFO
                            // Type 1 -> RED    -> SKULL
                            // Type 2 -> BLUE   -> SKULL
                            // Type 3 -> YELLOW -> INFO
                            // Type 4 -> GREEN  -> INFO
                            // Type 5 -> GREEN  -> INFO
                            // Type 6 -> GREEN  -> INFO
                            // Type 7 -> GREEN  -> INFO
                            // Type 8 -> YELLOW -> INFO
                            gTutor.TutorText(pEntity, Q_atoi(g_engfuncs.pfnCmd_Argv(2)), Q_atoi(g_engfuncs.pfnCmd_Argv(3)), Message);
                        }
                    }
                }
            }
        }
    }
    else
    {
        gpMetaUtilFuncs->pfnLogConsole(PLID, "[%s] Usage: %s <name or #userid> <0~8> <time> <message>", Plugin_info.logtag, g_engfuncs.pfnCmd_Argv(0));
    }
}

void CTutor::Hidetutor()
{
    if (g_engfuncs.pfnCmd_Argc() == 2)
    {
        auto User = g_engfuncs.pfnCmd_Argv(1);

        if (User)
        {
            if (User[0u] != '\n')
            {
                auto pEntity = gTutor.FindEntity(User);

                if (!FNullEnt(pEntity))
                {
                    gTutor.TutorClose(pEntity);
                }
            }
        }
    }
    else
    {
        gpMetaUtilFuncs->pfnLogConsole(PLID, "[%s] Usage: %s <name or #userid>", Plugin_info.logtag, g_engfuncs.pfnCmd_Argv(0));
    }
}

edict_t *CTutor::FindEntity(const char *Search)
{
    if (Search)
    {
        if (Search[0u] != '\0')
        {
            if (strlen(Search) > 1)
            {
                if (Search[0u] == '#')
                {
                    auto EntityIndex = Q_atoi(Search + 1);

                    if (EntityIndex > 0 && EntityIndex <= gpGlobals->maxClients)
                    {
                        edict_t *pEntity = INDEXENT(EntityIndex);

                        if (!FNullEnt(pEntity))
                        {
                            if (!(pEntity->v.flags & FL_DORMANT))
                            {
                                return pEntity;
                            }
                        }
                    }
                }
                else
                {
                    for (int i = 1; i <= gpGlobals->maxClients; i++)
                    {
                        edict_t *pEntity = INDEXENT(i);

                        if (!FNullEnt(pEntity))
                        {
                            if (!(pEntity->v.flags & FL_DORMANT))
                            {
                                if (Q_stricmp(STRING(pEntity->v.netname), Search) >= 0)
                                {
                                    return pEntity;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return nullptr;
}

void CTutor::TutorText(edict_t *pEntity, int Color, int Time, const char *Format, ...)
{
	if (!FNullEnt(pEntity))
    {
        char Text[256] = {0};

        va_list ArgPtr;
    
        va_start(ArgPtr, Format);
    
        vsnprintf(Text, sizeof(Text), Format, ArgPtr);
    
        va_end(ArgPtr);

        if (Text[0u] != '\0')
        {
            static int iMsgTutorText;

            if (iMsgTutorText || (iMsgTutorText = gpMetaUtilFuncs->pfnGetUserMsgID(PLID, "TutorText", nullptr)))
            {
                g_engfuncs.pfnMessageBegin(MSG_ONE_UNRELIABLE, iMsgTutorText, nullptr, pEntity);
                g_engfuncs.pfnWriteString(Text);
                g_engfuncs.pfnWriteByte(0);
                g_engfuncs.pfnWriteShort(0);
                g_engfuncs.pfnWriteShort(0);
                g_engfuncs.pfnWriteShort(1 << Color);
                g_engfuncs.pfnMessageEnd();
            }


            switch (Color)
            {
                case 1:
                {
                    g_engfuncs.pfnEmitSound(pEntity, CHAN_ITEM, "events/friend_died.wav", VOL_NORM, ATTN_NORM, 0, 120);
                    break;
                }
                case 2:
                {
                    g_engfuncs.pfnEmitSound(pEntity, CHAN_ITEM, "events/enemy_died.wav", VOL_NORM, ATTN_NORM, 0, 85);
                    break;
                }
                default:
                {
                    g_engfuncs.pfnEmitSound(pEntity, CHAN_ITEM, "events/tutor_msg.wav", VOL_NORM, ATTN_NORM, 0, 100);
                    break;
                }
            }

            if (Time > 0)
            {
                this->m_TutorTimeLeft[ENTINDEX(pEntity)] = (gpGlobals->time + static_cast<float>(Time));
            }
        }
	}
}

void CTutor::TutorClose(edict_t *pEntity)
{
    if (!FNullEnt(pEntity))
    {
        static int iMsgTutorClose;

        if (iMsgTutorClose || (iMsgTutorClose = gpMetaUtilFuncs->pfnGetUserMsgID(PLID, "TutorClose", nullptr)))
        {
            g_engfuncs.pfnMessageBegin(MSG_ONE_UNRELIABLE, iMsgTutorClose, nullptr, pEntity);
            g_engfuncs.pfnMessageEnd();
        }
    }
}
