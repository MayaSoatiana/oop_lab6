#pragma once
#include <sstream>
#include "npc.h"
#include "bear.h"
#include "elf.h"
#include "bandit.h"
#include "observer.h"

class NPCFactory {
public:
    static std::shared_ptr<NPC> create(std::istream &is);
    static std::shared_ptr<NPC> create(NpcType type, int x, int y, const std::string& name);
};
