#include "skse64_common/Utilities.h"

#include "skse64/PluginAPI.h"
#include "skse64_common/BranchTrampoline.h"
#include "skse64_common/skse_version.h"

#include <sstream>
#include <ShlObj.h>

#include "version.h"
#include "config.h"
#include "fixes.h"
#include "patches.h"
#include "utils.h"
#include "warnings.h"

SKSEMessagingInterface* g_messaging = nullptr;
SKSETrampolineInterface* g_trampolineInterface = nullptr;
PluginHandle g_pluginHandle = kPluginHandle_Invalid;
const size_t TRAMPOLINE_SIZE = 2048;

void MessageHandler(SKSEMessagingInterface::Message* a_msg)
{
    switch (a_msg->type)
    {
	case SKSEMessagingInterface::kMessage_DataLoaded:
    {
		// NEW SKSEVR feature: trampoline interface object from QueryInterface() - Use SKSE existing process code memory pool - allow Skyrim to run without ASLR
		if (g_trampolineInterface)
		{
			void* branch = g_trampolineInterface->AllocateFromBranchPool(g_pluginHandle, TRAMPOLINE_SIZE);
			if (!branch) {
				_ERROR("couldn't acquire branch trampoline from SKSE. this is fatal. skipping remainder of init process.");
				return;
			}

			g_branchTrampoline.SetBase(TRAMPOLINE_SIZE, branch);

			void* local = g_trampolineInterface->AllocateFromLocalPool(g_pluginHandle, TRAMPOLINE_SIZE);
			if (!local) {
				_ERROR("couldn't acquire codegen buffer from SKSE. this is fatal. skipping remainder of init process.");
				return;
			}

			g_localTrampoline.SetBase(TRAMPOLINE_SIZE, local);

			_MESSAGE("Using new SKSEVR trampoline interface memory pool alloc for codegen buffers.");
		}
		else  // otherwise if using an older SKSEVR version, fall back to old code
		{

			if (!g_branchTrampoline.Create(TRAMPOLINE_SIZE))  // don't need such large buffers
			{
				_FATALERROR("[ERROR] couldn't create branch trampoline. this is fatal. skipping remainder of init process.");
				return;
			}

			if (!g_localTrampoline.Create(TRAMPOLINE_SIZE, nullptr))
			{
				_FATALERROR("[ERROR] couldn't create codegen buffer. this is fatal. skipping remainder of init process.");
				return;
			}

			_MESSAGE("Using legacy SKSE trampoline creation.");
		}

		_MESSAGE("WARNING: This is an experimental alpha build for Skyrim VR which does not support MOST patches! You have been warned!");
		_MESSAGE("beginning pre-load patches");

		if (config::cleanSKSECosaves)
			CleanSKSECosaves();

		patches::PatchAll();
		fixes::PatchAll();
		warnings::PatchAll();

		_MESSAGE("pre-load patches complete");

		_MESSAGE("beginning post-load patches");
        // patch post load so ini settings are loaded
      
		/**
		if (config::fixSaveScreenshots)
            fixes::PatchSaveScreenshots();

        if (config::warnRefHandleLimit)
        {
            warnings::WarnActiveRefrHandleCount(config::warnRefrMainMenuLimit);
        }

        if (config::patchSaveAddedSoundCategories)
            patches::LoadVolumes();

		if (config::fixTreeReflections)
			fixes::PatchTreeReflections();

		_VMESSAGE("clearing node map");
        warnings::ClearNodeMap();
		*/

		_MESSAGE("Post-load patches not supported yet in VR");
		//_MESSAGE("post-load patches complete");
    }
    break;
	case SKSEMessagingInterface::kMessage_PostLoad:
        {
        if (config::warnRefHandleLimit)
        {
            //warnings::WarnActiveRefrHandleCount(config::warnRefrLoadedGameLimit);
        }
        }
    break;
    default:
        break;
    }
}

extern "C" {
	bool SKSEPlugin_Query(const SKSEInterface* a_skse, PluginInfo* a_info)
    {
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, R"(\My Games\Skyrim VR\SKSE\VREngineFixes.log)");

		gLog.SetPrintLevel(IDebugLog::kLevel_Error);
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);

		_MESSAGE("VR Engine Fixes v%s", EF_VERSION_VERSTRING);

        // populate info structure
        a_info->infoVersion = PluginInfo::kInfoVersion;
        a_info->name = "VREngineFixes plugin";
		a_info->version = EF_VERSION_MAJOR;

        if (a_skse->isEditor)
        {
            _FATALERROR("loaded in editor, marking as incompatible");
            return false;
        }

		switch (a_skse->runtimeVersion) {
		case RUNTIME_VR_VERSION_1_4_15:
			break;
		default:
			_FATALERROR("Unsupported runtime version %d!\n", a_skse->runtimeVersion);
			return false;
		}

		g_pluginHandle = a_skse->GetPluginHandle();

		g_messaging = static_cast<SKSEMessagingInterface*>(a_skse->QueryInterface((kInterface_Messaging)));
		if (!g_messaging)
		{
			_FATALERROR("[ERROR] couldn't get messaging interface");
			return false;
		}

		g_trampolineInterface = static_cast<SKSETrampolineInterface*>(a_skse->QueryInterface(kInterface_Trampoline));
		if (!g_trampolineInterface)
		{
			_MESSAGE("WARNING: Could not get new trampoline alloc interface, Using legacy SKSE VR");
		}

        return true;
    }

	bool SKSEPlugin_Load(const SKSEInterface* a_skse)
    {
		/*
		if (!SKSE::Init(a_skse)) {
			return false;
		}

		if (!SKSE::AllocTrampoline(1 << 11)) {
			return false;
		}
		*/

		bool res = g_messaging->RegisterListener(g_pluginHandle, "SKSE", MessageHandler);
		if (!res)
		{
			_MESSAGE("Failed to register SKSE Message handler.");
		}

		return true;

		const auto runtimePath = GetRuntimeDirectory();

		if (config::LoadConfig(runtimePath + R"(Data\SKSE\plugins\EngineFixes.ini)"))
		{
			_MESSAGE("loaded config successfully");
		}
		else
		{
			_MESSAGE("config load failed, using default config");
		}

		if (config::verboseLogging)
		{
			_MESSAGE("enabling verbose logging");
			//SKSE::Logger::SetPrintLevel(SKSE::Logger::Level::kVerboseMessage);
			//SKSE::Logger::SetFlushLevel(SKSE::Logger::Level::kVerboseMessage);
		}


        return true;
    }
}
