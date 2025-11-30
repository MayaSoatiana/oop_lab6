#pragma once
#include <memory>

class NPC;
class Bear;
class Elf;
class Bandit;
class IFightObserver;

class FightVisitor {
private:
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<IFightObserver> observer;

public:
    FightVisitor(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<IFightObserver>& observer = nullptr);
    virtual ~FightVisitor() = default;
    
    virtual bool visit(const std::shared_ptr<Bear>& defender);
    virtual bool visit(const std::shared_ptr<Elf>& defender);
    virtual bool visit(const std::shared_ptr<Bandit>& defender);
};