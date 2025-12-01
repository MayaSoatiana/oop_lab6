#include <gtest/gtest.h>
#include "npc.h"
#include "bear.h"
#include "elf.h"
#include "bandit.h"
#include "npc_factory.h"
#include "observer.h"
#include "fight_visitor.h"
#include <sstream>
#include <memory>
#include <fstream>


class NPCTest : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(NPCTest, NPCCreation) {
    Bear bear("Bear1", 10, 20);
    EXPECT_EQ(bear.getName(), "Bear1");
    EXPECT_EQ(bear.getX(), 10);
    EXPECT_EQ(bear.getY(), 20);
    EXPECT_EQ(bear.getType(), NpcType::BearType);
    
    Elf elf("Elf1", 30, 40);
    EXPECT_EQ(elf.getName(), "Elf1");
    EXPECT_EQ(elf.getX(), 30);
    EXPECT_EQ(elf.getY(), 40);
    EXPECT_EQ(elf.getType(), NpcType::ElfType);
    
    Bandit bandit("Bandit1", 50, 60);
    EXPECT_EQ(bandit.getName(), "Bandit1");
    EXPECT_EQ(bandit.getX(), 50);
    EXPECT_EQ(bandit.getY(), 60);
    EXPECT_EQ(bandit.getType(), NpcType::BanditType);
}

TEST_F(NPCTest, NPCFactoryCreation) {
    auto bear = NPCFactory::create(NpcType::BearType, 10, 20, "FactoryBear");
    ASSERT_NE(bear, nullptr);
    EXPECT_EQ(bear->getName(), "FactoryBear");
    EXPECT_EQ(bear->getX(), 10);
    EXPECT_EQ(bear->getY(), 20);
    EXPECT_EQ(bear->getType(), NpcType::BearType);
    
    auto elf = NPCFactory::create(NpcType::ElfType, 30, 40, "FactoryElf");
    ASSERT_NE(elf, nullptr);
    EXPECT_EQ(elf->getName(), "FactoryElf");
    EXPECT_EQ(elf->getX(), 30);
    EXPECT_EQ(elf->getY(), 40);
    EXPECT_EQ(elf->getType(), NpcType::ElfType);
    
    auto bandit = NPCFactory::create(NpcType::BanditType, 50, 60, "FactoryBandit");
    ASSERT_NE(bandit, nullptr);
    EXPECT_EQ(bandit->getName(), "FactoryBandit");
    EXPECT_EQ(bandit->getX(), 50);
    EXPECT_EQ(bandit->getY(), 60);
    EXPECT_EQ(bandit->getType(), NpcType::BanditType);
}

TEST_F(NPCTest, NPCFactoryFromStream) {
    std::stringstream ss;
    ss << "1 100 200 StreamBear\n";  
    ss << "2 300 400 StreamElf\n";    
    ss << "3 500 600 StreamBandit\n"; 
    
    auto bear = NPCFactory::create(ss);
    ASSERT_NE(bear, nullptr);
    EXPECT_EQ(bear->getName(), "StreamBear");
    EXPECT_EQ(bear->getX(), 100);
    EXPECT_EQ(bear->getY(), 200);
    
    auto elf = NPCFactory::create(ss);
    ASSERT_NE(elf, nullptr);
    EXPECT_EQ(elf->getName(), "StreamElf");
    EXPECT_EQ(elf->getX(), 300);
    EXPECT_EQ(elf->getY(), 400);
    
    auto bandit = NPCFactory::create(ss);
    ASSERT_NE(bandit, nullptr);
    EXPECT_EQ(bandit->getName(), "StreamBandit");
    EXPECT_EQ(bandit->getX(), 500);
    EXPECT_EQ(bandit->getY(), 600);
}

TEST_F(NPCTest, IsCloseMethod) {
    auto bear1 = std::make_shared<Bear>("Bear1", 0, 0);
    auto bear2 = std::make_shared<Bear>("Bear2", 3, 4);
    
    EXPECT_TRUE(bear1->is_close(bear2, 5));
    EXPECT_TRUE(bear1->is_close(bear2, 6));
    EXPECT_FALSE(bear1->is_close(bear2, 4));
}

TEST_F(NPCTest, BearVsElfCombat) {
    auto bear = std::make_shared<Bear>("Bear", 0, 0);
    auto elf = std::make_shared<Elf>("Elf", 1, 1);
    
    auto visitor = std::make_shared<FightVisitor>(bear);
    bool result = elf->accept(visitor);
    EXPECT_TRUE(result);
    
    auto visitor2 = std::make_shared<FightVisitor>(elf);
    bool result2 = bear->accept(visitor2);
    EXPECT_FALSE(result2);
}

TEST_F(NPCTest, ElfVsBanditCombat) {
    auto elf = std::make_shared<Elf>("Elf", 0, 0);
    auto bandit = std::make_shared<Bandit>("Bandit", 1, 1);
    
    auto visitor = std::make_shared<FightVisitor>(elf);
    bool result = bandit->accept(visitor);
    EXPECT_TRUE(result);
    
    auto visitor2 = std::make_shared<FightVisitor>(bandit);
    bool result2 = elf->accept(visitor2);
    EXPECT_FALSE(result2);
}

TEST_F(NPCTest, SameTypeCombat) {
    auto bear1 = std::make_shared<Bear>("Bear1", 0, 0);
    auto bear2 = std::make_shared<Bear>("Bear2", 1, 1);
    auto visitor1 = std::make_shared<FightVisitor>(bear1);
    bool result1 = bear2->accept(visitor1);
    EXPECT_FALSE(result1);
    
    auto elf1 = std::make_shared<Elf>("Elf1", 0, 0);
    auto elf2 = std::make_shared<Elf>("Elf2", 1, 1);
    auto visitor2 = std::make_shared<FightVisitor>(elf1);
    bool result2 = elf2->accept(visitor2);
    EXPECT_FALSE(result2);
    
    auto bandit1 = std::make_shared<Bandit>("Bandit1", 0, 0);
    auto bandit2 = std::make_shared<Bandit>("Bandit2", 1, 1);
    auto visitor3 = std::make_shared<FightVisitor>(bandit1);
    bool result3 = bandit2->accept(visitor3);
    EXPECT_TRUE(result3);
}

TEST_F(NPCTest, BanditVsBearCombat) {
    auto bandit = std::make_shared<Bandit>("Bandit", 0, 0);
    auto bear = std::make_shared<Bear>("Bear", 1, 1);
    
    auto visitor = std::make_shared<FightVisitor>(bandit);
    bool result = bear->accept(visitor);
    EXPECT_FALSE(result);
    
    auto visitor2 = std::make_shared<FightVisitor>(bear);
    bool result2 = bandit->accept(visitor2);
    EXPECT_FALSE(result2);
}

TEST_F(NPCTest, ObserverNotifications) {
    class MockObserver : public IFightObserver {
    public:
        bool wasCalled = false;
        std::shared_ptr<NPC> lastAttacker;
        std::shared_ptr<NPC> lastDefender;
        bool lastWin = false;
        
        void on_fight(const std::shared_ptr<NPC> attacker, 
                     const std::shared_ptr<NPC> defender, 
                     bool win) override {
            wasCalled = true;
            lastAttacker = attacker;
            lastDefender = defender;
            lastWin = win;
        }
    };
    
    auto observer = std::make_shared<MockObserver>();
    auto bear = std::make_shared<Bear>("AttackerBear", 0, 0);
    auto elf = std::make_shared<Elf>("DefenderElf", 1, 1);
    
    bear->subscribe(observer);
    
    auto visitor = std::make_shared<FightVisitor>(bear, observer);
    
    bool result = elf->accept(visitor);
    EXPECT_TRUE(result);  
    EXPECT_TRUE(observer->wasCalled);
    EXPECT_TRUE(observer->lastWin);  
    EXPECT_EQ(observer->lastAttacker, bear);
    EXPECT_EQ(observer->lastDefender, elf);
}

TEST_F(NPCTest, TextObserverOutput) {
    testing::internal::CaptureStdout();
    
    auto observer = std::make_shared<TextObserver>();
    auto bear = std::make_shared<Bear>("Bear", 0, 0);
    auto elf = std::make_shared<Elf>("Elf", 1, 1);
    
    observer->on_fight(bear, elf, true);
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Murder"), std::string::npos);
    EXPECT_NE(output.find("Attacker:"), std::string::npos);
    EXPECT_NE(output.find("Defender:"), std::string::npos);
}

TEST_F(NPCTest, FileObserverSingleton) {
    auto observer1 = FileObserver::get();
    auto observer2 = FileObserver::get();
    
    EXPECT_EQ(observer1, observer2);
    EXPECT_NE(observer1, nullptr);
}

TEST_F(NPCTest, FightNotification) {
    class CountingObserver : public IFightObserver {
    public:
        int callCount = 0;
        
        void on_fight(const std::shared_ptr<NPC> attacker, 
                     const std::shared_ptr<NPC> defender, 
                     bool win) override {
            callCount++;
            (void)attacker;
            (void)defender;
            (void)win;
        }
    };
    
    auto observer = std::make_shared<CountingObserver>();
    auto bear = std::make_shared<Bear>("Bear", 0, 0);
    auto elf = std::make_shared<Elf>("Elf", 1, 1);
    
    bear->subscribe(observer);
    bear->fight_notify(elf, true);
    
    EXPECT_EQ(observer->callCount, 1);
}

TEST_F(NPCTest, OutputOperators) {
    {
        std::ostringstream oss;
        Bear bear("TestBear", 123, 456);
        oss << bear;
        std::string output = oss.str();
        EXPECT_NE(output.find("Bear:"), std::string::npos);
        EXPECT_NE(output.find("TestBear"), std::string::npos);
        EXPECT_NE(output.find("123"), std::string::npos);
        EXPECT_NE(output.find("456"), std::string::npos);
    }
    
    {
        std::ostringstream oss;
        Elf elf("TestElf", 789, 101);
        oss << elf;
        std::string output = oss.str();
        EXPECT_NE(output.find("Elf:"), std::string::npos);
        EXPECT_NE(output.find("TestElf"), std::string::npos);
    }
    
    {
        std::ostringstream oss;
        Bandit bandit("TestBandit", 202, 303);
        oss << bandit;
        std::string output = oss.str();
        EXPECT_NE(output.find("Bandit:"), std::string::npos);
        EXPECT_NE(output.find("TestBandit"), std::string::npos);
    }
}

TEST_F(NPCTest, EdgeCases) {
    auto bear = std::make_shared<Bear>("Bear", 0, 0);
    EXPECT_FALSE(bear->is_close(nullptr, 10));
    
    auto elf1 = std::make_shared<Elf>("Elf1", 0, 0);
    auto elf2 = std::make_shared<Elf>("Elf2", 1000, 1000);
    EXPECT_FALSE(elf1->is_close(elf2, 10));
    EXPECT_TRUE(elf1->is_close(elf2, 1500));
    
    Bandit bandit("", 0, 0);
    EXPECT_TRUE(bandit.getName().empty());
}

TEST_F(NPCTest, FightVisitorNoObserver) {
    auto bear = std::make_shared<Bear>("Bear", 0, 0);
    auto elf = std::make_shared<Elf>("Elf", 1, 1);
    auto visitor = std::make_shared<FightVisitor>(bear);
    
    bool result = elf->accept(visitor);
    EXPECT_TRUE(result); 
}

TEST_F(NPCTest, MultipleObservers) {
    class CountingObserver : public IFightObserver {
    public:
        int count = 0;
        void on_fight(const std::shared_ptr<NPC> attacker, 
                     const std::shared_ptr<NPC> defender, 
                     bool win) override {
            count++;
            (void)attacker;
            (void)defender;
            (void)win;
        }
    };
    
    auto observer1 = std::make_shared<CountingObserver>();
    auto observer2 = std::make_shared<CountingObserver>();
    auto observer3 = std::make_shared<CountingObserver>();
    
    auto bear = std::make_shared<Bear>("Bear", 0, 0);
    auto elf = std::make_shared<Elf>("Elf", 1, 1);
    
    bear->subscribe(observer1);
    bear->subscribe(observer2);
    bear->subscribe(observer3);
    
    auto visitor = std::make_shared<FightVisitor>(bear);
    elf->accept(visitor);
    bear->fight_notify(elf, true);
    
    // All observers should be notified
    EXPECT_EQ(observer1->count, 1);
    EXPECT_EQ(observer2->count, 1);
    EXPECT_EQ(observer3->count, 1);
}

TEST_F(NPCTest, FileSaveLoadIntegration) {
    const std::string testFile = "test_npcs.txt";
    {
        std::ofstream ofs(testFile);
        ASSERT_TRUE(ofs.is_open());
        
        Bear bear("SavedBear", 100, 200);
        Elf elf("SavedElf", 300, 400);
        Bandit bandit("SavedBandit", 500, 600);
        
        bear.save(ofs);
        elf.save(ofs);
        bandit.save(ofs);
        
        ofs.close();
    }
    
    {
        std::ifstream ifs(testFile);
        ASSERT_TRUE(ifs.is_open());
        
        auto bear = NPCFactory::create(ifs);
        auto elf = NPCFactory::create(ifs);
        auto bandit = NPCFactory::create(ifs);
        
        ASSERT_NE(bear, nullptr);
        ASSERT_NE(elf, nullptr);
        ASSERT_NE(bandit, nullptr);
        
        EXPECT_EQ(bear->getName(), "SavedBear");
        EXPECT_EQ(elf->getName(), "SavedElf");
        EXPECT_EQ(bandit->getName(), "SavedBandit");
        
        ifs.close();
    }
    
    std::remove(testFile.c_str());
}

TEST_F(NPCTest, InvalidNPCType) {
    std::stringstream ss;
    ss << "99 0 0 InvalidNPC\n";  
    
    auto npc = NPCFactory::create(ss);
    EXPECT_EQ(npc, nullptr);
}

TEST_F(NPCTest, CombatRulesMatrix) {
    // Test all combinations
    struct CombatTest {
        std::shared_ptr<NPC> attacker;
        std::shared_ptr<NPC> defender;
        bool expectedResult;
    };
    
    auto bear = std::make_shared<Bear>("Bear", 0, 0);
    auto elf = std::make_shared<Elf>("Elf", 0, 0);
    auto bandit = std::make_shared<Bandit>("Bandit", 0, 0);
    
    std::vector<CombatTest> tests = {
        {bear, bear, false},      
        {bear, elf, true},        
        {bear, bandit, false},    
        
        {elf, bear, false},       
        {elf, elf, false},        
        {elf, bandit, true},      
        
        {bandit, bear, false},    
        {bandit, elf, false},     
        {bandit, bandit, true},   
    };
    
    for (const auto& test : tests) {
        auto visitor = std::make_shared<FightVisitor>(test.attacker);
        bool result = test.defender->accept(visitor);
        EXPECT_EQ(result, test.expectedResult) 
            << "Failed: " << test.attacker->getName() << " vs " << test.defender->getName();
    }
}

TEST_F(NPCTest, NPCSetters) {
    Bear bear("Original", 0, 0);
    bear.setName("NewName");
    bear.setX(100);
    bear.setY(200);
    
    EXPECT_EQ(bear.getName(), "NewName");
    EXPECT_EQ(bear.getX(), 100);
    EXPECT_EQ(bear.getY(), 200);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}