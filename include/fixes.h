#pragma once

#include "skse64_common/Relocation.h"
#include "skse64_common/SafeWrite.h"

#include "xbyak/xbyak.h"

#include "config.h"
#include "offsets.h"

namespace fixes
{
	bool PatchArcheryDownwardAiming();
    bool PatchBethesdaNetCrash();
    bool PatchBSLightingAmbientSpecular();
    bool PatchBSLightingShaderForceAlphaTest();
    bool PatchBSLightingShaderSetupGeometryParallax();
    bool PatchCalendarSkipping();
	bool PatchConjurationEnchantAbsorbs();
    bool PatchDoublePerkApply();
    bool PatchEquipShoutEventSpam();
    bool PatchGetKeywordItemCount();
    bool PatchGHeapLeakDetectionCrash();
	bool PatchLipSync();
    bool PatchMemoryAccessErrors();
    bool PatchMO5STypo();
    bool PatchPerkFragmentIsRunning();
    bool PatchRemovedSpellBook();
    bool PatchSaveScreenshots();
    bool PatchSlowTimeCameraMovement();
    bool PatchTreeReflections();
    bool PatchVerticalLookSensitivity();
    bool PatchAnimationLoadSignedCrash();

    bool PatchAll();
}