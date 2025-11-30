#include "bear.h"
#include <iostream>

Bear::Bear(const std::string& name, int x_, int y_) 
    : NPC(name, NpcType::BearType, x_, y_) {}

Bear::Bear(std::istream &is) : NPC(NpcType::BearType, is) {}

bool Bear::accept(const std::shared_ptr<FightVisitor>& attacker) {
    auto bear_this = std::static_pointer_cast<Bear>(shared_from_this());
    return attacker->visit(bear_this);
}
       
bool Bear::fight(std::shared_ptr<Bear> other) {
    (void)other; 
    return false; 
}

bool Bear::fight(std::shared_ptr<Elf> other) {
    (void)other; 
    return true; 
}

bool Bear::fight(std::shared_ptr<Bandit> other) {
    (void)other; 
    return false;
}

void Bear::print(std::ostream& os) const {
    os << "Bear: " << name << " (" << x << ", " << y << ")";
}
