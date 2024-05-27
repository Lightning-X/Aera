#pragma once
#include "pch/pch.h"

namespace lists {
	struct scenario {
		std::string_view m_label{};
		std::string_view m_key{};
	};
	constexpr scenario g_scenarios[60]{
		{ "Drill", "WORLD_HUMAN_CONST_DRILL" },
		{ "Drink Coffee", "WORLD_HUMAN_AA_COFFEE" },
		{ "Smoke", "WORLD_HUMAN_AA_SMOKE" },
		{ "Binoculars", "WORLD_HUMAN_BINOCULARS" },
		{ "Freeway Bum", "WORLD_HUMAN_BUM_FREEWAY" },
		{ "Slumped Bum", "WORLD_HUMAN_BUM_SLUMPED" },
		{ "Standing Bum", "WORLD_HUMAN_BUM_STANDING" },
		{ "Bum Washing", "WORLD_HUMAN_BUM_WASH" },
		{ "Park Attendant", "WORLD_HUMAN_CAR_PARK_ATTENDANT" },
		{ "Clipboard", "WORLD_HUMAN_CLIPBOARD" },
		{ "Idle Cop", "WORLD_HUMAN_COP_IDLES" },
		{ "Drinking", "WORLD_HUMAN_CHEERING" },
		{ "Drug Dealer", "WORLD_HUMAN_DRUG_DEALER" },
		{ "Drug Dealer (Hard)", "WORLD_HUMAN_DRUG_DEALER_HARD" },
		{ "Mobile Film", "WORLD_HUMAN_MOBILE_FILM_SHOCKING" },
		{ "Leaf Blower", "WORLD_HUMAN_GARDENER_LEAF_BLOWER" },
		{ "Gardener", "WORLD_HUMAN_GARDENER_PLANT" },
		{ "Golf Player", "WORLD_HUMAN_GOLF_PLAYER" },
		{ "Guard Patrol", "WORLD_HUMAN_GUARD_PATROL" },
		{ "Guard Stand", "WORLD_HUMAN_GUARD_STAND" },
		{ "Guard Stand (Military)", "WORLD_HUMAN_GUARD_STAND_ARMY" },
		{ "Hammering", "WORLD_HUMAN_HAMMERING" },
		{ "Hangout Street", "WORLD_HUMAN_HANG_OUT_STREET" },
		{ "Hiker Standing", "WORLD_HUMAN_HIKER_STANDING" },
		{ "Janitor", "WORLD_HUMAN_JOG_STANDING" },
		{ "Jog Standing", "WORLD_HUMAN_HIKER_STANDING" },
		{ "Leaning", "WORLD_HUMAN_LEANING" },
		{ "Maid Cleaning", "WORLD_HUMAN_MAID_CLEAN" },
		{ "Muscle Flex", "WORLD_HUMAN_MUSCLE_FLEX" },
		{ "Free Weights", "WORLD_HUMAN_MUSCLE_FREE_WEIGHTS" },
		{ "Musician", "WORLD_HUMAN_MUSICIAN" },
		{ "Paparazzi", "WORLD_HUMAN_PAPARAZZI" },
		{ "Partying", "WORLD_HUMAN_PARTYING" },
		{ "Picnic", "WORLD_HUMAN_PICNIC" },
		{ "Prostitute (High)", "WORLD_HUMAN_PROSTITUTE_HIGH_CLASS" },
		{ "Prostitute (Low)", "WORLD_HUMAN_PROSTITUTE_LOW_CLASS" },
		{ "Pushups", "WORLD_HUMAN_PUSH_UPS" },
		{ "Security Shine Torch", "WORLD_HUMAN_SECURITY_SHINE_TORCH" },
		{ "Situps", "WORLD_HUMAN_SIT_UPS" },
		{ "Smoking", "WORLD_HUMAN_SMOKING" },
		{ "Smoking Pot", "WORLD_HUMAN_SMOKING_POT" },
		{ "Standing By Fire", "WORLD_HUMAN_STAND_FIRE" },
		{ "Fishining", "WORLD_HUMAN_STAND_FISHING" },
		{ "Impatient", "WORLD_HUMAN_STAND_IMPATIENT" },
		{ "Stand Mobile", "WORLD_HUMAN_STAND_MOBILE" },
		{ "Strip Watch", "WORLD_HUMAN_STRIP_WATCH_STAND" },
		{ "Stupor", "WORLD_HUMAN_STUPOR" },
		{ "Sunbathing (Front)", "WORLD_HUMAN_SUNBATHE" },
		{ "Sunbathing (Back)", "WORLD_HUMAN_SUNBATHE_BACK" },
		{ "Superhero", "WORLD_HUMAN_SUPERHERO" },
		{ "Swimming", "WORLD_HUMAN_SWIMMING" },
		{ "Tennis", "WORLD_HUMAN_TENNIS_PLAYER" },
		{ "Tourist (Map)", "WORLD_HUMAN_TOURIST_MAP" },
		{ "Tourist (Mobile)", "WORLD_HUMAN_TOURIST_MOBILE" },
		{ "Mechine", "WORLD_HUMAN_VEHICLE_MECHANIC" },
		{ "Welding", "WORLD_HUMAN_WELDING" },
		{ "Window Shopping", "WORLD_HUMAN_WINDOW_SHOP_BROWSE" },
		{ "Yoga", "WORLD_HUMAN_YOGA" }
	};
}