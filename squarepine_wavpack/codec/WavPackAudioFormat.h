/** Reads the WavPack audio format.

    @see http://www.wavpack.com/
    @see https://github.com/dbry/WavPack
*/
class WavPackAudioFormat final : public AudioFormat
{
public:
    /** Constructor */
    WavPackAudioFormat();

    //==============================================================================
    static const char* const title;
    static const char* const subtitle;
    static const char* const artist;
    static const char* const album;
    static const char* const debutAlbum;
    static const char* const publisher;
    static const char* const conductor;
    static const char* const track;
    static const char* const composer;
    static const char* const comment;
    static const char* const copyright;
    static const char* const publicationRight;
    static const char* const file;
    static const char* const eanUPC;
    static const char* const isbn;
    static const char* const catalog;
    static const char* const labelCode;
    static const char* const year;
    static const char* const recordDate;
    static const char* const recordLocation;
    static const char* const genre;
    static const char* const media;
    static const char* const index;
    static const char* const related;
    static const char* const isrc;
    static const char* const abstract;
    static const char* const language;
    static const char* const bibliography;
    static const char* const introplay;

    //==============================================================================
    /** @internal */
    Array<int> getPossibleSampleRates() override;
    /** @internal */
    Array<int> getPossibleBitDepths() override;
    /** @internal */
    bool canDoStereo() override;
    /** @internal */
    bool canDoMono() override;
    /** @internal */
    bool isCompressed() override;
    /** @internal */
    StringArray getQualityOptions() override;
    /** @internal */
    AudioFormatReader* createReaderFor (InputStream* sourceStream, bool deleteStreamIfOpeningFails) override;
    /** @internal */
    AudioFormatWriter* createWriterFor (OutputStream* streamToWriteTo, double sampleRateToUse, unsigned int numberOfChannels,
                                        int bitsPerSample, const StringPairArray& metadataValues, int qualityOptionIndex) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WavPackAudioFormat)
};
