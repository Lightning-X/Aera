#include "self.h"

namespace ui::submenus {
	void selfSubmenu::init(submenu& submenu) {
		submenu.add(toggleOption("beastJump"_TC));
		submenu.add(toggleOption("gracefulLanding"_TC));
	}
}