/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* ScriptData
SDName: Instance_Serpent_Shrine
SD%Complete: 100
SDComment: Instance Data Scripts and functions to acquire mobs and set encounter status for use in various Serpent Shrine Scripts
SDCategory: Coilfang Resevoir, Serpent Shrine Cavern
EndScriptData */

#include "precompiled.h"
#include "def_serpent_shrine.h"

#define MAX_ENCOUNTER 6

/* Serpentshrine cavern encounters:
0 - Hydross The Unstable event
1 - Leotheras The Blind Event
2 - The Lurker Below Event
3 - Fathom-Lord Karathress Event
4 - Morogrim Tidewalker Event
5 - Lady Vashj Event
*/

bool GOHello_go_bridge_console(Player* pPlayer, GameObject* go)
{
    ScriptedInstance* pInstance = go->GetInstanceData();

    if (!pInstance)
        return false;

    if (pInstance)
        pInstance->SetData(DATA_CONTROL_CONSOLE, DONE);

    return true;
}

struct TRINITY_DLL_DECL instance_serpentshrine_cavern : public ScriptedInstance
{
    instance_serpentshrine_cavern(Map* pMap) : ScriptedInstance(pMap) {Initialize();};

    uint64 LurkerBelow;
    uint64 Sharkkis;
    uint64 Tidalvess;
    uint64 Caribdis;
    uint64 LadyVashj;
    uint64 Karathress;
    uint64 KarathressEvent_Starter;
    uint64 LeotherasTheBlind;
    uint64 LeotherasEventStarter;

    uint64 ControlConsole;
    uint64 BridgePart[3];
    uint64 StrangePool;

    bool ShieldGeneratorDeactivated[4];
    uint32 m_auiEncounter[MAX_ENCOUNTER];

    void Initialize()
    {
        memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

        LurkerBelow = 0;
        Sharkkis = 0;
        Tidalvess = 0;
        Caribdis = 0;
        LadyVashj = 0;
        Karathress = 0;
        KarathressEvent_Starter = 0;
        LeotherasTheBlind = 0;
        LeotherasEventStarter = 0;

        ControlConsole = 0;
        BridgePart[0] = 0;
        BridgePart[1] = 0;
        BridgePart[2] = 0;
        StrangePool = 0;

        ShieldGeneratorDeactivated[0] = false;
        ShieldGeneratorDeactivated[1] = false;
        ShieldGeneratorDeactivated[2] = false;
        ShieldGeneratorDeactivated[3] = false;
    }

    bool IsEncounterInProgress() const
    {
        for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            if (m_auiEncounter[i] == IN_PROGRESS) return true;

        return false;
    }

    void OnGameObjectCreate(GameObject *go, bool add)
    {
        switch(go->GetEntry())
        {
            case 184568:
                ControlConsole = go->GetGUID();
                go->setActive(true);
            break;

            case 184203:
                BridgePart[0] = go->GetGUID();
                go->setActive(true);
            break;

            case 184204:
                BridgePart[1] = go->GetGUID();
                go->setActive(true);
            break;

            case 184205:
                BridgePart[2] = go->GetGUID();
                go->setActive(true);
            break;
            case 184956:
                StrangePool = go->GetGUID();
                if (go->isActiveObject())
                    SetData(DATA_STRANGE_POOL, DONE);
        }
    }

    void OnCreatureCreate(Creature *creature, bool add)
    {
        switch(creature->GetEntry())
        {
            case 21212: LadyVashj = creature->GetGUID();            break;
            case 21214: Karathress = creature->GetGUID();           break;
            case 21966: Sharkkis = creature->GetGUID();             break;
            case 21217: LurkerBelow = creature->GetGUID();          break;
            case 21965: Tidalvess = creature->GetGUID();            break;
            case 21964: Caribdis = creature->GetGUID();             break;
            case 21215: LeotherasTheBlind = creature->GetGUID();    break;}
    }

    void SetData64(uint32 type, uint64 data)
    {
        if (type == DATA_KARATHRESSEVENT_STARTER)
            KarathressEvent_Starter = data;
        if (type == DATA_LEOTHERAS_EVENT_STARTER)
            LeotherasEventStarter = data;
    }

    uint64 GetData64(uint32 identifier)
    {
        switch(identifier)
        {
            case DATA_THELURKERBELOW:           return LurkerBelow;
            case DATA_SHARKKIS:                 return Sharkkis;
            case DATA_TIDALVESS:                return Tidalvess;
            case DATA_CARIBDIS:                 return Caribdis;
            case DATA_LADYVASHJ:                return LadyVashj;
            case DATA_KARATHRESS:               return Karathress;
            case DATA_KARATHRESSEVENT_STARTER:  return KarathressEvent_Starter;
            case DATA_LEOTHERAS:                return LeotherasTheBlind;
            case DATA_LEOTHERAS_EVENT_STARTER:  return LeotherasEventStarter;
        }
        return 0;
    }

    void SetData(uint32 type, uint32 data)
    {
        switch(type)
        {
        case DATA_STRANGE_POOL: StrangePool = data;
        case DATA_CONTROL_CONSOLE:
            if (data == DONE)
            {
                HandleGameObject(BridgePart[0], true);
                HandleGameObject(BridgePart[0], true);
                HandleGameObject(BridgePart[0], true);
            }
            ControlConsole = data;
        case DATA_HYDROSSTHEUNSTABLEEVENT:  m_auiEncounter[0] = data;   break;
        case DATA_LEOTHERASTHEBLINDEVENT:   m_auiEncounter[1] = data;   break;
        case DATA_THELURKERBELOWEVENT:      m_auiEncounter[2] = data;   break;
        case DATA_KARATHRESSEVENT:          m_auiEncounter[3] = data;   break;
        case DATA_MOROGRIMTIDEWALKEREVENT:  m_auiEncounter[4] = data;   break;
            //Lady Vashj
        case DATA_LADYVASHJEVENT:
            if (data == NOT_STARTED)
            {
                ShieldGeneratorDeactivated[0] = false;
                ShieldGeneratorDeactivated[1] = false;
                ShieldGeneratorDeactivated[2] = false;
                ShieldGeneratorDeactivated[3] = false;
            }
            m_auiEncounter[5] = data;   break;
        case DATA_SHIELDGENERATOR1:ShieldGeneratorDeactivated[0] = (data) ? true : false;   break;
        case DATA_SHIELDGENERATOR2:ShieldGeneratorDeactivated[1] = (data) ? true : false;   break;
        case DATA_SHIELDGENERATOR3:ShieldGeneratorDeactivated[2] = (data) ? true : false;   break;
        case DATA_SHIELDGENERATOR4:ShieldGeneratorDeactivated[3] = (data) ? true : false;   break;
        }

        if (data == DONE)
            SaveToDB();
    }

    uint32 GetData(uint32 type)
    {
        switch(type)
        {
            case DATA_HYDROSSTHEUNSTABLEEVENT:  return m_auiEncounter[0];
            case DATA_LEOTHERASTHEBLINDEVENT:   return m_auiEncounter[1];
            case DATA_THELURKERBELOWEVENT:      return m_auiEncounter[2];
            case DATA_KARATHRESSEVENT:          return m_auiEncounter[3];
            case DATA_MOROGRIMTIDEWALKEREVENT:  return m_auiEncounter[4];
                //Lady Vashj
            case DATA_LADYVASHJEVENT:           return m_auiEncounter[5];
            case DATA_SHIELDGENERATOR1:         return ShieldGeneratorDeactivated[0];
            case DATA_SHIELDGENERATOR2:         return ShieldGeneratorDeactivated[1];
            case DATA_SHIELDGENERATOR3:         return ShieldGeneratorDeactivated[2];
            case DATA_SHIELDGENERATOR4:         return ShieldGeneratorDeactivated[3];
            case DATA_CANSTARTPHASE3:
                if (ShieldGeneratorDeactivated[0] && ShieldGeneratorDeactivated[1] && ShieldGeneratorDeactivated[2] && ShieldGeneratorDeactivated[3])return 1;break;
        }
        return 0;
    }
    std::string GetSaveData()
    {
        OUT_SAVE_INST_DATA;
        std::ostringstream stream;
        stream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " "
            << m_auiEncounter[3] << " " << m_auiEncounter[4] << " " << m_auiEncounter[5];
        char* out = new char[stream.str().length() + 1];
        strcpy(out, stream.str().c_str());
        if (out)
        {
            OUT_SAVE_INST_DATA_COMPLETE;
            return out;
        }
        return NULL;
    }

    void Load(const char* in)
    {
        if (!in)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }
        OUT_LOAD_INST_DATA(in);
        std::istringstream stream(in);
        stream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3]
        >> m_auiEncounter[4] >> m_auiEncounter[5];
        for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            if (m_auiEncounter[i] == IN_PROGRESS)                // Do not load an encounter as "In Progress" - reset it instead.
                m_auiEncounter[i] = NOT_STARTED;
        OUT_LOAD_INST_DATA_COMPLETE;
    }
};

InstanceData* GetInstanceData_instance_serpentshrine_cavern(Map* pMap)
{
    return new instance_serpentshrine_cavern(pMap);
}

void AddSC_instance_serpentshrine_cavern()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "instance_serpent_shrine";
    newscript->GetInstanceData = &GetInstanceData_instance_serpentshrine_cavern;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="go_bridge_console";
    newscript->pGOHello = &GOHello_go_bridge_console;
    newscript->RegisterSelf();
}

