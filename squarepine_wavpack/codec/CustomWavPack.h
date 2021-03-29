#if ! DOXYGEN

#define ENABLE_DSD 1

#define ChunkHeaderFormat "4L"

//#define DISPLAY_DIAGNOSTICS

#define WaveHeaderFormat "SSLLSSSSLS"
#define WP_FORMAT_WAV   0       // Microsoft RIFF, including BWF and RF64 varients
#define WP_FORMAT_W64   1       // Sony Wave64
#define WP_FORMAT_CAF   2       // Apple CoreAudio
#define WP_FORMAT_DFF   3       // Philips DSDIFF
#define WP_FORMAT_DSF   4       // Sony DSD Format
#define WavpackHeaderFormat "4LS2LLLLL"

// or-values for WavpackHeader.flags
#define BYTES_STORED    3       // 1-4 bytes/sample
#define MONO_FLAG       4       // not stereo
#define HYBRID_FLAG     8       // hybrid mode
#define JOINT_STEREO    0x10    // joint stereo
#define CROSS_DECORR    0x20    // no-delay cross decorrelation
#define HYBRID_SHAPE    0x40    // noise shape (hybrid mode only)
#define FLOAT_DATA      0x80    // ieee 32-bit floating point data

#define INT32_DATA      0x100   // special extended int handling
#define HYBRID_BITRATE  0x200   // bitrate noise (hybrid mode only)
#define HYBRID_BALANCE  0x400   // balance noise (hybrid stereo mode only)

#define INITIAL_BLOCK   0x800   // initial block of multichannel segment
#define FINAL_BLOCK     0x1000  // final block of multichannel segment

#define SHIFT_LSB       13
#define SHIFT_MASK      (0x1fL << SHIFT_LSB)

#define MAG_LSB         18
#define MAG_MASK        (0x1fL << MAG_LSB)

#define SRATE_LSB       23
#define SRATE_MASK      (0xfL << SRATE_LSB)

#define FALSE_STEREO    0x40000000      // block is stereo, but data is mono
#define NEW_SHAPING     0x20000000      // use IIR filter for negative shaping

#define MONO_DATA (MONO_FLAG | FALSE_STEREO)

// Introduced in WavPack 5.0:
#define HAS_CHECKSUM    0x10000000      // block contains a trailing checksum
#define DSD_FLAG        0x80000000      // block is encoded DSD (1-bit PCM)

#define IGNORED_FLAGS   0x08000000      // reserved, but ignore if encountered
#define UNKNOWN_FLAGS   0x00000000      // we no longer have any of these spares

#define MIN_STREAM_VERS     0x402       // lowest stream version we'll decode
#define MAX_STREAM_VERS     0x410       // highest stream version we'll decode or encode

// These are the mask bit definitions for the metadata chunk id byte (see format.txt)

#define ID_UNIQUE               0x3f
#define ID_OPTIONAL_DATA        0x20
#define ID_ODD_SIZE             0x40
#define ID_LARGE                0x80
#define ID_DUMMY                0x0
#define ID_ENCODER_INFO         0x1
#define ID_DECORR_TERMS         0x2
#define ID_DECORR_WEIGHTS       0x3
#define ID_DECORR_SAMPLES       0x4
#define ID_ENTROPY_VARS         0x5
#define ID_HYBRID_PROFILE       0x6
#define ID_SHAPING_WEIGHTS      0x7
#define ID_FLOAT_INFO           0x8
#define ID_INT32_INFO           0x9
#define ID_WV_BITSTREAM         0xa
#define ID_WVC_BITSTREAM        0xb
#define ID_WVX_BITSTREAM        0xc
#define ID_CHANNEL_INFO         0xd
#define ID_DSD_BLOCK            0xe
#define ID_RIFF_HEADER          (ID_OPTIONAL_DATA | 0x1)
#define ID_RIFF_TRAILER         (ID_OPTIONAL_DATA | 0x2)
#define ID_ALT_HEADER           (ID_OPTIONAL_DATA | 0x3)
#define ID_ALT_TRAILER          (ID_OPTIONAL_DATA | 0x4)
#define ID_CONFIG_BLOCK         (ID_OPTIONAL_DATA | 0x5)
#define ID_MD5_CHECKSUM         (ID_OPTIONAL_DATA | 0x6)
#define ID_SAMPLE_RATE          (ID_OPTIONAL_DATA | 0x7)
#define ID_ALT_EXTENSION        (ID_OPTIONAL_DATA | 0x8)
#define ID_ALT_MD5_CHECKSUM     (ID_OPTIONAL_DATA | 0x9)
#define ID_NEW_CONFIG_BLOCK     (ID_OPTIONAL_DATA | 0xa)
#define ID_CHANNEL_IDENTITIES   (ID_OPTIONAL_DATA | 0xb)
#define ID_BLOCK_CHECKSUM       (ID_OPTIONAL_DATA | 0xf)
#define CONFIG_HYBRID_FLAG      8       // hybrid mode
#define CONFIG_JOINT_STEREO     0x10    // joint stereo
#define CONFIG_CROSS_DECORR     0x20    // no-delay cross decorrelation
#define CONFIG_HYBRID_SHAPE     0x40    // noise shape (hybrid mode only)
#define CONFIG_FAST_FLAG        0x200   // fast mode
#define CONFIG_HIGH_FLAG        0x800   // high quality mode
#define CONFIG_VERY_HIGH_FLAG   0x1000  // very high
#define CONFIG_BITRATE_KBPS     0x2000  // bitrate is kbps, not bits / sample
#define CONFIG_SHAPE_OVERRIDE   0x8000  // shaping mode specified
#define CONFIG_JOINT_OVERRIDE   0x10000 // joint-stereo mode specified
#define CONFIG_DYNAMIC_SHAPING  0x20000 // dynamic noise shaping
#define CONFIG_CREATE_EXE       0x40000 // create executable
#define CONFIG_CREATE_WVC       0x80000 // create correction file
#define CONFIG_OPTIMIZE_WVC     0x100000 // maximize bybrid compression
#define CONFIG_COMPATIBLE_WRITE 0x400000 // write files for decoders < 4.3
#define CONFIG_CALC_NOISE       0x800000 // calc noise in hybrid mode
#define CONFIG_EXTRA_MODE       0x2000000 // extra processing mode
#define CONFIG_SKIP_WVX         0x4000000 // no wvx stream w/ floats & big ints
#define CONFIG_MD5_CHECKSUM     0x8000000 // store MD5 signature
#define CONFIG_MERGE_BLOCKS     0x10000000 // merge blocks of equal redundancy (for lossyWAV)
#define CONFIG_PAIR_UNDEF_CHANS 0x20000000 // encode undefined channels in stereo pairs
#define CONFIG_OPTIMIZE_MONO    0x80000000 // optimize for mono streams posing as stereo

// The lower 8 bits of qmode indicate the use of new features in version 5 that (presently)
// only apply to Core Audio Files (CAF) and DSD files, but could apply to other things too.
// These flags are stored in the file and can be retrieved by a decoder that is aware of
// them, but the individual bits are meaningless to the library. If ANY of these bits are
// set then the MD5 sum is written with a new ID so that old decoders will not see it
// (because these features will cause the MD5 sum to be different and fail).

#define QMODE_BIG_ENDIAN        0x1     // big-endian data format (opposite of WAV format)
#define QMODE_SIGNED_BYTES      0x2     // 8-bit audio data is signed (opposite of WAV format)
#define QMODE_UNSIGNED_WORDS    0x4     // audio data (other than 8-bit) is unsigned (opposite of WAV format)
#define QMODE_REORDERED_CHANS   0x8     // source channels were not Microsoft order, so they were reordered
#define QMODE_DSD_LSB_FIRST     0x10    // DSD bytes, LSB first (most Sony .dsf files)
#define QMODE_DSD_MSB_FIRST     0x20    // DSD bytes, MSB first (Philips .dff files)
#define QMODE_DSD_IN_BLOCKS     0x40    // DSD data is blocked by channels (Sony .dsf only)
#define QMODE_DSD_AUDIO         (QMODE_DSD_LSB_FIRST | QMODE_DSD_MSB_FIRST)

// The rest of the qmode word is reserved for the private use of the command-line programs
// and are ignored by the library (and not stored either). They really should not be defined
// here, but I thought it would be a good idea to have all the definitions together.

#define QMODE_ADOBE_MODE        0x100   // user specified Adobe mode
#define QMODE_NO_STORE_WRAPPER  0x200   // user specified to not store audio file wrapper (RIFF, CAFF, etc.)
#define QMODE_CHANS_UNASSIGNED  0x400   // user specified "..." in --channel-order option
#define QMODE_IGNORE_LENGTH     0x800   // user specified to ignore length in file header
#define QMODE_RAW_PCM           0x1000  // user specified raw PCM format (no header present)

#define MAX_WAVPACK_SAMPLES ((1LL << 40) - 257)
#define OPEN_WVC        0x1     // open/read "correction" file
#define OPEN_TAGS       0x2     // read ID3v1 / APEv2 tags (seekable file)
#define OPEN_WRAPPER    0x4     // make audio wrapper available (i.e. RIFF)
#define OPEN_2CH_MAX    0x8     // open multichannel as stereo (no downmix)
#define OPEN_NORMALIZE  0x10    // normalize floating point data to +/- 1.0
#define OPEN_STREAMING  0x20    // "streaming" mode blindly unpacks blocks w/o regard to header file position info
#define OPEN_EDIT_TAGS  0x40    // allow editing of tags
#define OPEN_FILE_UTF8  0x80    // assume filenames are UTF-8 encoded, not ANSI (Windows only)
#define OPEN_DSD_NATIVE 0x100   // open DSD files as bitstreams (returned as 8-bit "samples" stored in 32-bit words)
#define OPEN_DSD_AS_PCM 0x200   // open DSD files as 24-bit PCM (decimated 8x)
#define OPEN_ALT_TYPES  0x400   // application is aware of alternate file types & qmode (just affects retrieving wrappers & MD5 checksums)
#define OPEN_NO_CHECKSUM 0x800  // don't verify block checksums before decoding

#define MODE_WVC        0x1     // a .wvc file has been found and will be used for lossless
#define MODE_LOSSLESS   0x2     // file is lossless (either pure or hybrid)
#define MODE_HYBRID     0x4     // file is hybrid mode (either lossy or lossless)
#define MODE_FLOAT      0x8     // audio data is 32-bit ieee floating point
#define MODE_VALID_TAG  0x10    // file contains a valid ID3v1 or APEv2 tag
#define MODE_HIGH       0x20    // file was created in "high" mode (information only)
#define MODE_FAST       0x40    // file was created in "fast" mode (information only)
#define MODE_EXTRA      0x80    // extra mode used, see MODE_XMODE for possible level
#define MODE_APETAG     0x100   // file contains a valid APEv2 tag
#define MODE_SFX        0x200   // file was created as a "self-extracting" executable
#define MODE_VERY_HIGH  0x400   // file was created in the "very high" mode (or in the "high" mode prior to 4.4)
#define MODE_MD5        0x800   // file contains an MD5 checksum
#define MODE_XMODE      0x7000  // level used for extra mode (1-6, 0=unknown)
#define MODE_DNS        0x8000  // dynamic noise shaping

#define FLOAT_SHIFT_ONES 1      // bits left-shifted into float = '1'
#define FLOAT_SHIFT_SAME 2      // bits left-shifted into float are the same
#define FLOAT_SHIFT_SENT 4      // bits shifted into float are sent literally
#define FLOAT_ZEROS_SENT 8      // "zeros" are not all real zeros
#define FLOAT_NEG_ZEROS  0x10   // contains negative zeros
#define FLOAT_EXCEPTIONS 0x20   // contains exceptions (inf, nan, etc.)
#define CPU_FEATURE_MMX     23

#define WORD_EOF ((int32_t)(1U << 31))

#define MAX_WRAPPER_BYTES 16777216
#define NEW_MAX_STREAMS 4096
#define OLD_MAX_STREAMS 8
#define MAX_NTERMS 16
#define MAX_TERM 8

#define CLEAR(destin) memset (&destin, 0, sizeof (destin));

// This flag provides the functionality of terminating the decoding and muting
// the output when a lossy sample appears to be corrupt. This is automatic
// for lossless files because a corrupt sample is unambigious, but for lossy
// data it might be possible for this to falsely trigger (although I have never
// seen it).

#define LOSSY_MUTE

/*
 * These config flags are not actually used for external configuration, which is
 * why they're not in the external wavpack.h file, but they are used internally
 * in the flags field of the WavpackConfig struct.
 */

#define CONFIG_MONO_FLAG        4       // not stereo
#define CONFIG_FLOAT_DATA       0x80    // ieee 32-bit floating point data

#define CONFIG_AUTO_SHAPING     0x4000  // automatic noise shaping
#define CONFIG_LOSSY_MODE       0x1000000 // obsolete (for information)

/*
 * These config flags were never actually used, or are no longer used, or are
 * used for something else now. They may be used in the future for what they
 * say, or for something else. WavPack files in the wild *may* have some of
 * these bit set in their config flags (with these older meanings), but only
 * if the stream version is 0x410 or less than 0x407. Of course, this is not
 * very important because once the file has been encoded, the config bits are
 * just for information purposes (i.e., they do not affect decoding),
 *
#define CONFIG_ADOBE_MODE       0x100   // "adobe" mode for 32-bit floats
#define CONFIG_VERY_FAST_FLAG   0x400   // double fast
#define CONFIG_COPY_TIME        0x20000 // copy file-time from source
#define CONFIG_QUALITY_MODE     0x200000 // psychoacoustic quality mode
#define CONFIG_RAW_FLAG         0x400000 // raw mode (not implemented yet)
#define CONFIG_QUIET_MODE       0x10000000 // don't report progress %
#define CONFIG_IGNORE_LENGTH    0x20000000 // ignore length in wav header
#define CONFIG_NEW_RIFF_HEADER  0x40000000 // generate new RIFF wav header
 *
 */

#define EXTRA_SCAN_ONLY         1
#define EXTRA_STEREO_MODES      2
#define EXTRA_TRY_DELTAS        8
#define EXTRA_ADJUST_DELTAS     16
#define EXTRA_SORT_FIRST        32
#define EXTRA_BRANCHES          0x1c0
#define EXTRA_SKIP_8TO16        512
#define EXTRA_TERMS             0x3c00
#define EXTRA_DUMP_TERMS        16384
#define EXTRA_SORT_LAST         32768

#define get_mantissa(f)     ((f) & 0x7fffff)
#define get_magnitude(f)    ((f) & 0x7fffffff)
#define get_exponent(f)     (((f) >> 23) & 0xff)
#define get_sign(f)         (((f) >> 31) & 0x1)

#define set_mantissa(f,v)   (f) ^= (((f) ^ (v)) & 0x7fffff)
#define set_exponent(f,v)   (f) ^= (((f) ^ ((uint32_t)(v) << 23)) & 0x7f800000)
#define set_sign(f,v)       (f) ^= (((f) ^ ((uint32_t)(v) << 31)) & 0x80000000)

// these control the time constant "slow_level" which is used for hybrid mode
// that controls bitrate as a function of residual level (HYBRID_BITRATE).
#define SLS 8
#define SLO ((1 << (SLS - 1)))

#define LIMIT_ONES 16   // maximum consecutive 1s sent for "div" data

// these control the time constant of the 3 median level breakpoints
#define DIV0 128        // 5/7 of samples
#define DIV1 64         // 10/49 of samples
#define DIV2 32         // 20/343 of samples

// this macro retrieves the specified median breakpoint (without frac; min = 1)
#define GET_MED(med) (((c->median [med]) >> 4) + 1)

// These macros update the specified median breakpoints. Note that the median
// is incremented when the sample is higher than the median, else decremented.
// They are designed so that the median will never drop below 1 and the value
// is essentially stationary if there are 2 increments for every 5 decrements.

#define INC_MED0() (c->median [0] += ((c->median [0] + DIV0) / DIV0) * 5)
#define DEC_MED0() (c->median [0] -= ((c->median [0] + (DIV0-2)) / DIV0) * 2)
#define INC_MED1() (c->median [1] += ((c->median [1] + DIV1) / DIV1) * 5)
#define DEC_MED1() (c->median [1] -= ((c->median [1] + (DIV1-2)) / DIV1) * 2)
#define INC_MED2() (c->median [2] += ((c->median [2] + DIV2) / DIV2) * 5)
#define DEC_MED2() (c->median [2] -= ((c->median [2] + (DIV2-2)) / DIV2) * 2)


// DSD-specific definitions

#define MAX_HISTORY_BITS    5       // maximum number of history bits in DSD "fast" mode
                                    // note that 5 history bits requires 32 history bins
#define MAX_BYTES_PER_BIN   1280    // maximum bytes for the value lookup array (per bin)
                                    //  such that the total storage per bin = 2K (also
                                    //  counting probabilities and summed_probabilities)

// This function scans a buffer of longs and accumulates the total log2 value
// of all the samples. This is useful for determining maximum compression
// because the bitstream storage required for entropy coding is proportional
// to the base 2 log of the samples. On some platforms there is an assembly
// version of this.
#ifdef OPT_ASM_X86
#define LOG2BUFFER log2buffer_x86
#elif defined(OPT_ASM_X64) && (defined (_WIN64) || defined(__CYGWIN__) || defined(__MINGW64__) || defined(__midipix__))
#define LOG2BUFFER log2buffer_x64win
#elif defined(OPT_ASM_X64)
#define LOG2BUFFER log2buffer_x64
#else
#define LOG2BUFFER log2buffer
#endif

uint32_t LOG2BUFFER (int32_t *samples, uint32_t num_samples, int limit);

// This function returns the log2 for the specified 32-bit signed value.
// All input values are valid and the return values are in the range of
// +/- 8192.
int wp_log2s (int32_t value);

// This function returns the original integer represented by the supplied
// logarithm (at least within the provided accuracy). The log is signed,
// but since a full 32-bit value is returned this can be used for unsigned
// conversions as well (i.e. the input range is -8192 to +8447).
int32_t wp_exp2s (int log);

// The concept of a base 2 logarithm is used in many parts of WavPack. It is
// a way of sufficiently accurately representing 32-bit signed and unsigned
// values storing only 16 bits (actually fewer). It is also used in the hybrid
// mode for quickly comparing the relative magnitude of large values (i.e.
// division) and providing smooth exponentials using only addition.
// These are not strict logarithms in that they become linear around zero and
// can therefore represent both zero and negative values. They have 8 bits
// of precision and in "roundtrip" conversions the total error never exceeds 1
// part in 225 except for the cases of +/-115 and +/-195 (which error by 1).
// This function returns the log2 for the specified 32-bit unsigned value.
// The maximum value allowed is about 0xff800000 and returns 8447.
int FASTCALL wp_log2 (uint32_t avalue);


// These two functions convert internal weights (which are normally +/-1024)
// to and from an 8-bit signed character version for storage in metadata. The
// weights are clipped here in the case that they are outside that range.
signed char store_weight (int weight);
int restore_weight (signed char weight);

void init_words (WavpackStream *wps);
void write_entropy_vars (WavpackStream *wps, WavpackMetadata *wpmd);
void write_hybrid_profile (WavpackStream *wps, WavpackMetadata *wpmd);

// Read the median log2 values from the specified metadata structure, convert
// them back to 32-bit unsigned values and store them. If length is not
// exactly correct then we flag and return an error.
int read_entropy_vars (WavpackStream *wps, WavpackMetadata *wpmd);

// Read the hybrid related values from the specified metadata structure, convert
// them back to their internal formats and store them. The extended profile
// stuff is not implemented yet, so return an error if we get more data than
// we know what to do with.
int read_hybrid_profile (WavpackStream *wps, WavpackMetadata *wpmd);

int32_t FASTCALL send_word (WavpackStream *wps, int32_t value, int chan);

void send_words_lossless (WavpackStream *wps, int32_t *buffer, int32_t nsamples);

// Read the next word from the bitstream "wvbits" and return the value. This
// function can be used for hybrid or lossless streams, but since an
// optimized version is available for lossless this function would normally
// be used for hybrid only. If a hybrid lossless stream is being read then
// the "correction" offset is written at the specified pointer. A return value
// of WORD_EOF indicates that the end of the bitstream was reached (all 1s) or
// some other error occurred.
int32_t FASTCALL get_word (WavpackStream *wps, int chan, int32_t *correction);

// This is an optimized version of get_word() that is used for lossless only
// (error_limit == 0). Also, rather than obtaining a single sample, it can be
// used to obtain an entire buffer of either mono or stereo samples.
int32_t get_words_lossless (WavpackStream *wps, int32_t *buffer, int32_t nsamples);

void flush_word (WavpackStream *wps);

int32_t nosend_word (WavpackStream *wps, int32_t value, int chan);

void scan_word (WavpackStream *wps, int32_t *samples, uint32_t num_samples, int dir);

// This function is called during both encoding and decoding of hybrid data to
// update the "error_limit" variable which determines the maximum sample error
// allowed in the main bitstream. In the HYBRID_BITRATE mode (which is the only
// currently implemented) this is calculated from the slow_level values and the
// bitrate accumulators. Note that the bitrate accumulators can be changing.
void update_error_limit (WavpackStream *wps);

extern const uint32_t bitset [32];
extern const uint32_t bitmask [32];
extern const char nbits_table [256];

// This internal structure contains everything required to handle a WavPack
// "stream", which is defined as a stereo or mono stream of audio samples. For
// multichannel audio several of these would be required. Each stream contains
// pointers to hold a complete allocated block of WavPack data, although it's
// possible to decode WavPack blocks without buffering an entire block.

struct Bitstream {
#ifdef BITSTREAM_SHORTS
    uint16_t *buf, *end, *ptr;
#else
    uint8_t *buf, *end, *ptr;
#endif
    void (*wrap)(Bitstream *bs);
    int error, bc;
    uint32_t sr;
} ;

// Note that this structure is directly accessed in assembly files, so modify with care
struct decorr_pass {
    int32_t term, delta, weight_A, weight_B;
    int32_t samples_A [MAX_TERM], samples_B [MAX_TERM];
    int32_t aweight_A, aweight_B;
    int32_t sum_A, sum_B;
};

struct WavpackDecorrSpec {
    signed char joint_stereo, delta, terms [MAX_NTERMS+1];
};

struct entropy_data {
    uint32_t median [3], slow_level, error_limit;
};

struct words_data {
    uint32_t bitrate_delta [2], bitrate_acc [2];
    uint32_t pend_data, holding_one, zeros_acc;
    int holding_zero, pend_count;
    struct entropy_data c [2];
};

struct DSDfilters {
    int32_t value, filter0, filter1, filter2, filter3, filter4, filter5, filter6, factor;
    uint32_t byte;
};

struct WavpackStream {
    WavpackHeader wphdr;
    struct words_data w;

    uint8_t *blockbuff, *blockend;
    uint8_t *block2buff, *block2end;
    int32_t *sample_buffer;

    int64_t sample_index;
    int bits, num_terms, mute_error, joint_stereo, false_stereo, shift;
    int num_decorrs, num_passes, best_decorr, mask_decorr;
    uint32_t crc, crc_x, crc_wvx;
    Bitstream wvbits, wvcbits, wvxbits;
    int init_done, wvc_skip;
    float delta_decay;

    uint8_t int32_sent_bits, int32_zeros, int32_ones, int32_dups;
    uint8_t float_flags, float_shift, float_max_exp, float_norm_exp;

    struct {
        int32_t shaping_acc [2], shaping_delta [2], error [2];
        double noise_sum, noise_ave, noise_max;
        int16_t *shaping_data, *shaping_array;
        int32_t shaping_samples;
    } dc;

    struct decorr_pass decorr_passes [MAX_NTERMS], analysis_pass;
    const WavpackDecorrSpec *decorr_specs;

    struct {
        uint8_t *byteptr, *endptr, (*probabilities) [256], *lookup_buffer, **value_lookup, mode, ready;
        int history_bins, p0, p1;
        uint16_t (*summed_probabilities) [256];
        uint32_t low, high, value;
        DSDfilters filters [2];
        int32_t *ptable;
    } dsd;

};


// This internal structure holds everything required to encode or decode WavPack
// files. It is recommended that direct access to this structure be minimized
// and the provided utilities used instead.
struct WavpackContext {
    WavpackConfig config;

    WavpackMetadata *metadata;
    uint32_t metabytes;
    int metacount;

    uint8_t *wrapper_data;
    uint32_t wrapper_bytes;

    WavpackBlockOutput blockout;
    void *wv_out, *wvc_out;

    WavpackStreamReader64 *reader;
    void *wv_in, *wvc_in;

    int64_t filelen, file2len, filepos, file2pos, total_samples, initial_index;
    uint32_t crc_errors, first_flags;
    int wvc_flag, open_flags, norm_offset, reduced_channels, lossy_blocks, version_five;
    uint32_t block_samples, ave_block_samples, block_boundary, max_samples, acc_samples, riff_trailer_bytes;
    int riff_header_added, riff_header_created;
    M_Tag m_tag;

    int current_stream, num_streams, max_streams, stream_version;
    WavpackStream **streams;
    void *stream3;

    // these items were added in 5.0 to support alternate file types (especially CAF & DSD)
    uint8_t file_format, *channel_reordering, *channel_identities;
    uint32_t channel_layout, dsd_multiplier;
    void *decimation_context;
    char file_extension [8];

    void (*close_callback)(void *wpc);
    char error_message [80];
};

// #define SKIP_DECORRELATION   // experimental switch to disable all decorrelation on encode

// These macros implement the weight application and update operations
// that are at the heart of the decorrelation loops. Note that there are
// sometimes two and even three versions of each macro. Theses should be
// equivalent and produce identical results, but some may perform better
// or worse on a given architecture.
#if 1   // PERFCOND - apply decorrelation weight when no 32-bit overflow possible
#define apply_weight_i(weight, sample) ((weight * sample + 512) >> 10)
#else
#define apply_weight_i(weight, sample) ((((weight * sample) >> 8) + 2) >> 2)
#endif

#if 1   // PERFCOND - apply decorrelation weight when 32-bit overflow is possible
#define apply_weight_f(weight, sample) (((((sample & 0xffff) * weight) >> 9) + \
    (((sample & ~0xffff) >> 9) * weight) + 1) >> 1)
#elif 1
#define apply_weight_f(weight, sample) ((int32_t)((weight * (int64_t) sample + 512) >> 10))
#else
#define apply_weight_f(weight, sample) ((int32_t)floor(((double) weight * sample + 512.0) / 1024.0))
#endif

#if 1   // PERFCOND - universal version that checks input magnitude or always uses long version
#define apply_weight(weight, sample) (sample != (int16_t) sample ? \
    apply_weight_f (weight, sample) : apply_weight_i (weight, sample))
#else
#define apply_weight(weight, sample) (apply_weight_f (weight, sample))
#endif

#if 1   // PERFCOND
#define update_weight(weight, delta, source, result) \
    if (source && result) { int32_t s = (int32_t) (source ^ result) >> 31; weight = (delta ^ s) + (weight - s); }
#elif 1
#define update_weight(weight, delta, source, result) \
    if (source && result) weight += (((source ^ result) >> 30) | 1) * delta;
#else
#define update_weight(weight, delta, source, result) \
    if (source && result) (source ^ result) < 0 ? (weight -= delta) : (weight += delta);
#endif

#define update_weight_clip(weight, delta, source, result) \
    if (source && result) { \
        const int32_t s = (source ^ result) >> 31; \
        if ((weight = (weight ^ s) + (delta - s)) > 1024) weight = 1024; \
        weight = (weight ^ s) - s; \
    }

void pack_init (WavpackContext *wpc);
int pack_block (WavpackContext *wpc, int32_t *buffer);
void send_general_metadata (WavpackContext *wpc);
void free_metadata (WavpackMetadata *wpmd);
int copy_metadata (WavpackMetadata *wpmd, uint8_t *buffer_start, uint8_t *buffer_end);
double WavpackGetEncodedNoise (WavpackContext *wpc, double *peak);
int unpack_init (WavpackContext *wpc);
int read_decorr_terms (WavpackStream *wps, WavpackMetadata *wpmd);

// Read decorrelation weights from specified metadata block into the
// decorr_passes array. The weights range +/-1024, but are rounded and
// truncated to fit in signed chars for metadata storage. Weights are
// separate for the two channels and are specified from the "last" term
// (first during encode). Unspecified weights are set to zero.
int read_decorr_weights (WavpackStream *wps, WavpackMetadata *wpmd);

// Read decorrelation samples from specified metadata block into the
// decorr_passes array. The samples are signed 32-bit values, but are
// converted to signed log2 values for storage in metadata. Values are
// stored for both channels and are specified from the "last" term
// (first during encode) with unspecified samples set to zero. The
// number of samples stored varies with the actual term value, so
// those must obviously come first in the metadata.
int read_decorr_samples (WavpackStream *wps, WavpackMetadata *wpmd);

// Read the shaping weights from specified metadata block into the
// WavpackStream structure. Note that there must be two values (even
// for mono streams) and that the values are stored in the same
// manner as decorrelation weights. These would normally be read from
// the "correction" file and are used for lossless reconstruction of
// hybrid data.
int read_shaping_info (WavpackStream *wps, WavpackMetadata *wpmd);
int32_t unpack_samples (WavpackContext *wpc, int32_t *buffer, uint32_t sample_count);
int check_crc_error (WavpackContext *wpc);

// Scan the provided buffer of floating-point values and (1) convert the
// significant portion of the data to integers for compression using the
// regular WavPack algorithms (which only operate on integers) and (2)
// determine whether the data requires a second stream for lossless
// storage (which will usually be the case except when the floating-point
// data was originally integer data). The converted integers are returned
// "in-place" and a return value of true indicates that a second stream
// is required.
int scan_float_data (WavpackStream *wps, int32_t *values, int32_t num_values);

// Given a buffer of float data, convert the data to integers (which is what the WavPack compression
// algorithms require) and write the other data required for lossless compression (which includes
// significant bits shifted out of the integers, plus information about +/- zeros and exceptions
// like NaN and +/- infinities) into the wvxbits stream (which is assumed to be opened). Note that
// for this work correctly, scan_float_data() must have been called on the original data to set
// the appropriate flags in float_flags and max_exp.
void send_float_data (WavpackStream *wps, int32_t *values, int32_t num_values);
void float_values (WavpackStream *wps, int32_t *values, int32_t num_values);
void dynamic_noise_shaping (WavpackContext *wpc, int32_t *buffer, int shortening_allowed);
void execute_stereo (WavpackContext *wpc, int32_t *samples, int no_history, int do_samples);
void execute_mono (WavpackContext *wpc, int32_t *samples, int no_history, int do_samples);

void pack_dsd_init (WavpackContext *wpc);
int pack_dsd_block (WavpackContext *wpc, int32_t *buffer);
int init_dsd_block (WavpackContext *wpc, WavpackMetadata *wpmd);
int32_t unpack_dsd_samples (WavpackContext *wpc, int32_t *buffer, uint32_t sample_count);

void *decimate_dsd_init (int num_channels);
void decimate_dsd_reset (void *decimate_context);
void decimate_dsd_run (void *decimate_context, int32_t *samples, int num_samples);
void decimate_dsd_destroy (void *decimate_context);

int unpack_cpu_has_feature_x86 (int findex), pack_cpu_has_feature_x86 (int findex);

WavpackContext *open_file3 (WavpackContext *wpc, char *error);
int32_t unpack_samples3 (WavpackContext *wpc, int32_t *buffer, uint32_t sample_count);
int seek_sample3 (WavpackContext *wpc, uint32_t desired_index);

// return currently decoded sample index
uint32_t get_sample_index3 (WavpackContext *wpc);

void free_stream3 (WavpackContext *wpc);
int get_version3 (WavpackContext *wpc);

#define bs_is_open(bs) ((bs)->ptr != NULL)
uint32_t bs_close_read (Bitstream *bs);

#define getbit(bs) ( \
    (((bs)->bc) ? \
        ((bs)->bc--, (bs)->sr & 1) : \
            (((++((bs)->ptr) != (bs)->end) ? (void) 0 : (bs)->wrap (bs)), (bs)->bc = sizeof (*((bs)->ptr)) * 8 - 1, ((bs)->sr = *((bs)->ptr)) & 1) \
    ) ? \
        ((bs)->sr >>= 1, 1) : \
        ((bs)->sr >>= 1, 0) \
)

#define getbits(value, nbits, bs) do { \
    while ((nbits) > (bs)->bc) { \
        if (++((bs)->ptr) == (bs)->end) (bs)->wrap (bs); \
        (bs)->sr |= (uint32_t)*((bs)->ptr) << (bs)->bc; \
        (bs)->bc += sizeof (*((bs)->ptr)) * 8; \
    } \
    *(value) = (bs)->sr; \
    if ((bs)->bc > 32) { \
        (bs)->bc -= (nbits); \
        (bs)->sr = *((bs)->ptr) >> (sizeof (*((bs)->ptr)) * 8 - (bs)->bc); \
    } \
    else { \
        (bs)->bc -= (nbits); \
        (bs)->sr >>= (nbits); \
    } \
} while (0)

#define putbit(bit, bs) do { if (bit) (bs)->sr |= (1U << (bs)->bc); \
    if (++((bs)->bc) == sizeof (*((bs)->ptr)) * 8) { \
        *((bs)->ptr) = (bs)->sr; \
        (bs)->sr = (bs)->bc = 0; \
        if (++((bs)->ptr) == (bs)->end) (bs)->wrap (bs); \
    }} while (0)

#define putbit_0(bs) do { \
    if (++((bs)->bc) == sizeof (*((bs)->ptr)) * 8) { \
        *((bs)->ptr) = (bs)->sr; \
        (bs)->sr = (bs)->bc = 0; \
        if (++((bs)->ptr) == (bs)->end) (bs)->wrap (bs); \
    }} while (0)

#define putbit_1(bs) do { (bs)->sr |= (1U << (bs)->bc); \
    if (++((bs)->bc) == sizeof (*((bs)->ptr)) * 8) { \
        *((bs)->ptr) = (bs)->sr; \
        (bs)->sr = (bs)->bc = 0; \
        if (++((bs)->ptr) == (bs)->end) (bs)->wrap (bs); \
    }} while (0)

#define putbits(value, nbits, bs) do { \
    (bs)->sr |= (uint32_t)(value) << (bs)->bc; \
    if (((bs)->bc += (nbits)) >= sizeof (*((bs)->ptr)) * 8) \
        do { \
            *((bs)->ptr) = (bs)->sr; \
            (bs)->sr >>= sizeof (*((bs)->ptr)) * 8; \
            if (((bs)->bc -= sizeof (*((bs)->ptr)) * 8) > 32 - sizeof (*((bs)->ptr)) * 8) \
                (bs)->sr |= ((value) >> ((nbits) - (bs)->bc)); \
            if (++((bs)->ptr) == (bs)->end) (bs)->wrap (bs); \
        } while ((bs)->bc >= sizeof (*((bs)->ptr)) * 8); \
} while (0)



#ifdef HAVE___BUILTIN_CLZ
#define count_bits(av) ((av) ? 32 - __builtin_clz (av) : 0)
#elif defined (_WIN64)
static __inline int count_bits (uint32_t av) { unsigned long res; return _BitScanReverse (&res, av) ? (int)(res + 1) : 0; }
#else
#define count_bits(av) ( \
 (av) < (1 << 8) ? nbits_table [av] : \
  ( \
   (av) < (1L << 16) ? nbits_table [(av) >> 8] + 8 : \
   ((av) < (1L << 24) ? nbits_table [(av) >> 16] + 16 : nbits_table [(av) >> 24] + 24) \
  ) \
)
#endif

// RIFF / wav header formats (these occur at the beginning of both wav files
// and pre-4.0 WavPack files that are not in the "raw" mode). Generally, an
// application using the library to read or write WavPack files will not be
// concerned with any of these.
struct RiffChunkHeader {
    char ckID [4];
    uint32_t ckSize;
    char formType [4];
};

struct ChunkHeader {
    char ckID [4];
    uint32_t ckSize;
};

struct WaveHeader {
    uint16_t FormatTag, NumChannels;
    uint32_t SampleRate, BytesPerSecond;
    uint16_t BlockAlign, BitsPerSample;
    uint16_t cbSize, ValidBitsPerSample;
    int32_t ChannelMask;
    uint16_t SubFormat;
    char GUID [14];
};

// This is the ONLY structure that occurs in WavPack files (as of version
// 4.0), and is the preamble to every block in both the .wv and .wvc
// files (in little-endian format). Normally, this structure has no use
// to an application using the library to read or write WavPack files,
// but if an application needs to manually parse WavPack files then this
// would be used (with appropriate endian correction).

struct WavpackHeader {
    char ckID [4];
    uint32_t ckSize;
    int16_t version;
    uint8_t block_index_u8;
    uint8_t total_samples_u8;
    uint32_t total_samples, block_index, block_samples, flags, crc;
};

// Macros to access the 40-bit block_index field
#define GET_BLOCK_INDEX(hdr) ( (int64_t) (hdr).block_index + ((int64_t) (hdr).block_index_u8 << 32) )

#define SET_BLOCK_INDEX(hdr,value) do { \
    int64_t tmp = (value);              \
    (hdr).block_index = (uint32_t) tmp; \
    (hdr).block_index_u8 =              \
        (uint8_t) (tmp >> 32);    \
} while (0)

// Macros to access the 40-bit total_samples field, which is complicated by the fact that
// all 1's in the lower 32 bits indicates "unknown" (regardless of upper 8 bits)

#define GET_TOTAL_SAMPLES(hdr) ( ((hdr).total_samples == (uint32_t) -1) ? -1 : \
    (int64_t) (hdr).total_samples + ((int64_t) (hdr).total_samples_u8 << 32) - (hdr).total_samples_u8 )

#define SET_TOTAL_SAMPLES(hdr,value) do {       \
    int64_t tmp = (value);                      \
    if (tmp < 0)                                \
        (hdr).total_samples = (uint32_t) -1;    \
    else {                                      \
        tmp += (tmp / 0xffffffffLL);            \
        (hdr).total_samples = (uint32_t) tmp;   \
        (hdr).total_samples_u8 =                \
            (uint8_t) (tmp >> 32);        \
    }                                           \
} while (0)

// This external structure is used during encode to provide configuration to
// the encoding engine and during decoding to provide fle information back to
// the higher level functions. Not all fields are used in both modes.
struct WavpackConfig {
    float bitrate, shaping_weight;
    int bits_per_sample, bytes_per_sample;
    int qmode, flags, xmode, num_channels, float_norm_exp;
    int32_t block_samples, extra_flags, sample_rate, channel_mask;
    uint8_t md5_checksum [16], md5_read;
    int num_tag_strings;                // this field is not used
    char** tag_strings;                 // this field is not used
};

struct WavpackStreamReader {
    int32_t (*read_bytes)(void* id, void* data, int32_t bcount);
    uint32_t (*get_pos)(void* id);
    int (*set_pos_abs)(void* id, uint32_t pos);
    int (*set_pos_rel)(void* id, int32_t delta, int mode);
    int (*push_back_byte)(void* id, int c);
    uint32_t (*get_length)(void* id);
    int (*can_seek)(void* id);

    // this callback is for writing edited tags only
    int32_t (*write_bytes)(void* id, void* data, int32_t bcount);
};

// Extended version of structure for handling large files and added
// functionality for truncating and closing files
struct WavpackStreamReader64 {
    int32_t (*read_bytes)(void* id, void* data, int32_t bcount);
    int32_t (*write_bytes)(void* id, void* data, int32_t bcount);
    int64_t (*get_pos)(void* id);                               // new signature for large files
    int (*set_pos_abs)(void* id, int64_t pos);                  // new signature for large files
    int (*set_pos_rel)(void* id, int64_t delta, int mode);      // new signature for large files
    int (*push_back_byte)(void* id, int c);
    int64_t (*get_length)(void* id);                            // new signature for large files
    int (*can_seek)(void* id);
    int (*truncate_here)(void* id);                             // new function to truncate file at current position
    int (*close)(void* id);                                     // new function to close file
};

struct M_Tag {
    int64_t tag_file_pos;
    int tag_begins_file;
    ID3_Tag id3_tag;
    APE_Tag_Hdr ape_tag_hdr;
    uint8_t *ape_tag_data;
};

struct WavpackMetadata {
    int32_t byte_length;
    void *data;
    uint8_t id;
} 

typedef int (*WavpackBlockOutput)(void* id, void* data, int32_t bcount);

typedef struct WavpackContext WavpackContext;

WavpackContext* WavpackOpenRawDecoder (void* main_data, int32_t main_size,
                                       void* corr_data, int32_t corr_size,
                                       int16_t version, char* error, int flags, int norm_offset);

WavpackContext* WavpackOpenFileInputEx64 (WavpackStreamReader64* reader, void* wv_id, void* wvc_id, char* error, int flags, int norm_offset);

// This function is identical to WavpackOpenFileInput64() except that instead
// of providing the new 64-bit reader callbacks, the old reader callbacks are
// utilized and a translation layer is employed. It is provided as a compatibility
// function for existing applications. To ensure that streaming applications using
// this function continue to work, the OPEN_NO_CHECKSUM flag is forced on when
// the OPEN_STREAMING flag is set.
WavpackContext* WavpackOpenFileInputEx (WavpackStreamReader* reader, void* wv_id, void* wvc_id, char* error, int flags, int norm_offset);

WavpackContext* WavpackOpenFileInput (const char* infilename, char* error, int flags, int norm_offset);

// This function obtains general information about an open input file and
// returns a mask with the following bit values:
int WavpackGetMode (WavpackContext* wpc);

int WavpackVerifySingleBlock (uint8_t* buffer, int verify_checksum);

// This function obtains information about specific file features that were
// added for version 5.0, specifically qualifications added to support CAF
// and DSD files. Except for indicating the presence of DSD data, these
// bits are meant to simply indicate the format of the data in the original
// source file and do NOT indicate how the library will return the data to
// the appication (which is always the same). This means that in general an
// application that simply wants to play or process the audio data need not
// be concerned about these. If the file is DSD audio, then either of the
// QMDOE_DSD_LSB_FIRST or QMODE_DSD_MSB_FIRST bits will be set (but the
// DSD audio is always returned to the caller MSB first).
int WavpackGetQualifyMode (WavpackContext* wpc);

// This function returns a pointer to a string describing the last error
// generated by WavPack.
char* WavpackGetErrorMessage (WavpackContext* wpc);


// This function returns the major version number of the WavPack program
// (or library) that created the open file. Currently, this can be 1 to 5.
// Minor versions are not recorded in WavPack files.
int WavpackGetVersion (WavpackContext* wpc);

// Return a string representing the recommended file extension for the open
// WavPack file. For all files created prior to WavPack 5.0 this will be "wav",
// even for raw files with no RIFF into. This string is specified in the
// call to WavpackSetFileInformation() when the file was created.
char* WavpackGetFileExtension (WavpackContext* wpc);

// Return the file format specified in the call to WavpackSetFileInformation()
// when the file was created. For all files created prior to WavPack 5.0 this
// will 0 (WP_FORMAT_WAV).
uint8_t WavpackGetFileFormat (WavpackContext* wpc);

// Unpack the specified number of samples from the current file position.
// Note that "samples" here refers to "complete" samples, which would be
// 2 longs for stereo files or even more for multichannel files, so the
// required memory at "buffer" is 4 * samples * num_channels bytes. The
// audio data is returned right-justified in 32-bit longs in the endian
// mode native to the executing processor. So, if the original data was
// 16-bit, then the values returned would be +/-32k. Floating point data
// can also be returned if the source was floating point data (and this
// can be optionally normalized to +/-1.0 by using the appropriate flag
// in the call to WavpackOpenFileInput ()). The actual number of samples
// unpacked is returned, which should be equal to the number requested unless
// the end of fle is encountered or an error occurs. After all samples have
// been unpacked then 0 will be returned.
uint32_t WavpackUnpackSamples (WavpackContext* wpc, int32_t* buffer, uint32_t samples);

// Get total number of samples contained in the WavPack file, or -1 if unknown
uint32_t WavpackGetNumSamples (WavpackContext* wpc);

int64_t WavpackGetNumSamples64 (WavpackContext* wpc);
uint32_t WavpackGetNumSamplesInFrame (WavpackContext* wpc);

// Get the current sample index position, or -1 if unknown
uint32_t WavpackGetSampleIndex (WavpackContext* wpc);

int64_t WavpackGetSampleIndex64 (WavpackContext* wpc);

// Get the number of errors encountered so far
int WavpackGetNumErrors (WavpackContext* wpc);

// return TRUE if any uncorrected lossy blocks were actually written or read
int WavpackLossyBlocks (WavpackContext* wpc);

int WavpackSeekSample (WavpackContext* wpc, uint32_t sample);
int WavpackSeekSample64 (WavpackContext* wpc, int64_t sample);

// Close the specified WavPack file and release all resources used by it.
// Returns nullptr.
WavpackContext* WavpackCloseFile (WavpackContext* wpc);

// Returns the sample rate of the specified WavPack file
uint32_t WavpackGetSampleRate (WavpackContext* wpc);

// Returns the native sample rate of the specified WavPack file
// (provides the native rate for DSD files rather than the "byte" rate that's used for
//   seeking, duration, etc. and would generally be used just for user facing reports)
uint32_t WavpackGetNativeSampleRate (WavpackContext* wpc);

// Returns the actual number of valid bits per sample contained in the
// original file, which may or may not be a multiple of 8. Floating data
// always has 32 bits, integers may be from 1 to 32 bits each. When this
// value is not a multiple of 8, then the "extra" bits are located in the
// LSBs of the results. That is, values are right justified when unpacked
// into ints, but are left justified in the number of bytes used by the
// original data.
int WavpackGetBitsPerSample (WavpackContext* wpc);

// Returns the number of bytes used for each sample (1 to 4) in the original
// file. This is required information for the user of this module because the
// audio data is returned in the LOWER bytes of the long buffer and must be
// left-shifted 8, 16, or 24 bits if normalized longs are required.
int WavpackGetBytesPerSample (WavpackContext* wpc);

// Returns the number of channels of the specified WavPack file. Note that
// this is the actual number of channels contained in the file even if the
// OPEN_2CH_MAX flag was specified when the file was opened.
int WavpackGetNumChannels (WavpackContext* wpc);

// Returns the standard Microsoft channel mask for the specified WavPack
// file. A value of zero indicates that there is no speaker assignment
// information.
int WavpackGetChannelMask (WavpackContext* wpc);

// If the OPEN_2CH_MAX flag is specified when opening the file, this function
// will return the actual number of channels decoded from the file (which may
// or may not be less than the actual number of channels, but will always be
// 1 or 2). Normally, this will be the front left and right channels of a
// multichannel file.
int WavpackGetReducedChannels (WavpackContext* wpc);

// Return the normalization value for floating point data (valid only
// if floating point data is present). A value of 127 indicates that
// the floating point range is +/- 1.0. Higher values indicate a
// larger floating point range. Note that if the client specified
// OPEN_NORMALIZE we return the normalized value (i.e., 127 + offset)
// rather than what's in the file (which isn't really relevant).
int WavpackGetFloatNormExp (WavpackContext* wpc);
int WavpackGetMD5Sum (WavpackContext* wpc, uint8_t data [16]);

// This function provides the identities of ALL the channels in the file, including the
// standard Microsoft channels (which come first, in order, and are numbered 1-18) and also
// any non-Microsoft channels (which can be in any order and have values from 33-254). The
// value 0x00 is invalid and 0xFF indicates an "unknown" or "unnassigned" channel. The
// string is nullptr terminated so the caller must supply enough space for the number
// of channels indicated by WavpackGetNumChannels(), plus one.
//
// Note that this function returns the actual order of the channels in the Wavpack file
// (i.e., the order returned by WavpackUnpackSamples()). If the file includes a "reordering"
// string because the source file was not in Microsoft order that is NOT taken into account
// here and really only needs to be considered if doing an MD5 verification or if it's
// required to restore the original order/file (like wvunpack does).
void WavpackGetChannelIdentities (WavpackContext* wpc, uint8_t* identities);

// This function allows retrieving the Core Audio File channel layout, many of which do not
// conform to the Microsoft ordering standard that WavPack requires internally (at least for
// those channels present in the "channel mask"). In addition to the layout tag, this function
// returns the reordering string (if stored in the file) to allow the unpacker to reorder the
// channels back to the specified layout (if it wants to restore the CAF order). The number of
// channels in the layout is determined from the lower nybble of the layout word (and should
// probably match the number of channels in the file), and if a reorder string is requested
// then that much space must be allocated. Note that all the reordering is actually done
// outside of this library, and that if reordering is done then the appropriate qmode bit
// will be set.
//
// Note: Normally this function would not be used by an application unless it specifically
// wanted to restore a non-standard channel order (to check an MD5, for example) or obtain
// the Core Audio channel layout ID. For simple file decoding for playback, the channel_mask
// should provide all the information required unless there are non-Microsoft channels
// involved, in which case WavpackGetChannelIdentities() will provide the identities of
// the other channels (if they are known).
uint32_t WavpackGetChannelLayout (WavpackContext* wpc, uint8_t* reorder);

// These routines are used to access (and free) header and trailer data that
// was retrieved from the Wavpack file. The header will be available before
// the samples are decoded and the trailer will be available after all samples
// have been read.
uint32_t WavpackGetWrapperBytes (WavpackContext* wpc);
uint8_t* WavpackGetWrapperData (WavpackContext* wpc);
void WavpackFreeWrapper (WavpackContext* wpc);
void WavpackSeekTrailingWrapper (WavpackContext* wpc);

// Calculate the progress through the file as a double from 0.0 (for begin)
// to 1.0 (for done). A return value of -1.0 indicates that the progress is
// unknown.
double WavpackGetProgress (WavpackContext* wpc);

// Return the total size of the WavPack file(s) in bytes.
uint32_t WavpackGetFileSize (WavpackContext* wpc);
int64_t WavpackGetFileSize64 (WavpackContext* wpc);

// Calculate the ratio of the specified WavPack file size to the size of the
// original audio data as a double greater than 0.0 and (usually) smaller than
// 1.0. A value greater than 1.0 represents "negative" compression and a
// return value of 0.0 indicates that the ratio cannot be determined.
double WavpackGetRatio (WavpackContext* wpc);

// Calculate the average bitrate of the WavPack file in bits per second. A
// return of 0.0 indicates that the bitrate cannot be determined. An option is
// provided to use (or not use) any attendant .wvc file.
double WavpackGetAverageBitrate (WavpackContext* wpc, int count_wvc);

// Calculate the bitrate of the current WavPack file block in bits per second.
// This can be used for an "instant" bit display and gets updated from about
// 1 to 4 times per second. A return of 0.0 indicates that the bitrate cannot
// be determined.
double WavpackGetInstantBitrate (WavpackContext* wpc);

// Count and return the total number of tag items in the specified file.
int WavpackGetNumTagItems (WavpackContext* wpc);

// Attempt to get the specified item from the specified file's ID3v1 or APEv2
// tag. The "size" parameter specifies the amount of space available at "value",
// if the desired item will not fit in this space then ellipses (...) will
// be appended and the string terminated. Only text data are supported. The
// actual length of the string is returned (or 0 if no matching value found).
// Note that with APEv2 tags the length might not be the same as the number of
// characters because UTF-8 encoding is used. Also, APEv2 tags can have multiple
// (nullptr separated) strings for a single value (this is why the length is
// returned). If this function is called with a nullptr "value" pointer (or a
// zero "length") then only the actual length of the value data is returned
// (not counting the terminating nullptr). This can be used to determine the
// actual memory to be allocated beforehand.
int WavpackGetTagItem (WavpackContext* wpc, const char* item, char* value, int size);

// This function looks up the tag item name by index and is used when the
// application wants to access all the items in the file's ID3v1 or APEv2 tag.
// Note that this function accesses only the item's name; WavpackGetTagItem()
// still must be called to get the actual value. The "size" parameter specifies
// the amount of space available at "item", if the desired item will not fit in
// this space then ellipses (...) will be appended and the string terminated.
// The actual length of the string is returned (or 0 if no item exists for
// index). If this function is called with a nullptr "value" pointer (or a
// zero "length") then only the actual length of the item name is returned
// (not counting the terminating nullptr). This can be used to determine the
// actual memory to be allocated beforehand. For binary tag values use the
// otherwise identical WavpackGetBinaryTagItemIndexed ();
int WavpackGetTagItemIndexed (WavpackContext* wpc, int index, char* item, int size);

// Count and return the total number of binary tag items in the specified file. This applies
// only to APEv2 tags and was implemented as a separate function to avoid breaking the old API.
int WavpackGetNumBinaryTagItems (WavpackContext* wpc);

// Attempt to get the specified binary item from the specified file's APEv2
// tag. The "size" parameter specifies the amount of space available at "value".
// If the desired item will not fit in this space then nothing will be copied
// and 0 will be returned, otherwise the actual size will be returned. If this
// function is called with a nullptr "value" pointer (or a zero "length") then only
// the actual length of the value data is returned and can be used to determine
// the actual memory to be allocated beforehand.
int WavpackGetBinaryTagItem (WavpackContext* wpc, const char* item, char* value, int size);

int WavpackGetBinaryTagItemIndexed (WavpackContext* wpc, int index, char* item, int size);

// These two functions are used to append APEv2 tags to WavPack files; one is
// for text values (UTF-8 encoded) and the other is for binary values. If no tag
// has been started, then an empty one will be allocated first. When finished,
// use WavpackWriteTag() to write the completed tag to the file. The purpose of
// the passed size parameter is obvious for binary values, but might not be for
// text values. Keep in mind that APEv2 text values can have multiple values
// that are nullptr separated, so the size is required to know the extent of the
// value (although the final terminating nullptr is not included in the passed
// size). If the specified item already exists, it will be replaced with the
// new value. ID3v1 tags are not supported.
int WavpackAppendTagItem (WavpackContext* wpc, const char* item, const char* value, int vsize);

int WavpackAppendBinaryTagItem (WavpackContext* wpc, const char* item, const char* value, int vsize);

// Delete the specified tag item from the APEv2 tag on the specified WavPack file
// (fields cannot be deleted from ID3v1 tags). A return value of true indicates
// that the item was found and successfully deleted.
int WavpackDeleteTagItem (WavpackContext* wpc, const char* item);

// Once a APEv2 tag has been created with WavpackAppendTag(), this function is
// used to write the completed tag to the end of the WavPack file. Note that
// this function uses the same "blockout" function that is used to write
// regular WavPack blocks, although that's where the similarity ends. It is also
// used to write tags that have been edited on existing files.
int WavpackWriteTag (WavpackContext* wpc);

WavpackContext* WavpackOpenFileOutput (WavpackBlockOutput blockout, void* wv_id, void* wvc_id);

void WavpackSetFileInformation (WavpackContext* wpc, char* file_extension, uint8_t file_format);

int WavpackSetConfiguration (WavpackContext* wpc, WavpackConfig* config, uint32_t total_samples);
int WavpackSetConfiguration64 (WavpackContext* wpc, WavpackConfig* config, int64_t total_samples, const uint8_t* chan_ids);
int WavpackSetChannelLayout (WavpackContext* wpc, uint32_t layout_tag, const uint8_t* reorder);
int WavpackAddWrapper (WavpackContext* wpc, void* data, uint32_t bcount);
int WavpackStoreMD5Sum (WavpackContext* wpc, uint8_t data [16]);
int WavpackPackInit (WavpackContext* wpc);
int WavpackPackSamples (WavpackContext* wpc, int32_t* sample_buffer, uint32_t sample_count);
int WavpackFlushSamples (WavpackContext* wpc);
void WavpackUpdateNumSamples (WavpackContext* wpc, void* first_block);
void* WavpackGetWrapperLocation (void* first_block, uint32_t* size);
double WavpackGetEncodedNoise (WavpackContext* wpc, double* peak);

void WavpackFloatNormalize (int32_t* values, int32_t num_values, int delta_exp);

void WavpackLittleEndianToNative (void* data, char* format);
void WavpackNativeToLittleEndian (void* data, char* format);
void WavpackBigEndianToNative (void* data, char* format);
void WavpackNativeToBigEndian (void* data, char* format);

uint32_t WavpackGetLibraryVersion();
const char* WavpackGetLibraryVersionString();

// Return true is a valid ID3v1 or APEv2 tag has been loaded.
int valid_tag (M_Tag *m_tag);

// Return false if a valid APEv2 tag was only found at the beginning of the file (these are read-only
// because they cannot be edited without possibly shifting the entire file)
int editable_tag (M_Tag *m_tag);
// Free the data for any APEv2 tag that was allocated.
void free_tag (M_Tag *m_tag);

// This function initializes everything required to unpack a WavPack block
// and must be called before unpack_samples() is called to obtain audio data.
// It is assumed that the WavpackHeader has been read into the wps->wphdr
// (in the current WavpackStream) and that the entire block has been read at
// wps->blockbuff. If a correction file is available (wpc->wvc_flag = true)
// then the corresponding correction block must be read into wps->block2buff
// and its WavpackHeader has overwritten the header at wps->wphdr. This is
// where all the metadata blocks are scanned including those that contain
// bitstream data.
static int read_metadata_buff (WavpackMetadata *wpmd, uint8_t *blockbuff, uint8_t **buffptr);
static int process_metadata (WavpackContext *wpc, WavpackMetadata *wpmd);
static void bs_open_read (Bitstream *bs, void *buffer_start, void *buffer_end);



#endif // DOXYGEN
