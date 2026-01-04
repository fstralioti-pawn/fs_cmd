/*
FS_CMD 1.0

CRIADO POR: FSTRALIOTI
www.fstralioti.com.br
*/

#if defined _FS_CMD_INCLUDED
    #endinput
#endif
#define _FS_CMD_INCLUDED

#include <a_samp>

#define FS_CMD_MAX_CMDS   (64) // Limite de comandos
#define FS_CMD_MAX_ARGS   (10) // Argumentos por comando
#define FS_CMD_MAX_LEN    (32) // Tamanho do nome do comando

enum eFS_CMD
{
    cmd_name[FS_CMD_MAX_LEN],
    cmd_desc[64]
};

static FS_CMD_Data[FS_CMD_MAX_CMDS][eFS_CMD];
static FS_CMD_Count;

static FS_CMD_Argc[MAX_PLAYERS];
static FS_CMD_Args[MAX_PLAYERS][FS_CMD_MAX_ARGS][64];

#define FS_CMD(%1) \
    forward fs_cmd_%1(playerid); \
    public fs_cmd_%1(playerid)

stock FS_CMD_Register(const name[], const desc[])
{
    if (FS_CMD_Count >= FS_CMD_MAX_CMDS) return 0;

    format(FS_CMD_Data[FS_CMD_Count][cmd_name], FS_CMD_MAX_LEN, "%s", name);
    format(FS_CMD_Data[FS_CMD_Count][cmd_desc], 64, "%s", desc);
    FS_CMD_Count++;
    return 1;
}

stock FS_CMD_Init()
{
    FS_CMD_Count = 0;
    if (funcidx("FS_CMD_OnRegister") != -1)
        CallLocalFunction("FS_CMD_OnRegister", "");
    return 1;
}

stock FS_CMD_ARGC(playerid)
{
    return FS_CMD_Argc[playerid];
}

stock FS_CMD_ARG(playerid, index, dest[], size = sizeof dest)
{
    if (index >= FS_CMD_Argc[playerid]) return 0;
    format(dest, size, "%s", FS_CMD_Args[playerid][index]);
    return 1;
}

stock FS_CMD_ARG_INT(playerid, index)
{
    if (index >= FS_CMD_Argc[playerid]) return 0;
    return strval(FS_CMD_Args[playerid][index]);
}

static FS_CMD_ShowHelp(playerid, const cmdname[] = "")
{
    if (!strlen(cmdname))
    {
        SendClientMessage(playerid, -1, "COMANDOS DISPONÍVEIS:");
        for (new i; i < FS_CMD_Count; i++)
        {
            new msg[96];
            format(msg, sizeof msg, "/%s - %s",
                FS_CMD_Data[i][cmd_name],
                FS_CMD_Data[i][cmd_desc]);
            SendClientMessage(playerid, -1, msg);
        }
        return 1;
    }

    for (new i; i < FS_CMD_Count; i++)
    {
        if (!strcmp(cmdname, FS_CMD_Data[i][cmd_name], true))
        {
            new msg[96];
            format(msg, sizeof msg, "/%s - %s",
                FS_CMD_Data[i][cmd_name],
                FS_CMD_Data[i][cmd_desc]);
            SendClientMessage(playerid, -1, msg);
            return 1;
        }
    }

    SendClientMessage(playerid, -1, "Comando não encontrado.");
    return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
    new cmd[FS_CMD_MAX_LEN];
    new idx;

    if (cmdtext[0] != '/') return 0;

    idx = strfind(cmdtext, " ");
    if (idx == -1)
        format(cmd, sizeof cmd, "%s", cmdtext[1]);
    else
        strmid(cmd, cmdtext, 1, idx);

    FS_CMD_Argc[playerid] = 0;

    if (idx != -1)
    {
        new args[128];
        format(args, sizeof args, "%s", cmdtext[idx + 1]);

        new pos, len = strlen(args);
        while (pos < len && FS_CMD_Argc[playerid] < FS_CMD_MAX_ARGS)
        {
            while (args[pos] == ' ') pos++;
            if (pos >= len) break;

            new start = pos;
            while (pos < len && args[pos] != ' ') pos++;

            strmid(
                FS_CMD_Args[playerid][FS_CMD_Argc[playerid]],
                args,
                start,
                pos,
                64
            );
            FS_CMD_Argc[playerid]++;
        }
    }

    if (!strcmp(cmd, "help", true))
    {
        if (FS_CMD_Argc[playerid] > 0)
            return FS_CMD_ShowHelp(playerid, FS_CMD_Args[playerid][0]);
        return FS_CMD_ShowHelp(playerid);
    }

    for (new i; i < FS_CMD_Count; i++)
    {
        if (!strcmp(cmd, FS_CMD_Data[i][cmd_name], true))
        {
            new fname[64];
            format(fname, sizeof fname, "fs_cmd_%s", FS_CMD_Data[i][cmd_name]);
            CallLocalFunction(fname, "i", playerid);
            return 1;
        }
    }

    SendClientMessage(playerid, -1, "Comando desconhecido.");
    return 1;
}
