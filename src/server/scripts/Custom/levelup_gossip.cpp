#include "ScriptPCH.h"
#include <cstring>


#define GOSSIP_ITEM_1       "Level 19"
#define GOSSIP_ITEM_2       "Level 60"
#define GOSSIP_ITEM_3       "Level 70"
#define GOSSIP_ITEM_4       "Level 80"

class levelup_gossip : public CreatureScript
{
    public:

        levelup_gossip() : CreatureScript("levelup_gossip") { }

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
	     pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
	     pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
            	pPlayer->PlayerTalkClass->SendGossipMenu(1, pCreature->GetGUID());

            return true;
        }

       bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction){
		pPlayer->PlayerTalkClass->ClearMenus();
		switch(uiAction){ 
		case GOSSIP_ACTION_INFO_DEF+1: pPlayer->GiveLevel(19); player->InitTalentForLevel(); player->SetUInt32Value(PLAYER_XP,0); player->TeleportTo(0, -8639.493164, -540.788818, 145.377731, 5.640298); break;
          	case GOSSIP_ACTION_INFO_DEF+2: pPlayer->GiveLevel(60); player->InitTalentForLevel(); player->SetUInt32Value(PLAYER_XP,0); player->TeleportTo(0, -8751.357422, 373.591400, 101.056320, 4.275435); break;
         	case GOSSIP_ACTION_INFO_DEF+3: pPlayer->GiveLevel(70); player->InitTalentForLevel(); player->SetUInt32Value(PLAYER_XP,0); player->TeleportTo(0, -9667.258789, 691.078003, 36.927094, 5.846066); break;
         	case GOSSIP_ACTION_INFO_DEF+4: pPlayer->GiveLevel(80); player->InitTalentForLevel(); player->SetUInt32Value(PLAYER_XP,0); player->TeleportTo(571, 558.987183, -5000.711914, 11.273766, 5.967137); break;
          //can't remember if 'default:' is needed
		}
     pPlayer->CLOSE_GOSSIP_MENU();
     return true;
}
};

void AddSC_levelup_gossip()
{
    new levelup_gossip();
}
