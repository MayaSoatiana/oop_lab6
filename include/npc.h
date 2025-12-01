#pragma once 

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <fstream>
#include "fight_visitor.h"

class Bear;
class Elf; 
class Bandit;
class NPC;

enum class NpcType {
    Unknown = 0,
    BearType = 1,
    ElfType = 2,
    BanditType = 3
};

class IFightObserver {
public:
    virtual ~IFightObserver() = default;
    virtual void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) = 0;
};

class NPC : public std::enable_shared_from_this<NPC> {
protected:
    std::string name;
    NpcType type;
    int x{0};
    int y{0}; 
    std::vector<std::shared_ptr<IFightObserver>> observers;

public:
    NPC(const std::string& name_, NpcType type_, int x_, int y_);
    NPC(NpcType type_, std::istream &is);
    virtual ~NPC() = default;

    const std::string& getName() const { return name; }
    NpcType getType() const { return type; }
    int getX() const { return x; }
    int getY() const { return y; }
    
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void setName(const std::string& newName) { name = newName; }
    
    void subscribe(std::shared_ptr<IFightObserver> observer);
    void fight_notify(const std::shared_ptr<NPC> defender, bool win);
    bool is_close(const std::shared_ptr<NPC> &other, size_t distance) const;

    virtual bool accept(const std::shared_ptr<FightVisitor>& attacker) = 0;
    virtual bool fight(std::shared_ptr<Bear> other) = 0;
    virtual bool fight(std::shared_ptr<Elf> other) = 0;
    virtual bool fight(std::shared_ptr<Bandit> other) = 0;
    
    virtual void print(std::ostream& os) const = 0;
    void save(std::ostream &os) const;

    friend std::ostream& operator<<(std::ostream &os, const NPC &npc);
};

using set_t = std::set<std::shared_ptr<NPC>>;