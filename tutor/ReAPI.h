#pragma once

extern IRehldsApi *g_RehldsApi;
extern const RehldsFuncs_t *g_RehldsFuncs;
extern IRehldsServerData *g_RehldsData;
extern IRehldsHookchains *g_RehldsHookchains;
extern IRehldsServerStatic *g_RehldsSvs;

extern bool ReAPI_Init();
extern bool ReAPI_Stop();
