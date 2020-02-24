#pragma once

#include "skse64/gametypes.h"
#include "skse64/GameForms.h"

#include "RE/BSTArray.h"
//#include "RE/FormTypes.h"
//#include "RE/TESForm.h"
//#include "RE/TESTexture.h"

typedef UInt32 FormID;

// NOTE: Definition of TESFile taken from CommonLib -->  with some parts missing so it won't be very accurate
typedef void BSFile;
typedef void TESBitArrayFile;


namespace RE
{
	// 4C8
	class TESFile
	{
	public:
		enum class Error : UInt32
		{
			kNone = 0,
			kNotFound = 1,
			kNoFile = 2,
			kNoForm = 3,
			kNoChunk = 4,
			kNoID = 5,
			kBadFile = 6,
			kBadID = 7,
			kFormOpen = 8,
			kFileOpen = 9,
			kWriteFailure = 10,
			kInvalidFile = 11,
			kFileInUse = 12,
			kCreateFailure = 13
		};


		enum class RecordFlag : UInt32
		{
			kNone = 0,
			kMaster = 1 << 0,
			kAltered = 1 << 1,
			kChecked = 1 << 2,
			kActive = 1 << 3,
			kOptimizedFile = 1 << 4,
			kTempIDOwner = 1 << 5,
			kDelocalized = 1 << 7,
			kPrecalcDataOnly = 1 << 8,
			kSmallFile = 1 << 9
		};


		struct FORM
		{
			UInt32	form;			// 00
			UInt32	length;			// 04
			UInt32	flags;			// 08
			FormID	formID;			// 0C
			UInt32	versionControl;	// 10
			UInt16	formVersion;	// 14
			UInt16	vcVersion;		// 16
		};
		STATIC_ASSERT(sizeof(FORM) == 0x18);


		TESFile* Duplicate(UInt32 a_cacheSize = 0x4000);
		UInt32		GetCurrentSubRecordType();
		UInt32		GetCurrentSubRecordSize() const;
		FormType	GetFormType();
		bool		IsLoaded() const;
		bool		IsLocalized() const;
		void		ReadData(void* a_buf, UInt32 a_size);
		bool		Seek(UInt32 a_offset);
		bool		SeekNextSubrecord();


		// members
		Error							lastError;							// 000
		UInt32							pad004;								// 004
		TESFile* threadSafeParent;					// 008
		void* threadSafeFileMap;					// 010 - NiTPointerMap<UInt32, TESFile*>* - size == 0x20
		UInt64							unk018;								// 018
		UInt64							unk020;								// 020
		UInt8							unk028;								// 028
		UInt8							unk029;								// 029
		UInt16							pad02A;								// 02A
		UInt32							pad02C;								// 02C
		BSFile* lockedFile;							// 030
		BSFile* file;								// 038
		TESBitArrayFile* formUserDataBitArray;				// 040
		TESBitArrayFile* formVersionBitArray;				// 048
		TESBitArrayFile* formIDBitArray;						// 050
		char							fileName[MAX_PATH];					// 058
		char							path[MAX_PATH];						// 15C
		char* buffer;								// 260
		UInt32							bufferAllocSize;					// 268
		UInt32							firstCellOffset;					// 26C
		UInt32							currCellOffset;						// 270
		UInt32							unk274;								// 274
		TESObjectCELL* currCell;							// 278
		UInt32							currRefOffset;						// 280
		FORM							currentform;						// 284
		UInt32							currentchunkID;						// 29C
		UInt32							actualChunkSize;					// 2A0
		UInt32							filesize;							// 2A4
		UInt32							fileOffset;							// 2A8
		UInt32							formoffset;							// 2AC
		UInt32							chunkoffset;						// 2B0
		FORM							saveform;							// 2B4
		UInt32							saveFormOffset;						// 2CC
		UInt64							saveChunkOffset;					// 2D0
		UInt64							unk2D8;								// 2D8
		UInt64							unk2E0;								// 2E0
		UInt8							unk2E8;								// 2E8
		bool							isBigEndian;						// 2E9
		UInt8							unk2EA;								// 2EA
		UInt8							pad2EB;								// 2EB
		WIN32_FIND_DATA					fileData;							// 2EC
		float							unk42C;								// 42C
		UInt32							unk430;								// 430
		UInt32							flags;								// 434
		RecordFlag						recordFlags;						// 438
		UInt32							pad43C;								// 43C
	
		// WARNING: ----------------- Totally missing members  --- replaced with padding below ----				
		//BSSimpleList<const char*>		masters;							// 440
		//BSSimpleList<ULARGE_INTEGER*>	mastersData;						// 450
		char padding[0x24];
		UInt32							masterCount;						// 460
		UInt32							pad464;								// 464
		TESFile** masterPtrs;							// 468
		FILETIME						deletedFormTime;					// 470
		UInt8							compileIndex;						// 478
		UInt8							pad479;								// 479
		UInt16							smallFileCompileIndex;				// 47A
		UInt32							pad47C;								// 47C
		BSString						createdBy;							// 480
		BSString						summary;							// 490
		char* decompressedFormBuffer;				// 4A0
		UInt32							decompressedFormBufferSize;			// 4A8
		UInt32							pad4AC;								// 4AC
		void* reservedDecompressionBuffer;		// 4B0
		UInt32							reservedDecompressionBufferSize;	// 4B8
		UInt32							pad4BC;								// 4BC
		void* unk4C0;								// 4C0
	};
	//STATIC_ASSERT(sizeof(TESFile) == 0x4C8);





	union SETTING_VALUE
	{
		float	f;
		UInt32	i;
	};
	STATIC_ASSERT(sizeof(SETTING_VALUE) == 0x4);


	class BGSShaderParticleGeometryData : public TESForm
	{
	public:
		//inline static const void* RTTI = nullptr; //RTTI_BGSShaderParticleGeometryData;


		enum { kTypeID = 0x38 }; //ShaderParticleGeometryData,	//	38 SPGD	BGSShaderParticleGeometryData


		enum class DataID : UInt32
		{
			kGravityVelocity = 0,
			kRotationVelocity,
			kParticleSizeX,
			kParticleSizeY,
			kCenterOffsetMin,
			kCenterOffsetMax,
			kStartRotationRange,
			kNumSubtexturesX,
			kNumSubtexturesY,
			kParticleType,
			kBoxSize,
			kParticleDensity,

			kTotal
		};


		enum class ParticleType : UInt32
		{
			kRain = 0,
			kSnow = 1
		};


		struct RecordFlags
		{
			enum RecordFlag : UInt32
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};


		virtual ~BGSShaderParticleGeometryData();		// 00

		// override (TESForm)
	/*
		virtual void	InitializeData() override;		// 04
		virtual void	ClearData() override;			// 05
		virtual bool	Load(TESFile* a_mod) override;	// 06
		virtual void	InitItemImpl() override;		// 13
		*/

		BSTArray<SETTING_VALUE>	data;				// 20 - DATA - size == DataID::kTotal
		TESTexture				particleTexture;	// 38 - ICON
	};
	STATIC_ASSERT(sizeof(BGSShaderParticleGeometryData) == 0x48);
}