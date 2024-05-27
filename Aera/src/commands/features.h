#pragma once
#include "fiber/fiber.h"
#include "fiber/manager.h"
#include "fiber/pool.h"
#include "memory/pointers.h"
#include "rage/classes.h"
#include "rage/commands/list.h"
#include "manager/manager.h"
#include "engine/engine.h"
#include "math.h"
#include "util/util.h"
#include "util/clipboard.h"
#include "util/global.h"

namespace commands::features {
	inline CPed* cPed{};
	inline CPedWeaponManager* cPedWeaponManager{};
	inline CWeaponInfo* cWeaponInfo{};
	inline CAmmoInfo* cAmmoInfo{};
	inline CVehicle* cVehicle{};
	inline CPlayerInfo* cPlayerInfo{};
	namespace self {
		extern void beastJump(toggleCommand* command);
		extern void gracefulLanding(toggleCommand* command);
	}
	extern void init();
	extern void uninit();
	extern void onInit();
	extern void onTick();
}