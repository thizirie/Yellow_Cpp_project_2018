 //
    // SFML - Simple and Fast Multimedia Library
    // Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
    //
    // This software is provided 'as-is', without any express or implied warranty.
    // In no event will the authors be held liable for any damages arising from the use of this software.
    //
    // Permission is granted to anyone to use this software for any purpose,
    // including commercial applications, and to alter it and redistribute it freely,
    // subject to the following restrictions:
    //
    // 1. The origin of this software must not be misrepresented;
    //    you must not claim that you wrote the original software.
    //    If you use this software in a product, an acknowledgment
    //    in the product documentation would be appreciated but is not required.
    //
    // 2. Altered source versions must be plainly marked as such,
    //    and must not be misrepresented as being the original software.
    //
    // 3. This notice may not be removed or altered from any source distribution.
    //
    
    #ifndef SFML_MUSIC_HPP
    #define SFML_MUSIC_HPP
    
    // Headers
    #include <SFML/Audio/Export.hpp>
    #include <SFML/Audio/SoundStream.hpp>
    #include <SFML/Audio/InputSoundFile.hpp>
    #include <SFML/System/Mutex.hpp>
    #include <SFML/System/Time.hpp>
    #include <string>
    #include <vector>
    
    
    namespace sf
    {
    class InputStream;
    
    class SFML_AUDIO_API Music : public SoundStream
    {
    public:
    
        template <typename T>
        struct Span
        {
            Span()
            {
    
            }
    
            Span(T off, T len):
            offset(off),
            length(len)
            {
    
            }
    
            T offset; 
            T length; 
        };
    
        // Define the relevant Span types
        typedef Span<Time> TimeSpan;
    
        Music();
    
        ~Music();
   
       bool openFromFile(const std::string& filename);
   
       bool openFromMemory(const void* data, std::size_t sizeInBytes);
   
       bool openFromStream(InputStream& stream);
   
       Time getDuration() const;
   
       TimeSpan getLoopPoints() const;
   
       void setLoopPoints(TimeSpan timePoints);
   
   protected:
   
       virtual bool onGetData(Chunk& data);
   
       virtual void onSeek(Time timeOffset);
   
       virtual Int64 onLoop();
   
   private:
   
       void initialize();
   
       Uint64 timeToSamples(Time position) const;
   
       Time samplesToTime(Uint64 samples) const;
   
       // Member data
       InputSoundFile     m_file;     
       std::vector<Int16> m_samples;  
       Mutex              m_mutex;    
       Span<Uint64>       m_loopSpan; 
   };
   
   } // namespace sf
   
   
   #endif // SFML_MUSIC_HPP

