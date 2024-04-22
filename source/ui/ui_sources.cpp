#include "ui/ui_sources.h"
#include "ui/ui_mods.h"

GuiSources::GuiSources(Controller& controller_, const std::string& group_) : controller(controller_), group(group_) { }

tsl::elm::Element* GuiSources::createUI() {
  auto frame = new tsl::elm::OverlayFrame("The Mod Alchemist", this->group);

  auto groupList = new tsl::elm::List();

  std::vector<std::string_view> sources = this->controller.loadSources(this->group);

  // For when the group is empty for some reason:
  if (sources.empty()) {
    auto uiMessage = new tsl::elm::CategoryHeader("Group is empty");
    frame->setContent(uiMessage);
    return frame;
  }

  // List all of the group's sources:
  for (const std::string_view &source : sources) {
    auto item = new tsl::elm::ListItem(std::string(source));

    item->setClickListener([&](u64 keys) {
      if (keys & HidNpadButton_A) {
        tsl::changeTo<GuiMods>(controller, source, group); // Use the GuiMods class to navigate to the mods UI
        return true;
      }
      return false;
    });

    groupList->addItem(item);
  }

  frame->setContent(groupList);
  return frame;
}

bool GuiSources::handleInput(
  u64 keysDown,
  u64 keysHeld,
  const HidTouchState &touchPos,
  HidAnalogStickState joyStickPosLeft,
  HidAnalogStickState joyStickPosRight
) {
  if (keysDown & HidNpadButton_B) {
    tsl::goBack();
    return true;
  }
  return false;
}
