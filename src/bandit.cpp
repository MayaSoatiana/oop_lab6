#include "bandit.h"
#include <iostream>

Bandit::Bandit(const std::string& name, int x_, int y_) 
    : NPC(name, NpcType::BanditType, x_, y_) {}

Bandit::Bandit(std::istream &is) : NPC(NpcType::BanditType, is) {}

bool Bandit::accept(const std::shared_ptr<FightVisitor>& attacker) {
    auto bandit_this = std::static_pointer_cast<Bandit>(shared_from_this());
    return attacker->visit(bandit_this);
}
       
bool Bandit::fight(std::shared_ptr<Bear> other) {
    (void)other; 
    return false;
}

bool Bandit::fight(std::shared_ptr<Elf> other) {
    (void)other; 
    return false; 
}

bool Bandit::fight(std::shared_ptr<Bandit> other) {
    (void)other; 
    return true; 
}

void Bandit::print(std::ostream& os) const {
    os << "Bandit: " << name << " (" << x << ", " << y << ")";
}
