#include "observer.h"

std::shared_ptr<FileObserver> FileObserver::instance = nullptr;

void TextObserver::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) {
    if (win) {
        std::cout << std::endl << "Murder --------" << std::endl;
        std::cout << "Attacker: " << *attacker << std::endl;
        std::cout << "Defender: " << *defender << std::endl;
    }
}

FileObserver::FileObserver() {
    logfile.open("log.txt", std::ios::out | std::ios::trunc);
}

FileObserver::~FileObserver() {
    if (logfile.is_open()) {
        logfile.close();
    }
}

std::shared_ptr<FileObserver> FileObserver::get() {
    if (!instance) {
        instance = std::shared_ptr<FileObserver>(new FileObserver());
    }
    return instance;
}

void FileObserver::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) {
    if (logfile.is_open() && win) {
        logfile << "KILL: " << *attacker << " killed " << *defender << std::endl;
    }
}