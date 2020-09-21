#pragma once
#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <list>

#include "windows.h"

/*
 Get documentation here: https://www.audiokinetic.com/library/2015.1.9_5624/?source=SDK&id=namespace_a_k_1_1_sound_engine.html

 Note: Rocksmith is made with Wwise 2013, not Wwise 2015. This is the earliest version with good documentation.
 This means that some functions are in that documentation that aren't in the 2013 version, and vise-versa.
 To tell what functions we have access to, go to the functions part of this document as I layed everything out

 Documentation by: Audiokinetic (makers of Wwise)
 Types add by: LovroM8
 Functions added by: Ffio
*/

/*------------------Dependancies---------------------------------*/

typedef unsigned char		AkUInt8;			///< Unsigned 8-bit integer
typedef unsigned short		AkUInt16;			///< Unsigned 16-bit integer
typedef unsigned long		AkUInt32;			///< Unsigned 32-bit integer
typedef char			AkInt8;					///< Signed 8-bit integer
typedef short			AkInt16;				///< Signed 16-bit integer
typedef long   			AkInt32;				///< Signed 32-bit integer
typedef int 		AkInt;					///< Signed integer
typedef int AkIntPtr;						///< Integer type for pointers
typedef  unsigned int AkUIntPtr;			///< Integer (unsigned) type for pointers
typedef float			AkReal32;				///< 32-bit floating point
typedef double          AkReal64;				///< 64-bit floating point

typedef AkUInt32		AkUniqueID;			 		///< Unique 32-bit ID
typedef AkUInt32		AkStateID;			 		///< State ID
typedef AkUInt32		AkStateGroupID;		 		///< State group ID
typedef AkUInt32		AkPlayingID;		 		///< Playing ID
typedef	AkInt32			AkTimeMs;			 		///< Time in ms
typedef AkReal32		AkPitchValue;		 		///< Pitch value
typedef AkReal32		AkVolumeValue;		 		///< Volume value( also apply to LFE )
typedef AkUIntPtr		AkGameObjectID;		 		///< Game object ID
typedef AkReal32		AkLPFType;			 		///< Low-pass filter type
typedef AkInt32			AkMemPoolId;		 		///< Memory pool ID
typedef AkUInt32		AkPluginID;			 		///< Source or effect plug-in ID
typedef AkUInt32		AkCodecID;			 		///< Codec plug-in ID
typedef AkUInt32		AkEnvID;			 		///< Environmental ID
typedef AkInt16			AkPluginParamID;	 		///< Source or effect plug-in parameter ID
typedef AkInt8			AkPriority;			 		///< Priority
typedef AkUInt16        AkDataCompID;		 		///< Data compression format ID
typedef AkUInt16        AkDataTypeID;		 		///< Data sample type ID
typedef AkUInt8			AkDataInterleaveID;	 		///< Data interleaved state ID
typedef AkUInt32        AkSwitchGroupID;	 		///< Switch group ID
typedef AkUInt32        AkSwitchStateID;	 		///< Switch ID
typedef AkUInt32        AkRtpcID;			 		///< Real time parameter control ID
typedef AkReal32        AkRtpcValue;		 		///< Real time parameter control value
typedef AkUInt32        AkBankID;			 		///< Run time bank ID
typedef AkUInt32        AkFileID;			 		///< Integer-type file identifier
typedef AkUInt32        AkDeviceID;			 		///< I/O device ID
typedef AkUInt32		AkTriggerID;		 		///< Trigger ID
typedef AkUInt32		AkArgumentValueID;			///< Argument value ID
typedef AkUInt32		AkChannelMask;				///< Channel mask (similar to WAVE_FORMAT_EXTENSIBLE). Bit values are defined in AkCommonDefs.h.

static const AkGameObjectID	AK_INVALID_GAME_OBJECT = (AkGameObjectID)-1;	///< Invalid game object (may also mean all game objects)

enum AKRESULT
{
	AK_NotImplemented = 0,	///< This feature is not implemented.
	AK_Success = 1,	///< The operation was successful.
	AK_Fail = 2,	///< The operation failed.
	AK_PartialSuccess = 3,	///< The operation succeeded partially.
	AK_NotCompatible = 4,	///< Incompatible formats
	AK_AlreadyConnected = 5,	///< The stream is already connected to another node.
	AK_NameNotSet = 6,	///< Trying to open a file when its name was not set
	AK_InvalidFile = 7,	///< An unexpected value causes the file to be invalid.
	AK_CorruptedFile = 8,	///< The file is missing some exprected data.
	AK_MaxReached = 9,	///< The maximum was reached.
	AK_InputsInUsed = 10,	///< Inputs are currently used.
	AK_OutputsInUsed = 11,	///< Outputs are currently used.
	AK_InvalidName = 12,	///< The name is invalid.
	AK_NameAlreadyInUse = 13,	///< The name is already in use.
	AK_InvalidID = 14,	///< The ID is invalid.
	AK_IDNotFound = 15,	///< The ID was not found.
	AK_InvalidInstanceID = 16,	///< The InstanceID is invalid.
	AK_NoMoreData = 17,	///< No more data is available from the source.
	AK_NoSourceAvailable = 18,	///< There is no child (source) associated with the node.
	AK_StateGroupAlreadyExists = 19,	///< The StateGroup already exists.
	AK_InvalidStateGroup = 20,	///< The StateGroup is not a valid channel.
	AK_ChildAlreadyHasAParent = 21,	///< The child already has a parent.
	AK_InvalidLanguage = 22,	///< The language is invalid (applies to the Low-Level I/O).
	AK_CannotAddItseflAsAChild = 23,	///< It is not possible to add itself as its own child.
	AK_TransitionNotFound = 24,	///< The transition is not in the list.
	AK_TransitionNotStartable = 25,	///< Start allowed in the Running and Done states.
	AK_TransitionNotRemovable = 26,	///< Must not be in the Computing state.
	AK_UsersListFull = 27,	///< No one can be added any more, could be AK_MaxReached.
	AK_UserAlreadyInList = 28,	///< This user is already there.
	AK_UserNotInList = 29,	///< This user is not there.
	AK_NoTransitionPoint = 30,	///< Not in use.
	AK_InvalidParameter = 31,	///< Something is not within bounds.
	AK_ParameterAdjusted = 32,	///< Something was not within bounds and was relocated to the nearest OK value.
	AK_IsA3DSound = 33,	///< The sound has 3D parameters.
	AK_NotA3DSound = 34,	///< The sound does not have 3D parameters.
	AK_ElementAlreadyInList = 35,	///< The item could not be added because it was already in the list.
	AK_PathNotFound = 36,	///< This path is not known.
	AK_PathNoVertices = 37,	///< Stuff in vertices before trying to start it
	AK_PathNotRunning = 38,	///< Only a running path can be paused.
	AK_PathNotPaused = 39,	///< Only a paused path can be resumed.
	AK_PathNodeAlreadyInList = 40,	///< This path is already there.
	AK_PathNodeNotInList = 41,	///< This path is not there.
	AK_VoiceNotFound = 42,	///< Unknown in our voices list
	AK_DataNeeded = 43,	///< The consumer needs more.
	AK_NoDataNeeded = 44,	///< The consumer does not need more.
	AK_DataReady = 45,	///< The provider has available data.
	AK_NoDataReady = 46,	///< The provider does not have available data.
	AK_NoMoreSlotAvailable = 47,	///< Not enough space to load bank.
	AK_SlotNotFound = 48,	///< Bank error.
	AK_ProcessingOnly = 49,	///< No need to fetch new data.
	AK_MemoryLeak = 50,	///< Debug mode only.
	AK_CorruptedBlockList = 51,	///< The memory manager's block list has been corrupted.
	AK_InsufficientMemory = 52,	///< Memory error.
	AK_Cancelled = 53,	///< The requested action was cancelled (not an error).
	AK_UnknownBankID = 54,	///< Trying to load a bank using an ID which is not defined.
	AK_IsProcessing = 55,   ///< Asynchronous pipeline component is processing.
	AK_BankReadError = 56,	///< Error while reading a bank.
	AK_InvalidSwitchType = 57,	///< Invalid switch type (used with the switch container)
	AK_VoiceDone = 58,	///< Internal use only.
	AK_UnknownEnvironment = 59,	///< This environment is not defined.
	AK_EnvironmentInUse = 60,	///< This environment is used by an object.
	AK_UnknownObject = 61,	///< This object is not defined.
	AK_NoConversionNeeded = 62,	///< Audio data already in target format, no conversion to perform.
	AK_FormatNotReady = 63,   ///< Source format not known yet.
	AK_WrongBankVersion = 64,	///< The bank version is not compatible with the current bank reader.
	AK_DataReadyNoProcess = 65,	///< The provider has some data but does not process it (virtual voices).
	AK_FileNotFound = 66,   ///< File not found.
	AK_DeviceNotReady = 67,   ///< IO device not ready (may be because the tray is open)
	AK_CouldNotCreateSecBuffer = 68,   ///< The direct sound secondary buffer creation failed.
	AK_BankAlreadyLoaded = 69,	///< The bank load failed because the bank is already loaded.
	AK_RenderedFX = 71,	///< The effect on the node is rendered.
	AK_ProcessNeeded = 72,	///< A routine needs to be executed on some CPU.
	AK_ProcessDone = 73,	///< The executed routine has finished its execution.
	AK_MemManagerNotInitialized = 74,	///< The memory manager should have been initialized at this point.
	AK_StreamMgrNotInitialized = 75,	///< The stream manager should have been initialized at this point.
	AK_SSEInstructionsNotSupported = 76,///< The machine does not support SSE instructions (required on PC).
	AK_Busy = 77,	///< The system is busy and could not process the request.
	AK_UnsupportedChannelConfig = 78,	///< Channel configuration is not supported in the current execution context.
	AK_PluginMediaNotAvailable = 79,	///< Plugin media is not available for effect.
};


/// Curve interpolation types
enum AkCurveInterpolation
{
	//DONT GO BEYOND 15! (see below for details)
	//Curves from 0 to LastFadeCurve NEED TO BE A MIRROR IMAGE AROUND LINEAR (eg. Log3 is the inverse of Exp3)
	AkCurveInterpolation_Log3 = 0, ///< Log3
	AkCurveInterpolation_Sine = 1, ///< Sine
	AkCurveInterpolation_Log1 = 2, ///< Log1
	AkCurveInterpolation_InvSCurve = 3, ///< Inversed S Curve
	AkCurveInterpolation_Linear = 4, ///< Linear (Default)
	AkCurveInterpolation_SCurve = 5, ///< S Curve
	AkCurveInterpolation_Exp1 = 6, ///< Exp1
	AkCurveInterpolation_SineRecip = 7, ///< Reciprocal of sine curve
	AkCurveInterpolation_Exp3 = 8, ///< Exp3
	AkCurveInterpolation_LastFadeCurve = 8, ///< Update this value to reflect last curve available for fades
	AkCurveInterpolation_Constant = 9  ///< Constant ( not valid for fading values )
//DONT GO BEYOND 15! The value is stored on 5 bits,
//but we can use only 4 bits for the actual values, keeping
//the 5th bit at 0 to void problems when the value is
//expanded to 32 bits.
};

enum RTPCValue_type
{
	RTPCValue_Default,      ///< The value is the Default RTPC.
	RTPCValue_Global,       ///< The value is the Global RTPC.
	RTPCValue_GameObject,   ///< The value is the game object specific RTPC.
	RTPCValue_PlayingID,    ///< The value is the playing ID specific RTPC.
	RTPCValue_Unavailable   ///< The value is not available for the RTPC specified.
};

enum AkCallbackType
{
	AK_EndOfEvent = 0x0001,
	AK_EndOfDynamicSequenceItem = 0x0002,
	AK_Marker = 0x0004,
	AK_Duration = 0x0008,

	AK_SpeakerVolumeMatrix = 0x0010,

	AK_Starvation = 0x0020,

	AK_MusicPlaylistSelect = 0x0040,
	AK_MusicPlayStarted = 0x0080,

	AK_MusicSyncBeat = 0x0100,
	AK_MusicSyncBar = 0x0200,
	AK_MusicSyncEntry = 0x0400,
	AK_MusicSyncExit = 0x0800,
	AK_MusicSyncGrid = 0x1000,
	AK_MusicSyncUserCue = 0x2000,
	AK_MusicSyncPoint = 0x4000,
	AK_MusicSyncAll = 0x7f00,

	AK_MidiEvent = 0x10000,

	AK_CallbackBits = 0xfffff,

	// Not callback types, but need to be part of same bitfield for AK::SoundEngine::PostEvent().
	AK_EnableGetSourcePlayPosition = 0x100000,
	AK_EnableGetMusicPlayPosition = 0x200000,
	AK_EnableGetSourceStreamBuffering = 0x400000
};
struct AkCallbackInfo
{
	void* pCookie;
	AkGameObjectID  gameObjID;
};

enum DynamicSequenceType
{
	DynamicSequenceType_SampleAccurate,
	DynamicSequenceType_NormalTransition
};

typedef void(*AkCallbackFunc)(AkCallbackType in_eType, AkCallbackInfo* in_pCallbackInfo);

enum AkActionOnEventType
{
	AkActionOnEventType_Stop = 0,
	AkActionOnEventType_Pause = 1,
	AkActionOnEventType_Resume = 2,
	AkActionOnEventType_Break = 3,
	AkActionOnEventType_ReleaseEnvelope = 4
};

struct AkCommSettings
{
	AkCommSettings()
	{
		szAppNetworkName[0] = 0;
	}
	AkUInt32    uPoolSize;
	struct Ports
	{
		Ports()
			: uDiscoveryBroadcast(24024)
			, uCommand(0)
			, uNotification(0)
		{
		}
		AkUInt16 uDiscoveryBroadcast;
		AkUInt16 uCommand;
		AkUInt16 uNotification;
	};
	Ports ports;
	bool bInitSystemLib;
	char szAppNetworkName[64];
};


typedef void(*AkBankCallbackFunc)(AkUInt32 in_bankID, const void* in_pInMemoryBankPtr, AKRESULT in_eLoadResult, AkMemPoolId in_memPoolId, void* in_pCookie);

typedef wchar_t AkOSChar;

struct AkExternalSourceInfo
{
	AkUInt32 iExternalSrcCookie;
	AkCodecID idCodec;
	AkOSChar* szFile;
	void* pInMemory;
	AkUInt32 uiMemorySize;
	AkFileID idFile;

	AkExternalSourceInfo()
		: iExternalSrcCookie(0)
		, idCodec(0)
		, szFile(0)
		, pInMemory(0)
		, uiMemorySize(0)
		, idFile(0) {}

	AkExternalSourceInfo(
		void* in_pInMemory,
		AkUInt32 in_uiMemorySize,
		AkUInt32 in_iExternalSrcCookie,
		AkCodecID in_idCodec
	)
		: iExternalSrcCookie(in_iExternalSrcCookie)
		, idCodec(in_idCodec)
		, szFile(0)
		, pInMemory(in_pInMemory)
		, uiMemorySize(in_uiMemorySize)
		, idFile(0) {}

	AkExternalSourceInfo(
		AkOSChar* in_pszFileName,
		AkUInt32 in_iExternalSrcCookie,
		AkCodecID in_idCodec
	)
		: iExternalSrcCookie(in_iExternalSrcCookie)
		, idCodec(in_idCodec)
		, szFile(in_pszFileName)
		, pInMemory(0)
		, uiMemorySize(0)
		, idFile(0) {}

	AkExternalSourceInfo(
		AkFileID in_idFile,
		AkUInt32 in_iExternalSrcCookie,
		AkCodecID in_idCodec
	)
		: iExternalSrcCookie(in_iExternalSrcCookie)
		, idCodec(in_idCodec)
		, szFile(0)
		, pInMemory(0)
		, uiMemorySize(0)
		, idFile(in_idFile) {}
};

enum PreparationType
{
	Preparation_Load,
	Preparation_Unload
};

enum AkBankContent
{
	AkBankContent_StructureOnly,
	AkBankContent_All
};

enum AkGroupType // should stay set as Switch = 0 and State = 1
{
	AkGroupType_Switch = 0,
	AkGroupType_State = 1
};

typedef AkUInt32 AkAuxBusID;

struct AkAuxSendValue
{
	AkAuxBusID auxBusID;
	AkReal32 fControlValue;
};

struct AkVector
{
	AkReal32 X;
	AkReal32 Y;
	AkReal32 Z;
};

struct AkListenerPosition
{
	AkVector OrientationFront;
	AkVector OrientationTop;
	AkVector Position;
};

struct AkSoundPosition
{
	AkVector        Position;
	AkVector        Orientation;
};

enum AkPannerType
{
	Ak2D = 0,
	Ak3D = 1
};

enum AkPositionSourceType
{
	AkUserDef = 0,
	AkGameDef = 1
};

struct AkPositioningInfo
{
	AkReal32            fCenterPct;
	AkPannerType        pannerType;
	AkPositionSourceType posSourceType;
	bool                bUpdateEachFrame;
	bool                bUseSpatialization;
	bool                bUseAttenuation;

	bool                bUseConeAttenuation;
	AkReal32            fInnerAngle;
	AkReal32            fOuterAngle;
	AkReal32            fConeMaxAttenuation;
	AkLPFType           LPFCone;
	AkLPFType           HPFCone;

	AkReal32            fMaxDistance;
	AkReal32            fVolDryAtMaxDist;
	AkReal32            fVolAuxGameDefAtMaxDist;
	AkReal32            fVolAuxUserDefAtMaxDist;
	AkLPFType           LPFValueAtMaxDist;
	AkLPFType           HPFValueAtMaxDist;
};

struct AkObjectInfo
{
	AkUniqueID  objID;
	AkUniqueID  parentID;
	AkInt32     iDepth;
};
class IAkSoftwareCodec;

typedef IAkSoftwareCodec* (AkCreateFileSourceCallback)(void* in_pCtx);
typedef IAkSoftwareCodec* (AkCreateBankSourceCallback)(void* in_pCtx);
typedef void(AkGlobalCallbackFunc)(bool in_bLastCall);

enum AkPluginType
{
	AkPluginTypeNone = 0,
	AkPluginTypeCodec = 1,
	AkPluginTypeSource = 2,
	AkPluginTypeEffect = 3,
	AkPluginTypeMotionDevice = 4,
	AkPluginTypeMotionSource = 5,
	AkPluginTypeMixer = 6,
	AkPluginTypeSink = 7,
	AkPluginTypeMask = 0xf
};

struct AkPluginInfo
{
	AkPluginType eType;
	bool bIsInPlace;
	bool bIsAsynchronous;
};

class IAkPluginMemAlloc
{
protected:
	virtual ~IAkPluginMemAlloc() {}

public:
	virtual void* Malloc(
		size_t in_uSize
	) = 0;

	virtual void Free(
		void* in_pMemAddress
	) = 0;
};

class IAkPlugin
{
protected:
	virtual ~IAkPlugin() {}

public:
	virtual AKRESULT Term(
		IAkPluginMemAlloc* in_pAllocator
	) = 0;

	virtual AKRESULT Reset() = 0;

	virtual AKRESULT GetPluginInfo(
		AkPluginInfo& out_rPluginInfo
	) = 0;

	virtual bool SupportMediaRelocation() const {
		return false;
	}


	virtual AKRESULT RelocateMedia(
		AkUInt8* /*in_pNewMedia*/,
		AkUInt8* /*in_pOldMedia*/
	)
	{
		return AK_NotImplemented;
	}

};

class IAkRTPCSubscriber
{
protected:
	virtual ~IAkRTPCSubscriber() {}

public:
	virtual AKRESULT SetParam(
		AkPluginParamID in_paramID,
		const void* in_pParam,
		AkUInt32        in_uParamSize
	) = 0;
};

class IAkPluginParam : public IAkRTPCSubscriber
{
protected:
	virtual ~IAkPluginParam() {}

public:
	virtual IAkPluginParam* Clone(
		IAkPluginMemAlloc* in_pAllocator
	) = 0;

	virtual AKRESULT Init(
		IAkPluginMemAlloc* in_pAllocator,
		const void* in_pParamsBlock,
		AkUInt32            in_uBlockSize
	) = 0;

	virtual AKRESULT Term(
		IAkPluginMemAlloc* in_pAllocator
	) = 0;

	virtual AKRESULT SetParamsBlock(
		const void* in_pParamsBlock,
		AkUInt32 in_uBlockSize
	) = 0;

	virtual AKRESULT SetParam(
		AkPluginParamID in_paramID,
		const void* in_pValue,
		AkUInt32 in_uParamSize
	) = 0;
	static const AkPluginParamID ALL_PLUGIN_DATA_ID = 0x7FFF;
};

typedef IAkPlugin* (AkCreatePluginCallback)(IAkPluginMemAlloc* in_pAllocator);
typedef IAkPluginParam* (AkCreateParamCallback)(IAkPluginMemAlloc* in_pAllocator);

enum MultiPositionType
{
	MultiPositionType_SingleSource,
	MultiPositionType_MultiSources,
	MultiPositionType_MultiDirections
};

struct PoolMemInfo
{
	// Current state
	AkUInt32 uReserved;
	AkUInt32 uUsed;
};

struct PoolStats
{
	// Current state
	AkUInt32 uReserved;
	AkUInt32 uUsed;
	AkUInt32 uMaxFreeBlock;

	// Statistics
	AkUInt32 uAllocs;
	AkUInt32 uFrees;
	AkUInt32 uPeakUsed;
};

enum ErrorLevel
{
	ErrorLevel_Message = (1 << 0), // used as bitfield
	ErrorLevel_Error = (1 << 1),

	ErrorLevel_All = ErrorLevel_Message | ErrorLevel_Error
};

enum ErrorCode
{
	ErrorCode_NoError = 0, // 0-based index into AK::Monitor::s_aszErrorCodes table 
	ErrorCode_FileNotFound,
	ErrorCode_CannotOpenFile,
	ErrorCode_CannotStartStreamNoMemory,
	ErrorCode_IODevice,
	ErrorCode_IncompatibleIOSettings,

	ErrorCode_PluginUnsupportedChannelConfiguration,
	ErrorCode_PluginMediaUnavailable,
	ErrorCode_PluginInitialisationFailed,
	ErrorCode_PluginProcessingFailed,
	ErrorCode_PluginExecutionInvalid,
	ErrorCode_PluginAllocationFailed,

	ErrorCode_VorbisRequireSeekTable,
	ErrorCode_VorbisRequireSeekTableVirtual,

	ErrorCode_VorbisDecodeError,
	ErrorCode_AACDecodeError,

	ErrorCode_xWMACreateDecoderFailed,

	ErrorCode_ATRAC9CreateDecoderFailed,
	ErrorCode_ATRAC9CreateDecoderFailedChShortage,
	ErrorCode_ATRAC9DecodeFailed,
	ErrorCode_ATRAC9ClearContextFailed,
	ErrorCode_ATRAC9LoopSectionTooSmall,

	ErrorCode_InvalidAudioFileHeader,
	ErrorCode_AudioFileHeaderTooLarge,
	ErrorCode_FileTooSmall,

	ErrorCode_TransitionNotAccurateChannel,
	ErrorCode_TransitionNotAccurateStarvation,
	ErrorCode_NothingToPlay,
	ErrorCode_PlayFailed,

	ErrorCode_StingerCouldNotBeScheduled,
	ErrorCode_TooLongSegmentLookAhead,
	ErrorCode_CannotScheduleMusicSwitch,
	ErrorCode_TooManySimultaneousMusicSegments,
	ErrorCode_PlaylistStoppedForEditing,
	ErrorCode_MusicClipsRescheduledAfterTrackEdit,

	ErrorCode_CannotPlaySource_Create,
	ErrorCode_CannotPlaySource_VirtualOff,
	ErrorCode_CannotPlaySource_TimeSkip,
	ErrorCode_CannotPlaySource_InconsistentState,
	ErrorCode_MediaNotLoaded,
	ErrorCode_VoiceStarving,
	ErrorCode_StreamingSourceStarving,
	ErrorCode_XMADecoderSourceStarving,
	ErrorCode_XMADecodingError,
	ErrorCode_InvalidXMAData,

	ErrorCode_PluginNotRegistered,
	ErrorCode_CodecNotRegistered,

	ErrorCode_EventIDNotFound,

	ErrorCode_InvalidGroupID,
	ErrorCode_SelectedChildNotAvailable,
	ErrorCode_SelectedNodeNotAvailable,
	ErrorCode_SelectedMediaNotAvailable,
	ErrorCode_NoValidSwitch,

	ErrorCode_SelectedNodeNotAvailablePlay,

	ErrorCode_FeedbackVoiceStarving,

	ErrorCode_BankLoadFailed,
	ErrorCode_BankUnloadFailed,
	ErrorCode_ErrorWhileLoadingBank,
	ErrorCode_InsufficientSpaceToLoadBank,

	ErrorCode_LowerEngineCommandListFull,

	ErrorCode_SeekNoMarker,
	ErrorCode_CannotSeekContinuous,
	ErrorCode_SeekAfterEof,

	ErrorCode_UnknownGameObjectEvent,
	ErrorCode_UnknownGameObject,

	ErrorCode_ExternalSourceNotResolved,
	ErrorCode_FileFormatMismatch,

	ErrorCode_CommandQueueFull,
	ErrorCode_CommandTooLarge,

	ErrorCode_ExecuteActionOnEvent,
	ErrorCode_StopAll,
	ErrorCode_StopPlayingID,

	ErrorCode_XMACreateDecoderLimitReached,
	ErrorCode_XMAStreamBufferTooSmall,

	ErrorCode_ModulatorScopeError_Inst,
	ErrorCode_ModulatorScopeError_Obj,

	Num_ErrorCodes // THIS STAYS AT END OF ENUM
};

struct AkMusicSettings
{
	AkReal32 fStreamingLookAheadRatio;
};

struct AkSegmentInfo
{
	AkTimeMs iCurrentPosition;
	AkTimeMs iPreEntryDuration;
	AkTimeMs iActiveDuration;
	AkTimeMs iPostExitDuration;
	AkTimeMs iRemainingLookAheadTime;
};

typedef void(*AkLanguageChangeHandler)(const AkOSChar* const in_pLanguageName, void* in_pCookie);

struct AkStreamMgrSettings
{
	AkUInt32 uMemorySize;
};

enum AkMemPoolAttributes
{
	AkNoAlloc = 0,
	AkMalloc = 1,
	AkAllocMask = AkNoAlloc | AkMalloc,

	AkFixedSizeBlocksMode = 1 << 3,
	AkBlockMgmtMask = AkFixedSizeBlocksMode
};

// TODO: Merge Function with Type-Variable in DLLMain::InitEngineFunctions()

/* Offsets For Functions */

// Wwise Hijack
		// Root
uintptr_t func_Wwise_Root_IsRestoreSinkRequested = 0x1b5bfd3;
uintptr_t func_Wwise_Root_IsUsingDummySink = 0x1b5bfc3;
// IAkStreamMgr
uintptr_t func_Wwise_IAkStreamMgr_m_pStreamMgr = 0xf4f500;
// MemoryMgr
uintptr_t func_Wwise_Memory_CheckPoolId = 0x1b32828;
uintptr_t func_Wwise_Memory_CreatePool = 0x1b32519;
uintptr_t func_Wwise_Memory_DestroyPool = 0x1b326d4;
uintptr_t func_Wwise_Memory_Falign = 0x1b329ee;
uintptr_t func_Wwise_Memory_GetBlock = 0x1b32aee;
uintptr_t func_Wwise_Memory_GetBlockSize = 0x1b327e8;
uintptr_t func_Wwise_Memory_GetMaxPools = 0x1b32818;
uintptr_t func_Wwise_Memory_GetNumPools = 0x1b32808;
uintptr_t func_Wwise_Memory_GetPoolAttributes = 0x1b327c4;
uintptr_t func_Wwise_Memory_GetPoolMemoryUsed = 0x1b32aae;
uintptr_t func_Wwise_Memory_GetPoolName = 0x1c06a57;
uintptr_t func_Wwise_Memory_GetPoolStats = 0x1b32a3e;
uintptr_t func_Wwise_Memory_IsInitialized = 0x1b32784;
uintptr_t func_Wwise_Memory_Malign = 0x1b3298a;
uintptr_t func_Wwise_Memory_Malloc = 0x1b3290a;
uintptr_t func_Wwise_Memory_ReleaseBlock = 0x1b32b3e;
uintptr_t func_Wwise_Memory_SetMonitoring = 0x127e4f3;
uintptr_t func_Wwise_Memory_SetPoolName = 0x1b32794;
uintptr_t func_Wwise_Memory_Term = 0x1b32b8e;
// Monitor
uintptr_t func_Wwise_Monitor_PostCode = 0x1b587ba;
// Motion Engine
uintptr_t func_Wwise_Motion_AddPlayerMotionDevice = 0x1b58638;
uintptr_t func_Wwise_Motion_RegisterMotionDevice = 0x1b58712;
uintptr_t func_Wwise_Motion_RemovePlayerMotionDevice = 0x1b586ad;
uintptr_t func_Wwise_Motion_SetPlayerListener = 0x1b58722;
uintptr_t func_Wwise_Motion_SetPlayerVolume = 0x1b5876e;
// Music Engine
uintptr_t func_Wwise_Music_GetDefaultInitSettings = 0x1b340ef;
uintptr_t func_Wwise_Music_GetPlayingSegmentInfo = 0x1b3413f;
uintptr_t func_Wwise_Music_Init = 0x1b34f8c;
uintptr_t func_Wwise_Music_Term = 0x1b34e38;
// Sound Engine
uintptr_t func_Wwise_Sound_AddBehaviorExtension = 0x1b5a741;
uintptr_t func_Wwise_Sound_CancelBankCallbackCookie = 0x1b57f0c;
uintptr_t func_Wwise_Sound_CancelEventCallback = 0x1b5760d;
uintptr_t func_Wwise_Sound_CancelEventCallbackCookie = 0x1b575ed;
uintptr_t func_Wwise_Sound_ClearBanks = 0x1b58ecc;
uintptr_t func_Wwise_Sound_ClearPreparedEvents = 0x1b58064;
uintptr_t func_Wwise_Sound_CloneActorMixerEffect = 0x1b5bd9d;
uintptr_t func_Wwise_Sound_CloneBusEffect = 0x1b5bd79;
uintptr_t func_Wwise_Sound_DynamicDialogue_ResolveDialogueEvent_UniqueID = 0x1b5b68e;
uintptr_t func_Wwise_Sound_DynamicDialogue_ResolveDialogueEvent_Char = 0x1b5b77a;
uintptr_t func_Wwise_Sound_DynamicSequence_Break = 0x1b5baba;
uintptr_t func_Wwise_Sound_DynamicSequence_Close = 0x1b5bb4c;
uintptr_t func_Wwise_Sound_DynamicSequence_LockPlaylist = 0x1b5bbde;
uintptr_t func_Wwise_Sound_DynamicSequence_Open = 0x1b57661;
uintptr_t func_Wwise_Sound_DynamicSequence_Pause = 0x1b5b8ac;
uintptr_t func_Wwise_Sound_DynamicSequence_Play = 0x1b5b816;
uintptr_t func_Wwise_Sound_DynamicSequence_Resume = 0x1b5b93e;
uintptr_t func_Wwise_Sound_DynamicSequence_Stop = 0x1b5b9d4;
uintptr_t func_Wwise_Sound_DynamicSequence_UnlockPlaylist = 0x1b5bc1e;
uintptr_t func_Wwise_Sound_ExecuteActionOnEvent_UniqueID = 0x1b5b302;
uintptr_t func_Wwise_Sound_ExecuteActionOnEvent_Char = 0x1b5b3ca;
uintptr_t func_Wwise_Sound_g_PlayingID = 0xf4e790;
uintptr_t func_Wwise_Sound_GetDefaultInitSettings = 0x1b5683d;
uintptr_t func_Wwise_Sound_GetDefaultPlatformInitSettings = 0x1b5689d;
uintptr_t func_Wwise_Sound_GetIDFromString = 0x1b58956;
uintptr_t func_Wwise_Sound_GetPanningRule = 0x1b568fd;
uintptr_t func_Wwise_Sound_GetSourcePlayPosition = 0x1b57631;
uintptr_t func_Wwise_Sound_GetSpeakerConfiguration = 0x1b5690d;
uintptr_t func_Wwise_Sound_Init = 0x1b5bdbd;
uintptr_t func_Wwise_Sound_IsInitialized = 0x01f56829;
uintptr_t func_Wwise_Sound_LoadBank_BankID_MemPoolID = 0x1b57a8f;
uintptr_t func_Wwise_Sound_LoadBank_Void_UInt32_BankID = 0x1b57b81;
uintptr_t func_Wwise_Sound_LoadBank_BankID_CallBack = 0x1b57c55;
uintptr_t func_Wwise_Sound_LoadBank_Void_UInt32_CallBack = 0x1b57cd0;
uintptr_t func_Wwise_Sound_LoadBank_Char_MemPoolID = 0x1b5916c;
uintptr_t func_Wwise_Sound_LoadBank_Char_CallBack = 0x1b592c1;
uintptr_t func_Wwise_Sound_LoadBankUnique = 0x1b5933c;
uintptr_t func_Wwise_Sound_PlaySourcePlugin = 0x1b574d5;
uintptr_t func_Wwise_Sound_PostEvent_Char = 0x1b5b260;
uintptr_t func_Wwise_Sound_PostEvent_UniqueID = 0x1b5bf11;
uintptr_t func_Wwise_Sound_PostTrigger_TriggerID = 0x1b56e60;
uintptr_t func_Wwise_Sound_PostTrigger_Char = 0x1b58c2b;
uintptr_t func_Wwise_Sound_PrepareBank_BankID_Callback = 0x1b57f2c;
uintptr_t func_Wwise_Sound_PrepareBank_BankID_BankContent = 0x1b59588;
uintptr_t func_Wwise_Sound_PrepareBank_Char_CallBack = 0x1b596d4;
uintptr_t func_Wwise_Sound_PrepareBank_Char_BankContent = 0x1b5a651;
uintptr_t func_Wwise_Sound_PrepareEvent_EventID_UInt32 = 0x1b57fa1;
uintptr_t func_Wwise_Sound_PrepareEvent_EventID_UInt32_Callback_Void = 0x1b58034;
uintptr_t func_Wwise_Sound_PrepareEvent_Char_UInt32 = 0x1b59915;
uintptr_t func_Wwise_Sound_PrepareEvent_Char_UInt32_Callback_Void = 0x1b59c73;
uintptr_t func_Wwise_Sound_PrepareGameSyncs_UInt32_UInt32_UInt32_Callback_Void = 0x1b58125;
uintptr_t func_Wwise_Sound_PrepareGameSyncs_UInt32_UInt32_UInt32 = 0x1b58155;
uintptr_t func_Wwise_Sound_PrepareGameSyncs_Char_Char_UInt32_Callback_Void = 0x1b59f4d;
uintptr_t func_Wwise_Sound_PrepareGameSyncs_Char_Char_UInt32 = 0x1b5a1c0;
uintptr_t func_Wwise_Sound_Query_GetActiveGameObjects = 0x1b55e5f;
uintptr_t func_Wwise_Sound_Query_GetActiveListeners = 0x1b56168;
uintptr_t func_Wwise_Sound_Query_GetCustomPropertyValue_Int32 = 0x1b55f95;
uintptr_t func_Wwise_Sound_Query_GetCustomPropertyValue_Real32 = 0x1b56025;
uintptr_t func_Wwise_Sound_Query_GetEventIDFromPlayingID = 0x1b55f25;
uintptr_t func_Wwise_Sound_Query_GetGameObjectAuxSendValues = 0x1b56493;
uintptr_t func_Wwise_Sound_Query_GetGameObjectDryLevelValue = 0x1b5658f;
uintptr_t func_Wwise_Sound_Query_GetGameObjectFromPlayingID = 0x1b55f45;
uintptr_t func_Wwise_Sound_Query_GetIsGameObjectActive = 0x1b55e8f;
uintptr_t func_Wwise_Sound_Query_GetListenerPosition = 0x1b55c7f;
uintptr_t func_Wwise_Sound_Query_GetListenerSpatialization = 0x1b55cdf;
uintptr_t func_Wwise_Sound_Query_GetMaxRadius_Array = 0x1b55ebf;
uintptr_t func_Wwise_Sound_Query_GetMaxRadius_GameObject = 0x1b55eef;
uintptr_t func_Wwise_Sound_Query_GetObjectObstructionAndOcclusion = 0x1b56622;
uintptr_t func_Wwise_Sound_Query_GetPlayingIDsFromGameObject = 0x1b55f65;
uintptr_t func_Wwise_Sound_Query_GetPosition = 0x1b560b5;
uintptr_t func_Wwise_Sound_Query_GetPositioningInfo = 0x1b55dff;
uintptr_t func_Wwise_Sound_Query_GetRTPCValue_RTPCID = 0x1b561fb;
uintptr_t func_Wwise_Sound_Query_GetRTPCValue_Char = 0x1b5634a;
uintptr_t func_Wwise_Sound_Query_GetState_StateGroupID = 0x1b55d1f;
uintptr_t func_Wwise_Sound_Query_GetState_Char = 0x1b55daf;
uintptr_t func_Wwise_Sound_Query_GetSwitch_SwitchGroupID = 0x1b5638a;
uintptr_t func_Wwise_Sound_Query_GetSwitch_Char = 0x1b56463;
uintptr_t func_Wwise_Sound_Query_QueryAudioObjectIDs_UniqueID = 0x1b566e5;
uintptr_t func_Wwise_Sound_Query_QueryAudioObjectIDs_Char = 0x1b56799;
uintptr_t func_Wwise_Sound_RegisterBusVolumeCallback = 0x1b57018;
uintptr_t func_Wwise_Sound_RegisterCodec = 0x1b5693d;
uintptr_t func_Wwise_Sound_RegisterGameObj = 0x1b57728;
uintptr_t func_Wwise_Sound_RegisterGlobalCallback = 0x1b5a814;
uintptr_t func_Wwise_Sound_RegisterPlugin = 0x1b5692d;
uintptr_t func_Wwise_Sound_RemoveBehavioralExtension = 0x1b5a7b1;
uintptr_t func_Wwise_Sound_RenderAudio = 0x1b5691d;
uintptr_t func_Wwise_Sound_ResetRTPCValue_RTPCID = 0x1b56f0e;
uintptr_t func_Wwise_Sound_ResetRTPCValue_Char = 0x1b58e2c;
uintptr_t func_Wwise_Sound_SeekOnEvent_UniqueID_Int32 = 0x1b5b3fa;
uintptr_t func_Wwise_Sound_SeekOnEvent_Char_Int32 = 0x1b5b4af;
uintptr_t func_Wwise_Sound_SeekOnEvent_UniqueID_Float = 0x1b5b4df;
uintptr_t func_Wwise_Sound_SeekOnEvent_Char_Float = 0x1b5b5f9;
uintptr_t func_Wwise_Sound_SetActiveListeners = 0x1b56b76;
uintptr_t func_Wwise_Sound_SetActorMixerEffect = 0x1b5825a;
uintptr_t func_Wwise_Sound_SetAttenuationScalingFactor = 0x1b56aba;
uintptr_t func_Wwise_Sound_SetBankLoadIOSettings = 0x1b5785a;
uintptr_t func_Wwise_Sound_SetBusEffect_UniqueID = 0x1b581f4;
uintptr_t func_Wwise_Sound_SetBusEffect_Char = 0x1b5a3b1;
uintptr_t func_Wwise_Sound_SetEffectParam = 0x1b582bc;
uintptr_t func_Wwise_Sound_SetGameObjectAuxSendValues = 0x1b56fa9;
uintptr_t func_Wwise_Sound_SetGameObjectOutputBusVolume = 0x1b5704c;
uintptr_t func_Wwise_Sound_SetListenerPipeline = 0x1b56d24;
uintptr_t func_Wwise_Sound_SetListenerPosition = 0x1b56bc2;
uintptr_t func_Wwise_Sound_SetListenerScalingFactor = 0x1b56b1a;
uintptr_t func_Wwise_Sound_SetListenerSpatialization = 0x1b56c90;
uintptr_t func_Wwise_Sound_SetMaxNumVoicesLimit = 0x1b58e8c;
uintptr_t func_Wwise_Sound_SetMultiplePositions = 0x1b569c8;
uintptr_t func_Wwise_Sound_SetObjectObstructionAndOcclusion = 0x1b57098;
uintptr_t func_Wwise_Sound_SetPanningRule = 0x1b5744c;
uintptr_t func_Wwise_Sound_SetPosition = 0x1b58a31;
uintptr_t func_Wwise_Sound_SetPositionInternal = 0x1b5694d;
uintptr_t func_Wwise_Sound_SetRTPCValue_RTPCID = 0x1b56d73;
uintptr_t func_Wwise_Sound_SetRTPCValue_Char = 0x1b58a91;
uintptr_t func_Wwise_Sound_SetState_StateGroupID = 0x1b58c8b;
uintptr_t func_Wwise_Sound_SetState_Char = 0x1b58d69;
uintptr_t func_Wwise_Sound_SetSwitch_SwitchGroupID = 0x1b56e11;
uintptr_t func_Wwise_Sound_SetSwitch_Char = 0x1b58b50;
uintptr_t func_Wwise_Sound_SetVolumeThreshold = 0x1b58e6c;
uintptr_t func_Wwise_Sound_StartOutputCapture = 0x1b583a4;
uintptr_t func_Wwise_Sound_StopAll = 0x1b58590;
uintptr_t func_Wwise_Sound_StopOutputCapture = 0x1b58463;
uintptr_t func_Wwise_Sound_StopPlayingID = 0x1b585d9;
uintptr_t func_Wwise_Sound_StopSourcePlugin = 0x1b5756c;
uintptr_t func_Wwise_Sound_Term = 0x1b5acc6;
uintptr_t func_Wwise_Sound_UnloadBank_BankID_MemPoolID = 0x1b57d6b;
uintptr_t func_Wwise_Sound_UnloadBank_BankID_Callback = 0x1b57e91;
uintptr_t func_Wwise_Sound_UnloadBank_Char_MemPoolID = 0x1b593e7;
uintptr_t func_Wwise_Sound_UnloadBank_Char_Callback = 0x1b59482;
uintptr_t func_Wwise_Sound_UnloadBankUnique = 0x1b594fd;
uintptr_t func_Wwise_Sound_UnregisterAllGameObj = 0x1b577dd;
uintptr_t func_Wwise_Sound_UnregisterGameObj = 0x1b57784;
uintptr_t func_Wwise_Sound_UnregisterGlobalCallback = 0x1b5a844;
// StreamMgr
uintptr_t func_Wwise_Stream_AddLanguageChangeObserver = 0x1bbc23a;
uintptr_t func_Wwise_Stream_Create = 0x1bbbf66;
uintptr_t func_Wwise_Stream_CreateDevice = 0x1bbc3dc;
uintptr_t func_Wwise_Stream_DestroyDevice = 0x1bbbfe6;
uintptr_t func_Wwise_Stream_FlushAllCaches = 0x1bbc076;
uintptr_t func_Wwise_Stream_GetCurrentLanguage = 0x1bbb4c3;
uintptr_t func_Wwise_Stream_GetDefaultDeviceSettings = 0x1bbb433;
uintptr_t func_Wwise_Stream_GetDefaultSettings = 0x1bbb423;
uintptr_t func_Wwise_Stream_GetFileLocationResolver = 0x1bbb493;
uintptr_t func_Wwise_Stream_GetPoolID = 0x1bbb4b3;
uintptr_t func_Wwise_Stream_RemoveLanguageChangeObserver = 0x1bbc056;
uintptr_t func_Wwise_Stream_SetCurrentLanguage = 0x1bbc036;
uintptr_t func_Wwise_Stream_SetFileLocationResolver = 0x1bbb4a3;
// End Wwise Hijack


/* Typedef Functions */

	// IAKStreamMgr
	// Only has a single pointer, and is protected https://www.audiokinetic.com/library/2015.1.9_5624/?source=SDK&id=class_a_k_1_1_i_ak_stream_mgr_a85c6043c1a45f13b7df2f05729248b1f.html
	// End IAKStreamMgr

typedef bool(__cdecl* tIsRestoreSinkRequested)(void);
typedef bool(__cdecl* tIsUsingDummySink)(void);
// MemoryMgr
typedef AKRESULT(__cdecl* tMemory_CheckPoolId)(AkMemPoolId in_poolId);
typedef AKRESULT(__cdecl* tMemory_CreatePool)(void* in_pMemAddress, AkUInt32 in_uMemSize, AkUInt32 in_uBlockSize, AkUInt32 in_eAttributes, AkUInt32 in_uBlockAlign);
typedef AKRESULT(__cdecl* tMemory_DestroyPool)(AkMemPoolId in_poolId);
typedef AKRESULT(__cdecl* tMemory_Falign)(AkMemPoolId in_poolId, void* in_pMemAddress);
typedef void* (__cdecl* tMemory_GetBlock)(AkMemPoolId in_poolId);
typedef AkUInt32(__cdecl* tMemory_GetBlockSize)(AkMemPoolId in_poolId);
typedef AkInt32(__cdecl* tMemory_GetMaxPools)(void);
typedef AkInt32(__cdecl* tMemory_GetNumPools)(void);
typedef AkMemPoolAttributes(__cdecl* tMemory_GetPoolAttributes)(AkMemPoolId in_poolId);
typedef void(__cdecl* tMemory_GetPoolMemoryUsed)(AkMemPoolId in_poolId, PoolMemInfo* out_memInfo);
typedef AkOSChar* (__cdecl* tMemory_GetPoolName)(AkMemPoolId in_poolId);
typedef AKRESULT(__cdecl* tMemory_GetPoolStats)(AkMemPoolId in_poolId, PoolStats* out_stats);
typedef bool(__cdecl* tMemory_IsInitialized)(void);
typedef void* (__cdecl* tMemory_Malign)(AkMemPoolId in_poolId, size_t in_uSize, AkUInt32 in_uAlignment);
typedef void* (__cdecl* tMemory_Malloc)(AkMemPoolId in_poolId, size_t in_uSize);
typedef AKRESULT(__cdecl* tMemory_ReleaseBlock)(AkMemPoolId in_poolId, void* in_pMemAddress);
typedef AKRESULT(__cdecl* tMemory_SetMonitoring)(AkMemPoolId in_poolId, bool in_bDoMonitor);
typedef AKRESULT(__cdecl* tMemory_SetPoolName)(AkMemPoolId in_poolId, const char* in_pszPoolName);
typedef void(__cdecl* tMemory_Term)(void);
// End MemoryMgr
// Monitor
typedef AKRESULT(__cdecl* tMonitor_PostCode)(ErrorCode in_eError, ErrorLevel in_eErrorLevel);
// End Monitor
// Motion Engine
typedef AKRESULT(__cdecl* tMotion_AddPlayerMotionDevice)(AkUInt8 in_iPlayerID, AkUInt32 in_iCompanyID, AkUInt32 in_iDeviceID, void* in_pDevice);
typedef void(__cdecl* tMotion_RegisterMotionDevice)(AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, AkCreatePluginCallback in_pCreateFunc);
typedef void(__cdecl* tMotion_RemovePlayerMotionDevice)(AkUInt8 in_iPlayerID, AkUInt32 in_iCompanyID, AkUInt32 in_iDeviceID);
typedef void(__cdecl* tMotion_SetPlayerListener)(AkUInt8 in_iPlayerID, AkUInt8 in_iListener);
typedef void(__cdecl* tMotion_SetPlayerVolume)(AkUInt8 in_iPlayerID, AkReal32 in_fVolume);
// End Motion Engine
// Music Engine
typedef void(__cdecl* tMusic_GetDefaultInitSettings)(AkMusicSettings* out_settings);
typedef AKRESULT(__cdecl* tMusic_GetPlayingSegmentInfo)(AkPlayingID in_playingID, AkSegmentInfo* out_segmentInfo, bool in_bExtrapolate);
typedef AKRESULT(__cdecl* tMusic_Init)(AkMusicSettings* in_pSettings);
typedef void(__cdecl* tMusic_Term)(void);
// End Music Engine
// Sound Engine
typedef void(__cdecl* tCancelBankCallbackCookie)(void* in_pCookie);
typedef void(__cdecl* tCancelEventCallback)(AkPlayingID in_playingID);
typedef void(__cdecl* tCancelEventCallbackCookie)(void* in_pCookie);
typedef AKRESULT(__cdecl* tClearBanks)(void);
typedef AKRESULT(__cdecl* tClearPreparedEvents)(void);
// Dynamic Dialogue
typedef AkUniqueID(__cdecl* tDynamicDialogue_ResolveDialogueEvent_UniqueID)(AkUniqueID in_eventID, AkArgumentValueID* in_aArgumentValues, AkUInt32 in_uNumArguments, AkPlayingID in_idSequence);
typedef AkUniqueID(__cdecl* tDynamicDialogue_ResolveDialogueEvent_Char)(const char* in_pszEventName, const char** in_aArgumentValueNames, AkUInt32 in_uNumArguments, AkPlayingID in_idSequence);
// End Dynamic Dialogue
// Dynamic Sequence
typedef AKRESULT(__cdecl* tDynamicSequence_Break)(AkPlayingID in_playingID);
typedef AKRESULT(__cdecl* tDynamicSequence_Close)(AkPlayingID in_playingID);
// LockPlaylist (Dependancies)
typedef AkPlayingID(__cdecl* tDynamicSequence_Open)(AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, AkCallbackFunc in_pfnCallback, void* in_pCookie, DynamicSequenceType in_eDynamicSequenceType);
typedef AKRESULT(__cdecl* tDynamicSequence_Pause)(AkPlayingID in_playingID, AkTimeMs in_uTransitionDuration, AkCurveInterpolation in_eFadeCurve);
typedef AKRESULT(__cdecl* tDynamicSequence_Play)(AkPlayingID in_playingID, AkTimeMs in_uTransitionDuration, AkCurveInterpolation in_eFadeCurve);
typedef AKRESULT(__cdecl* tDynamicSequence_Resume)(AkPlayingID in_playingID, AkTimeMs in_uTransitionDuration, AkCurveInterpolation in_eFadeCurve);
typedef AKRESULT(__cdecl* tDynamicSequence_Stop)(AkPlayingID in_playingID, AkTimeMs in_uTransitionDuration, AkCurveInterpolation in_eFadeCurve);
// UnlockPlaylist (Dependancies)
// End Dynamic Sequence
typedef AKRESULT(__cdecl* tExecuteActionOnEvent_UniqueID)(AkUniqueID in_eventID, AkActionOnEventType in_ActionType, AkGameObjectID in_gameObjectID, AkTimeMs in_uTransitionDuration, AkCurveInterpolation in_eFadeCurve, AkPlayingID in_PlayingID);
typedef AKRESULT(__cdecl* tExecuteActionOnEvent_Char)(const char* in_pszEventName, AkActionOnEventType in_ActionType, AkGameObjectID in_gameObjectID, AkTimeMs in_uTransitionDuration, AkCurveInterpolation in_eFadeCurve, AkPlayingID in_PlayingID);
typedef void(__cdecl* tGetDefaultInitSettings)(AkCommSettings& out_settings);
// GetDefaultPlatformInitSettings (We only run on Windows, so we don't need this)
typedef AkUInt32(__cdecl* tGetIDFromString)(const char* in_pszString);
// GetPanningRule (Dependancies)
typedef AKRESULT(__cdecl* tGetSourcePlayPosition)(AkPlayingID in_PlayingID, AkTimeMs* out_puPosition, bool in_bExtrapolate);
typedef AkUInt32(__cdecl* tGetSpeakerConfiguration)(void);
// Init (This is called before we can even push different settings to it)
typedef bool(__cdecl* tIsInitialized)(void);
typedef AKRESULT(__cdecl* tLoadBank_BankID_MemPoolID)(AkBankID in_bankID, AkMemPoolId in_memPoolId);
typedef AKRESULT(__cdecl* tLoadBank_Void_UInt32_BankID)(const void* in_plnMemoryBankPtr, AkUInt32 in_ulnMemoryBankSize, AkBankID* out_bankID);
typedef AKRESULT(__cdecl* tLoadBank_BankID_CallBack)(AkBankID in_BankID, AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkMemPoolId in_memPoolId);
typedef AKRESULT(__cdecl* tLoadBank_Void_UInt32_CallBack)(const void* in_plnMemoryBankPtr, AkUInt32 in_ulnMemoryBankSize, AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkBankID* out_bankID);
typedef AKRESULT(__cdecl* tLoadBank_Char_MemPoolID)(const char* in_pszString, AkMemPoolId in_memPoolId, AkBankID* out_bankID);
typedef AKRESULT(__cdecl* tLoadBank_Char_CallBack)(const char* in_pszString, AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkMemPoolId in_memPoolId, AkBankID* out_bankId);
typedef AkPlayingID(__cdecl* tPostEvent_Char)(const char* in_pszEventName, AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, AkCallbackFunc in_pfnCallback, void* in_pCookie, AkUInt32 in_cExternals, AkExternalSourceInfo* in_pExternalSources, AkPlayingID in_PlayingID);
typedef AkPlayingID(__cdecl* tPostEvent_UniqueID)(AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, AkCallbackFunc in_pfnCallback, void* in_pCookie, AkUInt32 in_cExternals, AkExternalSourceInfo* in_pExternalSources, AkPlayingID in_PlayingID);
typedef AKRESULT(__cdecl* tPostTrigger_TriggerID)(AkTriggerID in_triggerID, AkGameObjectID in_gameObjectID);
typedef AKRESULT(__cdecl* tPostTrigger_Char)(char* in_szTriggerName, AkGameObjectID in_gameObjectID);
typedef AKRESULT(__cdecl* tPrepareBank_BankID_Callback)(PreparationType in_PreparationType, AkBankID in_bankID, AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkBankContent in_uFlags);
typedef AKRESULT(__cdecl* tPrepareBank_BankID_BankContent)(PreparationType in_PreparationType, AkBankID in_bankID, AkBankContent in_uFlags);
typedef AKRESULT(__cdecl* tPrepareBank_Char_CallBack)(PreparationType in_PreparationType, const char* in_pszString, AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkBankContent in_uFlags);
typedef AKRESULT(__cdecl* tPrepareBank_Char_BankContent)(PreparationType in_PreparationType, const char* in_pszString, AkBankContent in_uFlags);
typedef AKRESULT(__cdecl* tPrepareEvent_EventID_UInt32)(PreparationType in_PreparationType, AkUniqueID* in_pEventID, AkUInt32 in_uNumEvent);
typedef AKRESULT(__cdecl* tPrepareEvent_EventID_UInt32_Callback_Void)(PreparationType in_PreparationType, AkUniqueID* in_pEventID, AkUInt32 in_uNumEvent, AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie);
typedef AKRESULT(__cdecl* tPrepareEvent_Char_UInt32)(PreparationType in_PreparationType, const char** in_ppszString, AkUInt32 in_uNumEvent);
typedef AKRESULT(__cdecl* tPrepareEvent_Char_UInt32_Callback_Void)(PreparationType in_PreparationType, const char** in_ppszString, AkUInt32 in_uNumEvent, AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie);
typedef AKRESULT(__cdecl* tPrepareGameSyncs_UInt32_UInt32_UInt32_Callback_Void)(PreparationType in_PreparationType, AkGroupType in_eGameSyncType, AkUInt32 in_GroupID, AkUInt32* in_paGameSyncID, AkUInt32 in_uNumGameSyncs, AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie);
typedef AKRESULT(__cdecl* tPrepareGameSyncs_UInt32_UInt32_UInt32)(PreparationType in_PreparationType, AkGroupType in_eGameSyncType, AkUInt32 in_GroupID, AkUInt32* in_paGameSyncID, AkUInt32 in_uNumGameSyncs);
typedef AKRESULT(__cdecl* tPrepareGameSyncs_Char_Char_UInt32_Callback_Void)(PreparationType in_PreparationType, AkGroupType in_eGameSyncType, const char* in_pszGroupName, const char** in_ppszGameSyncName, AkUInt32 in_uNumGameSyncs, AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie);
typedef AKRESULT(__cdecl* tPrepareGameSyncs_Char_Char_UInt32)(PreparationType in_PreparationType, AkGroupType in_eGameSyncType, const char* in_pszGroupName, const char** in_ppszGameSyncName, AkUInt32 in_uNumGameSyncs);
// Query
// GetActiveGameObjects (Dependancies & Requires AkArray)
typedef AKRESULT(__cdecl* tQuery_GetActiveListeners)(AkGameObjectID in_GameObjectID, AkUInt32* out_ruListenerMask);
typedef AKRESULT(__cdecl* tQuery_GetCustomPropertyValue_Int32)(AkUniqueID in_ObjectID, AkUInt32 in_uPropID, AkInt32* out_iValue);
typedef AKRESULT(__cdecl* tQuery_GetCustomPropertyValue_Real32)(AkUniqueID in_ObjectID, AkUInt32 in_uPropID, AkReal32* out_fValue);
typedef AkUniqueID(__cdecl* tQuery_GetEventIDFromPlayingID)(AkPlayingID in_playingID);
typedef AKRESULT(__cdecl* tQuery_GetGameObjectAuxSendValues)(AkGameObjectID in_gameObjectID, AkAuxSendValue* out_paAuxSendValues, AkUInt32& io_ruNumSendValues);
typedef AKRESULT(__cdecl* tQuery_GetGameObjectDryLevelValue)(AkGameObjectID in_gameObjectID, AkReal32* out_rfControlValue);
typedef AkGameObjectID(__cdecl* tQuery_GetGameObjectFromPlayingID)(AkPlayingID in_playingID);
typedef bool(__cdecl* tQuery_GetIsGameObjectActive)(AkGameObjectID in_GameObjId);
typedef AKRESULT(__cdecl* tQuery_GetListenerPosition)(AkUInt32 in_uIndex, AkListenerPosition* out_rPosition);
// GetMaxRadius(AkArray) (Dependancies & Requires AkArray)
typedef AKRESULT(__cdecl* tQuery_GetMaxRadius)(AkGameObjectID in_GameObjId);
typedef AKRESULT(__cdecl* tQuery_GetObjectObstructionAndOcclusion)(AkGameObjectID in_ObjectID, AkUInt32 in_uListener, AkReal32* out_rfObstructionLevel, AkReal32* out_rfOcclusionLevel);
typedef AKRESULT(__cdecl* tQuery_GetPlayingIDsFromGameObject)(AkGameObjectID in_GameObjId, AkUInt32* io_ruNumIds, AkPlayingID* out_aPlayingIDs);
typedef AKRESULT(__cdecl* tQuery_GetPosition)(AkGameObjectID in_GameObjectID, AkSoundPosition* out_rPosition);
typedef AKRESULT(__cdecl* tQuery_GetPositioningInfo)(AkUniqueID in_ObjectID, AkPositioningInfo* out_rPositioningInfo);
typedef AKRESULT(__cdecl* tQuery_GetRTPCValue_Char)(const char* in_pszRtpcName, AkGameObjectID in_gameObjectID, AkRtpcValue* out_rValue, RTPCValue_type* io_rValueType);
typedef AKRESULT(__cdecl* tQuery_GetRTPCValue_RTPCID)(AkRtpcID in_rtpcID, AkGameObjectID in_gameObjectID, AkRtpcValue* out_rValue, RTPCValue_type* io_rValueType);
typedef AKRESULT(__cdecl* tQuery_GetState_StateGroupID)(AkStateGroupID in_stateGroup, AkStateID* out_rState);
typedef AKRESULT(__cdecl* tQuery_GetState_Char)(const char* in_pstrStateGroupName, AkStateID* out_rState);
typedef AKRESULT(__cdecl* tQuery_GetSwitch_SwitchGroupID)(AkSwitchGroupID in_switchGroup, AkGameObjectID in_gameObjectID, AkSwitchStateID* out_rSwitchState);
typedef AKRESULT(__cdecl* tQuery_GetSwitch_Char)(const char* in_pstrSwitchGroupName, AkGameObjectID in_GameObj, AkSwitchStateID* out_rSwitchState);
typedef AKRESULT(__cdecl* tQuery_QueryAudioObjectIDs_UniqueID)(AkUniqueID in_eventID, AkUInt32* io_ruNumItems, AkObjectInfo* out_aObjectInfos);
typedef AKRESULT(__cdecl* tQuery_QueryAudioObjectIDs_Char)(const char* in_pszEventName, AkUInt32* io_ruNumItems, AkObjectInfo* out_aObjectInfos);
// End Query
typedef AKRESULT(__cdecl* tRegisterCodec)(AkUInt32 in_ulCompanyID, AkUInt32 in_ulCodecID, AkCreateFileSourceCallback in_pFileCreateFunc, AkCreateBankSourceCallback in_pBankCreateFunc);
typedef AKRESULT(__cdecl* tRegisterGlobalCallback)(AkGlobalCallbackFunc in_pCallback);
typedef AKRESULT(__cdecl* tRegisterPlugin)(AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, AkCreatePluginCallback in_pCreateFunc, AkCreateParamCallback in_pCreateParamFunc);
typedef AKRESULT(__cdecl* tRenderAudio)(void);
typedef AKRESULT(__cdecl* tSetActiveListeners)(AkGameObjectID in_gameObjectID, AkUInt32 in_uiListenerMask);
typedef AKRESULT(__cdecl* tSetActorMixerEffect)(AkUniqueID in_audioNodeID, AkUInt32 in_uFXIndex, AkUniqueID in_shareSetID);
typedef AKRESULT(__cdecl* tSetAttenuationScalingFactor)(AkGameObjectID in_GameObjectID, AkReal32 in_fAttenuationScalingFactor);
typedef AKRESULT(__cdecl* tSetBankLoadIOSettings)(AkReal32 in_fThroughput, AkPriority in_priority);
typedef AKRESULT(__cdecl* tSetBusEffect_UniqueID)(AkUniqueID in_audioNodeID, AkUInt32 in_uFXIndex, AkUniqueID in_shareSetID);
typedef AKRESULT(__cdecl* tSetBusEffect_Char)(const char* in_pszBusName, AkUInt32 in_uFXIndex, AkUniqueID in_shareSetID);
typedef AKRESULT(__cdecl* tSetGameObjectAuxSendValues)(AkGameObjectID in_gameObjectID, AkAuxSendValue* in_aAuxSendValues, AkUInt32 in_uNumSendValues);
typedef AKRESULT(__cdecl* tSetGameObjectOutputBusVolume)(AkGameObjectID in_gameObjectID, AkReal32 in_fControlValue);
typedef AKRESULT(__cdecl* tSetListenerPipeline)(AkUInt32 in_uIndex, bool in_bAudio, bool in_bMotion);
typedef AKRESULT(__cdecl* tSetListenerPosition)(const AkListenerPosition* in_rPosition, AkUInt32 in_uiIndex);
typedef AKRESULT(__cdecl* tSetListenerScalingFactor)(AkUInt32 in_uiIndex, AkReal32 in_fAttenuationScalingFactor);
// SetListenerSpatialization (Dependancies)
typedef AKRESULT(__cdecl* tSetMaxNumVoicesLimit)(AkUInt16 in_maxNumberVoices);
typedef AKRESULT(__cdecl* tSetMultiplePositions)(AkGameObjectID in_GameObjectID, const AkSoundPosition* in_pPositions, AkUInt16 in_NumPositions, MultiPositionType in_eMultiPositionType);
typedef AKRESULT(__cdecl* tSetObjectObstructionAndOcclusion)(AkGameObjectID in_ObjectID, AkUInt32 in_uListener, AkReal32 in_fObstructionLevel, AkReal32 in_fOcclusionLevel);
// SetPanningRule (Dependancies)
typedef AKRESULT(__cdecl* tSetPosition)(AkGameObjectID in_GameObjectID, const AkSoundPosition* in_Position);
typedef AKRESULT(__cdecl* tSetRTPCValue_RTPCID)(AkRtpcID in_rtpcID, AkRtpcValue in_value, AkGameObjectID in_gameObjectID, AkTimeMs in_uValueChangeDuration, AkCurveInterpolation in_eFadeCruve, bool in_bBypassInternalValueInterpolation);
typedef AKRESULT(__cdecl* tSetRTPCValue_Char) (const char* in_pszRtpcName, AkRtpcValue in_value, AkGameObjectID in_gameObjectID, AkTimeMs in_uValueChangeDuration, AkCurveInterpolation in_eFadeCurve);
typedef AKRESULT(__cdecl* tSetState_StateGroupID)(AkStateGroupID in_stateGroup, AkStateID in_state);
typedef AKRESULT(__cdecl* tSetState_Char)(const char* in_pszStateGroup, const char* in_pszState);
typedef AKRESULT(__cdecl* tSetSwitch_SwitchGroupID)(AkSwitchGroupID in_switchGroup, AkSwitchStateID in_switchState, AkGameObjectID in_gameObjectID);
typedef AKRESULT(__cdecl* tSetSwitch_Char)(const char* in_pszSwitchGroup, const char* in_pszSwitchState, AkGameObjectID in_gameObjectID);
typedef AKRESULT(__cdecl* tSetVolumeThreshold)(AkReal32 in_fVolumeThresholdDB);
typedef AKRESULT(__cdecl* tStartOutputCapture)(const AkOSChar* in_CaptureFileName);
typedef void(__cdecl* tStopAll)(AkGameObjectID in_gameObjectID);
typedef AKRESULT(__cdecl* tStopOutputCapture)(void);
typedef AKRESULT(__cdecl* tStopPlayingID)(AkPlayingID in_playingID, AkTimeMs in_uTransitionDuration, AkCurveInterpolation in_eFadeCurve);
typedef AKRESULT(__cdecl* tTerm)(void);
typedef AKRESULT(__cdecl* tUnloadBank_BankID_MemPoolID)(AkBankID in_bankID, const void* in_pInMemoryBankPtr, AkMemPoolId* out_pMemPoolId);
typedef AKRESULT(__cdecl* tUnloadBank_BankID_Callback)(AkBankID in_bankID, const void* in_pInMemoryBankPtr, AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie);
typedef AKRESULT(__cdecl* tUnloadBank_Char_MemPoolID)(const char* in_pszString, const void* in_pInMemoryBankPtr, AkMemPoolId* out_pMemPoolId);
typedef AKRESULT(__cdecl* tUnloadBank_Char_Callback)(const char* in_pszString, const void* in_pInMemoryBankPtr, AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie);
typedef AKRESULT(__cdecl* tUnregisterAllGameObj)(void);
typedef AKRESULT(__cdecl* tUnregisterGameObj)(AkGameObjectID in_gameObjectID);
typedef AKRESULT(__cdecl* tUnregisterGlobalCallback)(AkGlobalCallbackFunc in_pCallback);
// End Sound Engine
// StreamMgr
// This Section has way too many dependancies for us to really use it.
// End StreamMgr
// End WWise Documentation

// Rocksmith Custom Wwise Functions | These will use vague types since that's all I can get out of Ghidra
// AddBehavioralExtension (Custom | Can't be added because a param requires a function)
typedef AkUInt32(__cdecl* tCloneActorMixerEffect)(AkUInt32 param_1, AkUInt32 param_2, AkUInt32 param_3);
typedef AkUInt32(__cdecl* tCloneBusEffect)(AkUInt32 param_1, AkUInt32 param_2, AkUInt32 param_3);
typedef AKRESULT(__cdecl* tLoadBankUnique)(const char* in_pszString, AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkMemPoolId in_memPoolId, AkBankID* out_bankId);
typedef AkUInt32(__cdecl* tPlaySourcePlugin)(AkUInt32 param_1, AkUInt32 param_2, AkUInt32 param_3);
// RegisterBusVolumeCallback (Custom | Can't be added because a param requires a function)
typedef AKRESULT(__cdecl* tRegisterGameObj)(AkGameObjectID in_gameObjectID);
typedef AKRESULT(__cdecl* tResetRTPCValue_RTPCID)(AkRtpcID in_rtpcID, UINT param_2, long param_3, AkCurveInterpolation in_curveInterpolation);
typedef AKRESULT(__cdecl* tResetRTPCValue_Char)(const char* in_pszRtpcName, UINT param_2, long param_3, AkCurveInterpolation in_curveInterpolation);
typedef AKRESULT(__cdecl* tSeekOnEvent_UniqueID_Int32)(AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, AkTimeMs in_iPosition, bool in_bSeekToNearestMarker);
typedef AKRESULT(__cdecl* tSeekOnEvent_Char_Int32)(const char* in_pszEventName, AkGameObjectID in_gameObjectID, AkTimeMs in_iPosition, bool in_bSeekToNearestMarker);
typedef AKRESULT(__cdecl* tSeekOnEvent_UniqueID_Float)(AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, AkReal32 in_iPosition, bool in_bSeekToNearestMarker);
typedef AKRESULT(__cdecl* tSeekOnEvent_Char_Float)(const char* in_pszEventName, AkGameObjectID in_gameObjectID, AkReal32 in_iPosition, bool in_bSeekToNearestMarker);
typedef AKRESULT(__cdecl* tSetEffectParam)(AkUInt32 param_1, short param_2, void* in_pCookie);
typedef AKRESULT(__cdecl* tSetPositionInternal)(AkGameObjectID in_GameObjectID, AkSoundPosition* in_soundPosition);
typedef AKRESULT(__cdecl* tStopSourcePlugin)(AkUInt32 param_1, AkUInt32 param_2, AkUInt32 param_3);
typedef AKRESULT(__cdecl* tUnloadBankUnique)(const char* in_pszString, AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie);
// End Rocksmith Custom Wwise Functions


/* Types To Variables (External Use) */

// TODO: Fill WwiseVariables namespace with the offset values.

// Template: type Variable = (type)MemoryAddress;
// Example: tSetRTPCValue_Char Wwise_Sound_SetRTPCValue_Char = (tSetRTPCValue_Char)func_Wwise_Sound_SetRTPCValue_Char;

namespace WwiseVariables {
	// Root Functions
	tIsRestoreSinkRequested Wwise_Root_IsRestoreSinkRequested = (tIsRestoreSinkRequested)func_Wwise_Root_IsRestoreSinkRequested;
	tIsUsingDummySink Wwise_Root_IsUsingDummySink = (tIsUsingDummySink)func_Wwise_Root_IsUsingDummySink;

	// MemoryMgr
	tMemory_CheckPoolId Wwise_Memory_CheckPoolId = (tMemory_CheckPoolId)func_Wwise_Memory_CheckPoolId;
	tMemory_CreatePool Wwise_Memory_CreatePool = (tMemory_CreatePool)func_Wwise_Memory_CreatePool;
	tMemory_DestroyPool Wwise_Memory_DestroyPool = (tMemory_DestroyPool)func_Wwise_Memory_DestroyPool;
	tMemory_Falign Wwise_Memory_Falign = (tMemory_Falign)func_Wwise_Memory_Falign;
	tMemory_GetBlock Wwise_Memory_GetBlock = (tMemory_GetBlock)func_Wwise_Memory_GetBlock;
	tMemory_GetBlockSize Wwise_Memory_GetBlockSize = (tMemory_GetBlockSize)func_Wwise_Memory_GetBlockSize;
	tMemory_GetMaxPools Wwise_Memory_GetMaxPools = (tMemory_GetMaxPools)func_Wwise_Memory_GetMaxPools;
	tMemory_GetNumPools Wwise_Memory_GetNumPools = (tMemory_GetNumPools)func_Wwise_Memory_GetNumPools;
	tMemory_GetPoolAttributes Wwise_Memory_GetPoolAttributes = (tMemory_GetPoolAttributes)func_Wwise_Memory_GetPoolAttributes;
	tMemory_GetPoolMemoryUsed Wwise_Memory_GetPoolMemoryUsed = (tMemory_GetPoolMemoryUsed)func_Wwise_Memory_GetPoolMemoryUsed;
	tMemory_GetPoolName Wwise_Memory_GetPoolName = (tMemory_GetPoolName)func_Wwise_Memory_GetPoolName;
	tMemory_GetPoolStats Wwise_Memory_GetPoolStats = (tMemory_GetPoolStats)func_Wwise_Memory_GetPoolStats;
	tMemory_IsInitialized Wwise_Memory_IsInitialized = (tMemory_IsInitialized)func_Wwise_Memory_IsInitialized;
	tMemory_Malign Wwise_Memory_Malign = (tMemory_Malign)func_Wwise_Memory_Malign;
	tMemory_Malloc Wwise_Memory_Malloc = (tMemory_Malloc)func_Wwise_Memory_Malloc;
	tMemory_ReleaseBlock Wwise_Memory_ReleaseBlock = (tMemory_ReleaseBlock)func_Wwise_Memory_ReleaseBlock;
	tMemory_SetMonitoring Wwise_Memory_SetMonitoring = (tMemory_SetMonitoring)func_Wwise_Memory_SetMonitoring;
	tMemory_SetPoolName Wwise_Memory_SetPoolName = (tMemory_SetPoolName)func_Wwise_Memory_SetPoolName;
	tMemory_Term Wwise_Memory_Term = (tMemory_Term)func_Wwise_Memory_Term;

	// Monitor
	tMonitor_PostCode Wwise_Monitor_PostCode = (tMonitor_PostCode)func_Wwise_Monitor_PostCode;

	// Motion Engine
	tMotion_AddPlayerMotionDevice Wwise_Motion_AddPlayerMotionDevice = (tMotion_AddPlayerMotionDevice)func_Wwise_Motion_AddPlayerMotionDevice;
	tMotion_RegisterMotionDevice Wwise_Motion_RegisterMotionDevice = (tMotion_RegisterMotionDevice)func_Wwise_Motion_RegisterMotionDevice;
	tMotion_RemovePlayerMotionDevice Wwise_Motion_RemovePlayerMotionDevice = (tMotion_RemovePlayerMotionDevice)func_Wwise_Motion_RemovePlayerMotionDevice;
	tMotion_SetPlayerListener Wwise_Motion_SetPlayerListener = (tMotion_SetPlayerListener)func_Wwise_Motion_SetPlayerListener;
	tMotion_SetPlayerVolume Wwise_Motion_SetPlayerVolume = (tMotion_SetPlayerVolume)func_Wwise_Motion_SetPlayerVolume;

	// Music Engine
	tMusic_GetDefaultInitSettings Wwise_Music_GetDefaultInitSettings = (tMusic_GetDefaultInitSettings)func_Wwise_Music_GetDefaultInitSettings;
	tMusic_GetPlayingSegmentInfo Wwise_Music_GetPlayingSegmentInfo = (tMusic_GetPlayingSegmentInfo)func_Wwise_Music_GetPlayingSegmentInfo;
	tMusic_Init Wwise_Music_Init = (tMusic_Init)func_Wwise_Music_Init;
	tMusic_Term Wwise_Music_Term = (tMusic_Term)func_Wwise_Music_Term;

	// Sound Engine
	tCancelBankCallbackCookie Wwise_Sound_CancelBankCallbackCookie;
	tCancelEventCallback Wwise_Sound_CancelEventCallback;
	tCancelEventCallbackCookie Wwise_Sound_CancelEventCallbackCookie;
	tClearBanks Wwise_Sound_ClearBanks;
	tClearPreparedEvents Wwise_Sound_ClearPreparedEvents;
	tDynamicDialogue_ResolveDialogueEvent_UniqueID Wwise_Sound_DynamicDialogue_ResolveDialogueEvent_UniqueID;
	tDynamicDialogue_ResolveDialogueEvent_Char Wwise_Sound_DynamicDialogue_ResolveDialogueEvent_Char;
	tDynamicSequence_Break Wwise_Sound_DynamicSequence_Break;
	tDynamicSequence_Close Wwise_Sound_DynamicSequence_Close;
	tDynamicSequence_Open Wwise_Sound_DynamicSequence_Open;
	tDynamicSequence_Pause Wwise_Sound_DynamicSequence_Pause;
	tDynamicSequence_Play Wwise_Sound_DynamicSequence_Play;
	tDynamicSequence_Resume Wwise_Sound_DynamicSequence_Resume;
	tDynamicSequence_Stop Wwise_Sound_DynamicSequence_Stop;
	tExecuteActionOnEvent_UniqueID Wwise_Sound_ExecuteActionOnEvent_UniqueID;
	tExecuteActionOnEvent_Char Wwise_Sound_ExecuteActionOnEvent_Char;
	tGetDefaultInitSettings Wwise_Sound_GetDefaultInitSettings;
	tGetIDFromString Wwise_Sound_GetIDFromString;
	tGetSourcePlayPosition Wwise_Sound_GetSourcePlayPosition;
	tGetSpeakerConfiguration Wwise_Sound_GetSpeakerConfiguration;
	tIsInitialized Wwise_Sound_IsInitialized;
	tLoadBank_BankID_MemPoolID Wwise_Sound_LoadBank_BankID_MemPoolID;
	tLoadBank_Void_UInt32_BankID Wwise_Sound_LoadBank_Void_UInt32_BankID;
	tLoadBank_BankID_CallBack Wwise_Sound_LoadBank_BankID_CallBack;
	tLoadBank_Void_UInt32_CallBack Wwise_Sound_LoadBank_Void_UInt32_CallBack;
	tLoadBank_Char_MemPoolID Wwise_Sound_LoadBank_Char_MemPoolID;
	tLoadBank_Char_CallBack Wwise_Sound_LoadBank_Char_CallBack;
	tPostEvent_Char Wwise_Sound_PostEvent_Char;
	tPostEvent_UniqueID Wwise_Sound_PostEvent_UniqueID;
	tPostTrigger_TriggerID Wwise_Sound_PostTrigger_TriggerID;
	tPostTrigger_Char Wwise_Sound_PostTrigger_Char;
	tPrepareBank_BankID_Callback Wwise_Sound_PrepareBank_BankID_Callback;
	tPrepareBank_BankID_BankContent Wwise_Sound_PrepareBank_BankID_BankContent;
	tPrepareBank_Char_CallBack Wwise_Sound_PrepareBank_Char_CallBack;
	tPrepareBank_Char_BankContent Wwise_Sound_PrepareBank_Char_BankContent;
	tPrepareEvent_EventID_UInt32 Wwise_Sound_PrepareEvent_EventID_UInt32;
	tPrepareEvent_EventID_UInt32_Callback_Void Wwise_Sound_PrepareEvent_EventID_UInt32_Callback_Void;
	tPrepareEvent_Char_UInt32 Wwise_Sound_PrepareEvent_Char_UInt32;
	tPrepareEvent_Char_UInt32_Callback_Void Wwise_Sound_PrepareEvent_Char_UInt32_Callback_Void;
	tPrepareGameSyncs_UInt32_UInt32_UInt32_Callback_Void Wwise_Sound_PrepareGameSyncs_UInt32_UInt32_UInt32_Callback_Void;
	tPrepareGameSyncs_UInt32_UInt32_UInt32 Wwise_Sound_PrepareGameSyncs_UInt32_UInt32_UInt32;
	tPrepareGameSyncs_Char_Char_UInt32_Callback_Void Wwise_Sound_PrepareGameSyncs_Char_Char_UInt32_Callback_Void;
	tPrepareGameSyncs_Char_Char_UInt32 Wwise_Sound_PrepareGameSyncs_Char_Char_UInt32;
	tQuery_GetActiveListeners Wwise_Sound_Query_GetActiveListeners;
	tQuery_GetCustomPropertyValue_Int32 Wwise_Sound_Query_GetCustomPropertyValue_Int32;
	tQuery_GetCustomPropertyValue_Real32 Wwise_Sound_Query_GetCustomPropertyValue_Real32;
	tQuery_GetEventIDFromPlayingID Wwise_Sound_Query_GetEventIDFromPlayingID;
	tQuery_GetGameObjectAuxSendValues Wwise_Sound_Query_GetGameObjectAuxSendValues;
	tQuery_GetGameObjectDryLevelValue Wwise_Sound_Query_GetGameObjectDryLevelValue;
	tQuery_GetGameObjectFromPlayingID Wwise_Sound_Query_GetGameObjectFromPlayingID;
	tQuery_GetIsGameObjectActive Wwise_Sound_Query_GetIsGameObjectActive;
	tQuery_GetListenerPosition Wwise_Sound_Query_GetListenerPosition;
	tQuery_GetMaxRadius Wwise_Sound_Query_GetMaxRadius;
	tQuery_GetObjectObstructionAndOcclusion Wwise_Sound_Query_GetObjectObstructionAndOcclusion;
	tQuery_GetPlayingIDsFromGameObject Wwise_Sound_Query_GetPlayingIDsFromGameObject;
	tQuery_GetPosition Wwise_Sound_Query_GetPosition;
	tQuery_GetPositioningInfo Wwise_Sound_Query_GetPositioningInfo;
	tQuery_GetRTPCValue_Char Wwise_Sound_Query_GetRTPCValue_Char;
	tQuery_GetRTPCValue_RTPCID Wwise_Sound_Query_GetRTPCValue_RTPCID;
	tQuery_GetState_StateGroupID Wwise_Sound_Query_GetState_StateGroupID;
	tQuery_GetState_Char Wwise_Sound_Query_GetState_Char;
	tQuery_GetSwitch_SwitchGroupID Wwise_Sound_Query_GetSwitch_SwitchGroupID;
	tQuery_GetSwitch_Char Wwise_Sound_Query_GetSwitch_Char;
	tQuery_QueryAudioObjectIDs_UniqueID Wwise_Sound_Query_QueryAudioObjectIDs_UniqueID;
	tQuery_QueryAudioObjectIDs_Char Wwise_Sound_Query_QueryAudioObjectIDs_Char;
	tRegisterCodec Wwise_Sound_RegisterCodec;
	tRegisterGlobalCallback Wwise_Sound_RegisterGlobalCallback;
	tRegisterPlugin Wwise_Sound_RegisterPlugin;
	tRenderAudio Wwise_Sound_RenderAudio;
	tSetActiveListeners Wwise_Sound_SetActiveListeners;
	tSetActorMixerEffect Wwise_Sound_SetActorMixerEffect;
	tSetAttenuationScalingFactor Wwise_Sound_SetAttenuationScalingFactor;
	tSetBankLoadIOSettings Wwise_Sound_SetBankLoadIOSettings;
	tSetBusEffect_UniqueID Wwise_Sound_SetBusEffect_UniqueID;
	tSetBusEffect_Char Wwise_Sound_SetBusEffect_Char;
	tSetGameObjectAuxSendValues Wwise_Sound_SetGameObjectAuxSendValues;
	tSetGameObjectOutputBusVolume Wwise_Sound_SetGameObjectOutputBusVolume;
	tSetListenerPipeline Wwise_Sound_SetListenerPipeline;
	tSetListenerPosition Wwise_Sound_SetListenerPosition;
	tSetListenerScalingFactor Wwise_Sound_SetListenerScalingFactor;
	tSetMaxNumVoicesLimit Wwise_Sound_SetMaxNumVoicesLimit;
	tSetMultiplePositions Wwise_Sound_SetMultiplePositions;
	tSetObjectObstructionAndOcclusion Wwise_Sound_SetObjectObstructionAndOcclusion;
	tSetPosition Wwise_Sound_SetPosition;
	tSetRTPCValue_RTPCID Wwise_Sound_SetRTPCValue_RTPCID;
	tSetRTPCValue_Char Wwise_Sound_SetRTPCValue_Char = (tSetRTPCValue_Char)func_Wwise_Sound_SetRTPCValue_Char;
	tSetState_StateGroupID Wwise_Sound_SetState_StateGroupID;
	tSetState_Char Wwise_Sound_SetState_Char;
	tSetSwitch_SwitchGroupID Wwise_Sound_SetSwitch_SwitchGroupID;
	tSetSwitch_Char Wwise_Sound_SetSwitch_Char;
	tSetVolumeThreshold Wwise_Sound_SetVolumeThreshold;
	tStartOutputCapture Wwise_Sound_StartOutputCapture;
	tStopAll Wwise_Sound_StopAll;
	tStopOutputCapture Wwise_Sound_StopOutputCapture;
	tStopPlayingID Wwise_Sound_StopPlayingID;
	tTerm Wwise_Sound_Term;
	tUnloadBank_BankID_MemPoolID Wwise_Sound_UnloadBank_BankID_MemPoolID;
	tUnloadBank_BankID_Callback Wwise_Sound_UnloadBank_BankID_Callback;
	tUnloadBank_Char_MemPoolID Wwise_Sound_UnloadBank_Char_MemPoolID;
	tUnloadBank_Char_Callback Wwise_Sound_UnloadBank_Char_Callback;
	tUnregisterAllGameObj Wwise_Sound_UnregisterAllGameObj;
	tUnregisterGameObj Wwise_Sound_UnregisterGameObj;
	tUnregisterGlobalCallback Wwise_Sound_UnregisterGlobalCallback;

	// Rocksmith Custom Wwise_Sound Functions

	tCloneActorMixerEffect Wwise_Sound_CloneActorMixerEffect;
	tCloneBusEffect Wwise_Sound_CloneBusEffect;
	tLoadBankUnique Wwise_Sound_LoadBankUnique;
	tPlaySourcePlugin Wwise_Sound_PlaySourcePlugin;
	tRegisterGameObj Wwise_Sound_RegisterGameObj;
	tResetRTPCValue_RTPCID Wwise_Sound_ResetRTPCValue_RTPCID;
	tResetRTPCValue_Char Wwise_Sound_ResetRTPCValue_Char;
	tSeekOnEvent_UniqueID_Int32 Wwise_Sound_SeekOnEvent_UniqueID_Int32;
	tSeekOnEvent_UniqueID_Float Wwise_Sound_SeekOnEvent_UniqueID_Float;
	tSeekOnEvent_Char_Int32 Wwise_Sound_SeekOnEvent_Char_Int32;
	tSeekOnEvent_Char_Float Wwise_Sound_SeekOnEvent_Char_Float;
	tSetEffectParam Wwise_Sound_SetEffectParam;
	tSetPositionInternal Wwise_Sound_SetPositionInternal;
	tStopSourcePlugin Wwise_Sound_StopSourcePlugin;
	tUnloadBankUnique Wwise_Sound_UnloadBankUnique;
}