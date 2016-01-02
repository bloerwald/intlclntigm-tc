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

#include "Cheat.h"
#include "Group.h"
#include "Player.h"
#include "World.h"
#include "Creature.h"

namespace WorldPackets
{
  namespace Cheat
  {
    #define WRITE_GUID_FLAG(var, x) _worldPacket.WriteBit (var[x])
    #define WRITE_GUID_BYTE(var, x) if (var[x]) _worldPacket << uint8 (var[x] ^ 1)
    #define READ_GUID_FLAG(var, x) bool has_ ## var ## _ ## x = _worldPacket.ReadBit()
    #define READ_GUID_BYTE(var, x) if (has_ ## var ## _ ## x) var[x] = _worldPacket.read<unsigned char>() ^ 1

    WorldPacket const* ClientCheatPlayerLookup::Write()
    {

      WRITE_GUID_FLAG (guid, 1);
      WRITE_GUID_FLAG (guid, 7);
      WRITE_GUID_FLAG (guildGUID, 6);
      WRITE_GUID_FLAG (guildGUID, 2);
      WRITE_GUID_FLAG (guildGUID, 4);
      WRITE_GUID_FLAG (guid, 6);
      WRITE_GUID_FLAG (guid, 2);
      WRITE_GUID_FLAG (guildGUID, 1);

      WRITE_GUID_FLAG (guildGUID, 7);
      WRITE_GUID_FLAG (guildGUID, 5);
      _worldPacket.WriteBits (name.size(), 6);

      WRITE_GUID_FLAG (guildGUID, 3);
      WRITE_GUID_FLAG (guid, 5);
      WRITE_GUID_FLAG (guid, 3);
      WRITE_GUID_FLAG (guildGUID, 0);
      WRITE_GUID_FLAG (guid, 4);
      WRITE_GUID_FLAG (guid, 0);
      _worldPacket.FlushBits();

      _worldPacket << flags3;
      WRITE_GUID_BYTE (guildGUID, 5);
      _worldPacket << firstLogin;
      _worldPacket << flags2;
      _worldPacket << sexID;
      WRITE_GUID_BYTE (guid, 6);
      WRITE_GUID_BYTE (guid, 0);
      WRITE_GUID_BYTE (guid, 1);
      _worldPacket << experienceLevel;
      _worldPacket << raceID;
      _worldPacket << flags;
      WRITE_GUID_BYTE (guid, 7);
      _worldPacket << position.y;
      _worldPacket << facialHairStyleID;
      WRITE_GUID_BYTE (guildGUID, 6);
      _worldPacket << hairColorID;
      _worldPacket << classID;
      WRITE_GUID_BYTE (guildGUID, 7);
      _worldPacket << petCreatureFamilyID;
      WRITE_GUID_BYTE (guildGUID, 4);
      _worldPacket << petExperienceLevel;
      WRITE_GUID_BYTE (guildGUID, 1);
      _worldPacket << skinID;
      WRITE_GUID_BYTE (guid, 4);
      WRITE_GUID_BYTE (guid, 3);
      _worldPacket << faceID;
      _worldPacket << position.x;
      WRITE_GUID_BYTE (guid, 5);
      WRITE_GUID_BYTE (guildGUID, 2);
      _worldPacket.WriteString (name);
      _worldPacket << hairStyleID;
      WRITE_GUID_BYTE (guid, 2);
      _worldPacket << mapID;
      _worldPacket << zoneID;
      _worldPacket << petDisplayInfoID;
      WRITE_GUID_BYTE (guildGUID, 0);
      WRITE_GUID_BYTE (guildGUID, 3);
      _worldPacket << position.z;

      return &_worldPacket;
    }

    void UserClientCheatPlayerLogin::Read()
    {
      _worldPacket >> FarClip;

      READ_GUID_FLAG (Guid, 4);
      READ_GUID_FLAG (Guid, 2);
      READ_GUID_FLAG (Guid, 0);
      READ_GUID_FLAG (Guid, 6);
      READ_GUID_FLAG (Guid, 3);
      READ_GUID_FLAG (Guid, 5);
      READ_GUID_FLAG (Guid, 1);
      READ_GUID_FLAG (Guid, 7);
      _worldPacket.FlushBits();

      Guid = ObjectGuid::Create<HighGuid::Player> (0);
      READ_GUID_BYTE (Guid, 0);
      READ_GUID_BYTE (Guid, 4);
      READ_GUID_BYTE (Guid, 7);
      READ_GUID_BYTE (Guid, 6);
      READ_GUID_BYTE (Guid, 5);
      READ_GUID_BYTE (Guid, 3);
      READ_GUID_BYTE (Guid, 1);
      READ_GUID_BYTE (Guid, 2);
    }
  }
}
