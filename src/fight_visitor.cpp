#include "fight_visitor.h"
#include "npc.h"
#include "bear.h"
#include "elf.h"
#include "bandit.h"
#include "observer.h"

FightVisitor::FightVisitor(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<IFightObserver>& observer)
    : attacker(attacker), observer(observer) {}

bool FightVisitor::visit(const std::shared_ptr<Bear>& defender) {
    bool win = attacker->fight(defender);
    if (observer) {
        observer->on_fight(attacker, defender, win);
    }
    return win;
}

bool FightVisitor::visit(const std::shared_ptr<Elf>& defender) {
    bool win = attacker->fight(defender);
    if (observer) {
        observer->on_fight(attacker, defender, win);
    }
    return win;
}

bool FightVisitor::visit(const std::shared_ptr<Bandit>& defender) {
    bool win = attacker->fight(defender);
    if (observer) {
        observer->on_fight(attacker, defender, win);
    }
    return win;
}