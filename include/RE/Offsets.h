namespace RE
{
	namespace Offset
	{

		// TODO: Fix for VR....
		namespace MemoryManager
		{
			// DirectSig: 48 89 5C 24 ? 55 57 41 54 41 55 41 57 48 83 EC 30 65 48 8B 04 25 ? ? ? ?
			constexpr std::uintptr_t Allocate = 0x00C02260;				// 1_5_97
			// DirectSig: 48 85 D2 0F 84 ? ? ? ? 48 89 5C 24 ? 48 89 54 24 ? 57 48 83 EC 20 80 39 00
			constexpr std::uintptr_t Deallocate = 0x00C02560;			// 1_5_97
			// DirectSig: 40 53 48 83 EC 20 83 3D ? ? ? ? ? 74 1F
			constexpr std::uintptr_t GetSingleton = 0x000FCFE0;			// 1_5_97
			// DirectSig: 40 56 57 41 54 41 56 41 57 48 83 EC 30 48 C7 44 24 ? ? ? ? ? 48 89 5C 24 ? 48 89 6C 24 ? 48 8B F1 33 ED
			constexpr std::uintptr_t GetThreadScrapHeap = 0x00C01800;	// 1_5_97
			// IndirectSig: E8 ? ? ? ? 3B 77 48
			constexpr std::uintptr_t Reallocate = 0x00C024B0;			// 1_5_97
		}


	}
}
