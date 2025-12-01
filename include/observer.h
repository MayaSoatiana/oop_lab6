#pragma once

#include "npc.h"
#include <fstream>

class TextObserver : public IFightObserver {
public:
    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override;
};

class FileObserver : public IFightObserver {
private:
    std::ofstream logfile;
    FileObserver(); 
    static std::shared_ptr<FileObserver> instance; 

public:
    ~FileObserver();
    static std::shared_ptr<FileObserver> get();
    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override;
};