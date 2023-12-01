#include "Ghost.hpp"

auto Ghost::InitOnce() -> void {
	if (const auto pClass = I::Get("Assembly-CSharp.dll")->Get("GhostAI")) {
		mAwake = pClass->Get<IM>("Awake")->Cast<void, Ghost*>();
	}

	if (mAwake) {
		H::Install(mAwake, HAwake);
	}
}

auto Ghost::HAwake(Ghost* _this) -> void {
	ghost = _this;
	H::Fcall(HAwake, _this);
}
