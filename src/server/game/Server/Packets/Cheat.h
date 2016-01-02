/*
 * Copyright (C) 2008-2015 TrinityCore <http://www.trinitycore.org/>
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

#pragma once

#include "Packet.h"
#include "SharedDefines.h"
#include "ObjectGuid.h"
#include "PacketUtilities.h"

class WorldObject;

namespace WorldPackets
{
    namespace Cheat
    {
        class ClientCheatPlayerLookup final : public ServerPacket
        {
        public:
            ClientCheatPlayerLookup() : ServerPacket(CLIENT_CHEAT_PLAYER_LOOKUP, 18 + 4) { }

            WorldPacket const* Write() override;

  /*  0..  1*/ uint8_t experienceLevel;
  /*  1..  1*/ uint8_t faceID;
  /*  4..  1*/ uint32_t flags;
  /*  8..  1*/ uint32_t flags3;
  /*  c..  1*/ uint8_t raceID;
  /* 10..  1*/ uint32_t zoneID;
  /* 14..  1*/ uint32_t petExperienceLevel;
  /* 18..  1*/ uint8_t firstLogin;
  /* 19..  1*/ uint8_t sexID;
  /* 1a..  1*/ uint8_t hairStyleID;
  /* 1c..  1*/ uint32_t mapID;
  /* 20..  1*/ uint8_t classID;
  /* 28..  1*/ ObjectGuid guid;
  /* 30..  1*/ G3D::Vector3 position;
  /* 3c..  1*/ uint32_t petCreatureFamilyID;
  /* 40..  1*/ std::string name;
  /* 71..  1*/ uint8_t hairColorID;
  /* 72..  1*/ uint8_t skinID;
  /* 74..  1*/ uint32_t petDisplayInfoID;
  /* 78..  1*/ ObjectGuid guildGUID;
  /* 80..  1*/ uint32_t flags2;
  /* 84..  1*/ uint8_t facialHairStyleID;
        };
        
        class UserClientCheatPlayerLogin final : public ClientPacket
        {
        public:
            UserClientCheatPlayerLogin(WorldPacket&& packet) : ClientPacket(USER_CLIENT_CHEAT_PLAYER_LOGIN, std::move(packet)) { }

            void Read() override;

            ObjectGuid Guid;      ///< Guid of the player that is logging in
            float FarClip = 0.0f; ///< Visibility distance (for terrain)
        };
    }
}
