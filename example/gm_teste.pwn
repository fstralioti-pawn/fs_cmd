
#include <a_samp>
#include <FS_CMD>


main()
{
	print("\n----------------------------------");
	print("GAME MODE TESTE FS_CMD");
	print("----------------------------------\n");
}

public OnGameModeInit()
{
	// Don't use these lines if it's a filterscript
	SetGameModeText("Teste FS_CMD");
	FS_CMD_Init();
	AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
	return 1;
}

public OnGameModeExit()
{
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	return 1;
}

public OnPlayerConnect(playerid)
{
	SendClientMessage(playerid, -1,"Teste");
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	return 1;
}

public OnPlayerSpawn(playerid)
{
	return 1;
}

forward FS_CMD_OnRegister();
public FS_CMD_OnRegister()
{
    FS_CMD_Register("teste", "Comando de teste");
    FS_CMD_Register("skin", "Troca a skin do jogador");
    FS_CMD_Register("vida", "Da vida para os jogadores");
    return 1;
}

FS_CMD(teste)
{
    SendClientMessage(playerid, -1, "Funcionou!");
    return 1;
}

FS_CMD(skin)
{
    if (FS_CMD_ARGC(playerid) < 1)
        return SendClientMessage(playerid, -1, "Uso: /skin <id>");

    new skinid = FS_CMD_ARG_INT(playerid, 0);
    SetPlayerSkin(playerid, skinid);
    return 1;
}

FS_CMD(vida)
{
	if(FS_CMD_ARGC(playerid) < 1)
		return SendClientMessage(playerid, -1,"Uso: /vida [quantidade]");
		
	new vida = FS_CMD_ARG_INT(playerid, 0);
	SetPlayerHealth(playerid, vida);
	return 1;
}

