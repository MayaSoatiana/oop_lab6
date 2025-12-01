#include <iostream>
#include <set>
#include <fstream>
#include <memory>
#include <random>
#include "npc.h"
#include "npc_factory.h"
#include "observer.h"
#include "fight_visitor.h"
#include <cstring>

using set_t = std::set<std::shared_ptr<NPC>>;

class CombatManager {
private:
    set_t npcs;
    std::shared_ptr<IFightObserver> observer;

    std::random_device rd;
    std::mt19937 gen;

public:
    CombatManager() : gen(rd()) {}  

    void addNPC(const std::shared_ptr<NPC>& npc) {
        npcs.insert(npc);
    }

    const set_t& getNPCs() const {
        return npcs;
    }

    void save(const std::string &filename) const {
        std::ofstream fs(filename);
        if (!fs.is_open()) {
            throw std::runtime_error("Cannot open file for writing: " + filename);
        }
        
        fs << npcs.size() << std::endl;
        for (auto &n : npcs) {
            n->save(fs);
        }
        fs.flush();
        fs.close();
        
        std::cout << "Saved " << npcs.size() << " NPCs to " << filename << std::endl;
    }

    void load(const std::string &filename) {
        set_t result;
        std::ifstream is(filename);
        if (is.good() && is.is_open()) {
            int count;
            is >> count;
            for (int i = 0; i < count; ++i) {
                auto npc = NPCFactory::create(is);
                if (npc) {
                    result.insert(npc);
                }
            }
            is.close();
            npcs = result;
            std::cout << "Loaded " << result.size() << " NPCs from " << filename << std::endl;
        } else {
            std::cerr << "Error loading file: " << filename << " - " << std::strerror(errno) << std::endl;
        }
    }

    void generateRandomNPCs(int count = 10) {
        std::cout << "Generating " << count << " random NPCs..." << std::endl;
        
        std::uniform_int_distribution<> typeDist(1, 3);    
        std::uniform_int_distribution<> coordDist(0, 500); 
        std::uniform_int_distribution<> nameDist(1, 1000); 

        for (int i = 0; i < count; ++i) {
            NpcType type = static_cast<NpcType>(typeDist(gen));
            std::string name = std::to_string(nameDist(gen)); 
            int x = coordDist(gen);
            int y = coordDist(gen);
            
            auto npc = NPCFactory::create(type, x, y, name);
            if (npc) {
                addNPC(npc);
            }
        }
        
        std::cout << "Generated " << npcs.size() << " NPCs" << std::endl;
    }

    void fight(size_t distance) {
        set_t dead_list;

        for (const auto &attacker : npcs) {
            for (const auto &defender : npcs) {
                if ((attacker != defender) && attacker->is_close(defender, distance) && !dead_list.count(defender)) {
                    auto visitor = std::make_shared<FightVisitor>(attacker);
                    
                    bool success = defender->accept(visitor);
                    if (success) {
                        dead_list.insert(defender);
                        attacker->fight_notify(defender, true);
                    }
                }
            }
        }

        for (auto &d : dead_list) {
            npcs.erase(d);
        }

        std::cout << "Fight stats ----------" << std::endl
                  << "distance: " << distance << std::endl
                  << "killed: " << dead_list.size() << std::endl
                  << "survivors: " << npcs.size() << std::endl
                  << std::endl;
    }

    void runCombatSimulation() {
        std::cout << "Fighting ..." << std::endl;
        for (size_t distance = 20; (distance <= 100) && !npcs.empty(); distance += 10) {
            fight(distance);
        }
    }

    void printResults() const {
        std::cout << "\n=== FINAL RESULTS ===" << std::endl;
        std::cout << "Survivors: " << npcs.size() << std::endl;
        if (!npcs.empty()) {
            for (auto &n : npcs) {
                n->print(std::cout);
                std::cout << std::endl;
            }
        }
    }
};


std::ostream &operator<<(std::ostream &os, const set_t &npcs) {
    for (auto &n : npcs) {
        n->print(os);
        os << std::endl;
    }
    return os;
}

int main() {
    CombatManager manager;
    try {
        std::cout << "=== Balagur Fate 3 Dungeon Editor ===" << std::endl;

        manager.generateRandomNPCs(10);

        std::cout << "\nInitial NPCs (" << manager.getNPCs().size() << "):" << std::endl;
        std::cout << manager.getNPCs();
    
        std::cout << "\nSaving to file..." << std::endl;
        manager.save("dungeon.txt");

        std::cout << "\nLoading from file..." << std::endl;
        manager.load("dungeon.txt");

        manager.runCombatSimulation();

        manager.printResults();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}