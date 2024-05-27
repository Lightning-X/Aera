#include "classdefs.h"
#include "classes.h"
#include "memory/pointers.h"

u64 rage::datBitBuffer::WriteBitsSingle(u32 value, i32 bits) {
	return pointers::g_writeBitsSingle(m_data, value, bits, m_bitsRead + m_bitOffset);
}
u32 rage::datBitBuffer::ReadBitsSingle(u32 numBits) {
	u32 result{};
	pointers::g_readBitsSingle(m_data, &result, numBits, m_bitsRead + m_bitOffset);
	return result;
}
bool rage::datBitBuffer::WriteArray(void* array, i32 size) {
	return pointers::g_writeBitbufArray(this, array, size, 0);
}
bool rage::datBitBuffer::ReadArray(void* array, i32 size) {
	return pointers::g_readBitbufArray(this, array, size, 0);
}

int CGameScriptHandlerNetComponent::get_participant_index(CNetGamePlayer* player) {
	if (player == (*pointers::g_networkPlayerMgr)->m_local_net_player)
		return m_local_participant_index;
	if (m_num_participants <= 1)
		return -1;
	for (decltype(m_num_participants) i{}; i != m_num_participants - 1; ++i) {
		if (m_participants[i] && m_participants[i]->m_net_game_player == player)
			return m_participants[i]->m_participant_index;
	}
	return -1;
}
bool CGameScriptHandlerNetComponent::force_host() {
	if (auto& cNetworkPlayerMgr = *pointers::g_networkPlayerMgr; cNetworkPlayerMgr) {
		for (int32_t i{}; !is_local_player_host(); ++i) {
			if (i > 200)
				return false;

			send_host_migration_event(cNetworkPlayerMgr->m_local_net_player);
			send_host_migration_event(cNetworkPlayerMgr->m_local_net_player);
		}
		return is_local_player_host();
	}
	return false;
}

void CNetComplaintMgr::Add(uint64_t PeerAddress, bool UseAll, bool SpoofAddress) {
	auto net_mgr = (*pointers::g_networkPlayerMgr);
	if (HasComplaint(PeerAddress) || PeerAddress == net_mgr->m_local_net_player->GetGamerInfo()->m_peer_address)
		return;
	auto old_token = m_peer_address;
	if (m_peer_address == old_token && SpoofAddress)
		m_peer_address = PeerAddress;
	if (UseAll) {
		for (auto player : net_mgr->m_player_list) {
			if (auto gamer_info = player->GetGamerInfo(); player && player->IsConnected()) {
				if (gamer_info->m_peer_address != PeerAddress)
					m_peer_addresses_complained[m_num_addresses_complained++] = gamer_info->m_peer_address;
			}
		}
	}
	m_peer_addresses_complained[m_num_addresses_complained++] = PeerAddress;
	if (m_peer_address != old_token && SpoofAddress)
		m_peer_address = old_token;
}