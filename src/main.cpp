#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/loader/GameEvent.hpp>
#include <Geode/loader/SettingV3.hpp>

using namespace geode::prelude;

class $modify(CustomMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto visibilityMode = Mod::get()->getSettingValue<std::string>("hide-button");

        if (visibilityMode != "Visible") {
            if (auto bottomMenu = this->getChildByID("bottom-menu")) {
                if (auto geodeButton = typeinfo_cast<CCMenuItemSpriteExtra*>(bottomMenu->getChildByID("geode.loader/geode-button"))) {

                   
                    geodeButton->setVisible(false);
                    bottomMenu->updateLayout();

                    if (visibilityMode == "Ghost Mode (Mobile Safe)") {
                       
                        auto hitZoneSprite = CCSprite::create();
                        hitZoneSprite->setContentSize({ 65.f, 65.f });

                      
                        auto ghostItem = CCMenuItemSpriteExtra::create(
                            hitZoneSprite,
                            this,
                            menu_selector(CustomMenuLayer::onGhostTap)
                        );

                        auto ghostMenu = CCMenu::create();
                        ghostMenu->setID("ghost-geode-menu");
                        ghostMenu->addChild(ghostItem);

                      
                        auto winSize = CCDirector::sharedDirector()->getWinSize();
                        ghostMenu->setPosition({ winSize.width - 32.5f, winSize.height - 32.5f });

                        this->addChild(ghostMenu);
                    }
                }
            }
        }

       
        this->addEventListener(
            KeybindSettingPressedEventV3(Mod::get(), "menu-key"),
            [this](Keybind const& keybind, bool down, bool repeat, double timestamp) {
                if (down && !repeat) {
                    if (auto bottomMenu = this->getChildByID("bottom-menu")) {
                        if (auto geodeButton = typeinfo_cast<CCMenuItemSpriteExtra*>(bottomMenu->getChildByID("geode.loader/geode-button"))) {
                            geodeButton->activate();
                        }
                    }
                }
            }
        );

        return true;
    }

    
    void onGhostTap(CCObject * sender) {
        if (auto bottomMenu = this->getChildByID("bottom-menu")) {
            if (auto geodeButton = typeinfo_cast<CCMenuItemSpriteExtra*>(bottomMenu->getChildByID("geode.loader/geode-button"))) {
                geodeButton->activate();
            }
        }
    }
};