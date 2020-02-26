namespace RE
{
	namespace Offset
	{

		// Fixed with VR addresses
		namespace MemoryManager
		{
			// DirectSig: 48 89 5C 24 ? 55 57 41 54 41 55 41 57 48 83 EC 30 65 48 8B 04 25 ? ? ? ?
			// DIFF: 1.00	0.99	-------	0000000140C02260	sub_0000000140C02260	0000000140C3D0E0	Heap__Allocate	 
			constexpr std::uintptr_t Allocate = 0xC3D0E0; //0x00C02260;				// 1_5_97
			// DirectSig: 48 85 D2 0F 84 ? ? ? ? 48 89 5C 24 ? 48 89 54 24 ? 57 48 83 EC 20 80 39 00
			//1.00	0.99	-------	0000000140C02560	sub_0000000140C02560	0000000140C3D3E0	Heap__Free	 	call reference matching	21	21	21	79	79	79	27	27	27

			constexpr std::uintptr_t Deallocate = 0xC3D3E0; //0x00C02560;			// 1_5_97
			// DirectSig: 40 53 48 83 EC 20 83 3D ? ? ? ? ? 74 1F

			//1.00	0.99	-------	00000001400FCFE0	sub_00000001400FCFE0	000000014010D590	sub_000000014010D590	 	call reference matching	3	3	3	16	16	16	2	2	2

			constexpr std::uintptr_t GetSingleton = 0x10D590; //0x000FCFE0;			// 1_5_97

			// DirectSig: 40 56 57 41 54 41 56 41 57 48 83 EC 30 48 C7 44 24 ? ? ? ? ? 48 89 5C 24 ? 48 89 6C 24 ? 48 8B F1 33 ED
			//1.00	0.99	-------	0000000140C01800	sub_0000000140C01800	0000000140C3C680	sub_0000000140C3C680	 	call reference matching	8	8	8	62	62	62	10	10	10


			constexpr std::uintptr_t GetThreadScrapHeap = 0xC3C680; //0x00C01800;	// 1_5_97
			
		// IndirectSig: E8 ? ? ? ? 3B 77 48
			// 1.00	0.99	-------	0000000140C024B0	sub_0000000140C024B0	0000000140C3D330	sub_0000000140C3D330	 	call reference matching	7	7	7	48	48	48	8	8	8

			constexpr std::uintptr_t Reallocate = 0xC3D330; //0x00C024B0;			// 1_5_97
		}


	}
}
