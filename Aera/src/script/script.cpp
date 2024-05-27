#include "script.h"
#include "gui/interface.h"
#include "fiber/fiber.h"
#include "gui/types/option.h"
#include "gui/types/submenu_option.h"
#include "script/submenus/self.h"

namespace script {
	void onTick() {
		g_fiberPool.add([] {
			while (commands::g_manager.getCommands().empty()) {
				fiber::current()->sleep(100ms);
			}
			ui::menu::push(*ui::menuInstance<void>::get("Home", [](ui::submenu& submenu) {
				submenu.add(ui::submenuOption("Self", ui::submenus::selfSubmenu::get()));
				submenu.add(ui::option("Unload", [] {
					g_running = false;
				}));
			}));
		});
		while (true) {
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("commonmenu", FALSE);
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("timerbars", FALSE);
			ui::handlers::key::check();
			if (ui::g_open) {
				PAD::DISABLE_CONTROL_ACTION(0, ControlPhone, TRUE);
			}
			fiber::current()->sleep();
		}
	}
}