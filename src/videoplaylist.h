#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

/** A class used to represent a Playlist */

class VideoPlaylist {
  private:
  public:
    std::string playlistName;
    //std::vector<std::string> playlistVideoIdVec;
    std::unordered_map<std::string, std::string> playlistVideoIdMap;

    VideoPlaylist(std::string iVideoPlaylistName);

    std::string GetPlaylistName();
    const VideoPlaylist *getPlaylist(const std::string& playlistTitle) const;

};
