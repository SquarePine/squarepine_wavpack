#ifndef SQUAREPINE_MODULE_WAVPACK_H
#define SQUAREPINE_MODULE_WAVPACK_H

/** BEGIN_JUCE_MODULE_DECLARATION

    ID:             squarepine_wavpack
    vendor:         SquarePine
    version:        1.0.0
    name:           SquarePine WavPack
    description:    A WavPack codec wrapper for JUCE apps.
    website:        http://www.squarepine.io
    license:        ISC

    dependencies:   juce_events

    END_JUCE_MODULE_DECLARATION
*/
//==============================================================================
#include <juce_events/juce_events.h>

#include <unordered_map>

//==============================================================================
namespace sp
{
    using namespace juce;

    #include "codec/WavPackAudioFormat.h"
}

#endif //SQUAREPINE_MODULE_WAVPACK_H
