#include "npc.h"
#include <cmath>

NPC::NPC(const std::string& name_, NpcType type_, int x_, int y_) 
    : name(name_), type(type_), x(x_), y(y_) {}

NPC::NPC(NpcType type_, std::istream &is) : type(type_) {
    is >> x >> y >> name;
}

void NPC::subscribe(std::shared_ptr<IFightObserver> observer) {
    observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> defender, bool win) {
    for (auto &ob : observers) {
        ob->on_fight(shared_from_this(), defender, win);
    }
}

bool NPC::is_close(const std::shared_ptr<NPC> &other, size_t distance) const {
    if (!other) return false;
    double dx = static_cast<double>(x - other->x);
    double dy = static_cast<double>(y - other->y);
    return std::sqrt(dx * dx + dy * dy) <= distance;
}

void NPC::save(std::ostream &os) const {
    os << static_cast<int>(type) << " " << x << " " << y << " " << name << std::endl;
}

std::ostream& operator<<(std::ostream &os, const NPC &npc) {
    npc.print(os);
    return os;
}