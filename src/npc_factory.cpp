#include "npc_factory.h"

std::shared_ptr<NPC> NPCFactory::create(std::istream &is) {
    std::shared_ptr<NPC> result;
    int type{0};
    if (is >> type) {
        switch (static_cast<NpcType>(type)) {
        case NpcType::BearType:
            result = std::make_shared<Bear>(is);
            break;
        case NpcType::ElfType:
            result = std::make_shared<Elf>(is);
            break;
        case NpcType::BanditType:
            result = std::make_shared<Bandit>(is);
            break;
        default:
            std::cerr << "Unexpected NPC type: " << type << std::endl;
            break;
        }
    }

    if (result) {
        result->subscribe(std::make_shared<TextObserver>());
        result->subscribe(FileObserver::get());
    }

    return result;
}

std::shared_ptr<NPC> NPCFactory::create(NpcType type, int x, int y, const std::string& name) {
    std::shared_ptr<NPC> result;
    switch (type) {
    case NpcType::BearType:
        result = std::make_shared<Bear>(name, x, y);
        break;
    case NpcType::ElfType:
        result = std::make_shared<Elf>(name, x, y);
        break;
    case NpcType::BanditType:
        result = std::make_shared<Bandit>(name, x, y);
        break;
    default:
        std::cerr << "Unknown NPC type: " << static_cast<int>(type) << std::endl;
        break;
    }
    
    if (result) {
        result->subscribe(std::make_shared<TextObserver>());
        result->subscribe(FileObserver::get());
    }

    return result;
}