#include "IteamList.h"

auto PhotonObjectInteract::PhotonObjectInteract_Awake_NEW(void* p) -> void {
    HookManager::call(PhotonObjectInteract_Awake_NEW, p);
}

PhotonObjectInteract::PhotonObjectInteract() : Feature{} {
    HookManager::install(reinterpret_cast<void(*)(void*)>(unity::Il2cpp::Method::GetAddress("PhotonObjectInteract", "Awake", 0)), PhotonObjectInteract_Awake_NEW);
}

auto PhotonObjectInteract::GetInstance() -> PhotonObjectInteract& {
    static PhotonObjectInteract Instance;
    return Instance;
}

auto PhotonObjectInteract::GetInfo() const -> const GuiInfo& {
    static GuiInfo info{ reinterpret_cast<const char*>(u8"物品"), reinterpret_cast<const char*>(u8"物品列表"), true };
    return info;
}

auto PhotonObjectInteract::Render() -> void {
}

auto PhotonObjectInteract::Update() -> void { }

auto PhotonObjectInteract::DrawStatus() -> void {}

auto PhotonObjectInteract::Save(nlohmann::json& json) -> void {

}

auto PhotonObjectInteract::Load(nlohmann::json& json) -> void {

}
