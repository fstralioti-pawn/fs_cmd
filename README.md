# fs_cmd
**FS_CMD** é um processador de comandos minimalista, rápido e funcional para **SA-MP**, com **help automático**, suporte a múltiplos argumentos e fácil integração em gamemodes ou filterscripts.
---

## 🛠 Recursos / Features

- ✅ **Registro simples de comandos**: apenas declare `FS_CMD(nome)` no seu gamemode.  
- ✅ **Help automático**: `/help` lista todos os comandos com descrição.  
- ✅ **Suporte a argumentos**: use `FS_CMD_ARGC` e `FS_CMD_ARG_INT` ou `FS_CMD_ARG` para ler parâmetros.  
- ✅ **Minimalista e rápido**: feito para desempenho máximo sem depender de grandes bibliotecas.  
- ✅ **Compatível com filterscripts e gamemodes**.  

---

## 📦 Instalação

1. Baixe o arquivo `FS_CMD.inc` e coloque na pasta `include/` do seu SA-MP.  
2. Inclua no seu gamemode:

```pawn
#include <FS_CMD>

public OnGameModeInit()
{
    FS_CMD_Init(); // Inicializa FS_CMD
    return 1;
}

## 📦 Registre seus comandos para a utilização do /help

forward FS_CMD_OnRegister();
public FS_CMD_OnRegister()
{
    FS_CMD_Register("teste", "Comando de teste");
    FS_CMD_Register("skin", "Troca a skin do jogador");
    FS_CMD_Register("vida", "Vida do jogador");
    return 1;
}

🔹 Como criar comandos

FS_CMD(teste)
{
    SendClientMessage(playerid, -1, "Comando funcionando!");
    return 1;
}

// Com argumentos
FS_CMD(vida)
{
    if(FS_CMD_ARGC(playerid) < 1)
        return SendClientMessage(playerid, -1,"Uso: /vida [quantidade]");

    new vida = FS_CMD_ARG_INT(playerid, 0);
    SetPlayerHealth(playerid, vida);
    return 1;
}

♣ /help → Lista todos os comandos registrados.

♣ FS_CMD_ARGC(playerid) → Número de argumentos passados.

♣ FS_CMD_ARG_INT(playerid, index) → Converte argumento para inteiro.

♣ FS_CMD_ARG(playerid, index, dest[], size) → Obtém argumento como string.

| Recurso                  | FS_CMD | ZCMD | YCMD |
| ------------------------ | ------ | ---- | ---- |
| Registro simples         | ✅      | ⚡    | ⚡    |
| Help automático          | ✅      | ❌    | ✅    |
| Suporte a múltiplos args | ✅      | ⚡    | ✅    |
| Minimalista              | ✅      | ❌    | ⚡    |
| Independente de lib      | ✅      | ❌    | ❌    |

FS_CMD foi pensado para rapidez e simplicidade, evitando dependências externas e macros complexas.

📌 Licença

MIT License – use, modifique e distribua livremente.

