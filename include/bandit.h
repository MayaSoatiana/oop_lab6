#pragma once 

#include <iostream>
#include "npc.h"

class Bandit : public NPC{
public:
    Bandit(const std::string& name, int x_, int y_);
    Bandit(std::istream &is);

    bool accept(const std::shared_ptr<FightVisitor>& attacker) override;
    bool fight(std::shared_ptr<Bear> other) override;
    bool fight(std::shared_ptr<Elf> other) override;
    bool fight(std::shared_ptr<Bandit> other) override;

    void print(std::ostream& os) const override;
};