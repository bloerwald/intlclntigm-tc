/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
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
SDName: Instance_Mechanar
SD%Complete: 100
SDComment:
SDCategory: Mechanar
EndScriptData */

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "mechanar.h"

class instance_mechanar : public InstanceMapScript
{
    public: instance_mechanar(): InstanceMapScript("instance_mechanar", 554) {}

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_mechanar_InstanceMapScript(map);
        }

        struct instance_mechanar_InstanceMapScript : public InstanceScript
        {
            instance_mechanar_InstanceMapScript(Map* map) : InstanceScript(map)
            {
                SetBossNumber(EncounterCount);
            }



            uint32 GetData(uint32 type) const
            {
                switch (type)
                {
                    case DATA_GATEWATCHER_GYROKILL:   return SetBossNumber[DATA_GATEWATCHER_GYROKILL];
                    case DATA_IRON_HAND:   return SetBossNumber[DATA_IRON_HAND];
                    case DATA_MECHANOLORD_CAPACITUS:   return SetBossNumber[DATA_MECHANOLORD_CAPACITUS];
                    case DATA_NETHERMANCER_SEPRETHREA:   return SetBossNumber[DATA_NETHERMANCER_SEPRETHREA];
                    case DATA_PATHALEON_THE_CALCULATOR:   return SetBossNumber[DATA_PATHALEON_THE_CALCULATOR];
                }

                return false;
            }

            uint64 GetData64(uint32 /*identifier*/) const
            {
                return 0;
            }

            bool SetBossState(uint32 type, EncounterState state)
            {
                if (!InstanceScript::SetBossState(type, state))
                    return false;

                switch (type)
                {
                    case DATA_GATEWATCHER_GYROKILL:
                    case DATA_IRON_HAND:
                    case DATA_MECHANOLORD_CAPACITUS:
                    case DATA_NETHERMANCER_SEPRETHREA:
                    case DATA_PATHALEON_THE_CALCULATOR:
                        break;
                    default:
                        break;
                }

                return true;
            }

            std::string GetSaveData()
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "S O " << GetBossSaveData();

                OUT_SAVE_INST_DATA_COMPLETE;
                return saveStream.str();
            }

            void Load(const char* str)
            {
                if (!str)
                {
                    OUT_LOAD_INST_DATA_FAIL;
                    return;
                }

                OUT_LOAD_INST_DATA(str);

                char dataHead1, dataHead2;

                std::istringstream loadStream(str);
                loadStream >> dataHead1 >> dataHead2;

                if (dataHead1 == 'S' && dataHead2 == 'O')
                {
                    for (uint32 i = 0; i < EncounterCount; ++i)
                    {
                        uint32 tmpState;
                        loadStream >> tmpState;
                        if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                            tmpState = NOT_STARTED;
                        SetBossState(i, EncounterState(tmpState));
                    }
                }
                else
                    OUT_LOAD_INST_DATA_FAIL;

                OUT_LOAD_INST_DATA_COMPLETE;
            }
        };
};

void AddSC_instance_mechanar()
{
    new instance_mechanar;
}

