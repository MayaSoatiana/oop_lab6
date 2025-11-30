#pragma once

#include <iostream>
#include "npc.h"

class Bear : public NPC {
public:
    Bear(const std::string& name, int x_, int y_);
    Bear(std::istream &is);

    bool accept(const std::shared_ptr<FightVisitor>& attacker) override;
    bool fight(std::shared_ptr<Bear> other) override;
    bool fight(std::shared_ptr<Elf> other) override;
    bool fight(std::shared_ptr<Bandit> other) override;

    // std::string get_type() const override { return "Bear"; }

    void print(std::ostream& os) const override;

    friend std::ostream& operator<<(std::ostream &os, const NPC &npc);
};