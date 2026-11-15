#pragma once

#include <JuceHeader.h>

/**
 * @brief Manages a set of related Chebyshev amplitude parameters.
 * 
 * This class abstracts the complexity of managing multiple related
 * AudioParameterFloat objects, improving maintainability and scalability
 * in the PluginProcessor.
 */
class ChebyshevParameterGroup
{
public:
    ChebyshevParameterGroup()
    {
        // Initialize 9 individual parameters
        params.emplace_back (std::make_unique<AudioParameterFloat> ("chebyshevAmp1", "Chebyshev Amplitude", NormalisableRange<float> (-100.0f, 100.0f), 0.5f));
        params.emplace_back (std::make_unique<AudioParameterFloat> ("chebyshevAmp2", "Chebyshev Amplitude", NormalisableRange<float> (-100.0f, 100.0f), 0.5f));
        params.emplace_back (std::make_unique<AudioParameterFloat> ("chebyshevAmp3", "Chebyshev Amplitude", NormalisableRange<float> (-100.0f, 100.0f), 0.5f));
        params.emplace_back (std::make_unique<AudioParameterFloat> ("chebyshevAmp4", "Chebyshev Amplitude", NormalisableRange<float> (-100.0f, 100.0f), 0.5f));
        params.emplace_back (std::make_unique<AudioParameterFloat> ("chebyshevAmp5", "Chebyshev Amplitude", NormalisableRange<float> (-100.0f, 100.0f), 0.5f));
        params.emplace_back (std::make_unique<AudioParameterFloat> ("chebyshevAmp6", "Chebyshev Amplitude", NormalisableRange<float> (-100.0f, 100.0f), 0.5f));
        params.emplace_back (std::make_unique<AudioParameterFloat> ("chebyshevAmp7", "Chebyshev Amplitude", NormalisableRange<float> (-100.0f, 100.0f), 0.5f));
        params.emplace_back (std::make_unique<AudioParameterFloat> ("chebyshevAmp8", "Chebyshev Amplitude", NormalisableRange<float> (-100.0f, 100.0f), 0.5f));
        params.emplace_back (std::make_unique<AudioParameterFloat> ("chebyshevAmp9", "Chebyshev Amplitude", NormalisableRange<float> (-100.0f, 100.0f), 0.5f));
    }

    /**
     * @brief Retrieves the value for a specific Chebyshev amplitude index (0-8).
     * @param index The zero-based index of the amplitude (0 for amp1, 8 for amp9).
     * @return The current float value of the parameter.
     */
    float getAmplitude(int index) const
    {
        if (index >= 0 && index < params.size())
            return params[index]->getValue();
        return 0.0f;
    }

    /**
     * @brief Returns the number of Chebyshev parameters managed.
     */
    int getCount() const
    {
        return params.size();
    }

private:
    // Vector to hold all the individual parameter objects
    std::vector<std::unique_ptr<AudioParameterFloat>> params;
};