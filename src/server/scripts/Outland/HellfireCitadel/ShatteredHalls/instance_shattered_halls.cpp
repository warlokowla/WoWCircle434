/*
 * Copyright (C) 2008-2012 Trinity Core <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
SDName: Instance_Shattered_Halls
SD%Complete: 50
SDComment: currently missing info about door. instance not complete
SDCategory: Hellfire Citadel, Shattered Halls
EndScriptData */

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "shattered_halls.h"

#define MAX_ENCOUNTER  2

class instance_shattered_halls : public InstanceMapScript
{
    public:
        instance_shattered_halls() : InstanceMapScript("instance_shattered_halls", 540){}

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_shattered_halls_InstanceMapScript(map);
        }

        struct instance_shattered_halls_InstanceMapScript : public InstanceScript
        {
            instance_shattered_halls_InstanceMapScript(Map* map) : InstanceScript(map) {}

            void Initialize()
            {
                memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

                nethekurseGUID = 0;
                nethekurseDoor1GUID = 0;
                nethekurseDoor2GUID = 0;
            }

            void OnGameObjectCreate(GameObject* go)
            {
                switch (go->GetEntry())
                {
                    case GO_GRAND_WARLOCK_CHAMBER_DOOR_1:
                        nethekurseDoor1GUID = go->GetGUID();
                        break;
                    case GO_GRAND_WARLOCK_CHAMBER_DOOR_2:
                        nethekurseDoor2GUID = go->GetGUID();
                        break;
                }
            }

            void OnCreatureCreate(Creature* creature)
            {
                switch (creature->GetEntry())
                {
                    case 16807:
                        nethekurseGUID = creature->GetGUID();
                        break;
                }
            }

            void SetData(uint32 type, uint32 data)
            {
                switch (type)
                {
                    case TYPE_NETHEKURSE:
                        m_auiEncounter[0] = data;
                        if (data == DONE)
                        {
                            HandleGameObject(nethekurseDoor1GUID, true);
                            HandleGameObject(nethekurseDoor2GUID, true);
                        }
                        break;
                    case TYPE_OMROGG:
                        m_auiEncounter[1] = data;
                        break;
                }
            }

            uint32 GetData(uint32 type)
            {
                switch (type)
                {
                    case TYPE_NETHEKURSE:
                        return m_auiEncounter[0];
                    case TYPE_OMROGG:
                        return m_auiEncounter[1];
                }
                return 0;
            }

            uint64 GetData64(uint32 data)
            {
                switch (data)
                {
                    case DATA_NETHEKURSE:
                        return nethekurseGUID;
                }
                return 0;
            }

        private:

            uint32 m_auiEncounter[MAX_ENCOUNTER];
            uint64 nethekurseGUID;
            uint64 nethekurseDoor1GUID;
            uint64 nethekurseDoor2GUID;
        };
};

void AddSC_instance_shattered_halls()
{
    new instance_shattered_halls();
}

