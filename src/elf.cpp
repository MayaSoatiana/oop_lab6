#include "elf.h"
#include <iostream>

Elf::Elf(const std::string& name, int x_, int y_) 
    : NPC(name, NpcType::ElfType, x_, y_) {}

Elf::Elf(std::istream &is) : NPC(NpcType::ElfType, is) {}

bool Elf::accept(const std::shared_ptr<FightVisitor>& attacker) {
    auto elf_this = std::static_pointer_cast<Elf>(shared_from_this());
    return attacker->visit(elf_this);
}
       
bool Elf::fight(std::shared_ptr<Bear> other) {
    (void)other; 
    return false;
}

bool Elf::fight(std::shared_ptr<Elf> other) {
    (void)other; 
    return false; 
}

bool Elf::fight(std::shared_ptr<Bandit> other) {
    (void)other; 
    return true; 
}

void Elf::print(std::ostream& os) const {
    os << "Elf: " << name << " (" << x << ", " << y << ")";
}