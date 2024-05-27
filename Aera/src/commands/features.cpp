#include "features.h"
#include "script/script.h"
#include "hooking/hooking.h"
#include "renderer/renderer.h"

namespace commands::features {
	namespace self {
		void beastJump(toggleCommand* command) {

		}
		void gracefulLanding(toggleCommand* command) {

		}
	}
	void init() {
		g_manager.add(toggleCommand("gracefulLanding", "Graceful Landing", self::gracefulLanding));
		g_manager.add(toggleCommand("beastJump", "Beast Jump", self::beastJump));
	}
	void uninit() {
		Ped ped{ PLAYER::PLAYER_PED_ID() };
		ENTITY::SET_ENTITY_COLLISION(ped, TRUE, TRUE);
		ENTITY::RESET_ENTITY_ALPHA(ped);
		ENTITY::SET_ENTITY_VISIBLE(ped, TRUE, FALSE);
		ENTITY::SET_ENTITY_HAS_GRAVITY(ped, TRUE);
		PLAYER::SET_MAX_WANTED_LEVEL(5);
		PLAYER::SET_POLICE_RADAR_BLIPS(TRUE);
		Player player{ PLAYER::PLAYER_ID() };
		PLAYER::RESET_WANTED_LEVEL_HIDDEN_ESCAPE_TIME(player);
	}
	void onInit() {
		//These need to be after init because the values aren't created yet

	}
	void onTick() {
		cPed = util::classes::getPed();
		cPedWeaponManager = cPed->m_weapon_manager;
		cWeaponInfo = cPedWeaponManager->m_weapon_info;
		cAmmoInfo = cWeaponInfo->m_ammo_info;
		cVehicle = cPed->m_vehicle;
		cPlayerInfo = util::classes::getPlayerInfo();
	}
}