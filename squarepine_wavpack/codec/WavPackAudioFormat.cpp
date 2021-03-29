namespace WavPackNamespace
{
   #if JUCE_MSVC
    #pragma warning (push, 1)
    #pragma warning (disable: 4189 4245 4389 4706 4838)
   #elif JUCE_CLANG
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wall"
    #pragma clang diagnostic ignored "-Wconstant-conversion"
    #pragma clang diagnostic ignored "-Wconversion"
    #pragma clang diagnostic ignored "-Wextra-semi"
    #pragma clang diagnostic ignored "-Wint-conversion"
    #pragma clang diagnostic ignored "-Wnewline-eof"
    #pragma clang diagnostic ignored "-Wmissing-field-initializers"
    #pragma clang diagnostic ignored "-Wnon-virtual-dtor"
    #pragma clang diagnostic ignored "-Woverloaded-virtual"
    #pragma clang diagnostic ignored "-Wreorder"
    #pragma clang diagnostic ignored "-Wshadow"
    #pragma clang diagnostic ignored "-Wshorten-64-to-32"
    #pragma clang diagnostic ignored "-Wsign-compare"
    #pragma clang diagnostic ignored "-Wsign-conversion"
    #pragma clang diagnostic ignored "-Wstrict-aliasing"
    #pragma clang diagnostic ignored "-Wuninitialized"
    #pragma clang diagnostic ignored "-Wunused-parameter"
    #pragma clang diagnostic ignored "-Wformat-nonliteral"
    #pragma clang diagnostic ignored "-Wc++11-compat"
    #pragma clang diagnostic ignored "-Wc++98-compat"
    #pragma clang diagnostic ignored "-Wwrite-strings"
   #endif

    #undef ENABLE_DSD
    #define ENABLE_DSD 1

    extern "C"
    {
        #include <WavPack/src/common_utils.c>
        #include <WavPack/src/entropy_utils.c>
        #include <WavPack/src/decorr_utils.c>
        #include <WavPack/src/tags.c>
        #include <WavPack/src/open_legacy.c>
        #include <WavPack/src/open_utils.c>
        #include <WavPack/src/read_words.c>
        #include <WavPack/src/tag_utils.c>
        #include <WavPack/src/unpack_dsd.c>
        #include <WavPack/src/unpack_floats.c>
        #include <WavPack/src/unpack.c>
        #include <WavPack/src/unpack3.c>
        #include <WavPack/src/unpack_seek.c>
        #include <WavPack/src/unpack3_open.c>
        #include <WavPack/src/unpack3_seek.c>
        #include <WavPack/src/unpack_utils.c>
    }

   #if JUCE_MSVC
    #pragma warning (pop)
   #elif JUCE_CLANG
    #pragma clang diagnostic pop
   #endif
}

//==============================================================================
static const char* const wavPackFormatName = "WavPack file";

//==============================================================================
const char* const WavPackAudioFormat::title = "title";
const char* const WavPackAudioFormat::subtitle = "subtitle";
const char* const WavPackAudioFormat::artist = "artist";
const char* const WavPackAudioFormat::album = "album";
const char* const WavPackAudioFormat::debutAlbum = "debutAlbum";
const char* const WavPackAudioFormat::publisher = "publisher";
const char* const WavPackAudioFormat::conductor = "conductor";
const char* const WavPackAudioFormat::track = "track";
const char* const WavPackAudioFormat::composer = "composer";
const char* const WavPackAudioFormat::comment = "comment";
const char* const WavPackAudioFormat::copyright = "copyright";
const char* const WavPackAudioFormat::publicationRight = "publicationRight";
const char* const WavPackAudioFormat::file = "file";
const char* const WavPackAudioFormat::eanUPC = "eanUPC";
const char* const WavPackAudioFormat::isbn = "isbn";
const char* const WavPackAudioFormat::catalog = "catalog";
const char* const WavPackAudioFormat::labelCode = "labelCode";
const char* const WavPackAudioFormat::year = "year";
const char* const WavPackAudioFormat::recordDate = "recordDate";
const char* const WavPackAudioFormat::recordLocation = "recordLocation";
const char* const WavPackAudioFormat::genre = "genre";
const char* const WavPackAudioFormat::media = "media";
const char* const WavPackAudioFormat::index = "index";
const char* const WavPackAudioFormat::related = "related";
const char* const WavPackAudioFormat::isrc = "isrc";
const char* const WavPackAudioFormat::abstract = "abstract";
const char* const WavPackAudioFormat::language = "language";
const char* const WavPackAudioFormat::bibliography = "bibliography";
const char* const WavPackAudioFormat::introplay = "introplay";

//==============================================================================
class WavPackReader final : public AudioFormatReader
{
public:
    WavPackReader (InputStream* const inp) :
        AudioFormatReader (inp, wavPackFormatName)
    {
        zerostruct (wvReader);
        wvReader.read_bytes = &readBytes;
        wvReader.write_bytes = &writeBytes;
        wvReader.get_pos = &getPosition;
        wvReader.set_pos_abs = &setPositionAbsolute;
        wvReader.set_pos_rel = &setPositionRelative;
        wvReader.push_back_byte = &pushBackByte;
        wvReader.get_length = &getLength;
        wvReader.can_seek = &canSeek;
        wvReader.truncate_here = &truncate;
        wvReader.close = &closeStream;

        errorMessage.preallocateBytes (80);

        using namespace WavPackNamespace;
        context = WavpackOpenFileInputEx64 (&wvReader, input, nullptr, (char*) errorMessage.toRawUTF8(), OPEN_TAGS | OPEN_NORMALIZE | OPEN_NO_CHECKSUM, 0);
        if (context == nullptr)
        {
            Logger::writeToLog (String ("WavPack error:") + NewLine() + errorMessage + NewLine());
            jassertfalse;
            return;
        }

        errorMessage.clear();

        usesFloatingPointData   = isContextFloatingPoint();
        lengthInSamples         = (int64) WavpackGetNumSamples64 (context);
        numChannels             = (unsigned int) WavpackGetNumChannels (context);
        bitsPerSample           = (unsigned int) WavpackGetBitsPerSample (context);
        sampleRate              = (double) WavpackGetSampleRate (context);

        //N.B.: Mixture of APEv2 and ID3v2
        static const char* const tagNames[] =
        {
            WavPackAudioFormat::title,
            WavPackAudioFormat::subtitle,
            WavPackAudioFormat::artist,
            WavPackAudioFormat::album,
            WavPackAudioFormat::debutAlbum,
            WavPackAudioFormat::publisher,
            WavPackAudioFormat::conductor,
            WavPackAudioFormat::track,
            WavPackAudioFormat::composer,
            WavPackAudioFormat::comment,
            WavPackAudioFormat::copyright,
            WavPackAudioFormat::publicationRight,
            WavPackAudioFormat::file,
            WavPackAudioFormat::eanUPC,
            WavPackAudioFormat::isbn,
            WavPackAudioFormat::catalog,
            WavPackAudioFormat::labelCode,
            WavPackAudioFormat::year,
            WavPackAudioFormat::recordDate,
            WavPackAudioFormat::recordLocation,
            WavPackAudioFormat::genre,
            WavPackAudioFormat::media,
            WavPackAudioFormat::index,
            WavPackAudioFormat::related,
            WavPackAudioFormat::isrc,
            WavPackAudioFormat::abstract,
            WavPackAudioFormat::language,
            WavPackAudioFormat::bibliography,
            WavPackAudioFormat::introplay
        };

        for (auto tagName : tagNames)
        {
            String s;
            s.preallocateBytes (256);

            if (WavpackGetTagItem (context, tagName, (char*) s.toRawUTF8(), 256) > 0)
            {
                s = s.trim();

                if (s.isNotEmpty())
                    metadataValues.set (tagName, s);
            }
        }
    }

    ~WavPackReader() override
    {
        if (context != nullptr)
            WavPackNamespace::WavpackCloseFile (context);

        context = nullptr;
    }

    bool isOk() const
    {
        return context != nullptr
            && sampleRate > 0.0
            && errorMessage.isEmpty();
    }

    //==============================================================================
    bool readSamples (int** destSamples, int numDestChannels, int startOffsetInDestBuffer,
                      int64 startSampleInFile, int numSamples) override
    {
        using namespace WavPackNamespace;

        if (destSamples == nullptr)
            return false;

        clearSamplesBeyondAvailableLength (destSamples, numDestChannels, startOffsetInDestBuffer,
                                           startSampleInFile, numSamples, lengthInSamples);

        const auto numChansToProcess = jmin ((int) numChannels, numDestChannels);
        if (numSamples <= 0 || numChansToProcess <= 0)
            return true;

        if (WavpackSeekSample64 (context, (int64_t) startSampleInFile) != TRUE)
            return false;

        const auto newSize = numSamples * (int) numChannels;
        if (sampleBufferSize != newSize)
        {
            sampleBufferSize = newSize;
            sampleBuffer.realloc (sampleBufferSize);
            sampleBuffer.clear (sampleBufferSize);
        }

        const auto samplesRead = (int) WavpackUnpackSamples (context, sampleBuffer, (uint32_t) numSamples);

        if (samplesRead <= 0)           return true;
        if (samplesRead > numSamples)   return false;

        ReadHelper<AudioData::Float32, AudioData::Float32, AudioData::LittleEndian>
            ::read (destSamples, startOffsetInDestBuffer, numDestChannels,
                    sampleBuffer, (int) numChannels, samplesRead);

        return true;
    }

private:
    String errorMessage;

    WavPackNamespace::WavpackStreamReader64 wvReader;
    WavPackNamespace::WavpackContext* context = nullptr;
    HeapBlock<int, false> sampleBuffer;
    int sampleBufferSize = 0;

    //==============================================================================
    bool isContextFloatingPoint() const                             { return (WavpackGetMode (context) & MODE_FLOAT) != 0; }

    static int32_t readBytes (void* id, void* data, int32_t bcount) { return (int32_t) static_cast<InputStream*> (id)->read (data, (int) bcount); }
    static int32_t writeBytes (void*, void*, int32_t)               { return 0; }
    static int64_t getPosition (void* id)                           { return (int64_t) jmax ((int64) 0, static_cast<InputStream*> (id)->getPosition()); }
    static int64_t getLength (void* id)                             { return (int64_t) jmax ((int64) 0, static_cast<InputStream*> (id)->getTotalLength()); }
    static int canSeek (void*)                                      { return 1; }
    static int setPositionAbsolute (void* id, int64_t pos)          { return static_cast<InputStream*> (id)->setPosition ((int64) pos) ? 0 : EOF; }
    static int truncate (void*)                                     { return 0; }
    static int closeStream (void*)                                  { return 0; }

    static int pushBackByte (void* id, int c)
    {
        if (auto* const in = static_cast<InputStream*> (id))
            if (! in->setPosition (in->getPosition() - 1))
                return EOF;

        return c;
    }

    static int setPositionRelative (void* id, int64_t delta, int mode)
    {
        auto* const in = static_cast<InputStream*> (id);

        auto d = (int64) delta;

        if (mode == SEEK_CUR)
            d += in->getPosition();
        else if (mode == SEEK_END)
            d += in->getTotalLength();

        in->setPosition (d);
        return 0;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WavPackReader)
};

//==============================================================================
#undef ENABLE_LEGACY
#undef ENABLE_DSD
#undef SAVE
#undef RESTORE
#undef K_DEPTH
#undef MAX_NTERMS3
#undef FAST_FLAG
#undef RAW_FLAG
#undef CALC_NOISE
#undef HIGH_FLAG
#undef BYTES_3
#undef OVER_20
#undef WVC_FLAG
#undef LOSSY_SHAPE
#undef VERY_FAST_FLAG
#undef NEW_HIGH_FLAG
#undef CANCEL_EXTREME
#undef CROSS_DECORR
#undef NEW_DECORR_FLAG
#undef JOINT_STEREO
#undef EXTREME_DECORR
#undef STORED_FLAGS
#undef NOT_STORED_FLAGS
#undef strdup
#undef FASTCALL
#undef get_mantissa
#undef get_magnitude
#undef get_exponent
#undef get_sign
#undef set_mantissa
#undef set_exponent
#undef set_sign
#undef FALSE
#undef TRUE
#undef APE_Tag_Hdr_Format
#undef APE_TAG_TYPE_TEXT
#undef APE_TAG_TYPE_BINARY
#undef APE_TAG_THIS_IS_HEADER
#undef APE_TAG_CONTAINS_HEADER
#undef APE_TAG_MAX_LENGTH
#undef ChunkHeaderFormat
#undef WaveHeaderFormat
#undef WavpackHeaderFormat
#undef GET_BLOCK_INDEX
#undef SET_BLOCK_INDEX
#undef GET_TOTAL_SAMPLES
#undef SET_TOTAL_SAMPLES
#undef BYTES_STORED
#undef MONO_FLAG
#undef HYBRID_FLAG
#undef JOINT_STEREO
#undef CROSS_DECORR
#undef HYBRID_SHAPE
#undef FLOAT_DATA
#undef INT32_DATA
#undef HYBRID_BITRATE
#undef HYBRID_BALANCE
#undef INITIAL_BLOCK
#undef FINAL_BLOCK
#undef SHIFT_LSB
#undef SHIFT_MASK
#undef MAG_LSB
#undef MAG_MASK
#undef SRATE_LSB
#undef SRATE_MASK
#undef FALSE_STEREO
#undef NEW_SHAPING
#undef MONO_DATA
#undef HAS_CHECKSUM
#undef DSD_FLAG
#undef IGNORED_FLAGS
#undef UNKNOWN_FLAGS
#undef MIN_STREAM_VERS
#undef MAX_STREAM_VERS
#undef CUR_STREAM_VERS
#undef ID_UNIQUE
#undef ID_OPTIONAL_DATA
#undef ID_ODD_SIZE
#undef ID_LARGE
#undef ID_DUMMY
#undef ID_ENCODER_INFO
#undef ID_DECORR_TERMS
#undef ID_DECORR_WEIGHTS
#undef ID_DECORR_SAMPLES
#undef ID_ENTROPY_VARS
#undef ID_HYBRID_PROFILE
#undef ID_SHAPING_WEIGHTS
#undef ID_FLOAT_INFO
#undef ID_INT32_INFO
#undef ID_WV_BITSTREAM
#undef ID_WVC_BITSTREAM
#undef ID_WVX_BITSTREAM
#undef ID_CHANNEL_INFO
#undef ID_DSD_BLOCK
#undef ID_RIFF_HEADER
#undef ID_RIFF_TRAILER
#undef ID_ALT_HEADER
#undef ID_ALT_TRAILER
#undef ID_CONFIG_BLOCK
#undef ID_MD5_CHECKSUM
#undef ID_SAMPLE_RATE
#undef ID_ALT_EXTENSION
#undef ID_ALT_MD5_CHECKSUM
#undef ID_NEW_CONFIG_BLOCK
#undef ID_CHANNEL_IDENTITIES
#undef ID_BLOCK_CHECKSUM
#undef CONFIG_BYTES_STORED
#undef CONFIG_MONO_FLAG
#undef CONFIG_HYBRID_FLAG
#undef CONFIG_JOINT_STEREO
#undef CONFIG_CROSS_DECORR
#undef CONFIG_HYBRID_SHAPE
#undef CONFIG_FLOAT_DATA
#undef CONFIG_FAST_FLAG
#undef CONFIG_HIGH_FLAG
#undef CONFIG_VERY_HIGH_FLAG
#undef CONFIG_BITRATE_KBPS
#undef CONFIG_AUTO_SHAPING
#undef CONFIG_SHAPE_OVERRIDE
#undef CONFIG_JOINT_OVERRIDE
#undef CONFIG_DYNAMIC_SHAPING
#undef CONFIG_CREATE_EXE
#undef CONFIG_CREATE_WVC
#undef CONFIG_OPTIMIZE_WVC
#undef CONFIG_COMPATIBLE_WRITE
#undef CONFIG_CALC_NOISE
#undef CONFIG_LOSSY_MODE
#undef CONFIG_EXTRA_MODE
#undef CONFIG_SKIP_WVX
#undef CONFIG_MD5_CHECKSUM
#undef CONFIG_MERGE_BLOCKS
#undef CONFIG_PAIR_UNDEF_CHANS
#undef CONFIG_OPTIMIZE_MONO
#undef QMODE_DSD_AUDIO
#undef EXTRA_SCAN_ONLY
#undef EXTRA_STEREO_MODES
#undef EXTRA_TRY_DELTAS
#undef EXTRA_ADJUST_DELTAS
#undef EXTRA_SORT_FIRST
#undef EXTRA_BRANCHES
#undef EXTRA_SKIP_8TO16
#undef EXTRA_TERMS
#undef EXTRA_DUMP_TERMS
#undef EXTRA_SORT_LAST
#undef MAX_WRAPPER_BYTES
#undef NEW_MAX_STREAMS
#undef OLD_MAX_STREAMS
#undef MAX_NTERMS
#undef MAX_TERM
#undef FLOAT_SHIFT_ONES
#undef FLOAT_SHIFT_SAME
#undef FLOAT_SHIFT_SENT
#undef FLOAT_ZEROS_SENT
#undef FLOAT_NEG_ZEROS
#undef FLOAT_EXCEPTIONS
#undef CLEAR
#undef apply_weight_i
#undef apply_weight
#undef apply_weight_f
#undef update_weight
#undef update_weight_clip
#undef CPU_FEATURE_MMX
#undef bs_is_open
#undef getbit
#undef getbits
#undef putbit
#undef putbit_0
#undef putbit_1
#undef putbits
#undef SLS
#undef SLO
#undef LIMIT_ONES
#undef DIV0
#undef DIV1
#undef DIV2
#undef GET_MED
#undef INC_MED0
#undef DEC_MED0
#undef INC_MED1
#undef DEC_MED1
#undef INC_MED2
#undef DEC_MED2
#undef OPEN_WVC
#undef OPEN_TAGS
#undef OPEN_WRAPPER
#undef OPEN_2CH_MAX
#undef OPEN_NORMALIZE
#undef OPEN_STREAMING
#undef OPEN_EDIT_TAGS
#undef OPEN_FILE_UTF8
#undef OPEN_DSD_NATIVE
#undef OPEN_DSD_AS_PCM
#undef OPEN_ALT_TYPES
#undef OPEN_NO_CHECKSUM
#undef MODE_WVC
#undef MODE_LOSSLESS
#undef MODE_HYBRID
#undef MODE_FLOAT
#undef MODE_VALID_TAG
#undef MODE_HIGH
#undef MODE_FAST
#undef MODE_EXTRA
#undef MODE_APETAG
#undef MODE_SFX
#undef MODE_VERY_HIGH
#undef MODE_MD5
#undef MODE_XMODE
#undef MODE_DNS

//==============================================================================
WavPackAudioFormat::WavPackAudioFormat() :
    AudioFormat (wavPackFormatName, ".wv")
{
}

Array<int> WavPackAudioFormat::getPossibleSampleRates()
{
    return
    {
        6000, 8000, 9600, 11025, 12000, 16000, 22050, 24000,
        32000, 44100, 48000, 64000, 88200, 96000, 192000
    };
}

Array<int> WavPackAudioFormat::getPossibleBitDepths()   { return { 8, 12, 16, 20, 24, 32 }; }
bool WavPackAudioFormat::canDoStereo()                  { return true; }
bool WavPackAudioFormat::canDoMono()                    { return true; }
bool WavPackAudioFormat::isCompressed()                 { return true; }

AudioFormatReader* WavPackAudioFormat::createReaderFor (InputStream* in, const bool deleteStreamIfOpeningFails)
{
    auto r = std::make_unique<WavPackReader> (in);

    if (r->isOk())
        return r.release();

    if (! deleteStreamIfOpeningFails)
        r->input = nullptr;

    return nullptr;
}

AudioFormatWriter* WavPackAudioFormat::createWriterFor (OutputStream*, double, unsigned int,
                                                        int, const StringPairArray&, int)
{
    jassertfalse; // Not yet implemented!
    return nullptr;
}

StringArray WavPackAudioFormat::getQualityOptions()
{
    static const char* options[] =
    {
        NEEDS_TRANS ("Fast"),
        NEEDS_TRANS ("High"),
        NEEDS_TRANS ("Very High"),
        nullptr
    };

    return StringArray (options);
}
